//
// Created by anarion on 2019/12/17.
//

#include "FileStatus.h"

bool FileStatus::isRegular() const {
    return S_ISREG(dat.st_mode);
}

bool FileStatus::isDirectory() const {
    return S_ISDIR(dat.st_mode);
}

bool FileStatus::isBlock() const {
    return S_ISCHR(dat.st_mode);
}

bool FileStatus::isCharacter() const {
    return S_ISCHR(dat.st_mode);
}

bool FileStatus::isFifo() const {
    return S_ISFIFO(dat.st_mode);
}

bool FileStatus::isSocket() const {
    return S_ISSOCK(dat.st_mode);
}

bool FileStatus::isSymbolicLink() const {
    return S_ISLNK(dat.st_mode);
}

off_t FileStatus::fileSize() {
    return dat.st_size;
}

double FileStatus::lastModifiedTime() {
    auto &times = dat.st_mtim;
    return times.tv_nsec * 1e-9 + times.tv_sec;
}

double FileStatus::lastAccessTime() {
    auto &times = dat.st_atim;
    return times.tv_nsec * 1e-9 + times.tv_sec;
}

double FileStatus::lastStatusChangedTime() {
    auto &times = dat.st_ctim;
    return times.tv_nsec * 1e-9 + times.tv_sec;
}

blksize_t FileStatus::blockSize() {
    return dat.st_blksize;
}

blkcnt_t FileStatus::blockCount() {
    return dat.st_blocks;
}

uid_t FileStatus::userId() {
    return dat.st_uid;
}

gid_t FileStatus::groupId() {
    return dat.st_gid;
}
