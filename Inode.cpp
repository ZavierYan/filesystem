#include"header/common.hpp"
#include"header/Inode.hpp"
#include"header/SuperBlock.hpp"
#include"header/Block.hpp"
#include<vector>
#include<cstring>
//#include<cstring>
using namespace std;

extern SuperBlock *sblock;
extern char buffer[TOTAL_SPACE];
vector<Inode*> inodes;

void Inode::set(
    char name_[FILENAME_SIZE],
    int size_,
    itype type_,
    int parent_
){
    strncpy(name, name_, FILENAME_SIZE);
    size = size;
    type = type_;
    parent = parent_;
}

/* void input_inodes(){
    inodes.reserve(sblock->inum);
    char *p = buffer+INODETABLE_BEGIN;
    for (int i=0; i<sblock->inum; i++){
        inodes.push_back((Inode*)p);
        p+=sizeof(Inode);
    }
} */
bid_t get_bid(fid_t fid){
    return bid_t(fid+BLOCKS[SUPERBLOCK]+BLOCKS[BITMAP]);
}

Inode *inode_pointer(fid_t fid){
    return (Inode*)(buffer+BLOCK_SIZE*(fid+BLOCKS[SUPERBLOCK]+BLOCKS[BITMAP]));
}

void add_inode(char *name, itype type, fid_t parent){
    vector<bid_t> blocks = get_free_blocks(1, INODETABLE);
    bid_t bid = blocks[0];
    Inode *p = (Inode*)inode_pointer(bid);
    p->set(name, 0, type, parent);
}

void remove_inode(fid_t fid){
    Inode *p = inode_pointer(fid);
    if (p->type == DIR){
        for (int i=0; i<FILE_MAX_CHILDREN; i++){
            if (p->children[i].fid == -1) break;
            remove_inode(p->children[i].fid);
        }
    }
    else{
        for (int i=0; i<FILE_MAX_CHILDREN; i++){
            if (p->children[i].bid == -1) break;
            erase_block(p->children[i].bid);
        }
    }
}

void read_file(fid_t fid, char *&des){
    Inode *p = inode_pointer(fid);
    if (p->type == DIR) return;
    Block *bp;
    des = new char[p->size];
    char *cp = des;
    for (int i=0; i<FILE_MAX_CHILDREN; i++){
        if (p->children[i].bid == -1) break;
        bp = block_pointer(p->children[i].bid);
        strncpy(cp, (char*)bp, BLOCK_SIZE);
        cp+=BLOCK_SIZE;
    }
}

void write_file(fid_t fid, char *src, int size){
    Inode *p = inode_pointer(fid);
    if (p->type == DIR) return;
    int needed_blocks = (size+BLOCK_SIZE-1)/BLOCK_SIZE;
    int cnt;
    for (cnt=0; cnt<FILENAME_SIZE; cnt++){
        if (p->children[cnt].bid==-1)break;
    }
    while (cnt>needed_blocks){
        cnt--;
        erase_block(p->children[cnt].bid);
        p->children[cnt].bid=-1;
    }
    if (cnt<needed_blocks){
        vector<bid_t> blocks = get_free_blocks(needed_blocks-cnt, DATA);
        for (auto bid: blocks){
            p->children[cnt++].bid = bid;
        }
    }
    char *cp=src;
    for (int i=0; i<cnt-1; i++){
        write_block(p->children[i].bid, cp, BLOCK_SIZE);
        cp+=BLOCK_SIZE;
    }
    write_block(p->children[cnt-1].bid, cp, src+size-cp);
}