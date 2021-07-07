#include"common.hpp"

struct Block
{
    int bid;
    int pre;
    int next;
    int inode;
    char data[BLOCK_SIZE-sizeof(int)*3];
    //将块插入链表头部
    //void insert(int &list);
};

//void split(int bid);
//void join(Block &block, int &list);

void input_blocks();
//将块插入链表头部
void insert(int bid, int &list);
//从链表中取出一个块
int get(int &list);
//释放一个链表中的块
void free(int &list);
