//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#ifndef REFERENCELIB_FILECHANNEL_H
#define REFERENCELIB_FILECHANNEL_H

#include "../../../container/SString.h"
#include "../Channel.h"
#include "FileStatus.h"
#include "../../../base/Pointer.hpp"


#define ReadOnlyFlag O_RDONLY
#define WriteOnlyFlag O_WRONLY
#define ReadWriteFlag O_RDWR
#define ExecuteOnlyFlag O_EXEC
#define APPENDFlag O_APPEND
#define CreateFlag O_CREATE

struct stat;

class FileChannel : public Channel {
protected:
    int fd;
    Pointer<SString> dir;
    FileStatus status;

    void openFile(int flag);
    size_type measureSize();

    size_type write(char *arr, size_type num) override ;
    size_type read(char *arr, size_type num) override ;

    FileChannel(Pointer<SString> dir, int flag) : dir(dir) {
        openFile(flag);
    }

    void callStat(struct stat *buf);

public:
    ~FileChannel() override;

    size_type fileSize();

    static Pointer<FileChannel> open(Pointer<SString> dir);
    static Pointer<FileChannel> create(Pointer<SString> dir);

    void write(Pointer<Buffer> buffer) override ;
    void read(Pointer<Buffer> buffer) override ;
    void remove();

    void updateStatus();
    const FileStatus &getStatus() const ;

};



#endif //REFERENCELIB_FILECHANNEL_H
