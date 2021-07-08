#include"header/common.hpp"
#include"header/Block.hpp"
#include"header/Bitmap.hpp"
#include"header/SuperBlock.hpp"
#include<vector>
#include<cstring>
using namespace std;

extern SuperBlock *sblock;
extern char buffer[TOTAL_SPACE];
extern Bitmap *bitmap;

vector<bid_t> get_free_blocks(int n, Seg seg){
    vector<bid_t> blocks;
    if (n>sblock->free_blocks[seg]){
        return blocks;
    }
    sblock->free_blocks[seg]-=n;
    sblock->used_blocks[seg]+=n;
    for (int i=BOUND[seg][0]; i<BOUND[seg][1]; i++){
        if (bitmap->data[i]!=0xff){
            int pos=i*BIT_PER_CHAR;
            for (int j=0; j<BIT_PER_CHAR; j++){
                if (!bitmap->at(pos+j)){
                    blocks.push_back(pos+j);
                    bitmap->set(pos+j, 1);
                    //bitmap->swt(pos+j);
                    n--;
                    if (n==0) break;
                }
            }
            if (n==0) break;
        }
    }
    return blocks;
}

vector<bid_t> write_blocks(char *p, int size, Seg seg){
    int nblocks=(size+BLOCK_SIZE-1)/BLOCK_SIZE;
    vector<bid_t> blocks = get_free_blocks(nblocks, seg);
    int pos=0;
    for (auto bid: blocks){
        if (pos+BLOCK_SIZE<=size)
            strncpy(buffer+(bid*BLOCK_SIZE), p, BLOCK_SIZE);
        else
            strncpy(buffer+(bid*BLOCK_SIZE), p, size-pos);
        pos+=BLOCK_SIZE;
    }
    return blocks;
}

void erase_block(bid_t bid){
    bitmap->set(bid, 0);
}