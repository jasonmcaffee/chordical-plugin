#pragma once
#include <JuceHeader.h>

const String baseUrl = "http://127.0.0.1:3001/#test";

class WebBrowserWithMessaging  : public WebBrowserComponent {
public:
    WebBrowserWithMessaging()
    : WebBrowserComponent()
    {
        goToURL(baseUrl);
    }
    bool pageAboutToLoad(const String &newURL) override{
        if(newURL.contains("projucer://")){
            std::cout << "message from app: " << newURL << std::endl;
            sendMessageToWebApp("messagefromhost");
            return false;
        }
        if(newURL.contains("messageToWebApp")){
            std::cout << "message to app: " << newURL << std::endl;
            return true;
        }
        return true;
    }

    void sendMessageToWebApp(const String &message){
//        String urlWithMessageParam = baseUrl + "/#messageToWebApp=" + message;
        String urlWithMessageParam = "javascript:location.hash=\"" + message + "\";";
        goToURL(urlWithMessageParam);
    }
};