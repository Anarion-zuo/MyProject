//
// Created by 左钰 on 2019/12/14.
//

#include "FileChannel.h"
#include <unistd.h>
#include <exceptions/io/File/ReadFailedException.h>
#include <exceptions/io/File/WriteFailedException.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <exceptions/io/File/FileStatException.h>
#include <exceptions/io/File/OpenFileException.h>
#include <exceptions/io/File/FileRemoveException.h>
#include <exceptions/io/File/CloseFileException.h>
#include <exceptions/io/File/FileRenameException.h>

void FileChannel::openFile(int flag) {
    const char *dstr = dir.c_str();
    fd = ::open(dstr, flag, 0666);
    if (fd == -1) {
        throw OpenFileException();
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

void FileChannel::write(Buffer &buffer) {
    size_type bufSize = buffer.capacity(), ret;
    char *buf = buffer.getArr();
    write(buf, bufSize);
}

void FileChannel::read(Buffer &buffer) {
    size_type bufSize = buffer.writtenSize(), ret;
    char *buf = buffer.getArr();
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

FileChannel::FileChannel(FileChannel &&rhs) noexcept : fd(rhs.fd), dir(std::move(rhs.dir)), status(rhs.status) {
    rhs.fd = 0;
}

FileChannel FileChannel::open(SString &&dir) {
    return FileChannel(std::forward<SString>(dir), O_RDWR);
}

void FileChannel::callStat(struct stat *buf) {
    int ret;
    ret = ::fstat(fd, buf);
    if (ret == -1) {
        throw FileStatException();
    }
}

void FileChannel::updateStatus() {
    callStat(&status.dat);
}

const FileStatus &FileChannel::getStatus() const {
    return status;
}

FileChannel &FileChannel::operator=(FileChannel &&rhs) noexcept {
    fd = rhs.fd;
    dir = std::move(rhs.dir);
    status = rhs.status;
    rhs.fd = -1;
    return *this;
}

void FileChannel::remove() {
    int ret;
    ret = ::close(fd);
    if (ret == -1) {
        throw CloseFileException();
    }
    ret = ::remove(dir.c_str());
    if (ret == -1) {
        throw FileRemoveException();
    }
}

void FileChannel::rename(SString &&newname) {
    int ret;
    ret = ::rename(dir.c_str(), newname.c_str());
    if (ret == -1) {
        throw FileRenameException();
    }
    dir = std::forward<SString>(newname);
}

FileChannel FileChannel::create(SString &&dir) {
    return FileChannel(std::forward<SString>(dir), O_RDWR | O_CREAT | O_EXCL | O_TRUNC);
}
