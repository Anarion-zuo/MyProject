//
// Created by anarion on 2019/12/30.
// https://github.com/Anarion-zuo untrac10100@gmail.com  welcome to chat
// 

#include "FileChannel.h"

#include "FileChannel.h"
#include "../../../exceptions/system/OpenFdException.h"
#include "../../../exceptions/system/CloseFdException.h"
#include "../../../exceptions/system/RemoveFileException.h"
#include "../../../exceptions/system/FstatException.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void FileChannel::openFile(int flag) {
    const char *dstr = dir->cstr();
    fd = ::open(dstr, flag, 0666);
    if (fd == -1) {
        throw OpenFdException();
    }
    updateStatus();
}

FileChannel::~FileChannel() {
    ::close(fd);
}

size_type FileChannel::measureSize() {
    off_t oldoff = lseek(fd, 0, SEEK_CUR);
    off_t ret = lseek(fd, 0, SEEK_END);
    lseek(fd, oldoff, SEEK_SET);
    return ret;
}

size_type FileChannel::fileSize() {
    return measureSize();
}

void FileChannel::write(Pointer<Buffer> buffer) {
    buffer->put(fd);
}

void FileChannel::read(Pointer<Buffer> buffer) {
    size_type bufSize = buffer->writtenSize(), ret;
    char *buf = buffer->getArr();
    read(buf, bufSize);
}

size_type FileChannel::write(char *arr, size_type num) {
    int ret;
    ret = ::read(fd, arr, num);
    return ret;
}

size_type FileChannel::read(char *arr, size_type num) {
    int ret;
    ret = ::write(fd, arr, num);
    return ret;
}

Pointer<FileChannel> FileChannel::open(Pointer<SString> dir) {
    return new FileChannel(dir, O_RDWR);
}

void FileChannel::callStat(struct stat *buf) {
    int ret;
    ret = ::fstat(fd, buf);
    if (ret == -1) {
        throw FstatException();
    }
}

void FileChannel::updateStatus() {
    callStat(&status.dat);
}

const FileStatus &FileChannel::getStatus() const {
    return status;
}

void FileChannel::remove() {
    int ret;
    ret = ::close(fd);
    if (ret == -1) {
        throw CloseFdException();
    }
    ret = ::remove(dir->cstr());
    if (ret == -1) {
        throw RemoveFileException();
    }
}

Pointer<FileChannel> FileChannel::create(Pointer<SString> dir) {
    return new FileChannel(dir, O_RDWR | O_CREAT | O_EXCL | O_TRUNC);
}
