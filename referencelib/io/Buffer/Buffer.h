//
// Created by 左钰 on 2019/12/14.
//

#ifndef MYCPPLIB_BUFFER_H
#define MYCPPLIB_BUFFER_H

#include "../../base/Pointer.hpp"

/*
 * Only for sequential readings and writings
 * No interface for direct indexes
 * Once defined, the inner array does not change
 */



template <typename Obj> class Vector;

class Buffer : public Object {
    friend class FileChannel;
protected:
    char *begin, *cur, *end, *pos, *markPtr = nullptr;

    void clearAfterMove();
    char *duplicateRange(char *lower, char *upper);
    char *duplicateRange(size_type lower, size_type upper);

public:
    Buffer() : begin(nullptr), cur(nullptr), end(nullptr), pos(nullptr) {}

    explicit Buffer(size_type num) : begin(new char[num]) {
        end = begin + num;
        clearContent();
    }
    ~Buffer() {
        delete []begin;
    }
    Buffer(Buffer &&rhs) noexcept : begin(rhs.begin), cur(rhs.cur), end(rhs.end), pos(rhs.pos) {
        rhs.clearAfterMove();
    }
    Buffer &operator=(Buffer &&rhs) noexcept {
        clear();
        begin = rhs.begin;
        end = rhs.end;
        cur = begin;
        pos = rhs.pos;
        rhs.clearAfterMove();
        return *this;
    }

    size_type capacity() const ;
    size_type writtenSize() const ;
    size_type unWrittenSize() const ;
    size_type unTouchedSize() const ;
    size_type unReadSize() const ;

    static Pointer<Buffer> allocate(size_type num);
    void clear();
    void clearContent();
    void updateSize(size_type writtenSize);

    void put(char *arr, size_type num);
    void put(char byte);
    void put(Buffer &buffer);
    void put(Buffer &buffer, size_type num);
    void put(Pointer<Buffer> buffer);
    void put(Pointer<Buffer> buffer, size_type num);
    void put(Pointer<SString> str);
    void put(int fd);

    void flip();
    char get();
    char *get(size_type num);
    char *getRest();

    char *getUntil(char c, size_type *len);
    Pointer<Buffer> getUntil(char c);

    void mark();
    void reset();

    char *getArr();

    void print();

    void reallocate(size_type nsize);
};


#endif //MYCPPLIB_BUFFER_H
