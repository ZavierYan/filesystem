#pragma once

#include"common.hpp"
#include"Block.hpp"
#include"Bitmap.hpp"

typedef unsigned int fid_t;

int const FILE_MAX_BLOCKS   =100;

enum itype{
    FILE,
    DIR
};

struct Inode{
    char name[FILENAME_SIZE];       //文件名称
    int size;                       //文件大小
    itype type;                     //文件类型
    fid_t parent;                   //上一级目录
    bid_t blocks[FILE_MAX_BLOCKS];  //文件所占用块，或目录子文件
    void set(
        char name[FILENAME_SIZE],
        int size,
        bool is_dir,
        int parent,
        int first,
        int next
    );
};

//添加inode文件
void add_inode(char *name);

//移除inode文件
void remove_inode(fid_t fid);

//读取文件
void read_file(fid_t fid, char *p);

//写入文件
void write_file(fid_t fid, char *p, int size);