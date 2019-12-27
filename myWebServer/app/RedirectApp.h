//
// Created by anarion on 2019/11/5.
//

#ifndef MYWEBSERVER_REDIRECTAPP_H
#define MYWEBSERVER_REDIRECTAPP_H


#include "App.h"

class RedirectApp : public App {
private:
    std::string location;
public:
    explicit RedirectApp(std::string location, std::list<std::string> patterns) : App(std::move(patterns)), location(std::move(location)) {}
    void onGet(Request &request, Response &response) override ;
};


#endif //MYWEBSERVER_REDIRECTAPP_H
