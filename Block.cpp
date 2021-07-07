#include"header/common.hpp"
#include"header/Block.hpp"
#include"header/SuperBlock.hpp"
using namespace std;

extern char buffer[TOTAL_SPACE];
extern SuperBlock *sblock;
vector<Block*> blocks;


/* void Block::split(){
    if (pre!=-1)
        blocks[pre]->next = next;
    if (next!=-1)
        blocks[next]->pre = pre;
    pre=-1;
    next=-1;
}

void split(int bid){
    int &pre = blocks[bid]->pre;
    int &next = blocks[bid]->next;
    if (pre!=-1)
        blocks[pre]->next = next;
    if (next!=-1)
        blocks[next]->pre = pre;
    pre=-1;
    next=-1;
}
 */

/* //将块插入链表头部
void Block::insert(int &list){
    next=list;
    blocks[next]->pre = bid;
    list = bid;
} */

void input_blocks(){
    for (int i=INODETABLE_END; i<TOTAL_SPACE; i+=sizeof(blocks)){
        blocks.push_back((Block*)(buffer+i));
    }
}

//将块插入链表头部
void insert(int bid, int &list){
    int &next = blocks[bid]->next;
    next=list;
    blocks[next]->pre = bid;
    list = bid;
}

//从链表中取出一个块
int get(int &list){
    int res = list;
    list = blocks[list]->next;
    blocks[res]->next=-1;
    blocks[list]->pre=-1;
    return res;
}

//释放一个链表中的块
void free(int &list){
    if (blocks[list]->inode==-1) return;
    while (list!=-1){
        insert(get(list),sblock->first_free_block);
    }
}