//
// Created by anarion on 2019/11/2.
//

#ifndef MYWEBSERVER_TEXTAPP_H
#define MYWEBSERVER_TEXTAPP_H

#include "App.h"

class TextApp : public App {
protected:
    void onGet(Request &request, Response &response) override ;
public:
    explicit TextApp(std::list<std::string> patterns) : App(std::move(patterns)) {}
};


#endif //MYWEBSERVER_TEXTAPP_H
