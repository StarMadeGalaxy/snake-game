
/* date = October 20th 2022 1:59 am */

#if !defined(BASE_TYPES_H)
#define BASE_TYPES_H


using i8 = signed char;
using i16 = signed short int;
using i32 = signed int;
using i64 = signed long long int;

using u8 = unsigned char;
using u16 = unsigned short int;
using u32 = unsigned int;
using u64 = unsigned long long int;

using b8 = signed char;

using f32 = float;
using f64 = double;

#define ENDL '\n'

#if defined(interface)
#   undef interface
#else
#   define interface class
#endif // defined(interface)

#define internal static
#define global static
#define local static

#define MSB(type) (1 << ((sizeof(type) * 8) - 1))
#define BIT_AMOUNT(type) (sizeof(type) * 8)
#define RAND_RANGE(low, high) ((rand() % (high - low + 1)) + low)
#define COORD_INDEX(x, y, width) (y * width + x)
#define INDEX(x) (static_cast<std::size_t>(x))

#define Assert(expression)

#if defined(DEBUG_MODE)
#   define DEBUG_LOG(x) do { std::cout << "DEBUG: " << x << std::endl; } while (0);
#else
#   define DEBUG_LOG(x) do {} while(0);
#endif // defined(DEBUG_MODE)

#if defined(__cplusplus) && defined(_BITSET_)
# define BITSET_MSB(type) (std::bitset<(BIT_AMOUNT(type))>(MSB(type)))
#endif /* defined(__cplusplus) && defined(_BITSET_) */

#endif // !defined(BASE_TYPES_H)
