#include"common.hpp"

struct SuperBlock
{
    int unum;               //用户数量
    int inum;               //文件数量
    int free_blocks[4];     //空闲块数
    int used_blocks[4];     //已用块数
};
