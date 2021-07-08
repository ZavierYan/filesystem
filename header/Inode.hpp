#pragma once

#include"common.hpp"
#include"Block.hpp"
#include"Bitmap.hpp"

typedef unsigned int fid_t;

int const FILE_MAX_CHILDREN   =100;

enum itype{
    FILE,
    DIR
};

struct Inode{
    char name[FILENAME_SIZE];       //文件名称
    int size;                       //文件大小
    itype type;                     //文件类型
    fid_t parent;                   //上一级目录
    union{
        bid_t bid;                  //文件所占用块
        fid_t fid;                  //目录下子文件
    }children[FILE_MAX_CHILDREN];
    //赋值
    void set(
        char name[FILENAME_SIZE],
        int size,
        itype type,
        int parent
    );
};

//TODO
bid_t get_bid(fid_t fid);

//TODO
Inode *inode_pointer(fid_t fid);

//添加inode文件
void add_inode(char *name, itype type, fid_t parent);

//移除inode文件
void remove_inode(fid_t fid);

//读取文件
void read_file(fid_t fid, char *&des);

//写入文件
void write_file(fid_t fid, char *src, int size);