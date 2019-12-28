//
// Created by 左钰 on 2019/12/14.
//

#include "Buffer.h"
#include <cstring>
#include <exceptions/containers/IndexOutOfRangeException.h>
#include <containers/List/Vector.hpp>
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

Buffer Buffer::allocate(size_type num) {
    return Buffer(num);
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
    char *p = Allocator::allocate<char>(r - l);
    memcpy(p, l, r - l);
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

void Buffer::put(Vector<char> &vec) {
    put(vec.begin, vec.size());
}

void Buffer::put(Vector<char> &vec, size_type num) {
    if (num > vec.size()) {
        throw IndexOutOfRangeException();
    }
    put(vec.begin, num);
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

void Buffer::get(Vector<char> &vec, size_type num) {
    vec.clear();
    vec.begin = get(num);
    vec.end = vec.begin + num;
    vec.cur = vec.end;
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
    char *newspace = Allocator::allocate<char>(nsize);
    size_type newsize, oldsize = capacity(), curoff = cur - begin, posoff = pos - begin;
    if (nsize < oldsize) {
        newsize = nsize;
    } else {
        newsize = oldsize;
    }
    memcpy(newspace, begin, newsize);
    Allocator::deallocate(begin, oldsize);
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
        if (c == begin[i]) {
            if (len) {
                *len = i;
            }
            return get(i);
        }
    }
    return nullptr;
}
