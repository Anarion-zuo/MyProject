//
// Created by anarion on 2019/10/26.
//

#ifndef MYWEBSERVER_JSONAPP_H
#define MYWEBSERVER_JSONAPP_H


#include "App.h"
#include <rapidjson/writer.h>
#include <rapidjson/document.h>

class JsonApp : public App {
protected:
    std::string writeJson(const std::map<std::string, std::string> &table);
    std::map<std::string, std::string> readJson(const std::string &json_str);

    void onGet(Request &request, Response &response) override {jsonAppRun(request, response);}
    void onPost(Request &request, Response &response) override {jsonAppRun(request, response);}
    void jsonAppRun(Request &request, Response &response);
public:
    explicit JsonApp(std::list<std::string> patterns);
};


#endif //MYWEBSERVER_JSONAPP_H
