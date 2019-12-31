//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_FILESTATUS_H
#define REFERENCELIB_FILESTATUS_H

#include <sys/stat.h>

class FileStatus {
    friend class FileChannel;
protected:
    struct stat dat;
public:
    // file type
    bool isRegular() const ;
    bool isDirectory() const ;
    bool isBlock() const ;
    bool isCharacter() const ;
    bool isFifo() const ;
    bool isSocket() const ;
    bool isSymbolicLink() const ;

    // size
    off_t fileSize();
    blksize_t blockSize();
    blkcnt_t blockCount();

    // time
    double lastModifiedTime();
    double lastAccessTime();
    double lastStatusChangedTime();

    // user
    uid_t userId();
    gid_t groupId();
};


#endif //REFERENCELIB_FILESTATUS_H
