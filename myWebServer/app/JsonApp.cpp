//
// Created by anarion on 2019/10/26.
//

#include "JsonApp.h"

#include <utility>

JsonApp::JsonApp(std::list<std::string> patterns) : App(std::move(patterns)) {

}

void JsonApp::jsonAppRun(Request &request, Response &response) {

}
