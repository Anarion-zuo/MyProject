//
// Created by 左钰 on 2019/12/14.
//

#ifndef MYCPPLIB_FILECHANNEL_H
#define MYCPPLIB_FILECHANNEL_H


#include <containers/List/SString.h>
#include "io/Channel/Channel.h"
#include "FileStatus.h"


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
    SString dir;
    FileStatus status;

    void openFile(int flag);
    size_type measureSize();

    size_type write(char *arr, size_type num) override ;
    size_type read(char *arr, size_type num) override ;

    FileChannel(SString &dir, int flag) : dir(dir) {
        openFile(flag);
    }
    FileChannel(SString &&dir, int flag) : dir(std::forward<SString>(dir)) {
        openFile(flag);
    }

    void callStat(struct stat *buf);

public:
    ~FileChannel() override;
    FileChannel(FileChannel &&rhs) noexcept ;
    FileChannel &operator=(FileChannel &&rhs) noexcept;

    size_type fileSize();

    static FileChannel open(SString &&dir);
    static FileChannel create(SString &&dir);

    void write(Buffer &buffer) override ;
    void read(Buffer &buffer) override ;
    void remove();
    void rename(SString &&newname);

    void updateStatus();
    const FileStatus &getStatus() const ;

};



#endif //MYCPPLIB_FILECHANNEL_H
