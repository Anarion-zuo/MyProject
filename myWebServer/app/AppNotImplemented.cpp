//
// Created by anarion on 2019/10/29.
//

#include "AppNotImplemented.h"

AppNotImplemented *AppNotImplemented::instance = new AppNotImplemented();

void AppNotImplemented::onBoth(Request &request, Response &response) {
    response.addHeaderLength(0);
    response.setCode(501);
}
