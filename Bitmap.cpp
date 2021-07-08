#include"common.hpp"
#include"Bitmap.hpp"

Bitmap *bitmap;

bool Bitmap::operator[](bid_t pos){
    return (1<<(pos%BIT_PER_CHAR))&(data[pos/BIT_PER_CHAR]);
}

bool Bitmap::at(bid_t pos){
    return (1<<(pos%BIT_PER_CHAR))&(data[pos/BIT_PER_CHAR]);
}

void Bitmap::set(bid_t pos, bool val){
    int c = pos/BIT_PER_CHAR;
    int b = pos%BIT_PER_CHAR;
    data[c] = (~(1<<b)&data[c])|(char(val)<<b);
}

void Bitmap::swt(bid_t pos){
    data[pos/BIT_PER_CHAR] ^= 1<<(pos%BIT_PER_CHAR);
}