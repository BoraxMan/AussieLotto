 /* 
 * ****** IMPORTANT!!!!!!
 * 
 * A function or two has been removed from this source to make it 64 bit compatible.
 * 
 * For complete source, visit web page in header file.
 * 
 */
#include <sys/types.h>

#include "MersenneTwister.h"

#ifndef BYTE_ORDER
#undef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#undef BIG_ENDIAN
#define BIG_ENDIAN 4321
#if defined(_LITTLE_ENDIAN) || (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && (__BYTE_ORDER == __LITTLE_ENDIAN))
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(_BIG_ENDIAN) || (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && (__BYTE_ORDER == __BIG_ENDIAN))
#define BYTE_ORDER BIG_ENDIAN
#elif defined(WIN32)
#define BYTE_ORDER LITTLE_ENDIAN
#else
#error "Cannot determine byte order!"
#endif
#endif // !BYTE_ORDER

void
MersenneTwister::init_genrand(uint32_t seed) {
	// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
	// In the previous versions, MSBs of the seed affect
	// only MSBs of the array mt[].
	// 2002/01/09 modified by Makoto Matsumoto
	mt[0]= seed;
	for (mti = 1; mti < N; mti++)
		mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
}

void
MersenneTwister::init_by_array(uint32_t init_key[], int key_length) {
	int i, j, k;
	init_genrand(19650218UL);
	i = 1; j = 0;
	k = (N > key_length ? N : key_length);
	for (; k; k--) {
		mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
		  + init_key[j] + j; // non linear
		i++; j++;
		if (i >= N) { mt[0] = mt[N-1]; i = 1; }
		if (j >= key_length) j = 0;
	}
	for (k = N-1; k; k--) {
		mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
		  - i; // non linear
		i++;
		if (i >= N) { mt[0] = mt[N-1]; i=1; }
	}

	mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

