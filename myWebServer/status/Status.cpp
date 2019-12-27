//
// Created by anarion on 2019/10/6.
//

#include "Status.h"
#include <sys/socket.h>

std::unordered_map<int, std::string> Status::httpStatusCodeMap({
     {100, "Continue"},
     {101, "Switching Protocols"},
     {200, "OK"},
     {201, "Created"},
     {202, "Accepted"},
     {203, "Non-Authoritative Information"},
     {204, "No Content"},
     {205, "Reset Content"},
     {206, "Partial Content"},
     {300, "Multiple Choices"},
     {301, "Moved Permanently"},
     {302, "Found"},
     {303, "See Other"},
     {304, "Not Modified"},
     {305, "Use Proxy"},
     {306, "Unused"},
     {307, "Temporary Redirect"},
     {400, "Bad Request"},
     {401, "Unauthorized"},
     {402, "Payment Required"},
     {403, "Forbidden"},
     {404, "Not Found"},
     {405, "Method Not Allowed"},
     {406, "Not Acceptable"},
     {407, "Proxy Authentication Required"},
     {408, "Request Time-out"},
     {409, "Conflict"},
     {410, "Gone"},
     {411, "Length Required"},
     {412, "Precondition Failed"},
     {413, "Request Entity Too Large"},
     {414, "Request-URI Too Large"},
     {415, "Unsupported Media Type"},
     {416, "Requested range not satisfiable"},
     {417, "Expectation Failed"},
     {500, "Internal Server Error"},
     {501, "Not Implemented"},
     {502, "Bad Gateway"},
     {503, "Service Unavailable"},
     {504, "Gateway Time-out"},
     {505, "HTTP Version not supported"},
});

Status::Status(int code) : code(code) {
    auto it = httpStatusCodeMap.find(code);
    if (it == httpStatusCodeMap.end()) {
        // TODO code not found case
    }
    iter = it;
}

void Status::setCode(int code) {
    Status::code = code;
    auto it = httpStatusCodeMap.find(code);
    if (it == httpStatusCodeMap.end()) {
        // TODO code not found case
    }
    iter = it;
}

int Status::getCode() const {
    return code;
}

const std::string &Status::getDescription() const {
    return iter->second;
}

std::string Status::serialize() {
    return std::string("HTTP/1.1 ") + std::to_string(code) + std::string(" ") + getDescription() + std::string("\r\n");
}

