//
// Created by anarion on 2019/11/2.
//

#include "TextApp.h"
#include <fcntl.h>

void TextApp::onGet(Request &request, Response &response) {
    const std::string &dir = request.getDir();
    std::stringstream buffer;
    std::string targetDir = WebInfoDir + dir;
    int fd = ::open(targetDir.c_str(), O_RDONLY);
    if (fd < 0) {
        // TODO assets not found
    }
    response.setFFd(fd);
    // make response
    // type
    size_t index = dir.rfind('.') + 1;
    std::string typeStr = dir.substr(index);
    if (typeStr == "js") {
        typeStr = "javascript";
    }
    std::string contentType = "text/" + typeStr;
    response.addHeaderContentType(std::move(contentType));
    response.addHeaderAcceptRanges();
}
