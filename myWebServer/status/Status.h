//
// Created by anarion on 2019/10/6.
//

#ifndef CPPWHEELS_HTTPSTATUS_H
#define CPPWHEELS_HTTPSTATUS_H

#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

class Status {// http 1.1
protected:
    int code;
    std::unordered_map<int, std::string>::iterator iter;
    static std::unordered_map<int, std::string> httpStatusCodeMap;
public:
    Status() = default;
    explicit Status(int code);
    Status(const Status &that) = default;
    Status(Status &&that) = default;
    Status &operator=(Status &&that) = default;

    int getCode() const;
    void setCode(int code);
    const std::string &getDescription() const ;

    std::string serialize();
};


#endif //CPPWHEELS_HTTPSTATUS_H
