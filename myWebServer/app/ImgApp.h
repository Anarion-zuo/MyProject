//
// Created by anarion on 2019/10/26.
//

#ifndef MYWEBSERVER_IMGAPP_H
#define MYWEBSERVER_IMGAPP_H

#include "App.h"

class ImgApp : public App {
protected:
    void onGet(Request &request, Response &response) override ;
public:
    explicit ImgApp(std::list<std::string> patterns) : App(std::move(patterns)) {}
};


#endif //MYWEBSERVER_IMGAPP_H
