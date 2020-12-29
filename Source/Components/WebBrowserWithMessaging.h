#pragma once
#include <JuceHeader.h>
#include "../Services/EventBus/EventBus.h"
#include "../Factories/Message.h"

#include <random>
#include <sstream>
//serialize to char* array (not json) https://stackoverflow.com/questions/16543519/serialization-of-struct


const String separator = File::getCurrentWorkingDirectory().getFullPathName() == "/" ? "" : "/";
const String filePathBase = "/Users/Shared/"; //File::getCurrentWorkingDirectory().getFullPathName()
//const String baseUrl = "file://" + filePathBase + "index.html";
const String baseUrl = "http://127.0.0.1:3000/#test";

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
//    MemoryInputStream memInputStream (ChordicalBinaryData::test_html, ChordicalBinaryData::test_htmlSize,false);
    MemoryInputStream memInputStream (ChordicalBinaryData::index_html, ChordicalBinaryData::index_htmlSize,false);
//    File f ("/Users/jason/dev/chordical-plugin/test.html");
    const String filePath =  filePathBase + "index.html";
    File f (filePath);

    if(!f.hasWriteAccess()){
        auto result = AlertWindow::showYesNoCancelBox (
                AlertWindow::InfoIcon,
                "Message",
                "doesnt have write access to: " + filePath,
                "Save and Continue");
    }

    f.deleteFile();
    f.create();
    std::cout << "current working dir" << File::getCurrentWorkingDirectory().getFullPathName() << std::endl;

    FileOutputStream stream(f);
    stream.writeFromInputStream(memInputStream, memInputStream.getTotalLength());
    stream.flush();
}

inline std::string get_uuid() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

class WebBrowserWithMessaging  : public WebBrowserComponent {
public:
    bool isWebAppLoaded = false;
    WebBrowserWithMessaging() : WebBrowserComponent(){
        writeHtmlFileFromBinaryDataToDisk();
        goToURL(baseUrl);
        //since components are destroyed when window is minimized, don't use event bus here until you can unregister, otherwise this causes ableton to crash.
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
        auto requestId = get_uuid();
//        String urlWithMessageParam = "javascript:location.hash='message=" + message + "';";
        String urlWithMessageParam = "javascript:location.hash='requestId=" + requestId + "&message=" + message.toStdString() + "';";
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
            if(type == "webAppLoaded"){
                isWebAppLoaded = true;
                EventBus::eventBus().emitMessage(WebAppLoadedMessage{"tacooooo"});
                sendMessageToWebApp(convertTestMessageToJSONString(TestMessage{"received web app loaded"}));
            }else if(type == "requestToPlayMidiNotesMessage"){
                auto message = convertJSONStringToRequestToPlayMidiNotesMessage(parsedJson);
                EventBus::eventBus().emitMessage(message);


            }else if(type == "requestToStopMidiNotesMessage"){
                auto message = convertJSONStringToRequestToStopMidiNotesMessage(parsedJson);
                EventBus::eventBus().emitMessage(message);
            }

        }else{
            std::cout << "cant parse json" << std::endl;
        }
    }

};


