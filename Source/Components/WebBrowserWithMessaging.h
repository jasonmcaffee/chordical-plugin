#pragma once
#include <JuceHeader.h>
#include "../Services/EventBus/EventBus.h"
#include "../Factories/Message.h"

//serialize to char* array (not json) https://stackoverflow.com/questions/16543519/serialization-of-struct

const String baseUrl = "http://127.0.0.1:3001/#test";
const String messageFromAppIndicator = "projucer://";

inline String urlDecode(std::basic_string<char, std::char_traits<char>, std::allocator<char>> SRC) {
    std::string ret;
    char ch;
    int i, ii;
    for (i=0; i<SRC.length(); i++) {
        if (int(SRC[i])==37) {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}

inline void writeHtmlFileFromBinaryDataToDisk(){
    //https://forum.juce.com/t/example-for-creating-a-file-and-doing-something-with-it/31998/2
    MemoryInputStream memInputStream (ChordicalBinaryData::test_html, ChordicalBinaryData::test_htmlSize,false);
    File f ("/Users/jason/dev/chordical-plugin/test.html");
    f.deleteFile();
    std::cout << "current working dir" << File::getCurrentWorkingDirectory().getFullPathName() << std::endl;
    FileOutputStream stream(f);
    stream.writeFromInputStream(memInputStream, memInputStream.getTotalLength());
    stream.flush();
}

class WebBrowserWithMessaging  : public WebBrowserComponent {
public:
    bool isWebAppLoaded = false;
    WebBrowserWithMessaging() : WebBrowserComponent(){
        writeHtmlFileFromBinaryDataToDisk();
        goToURL(baseUrl);
        //since components are destroyed when window is minimized, don't use event bus here until you can unregister, otherwise this causes ableton to crash.
//        EventBus::eventBus().subscribeToWebAppLoaded([this](WebAppLoadedMessage message) -> void {
//            std::cout << "web browser got web app loaded " << message.data << std::endl;
//            isWebAppLoaded = true;
//
//            juce::String jsonString = convertMidiNotePlayedToJSONString(MidiNotePlayedMessage {MidiNoteData {9, 100}});
//            std::cout << "converted message: " << jsonString << std::endl;
//            this->sendMessageToWebApp(jsonString);
//        });

    }


    bool pageAboutToLoad(const String &newURL) override{
        if(newURL.contains(messageFromAppIndicator)){
            auto messageString = newURL.substring(newURL.indexOf(messageFromAppIndicator) + messageFromAppIndicator.length());
            std::cout << "message from app: " << messageString << std::endl;
            handleMessageFromWebApp(messageString);
            return false;
        }
        return true;
    }


    void sendMessageToWebApp(const String &message){
        if(!isWebAppLoaded) { std::cout << "web app is not loaded so cannot send messages or it will mess up the loading of the app (blank screen due to hash change?) " << std::endl; return; }
//        String urlWithMessageParam = baseUrl + "/#messageToWebApp=" + message;
//        String urlWithMessageParam = "javascript:location.hash=\"" + message + "\";";
        String urlWithMessageParam = "javascript:location.hash='message=" + message + "';";
        std::cout << "sending message: " << urlWithMessageParam << std::endl;
        goToURL(urlWithMessageParam);
    }

    void handleMessageFromWebApp(const String &messageString){
        //https://forum.juce.com/t/parsing-nested-json/21733
        String juceDecodedMessage= urlDecode(messageString.toStdString());
//        std::cout << "decoded message " << juceDecodedMessage << std::endl;

        //parse the json
        juce::var parsedJson;
        if(juce::JSON::parse(juceDecodedMessage, parsedJson).wasOk()){
            String type = parsedJson["type"];
//            std::cout << "message type: " << type << std::endl;
            if(type == "webAppLoaded"){
                isWebAppLoaded = true;
                EventBus::eventBus().emitWebAppLoaded(WebAppLoadedMessage {"hi"});
            }else if(type == "requestToPlayMidiNotesMessage"){
                auto message = convertJSONStringToRequestToPlayMidiNotesMessage(parsedJson);
                EventBus::eventBus().emitRequestToPlayMidiNotes(message);
            }else if(type == "requestToStopMidiNotesMessage"){
                auto message = convertJSONStringToRequestToStopMidiNotesMessage(parsedJson);
                EventBus::eventBus().emitRequestToStopMidiNotes(message);
            }

        }else{
            std::cout << "cant parse json" << std::endl;
        }
    }

};