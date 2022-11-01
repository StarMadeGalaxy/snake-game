
/* date = October 20th 2022 1:59 am */

#ifndef BASE_TYPES_H
#define BASE_TYPES_H


typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float r32;
typedef double r64;


#define function static
#define internal static
#define global static
#define local static


#define MSB(type) (1 << ((sizeof(type)) * 8) - 1)
#define BIT_AMOUNT(type) (sizeof(type) * 8)


#if defined(__cplusplus) && defined(_BITSET_)
# define BITSET_MSB(type) (std::bitset<(BIT_AMOUNT(type))>(MSB(type)))
#endif /* defined(__cplusplus) && defined(_BITSET_) */


#endif //BASE_TYPES_H
