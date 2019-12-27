//
// Created by anarion on 2019/10/23.
//

#ifndef MYWEBSERVER_PAGEAPP_H
#define MYWEBSERVER_PAGEAPP_H


#include "App.h"

class PageApp : public App {
protected:
    void onGet(Request &request, Response &response) override ;
    const std::string pageFile = "/hello.html";
public:
    explicit PageApp(std::list<std::string> patterns) : App(std::move(patterns)) {}
};


#endif //MYWEBSERVER_PAGEAPP_H
