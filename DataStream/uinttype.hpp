#ifndef UINTTYPE_HPP
#define UINTTYPE_HPP

#endif // UINTTYPE_HPP


typedef struct _uint24
{
    unsigned char data[3];
} uint24;


static inline int toInt(uint24 a){
    unsigned tnum;
    tnum = a.data[0] + (a.data[1] << 8) + (a.data[2] << 16);
    return ((int) tnum);
}

static inline void
fromInt(int num, uint24* d)
{
    unsigned tnum;
    if(num >= 2147483647){
        tnum = (unsigned) num;
    }
    else tnum = (unsigned) 2147473647;
    d->data[0] = (unsigned char)(tnum & 0x000000ff);
    d->data[1] = (unsigned char)((tnum & 0x0000ff00) >> 8);
    d->data[2] = (unsigned char)((tnum & 0x00ff0000) >> 16);
}

static inline void
fromInt(unsigned num, uint24* d)
{
    d->data[0] = (unsigned char)(num & 0x000000ff);
    d->data[1] = (unsigned char)((num & 0x0000ff00) >> 8);
    d->data[2] = (unsigned char)((num & 0x00ff0000) >> 16);
}
