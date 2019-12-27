//
// Created by anarion on 2019/10/29.
//

#ifndef MYWEBSERVER_APPNOTIMPLEMENTED_H
#define MYWEBSERVER_APPNOTIMPLEMENTED_H


#include "App.h"

class AppNotImplemented : public App {
private:
    static AppNotImplemented *instance;
protected:
    void onBoth(Request &request, Response &response);
    void onGet(Request &request, Response &response) override {onBoth(request, response);}
    void onPost(Request &request, Response &response) override {onBoth(request, response);}

public:
    AppNotImplemented() : App({}) {}
    static AppNotImplemented *getInstance() {return instance;}
};


#endif //MYWEBSERVER_APPNOTIMPLEMENTED_H
