//
// Created by anarion on 2019/10/26.
//

#ifndef MYWEBSERVER_COOKIE_H
#define MYWEBSERVER_COOKIE_H


#include "../request/Request.h"
#include "../response/Response.h"

class Cookie {
protected:
    std::unordered_map<std::string, std::string> kvs;

    void readCookieString(std::stringstream &&input);
    std::string serialize() const ;

public:
    explicit Cookie(Request &request);

    void add(const std::string& key, const std::string& val);
    bool hasKey(const std::string &key) const ;
    const std::string &get(const std::string &key) const ;
    void addToResponse(Response &response) const ;

    // session
    size_t getSessionId() const ;
    void setSessionId(size_t id);
};


#endif //MYWEBSERVER_COOKIE_H
