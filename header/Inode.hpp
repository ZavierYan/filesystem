#include"common.hpp"

struct Inode{
    char name[FILENAME_SIZE];//文件名称
    int size;//文件大小
    bool is_dir;//是否是目录
    int parent;//上一级目录
    int first;//如果是文件，表示第一个块；如果是目录，表示第一个子文件
    int next;//链表下一项
    Inode(Inode&);
    Inode(
        char name[FILENAME_SIZE],
        int size,
        bool is_dir,
        int parent,
        int first,
        int next
    );
    void set(
        char name[FILENAME_SIZE],
        int size,
        bool is_dir,
        int parent,
        int first,
        int next
    );
};

void input_inodes();