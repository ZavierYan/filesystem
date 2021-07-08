#include"header/common.hpp"
#include"header/Inode.hpp"
#include"header/SuperBlock.hpp"
#include<vector>
//#include<cstring>
using namespace std;

extern SuperBlock *sblock;
extern char buffer[TOTAL_SPACE];
vector<Inode*> inodes;

Inode::Inode(Inode &src):
    size(src.size),
    is_dir(src.is_dir),
    parent(src.parent),
    first(src.first),
    next(src.next){
    strncpy(name, src.name, FILENAME_SIZE);
}

Inode::Inode(
    char name_[FILENAME_SIZE],
    int size_,
    bool is_dir_,
    int parent_,
    int first_,
    int next_
):
    size(size_),
    is_dir(is_dir_),
    parent(parent_),
    first(first_),
    next(next_){
    strncpy(name, name_, FILENAME_SIZE);
}

void input_inodes(){
    inodes.reserve(sblock->inum);
    char *p = buffer+INODETABLE_BEGIN;
    for (int i=0; i<sblock->inum; i++){
        inodes.push_back((Inode*)p);
        p+=sizeof(Inode);
    }
}