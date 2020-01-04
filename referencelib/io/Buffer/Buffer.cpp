//
// Created by 左钰 on 2019/12/14.
//

#include "Buffer.h"
#include "../../base/Pointer.hpp"
#include "../../container/SString.h"
#include "../../exceptions/container/IndexOutOfRangeException.h"
#include "../../exceptions/system/ReadFdException.h"
#include <cstring>
#include <unistd.h>

void Buffer::clearAfterMove() {
    begin = nullptr;
    end = nullptr;
    cur = nullptr;
    pos = nullptr;
}

void Buffer::clear() {
    cur = begin;
    pos = begin;
}

size_type Buffer::capacity() const {
    return end - begin;
}

Pointer<Buffer> Buffer::allocate(size_type num) {
    return new Buffer(num);
}

void Buffer::clearContent() {
    memset(begin, 0, capacity());
    clear();
}

char *Buffer::duplicateRange(char *l, char *r) {
    if (r > end) {
        throw IndexOutOfRangeException();
    }
    if (l == r) {
        return nullptr;
    }
    char *p = new char[r - l + 1];
    memcpy(p, l, r - l + 1);
    p[r - l] = 0;
    return p;
}

char *Buffer::duplicateRange(size_type lower, size_type upper) {
    char *l = begin + lower, *r = begin + upper;
    return duplicateRange(l, r);
}

size_type Buffer::writtenSize() const {
    return cur - begin;
}

void Buffer::put(char *arr, size_type num) {
    size_type spare = end - pos;
    if (num >= spare) {
        reallocate((capacity() + num) << 1ul);
    }
    memcpy(pos, arr, num);
    pos += num;
    if (pos > cur) {
        cur = pos;
    }
}

void Buffer::put(char byte) {
    put(&byte, 1);
}

void Buffer::put(Buffer &buffer) {
    put(buffer.begin, buffer.writtenSize());
}

void Buffer::put(Buffer &buffer, size_type num) {
    if (num > buffer.writtenSize()) {
        throw IndexOutOfRangeException();
    }
    put(buffer.begin, num);
}

void Buffer::flip() {
    pos = begin;
}

char Buffer::get() {
    char c = *pos;
    ++pos;
    return c;
}

char *Buffer::get(size_type num) {
    char *ret = duplicateRange(pos, pos + num);
    pos += num;
    return ret;
}

void Buffer::mark() {
    markPtr = pos;
}

void Buffer::reset() {
    if (markPtr) {
        pos = markPtr;
    }
}

char *Buffer::getArr() {
    return begin;
}

void Buffer::reallocate(size_type nsize) {
    char *newspace = new char [nsize];
    size_type newsize, oldsize = capacity(), curoff = cur - begin, posoff = pos - begin;
    if (nsize < oldsize) {
        newsize = nsize;
    } else {
        newsize = oldsize;
    }
    memcpy(newspace, begin, newsize);
    delete[] begin;
    begin = newspace;
    end = newspace + nsize;
    cur = newspace + curoff;
    pos = newspace + posoff;
}

void Buffer::print() {
    ::write(STDOUT_FILENO, begin, writtenSize());
}

void Buffer::updateSize(size_type writtenSize) {
    pos += writtenSize;
    if (pos > cur) {
        cur += writtenSize - (pos - cur);
    }
}

void Buffer::put(int fd) {
    int len;
    while(true) {
        size_type cap = capacity();
        len = ::read(fd, pos, cap);
        if (len < 0) {
            throw ReadFdException();
        }
        pos += len;
        if (pos > cur) {
            cur = pos;
        }
        if (len == cap) {
            reallocate(cap << 1ul);
        } else {
            break;
        }
    }
}

size_type Buffer::unTouchedSize() const {
    return end - pos;
}

size_type Buffer::unWrittenSize() const {
    return end - cur;
}

char * Buffer::getUntil(char c, size_type *len) {
    for (size_type i = 0; i < writtenSize(); ++i) {
        if (c == pos[i]) {
            if (len) {
                *len = i;
            }
            return get(i);
        }
    }
    if (len) {
        *len = unReadSize();
    }
    return getRest();
}

size_type Buffer::unReadSize() const {
    return cur - pos;
}

Pointer<Buffer> Buffer::getUntil(char c) {
    Pointer<Buffer> p = new Buffer();
    size_type len;
    p->begin = getUntil(c, &len);
    p->cur = len + p->begin;
    p->end = p->cur;
    p->pos = p->begin;
    return p;
}

char *Buffer::getRest() {
    size_type restsize = unReadSize();
    char *p = new char[restsize + 1];
    memcpy(p, pos, restsize);
    p[restsize] = 0;
    pos = cur;
    return p;
}

void Buffer::put(Pointer<Buffer> buffer) {
    put(buffer->begin, buffer->writtenSize());
}

void Buffer::put(Pointer<Buffer> buffer, size_type num) {
    if (num > buffer->writtenSize()) {
        throw IndexOutOfRangeException();
    }
    put(buffer->begin, num);
}

void Buffer::put(Pointer<SString> str) {
    put(str->cstr(), str->length());
}
