#ifndef STD_BIT_H_INC
#define STD_BIT_H_INC

#define BM(bn)          ( (1UL) <<  (bn) )                              // Convert bit number to bit mask
#define SET(reg,bm)     ( (reg) |=  (bm) )                              // All bits in bit mask are set
#define CLR(reg,bm)     ( (reg) &= ~(bm) )                              // All bits in bit mask are cleared
#define TGL(reg,bm)     ( (reg) ^=  (bm) )                              // All bits in bit mask are toggle
#define PUT(reg,bm,val) ( (reg) = ( (reg) & (~(bm)) ) | ((bm)&(val)) )  // All bits in bit mask are replaced by value
#define ALL_SET(reg,bm) ( ( (reg) & (bm) ) == (bm) )                    // Check if all bits in bit mask are set
#define ALL_CLR(reg,bm) ( ( (reg) & (bm) ) ==  0   )                    // Check if all bits in bit mask are cleared
#define ANY_SET(reg,bm) ( ( (reg) & (bm) ) >   0   )                    // Check if any bits in bit mask are set
#define ANY_CLR(reg,bm) ( ( (reg) & (bm) ) != (bm) )                    // Check if any bits in bit mask are cleared

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef signed short        s16;
typedef signed long         s32;
typedef signed long long    s64;
typedef float               f32;
typedef double              f64;
typedef long double         f128;

#endif // STD_BIT_H_INC
