//
// Created by anarion on 2019/11/5.
//

#include "RedirectApp.h"

void RedirectApp::onGet(Request &request, Response &response) {
    response.setCode(302);
    response.addHeader("Location", std::move(location));
}
