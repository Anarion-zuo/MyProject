//
// Created by anarion on 2019/10/26.
//

#include "Cookie.h"

Cookie::Cookie(Request &request) {
    auto it = request.headers.find("Cookie");
    if (it == request.headers.end()) {
        return;
    }
    std::stringstream ss {it->second};
    readCookieString(std::move(ss));
}

void Cookie::readCookieString(std::stringstream &&input) {
    while (true) {
        std::string str_buf, key, val;
        getline(input, str_buf, '=');
        if (str_buf.empty()) {
            break;
        }
        key = std::move(str_buf);
        input.get();
        getline(input, str_buf, ';');
        val = std::move(str_buf);
        input.get();
        if (input.get() != ' ') {
            // TODO cookie format error
        }
        kvs[std::move(key)] = std::move(val);
    }
}

void Cookie::add(const std::string& key, const std::string& val) {
    kvs.insert({key, val});
}

const std::string &Cookie::get(const std::string &key) const {
    return kvs.find(key)->second;
}

bool Cookie::hasKey(const std::string &key) const {
    return kvs.find(key) == kvs.end();
}

std::string Cookie::serialize() const {
    std::stringstream buffer;
    for (auto &item : kvs) {
        buffer << item.first;
        buffer << '=';
        buffer << item.second;
        buffer << "; ";
    }
    std::string ret;
    buffer >> ret;
    return std::move(ret);
}

void Cookie::addToResponse(Response &response) const {
    response.addHeader("Set-Cookie", serialize());
}

size_t Cookie::getSessionId() const {
    auto it = kvs.find("sessionid");
    if (it == kvs.end()) {
        return 0;
    }
    std::stringstream ss(it->second);
    size_t ret;
    ss >> ret;
    return ret;
}

void Cookie::setSessionId(size_t id) {
    kvs.insert({"sessionid", std::to_string(id)});
}
