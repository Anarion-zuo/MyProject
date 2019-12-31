//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "ResponseStatus.h"

static Pointer<HashMap<Int, SString>> initializeStatusMap() {
    Pointer<HashMap<Int, SString>> map = new HashMap<Int, SString>;
    map->put(new Int(100), new SString("Continue"));
    map->put(new Int(101), new SString("Switching Protocols"));
    map->put(new Int(200), new SString("OK"));
    map->put(new Int(201), new SString("Created"));
    map->put(new Int(202), new SString("Accepted"));
    map->put(new Int(203), new SString("Non-Authoritative Information"));
    map->put(new Int(204), new SString("No Content"));
    map->put(new Int(205), new SString("Reset Content"));
    map->put(new Int(206), new SString("Partial Content"));
    map->put(new Int(300), new SString("Multiple Choices"));
    map->put(new Int(301), new SString("Moved Permanently"));
    map->put(new Int(302), new SString("Found"));
    map->put(new Int(303), new SString("See Other"));
    map->put(new Int(304), new SString("Not Modified"));
    map->put(new Int(305), new SString("Use Proxy"));
    map->put(new Int(306), new SString("Unused"));
    map->put(new Int(307), new SString("Temporary Redirect"));
    map->put(new Int(400), new SString("Bad Request"));
    map->put(new Int(401), new SString("Unauthorized"));
    map->put(new Int(402), new SString("Payment Required"));
    map->put(new Int(403), new SString("Forbidden"));
    map->put(new Int(404), new SString("Not Found"));
    map->put(new Int(405), new SString("Method Not Allowed"));
    map->put(new Int(406), new SString("Not Acceptable"));
    map->put(new Int(407), new SString("Proxy Authentication Required"));
    map->put(new Int(408), new SString("Request Time-out"));
    map->put(new Int(409), new SString("Conflict"));
    map->put(new Int(410), new SString("Gone"));
    map->put(new Int(411), new SString("Length Required"));
    map->put(new Int(412), new SString("Precondition Failed"));
    map->put(new Int(413), new SString("Request Entity Too Large"));
    map->put(new Int(414), new SString("Request-URI Too Large"));
    map->put(new Int(415), new SString("Unsupported Media Type"));
    map->put(new Int(416), new SString("Requested range not satisfiable"));
    map->put(new Int(417), new SString("Expectation Failed"));
    map->put(new Int(500), new SString("Internal Server Error"));
    map->put(new Int(501), new SString("Not Implemented"));
    map->put(new Int(502), new SString("Bad Gateway"));
    map->put(new Int(503), new SString("Service Unavailable"));
    map->put(new Int(504), new SString("Gateway Time-out"));
    map->put(new Int(505), new SString("HTTP Version not supported"));
    return map;
}

Pointer<HashMap<Int, SString>> ResponseStatus::map = initializeStatusMap();

ResponseStatus::ResponseStatus(int code) : code(new Int(code)) {

}

ResponseStatus::~ResponseStatus() {
    code.release();
}

Pointer<SString> ResponseStatus::getDescription() const {
    return map->get(code);
}

void ResponseStatus::set(int n) {
    code->setVal(n);
}

int ResponseStatus::getCode() {
    return code->getNum();
}
