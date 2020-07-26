#pragma once
#include <JuceHeader.h>
#include "../Services/EventBus/EventBus.h"

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
    WebBrowserWithMessaging()
    : WebBrowserComponent()
    {
        writeHtmlFileFromBinaryDataToDisk();
        goToURL(baseUrl);


//        std::function<void(EventMessage<std::string>)> f = [](EventMessage<std::string> message){
//            std::cout << "web browser received event bus message: " << message.getData() << std::endl;
//        };
//        EventBus::getInstance().subscribe2(f);
        EventBus::getInstance().subscribeToWebAppLoaded([](WebAppLoadedMessage message) -> void {
            std::cout << "web browser received event bus message: " << message.data << std::endl;
        });


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
//        String urlWithMessageParam = baseUrl + "/#messageToWebApp=" + message;
        String urlWithMessageParam = "javascript:location.hash=\"" + message + "\";";
        goToURL(urlWithMessageParam);
    }

    void handleMessageFromWebApp(const String &messageString){
        sendMessageToWebApp(messageString);

        //https://forum.juce.com/t/parsing-nested-json/21733
        String juceDecodedMessage= urlDecode(messageString.toStdString());
        std::cout << "decoded message " << juceDecodedMessage << std::endl;

        //parse the json
        juce::var parsedJson;
        if(juce::JSON::parse(juceDecodedMessage, parsedJson).wasOk()){
            String type = parsedJson["type"];
            std::cout << "message type: " << type << std::endl;
        }else{
            std::cout << "cant parse json" << std::endl;
        }
    }

};