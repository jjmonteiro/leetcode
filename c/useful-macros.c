
// macro to swap two variables using XOR operation
#define XOR_SWAP(a, b) do { (a) ^= (b); (b) ^= (a); (a) ^= (b); } while (0)

// macro to check if a number is even
#define IS_EVEN(x) ((x) % 2 == 0)
#define IS_EVEN(x) (~x & 1)

// macro to calculate average
#define AVERAGE(val1, val2) (((double)(val1) + (val2))/2.0)

// macro to calculate percentage
#define PERCENT(val, per) ((val)*(per)/100.0)

// macro to check value in range
#define IN_RANGE(x, lo, hi) (((x > lo) && (x < hi)) || (x == lo) || (x == hi))

// macro to get the element byte offset within a struct
#define OFFSET_OF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

// macro to get the size of an array
#define SIZE(x) (sizeof(x)/sizeof(x[0]))

// macro to set a bit in a variable
#define BIT_SET(value, bit) ((value) |=  (1L << (bit)))

// macro to clear a bit in a variable
#define BIT_CLR(value, bit) ((value) &= ~(1L << (bit)))

// macro to toggle a bit in a variable
#define BIT_FLIP(value, bit) ((value) ^= 1<<(bit)))

// macro to check a bit state in a variable
#define BIT_CHK(bit,reg)  ((reg >> (bit)) & 1)

// macro to get the LSB of a variable
#define BIT_LSB(reg) ((reg)&1)

// macro to get the MSB of a variable
#define BIT_MSB(reg) ((reg) & (1ULL << ((sizeof(reg) * 8) - 1)))