#include"common.hpp"
#include<vector>

typedef unsigned int bid_t;

struct Block
{
    char data[BLOCK_SIZE];
};

enum Seg{
    SUPERBLOCK,
    BITMAP,
    INODETABLE,
    DATA
};
//int const METADATA_SIZE     =4<<10;         //元数据大小
//int const USERTABLE_SIZE    =4000;              //用户表大小
int const TOTAL_BLOCKS      =TOTAL_SPACE/BLOCK_SIZE;

int const BLOCKS[4]{
    1,
    1,
    1,
    TOTAL_BLOCKS-3
};

//int const USERTABLE_BEGIN   =SUPERBLOCK_SIZE;
//int const USERTABLE_END     =USERTABLE_BEGIN+USERTABLE_SIZE;
int const SUPERBLOCK_BEGIN  =0;
int const SUPERBLOCK_END    =SUPERBLOCK_BEGIN+BLOCKS[SUPERBLOCK];
int const BITMAP_BEGIN      =SUPERBLOCK_END;
int const BITMAP_END        =BITMAP_BEGIN+BLOCKS[BITMAP];
int const INODETABLE_BEGIN  =BITMAP_END;
int const INODETABLE_END    =INODETABLE_BEGIN+BLOCKS[INODETABLE];
int const DATA_BEGIN        =INODETABLE_END;
int const DATA_END          =TOTAL_SPACE/BLOCK_SIZE;

int const BOUND[4][2]{
    {SUPERBLOCK_BEGIN, SUPERBLOCK_END},
    {BITMAP_BEGIN,BITMAP_END},
    {INODETABLE_BEGIN, INODETABLE_END},
    {DATA_BEGIN, DATA_END}
};

//在上下界[b,t]内取得n个空闲块
std::vector<bid_t> get_free_blocks(int n, bid_t b, bid_t t);

//写入数据，返回存放块的bid
std::vector<bid_t> write_blocks(char *p, int size, bid_t b, bid_t t);

//清除块的数据
void erase_block(bid_t bid);