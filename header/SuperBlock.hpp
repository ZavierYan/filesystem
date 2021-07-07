#include"common.hpp"

struct SuperBlock
{
    int unum;               //用户数量
    int inum;               //文件数量
    int first_free_block;   //第一个空闲块
};
