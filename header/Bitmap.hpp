#include"common.hpp"
#include"Block.hpp"
#include<vector>

int const BIT_PER_CHAR  =8;

struct Bitmap{
    char data[BITMAP_SIZE];
    bool operator[](bid_t pos);
    bool at(bid_t pos);
    void set(bid_t pos, bool val);
    void swt(bid_t pos);
};
