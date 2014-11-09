/* 
 * 
 * ****** IMPORTANT!!!!!!
 * 
 * A function or two has been removed from this source to make it 64 bit compatible.
 * 
 * For complete source, visit web page below.
 * 
 * 
   A C++ program for MT19937, with initialization improved 2002/1/26.
   Originally coded in C by Takuji Nishimura and Makoto Matsumoto.
   C++ version by Zubin Dittia, created 2006/2/5.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

class MersenneTwister;

#ifndef _MERSENNETWISTER_H_
#define _MERSENNETWISTER_H_
#include <stdint.h>


/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

// mag01[x] = x * MATRIX_A  for x=0,1
static uint32_t	mag01[2] = {0x0UL, MATRIX_A};

class MersenneTwister {
	uint32_t	mt[N];
	int			mti;

	void init_genrand(uint32_t seed);
	void init_by_array(uint32_t init_key[], int key_length);
public:
	MersenneTwister() {
		init_genrand(5489UL);	// a default initial seed is used
	}

	// initializes mt[N] with a seed
	MersenneTwister(uint32_t seed) {
		init_genrand(seed);
	}

	// initialize by an array with array-length
	// init_key is the array for initializing keys
	// key_length is its length
	// slight change for C++, 2004/2/26
	MersenneTwister(uint32_t init_key[], int key_length) {
		init_by_array(init_key, key_length);
	}

	// generates a random number on [0,0xffffffff]-interval
	inline uint32_t genrand_uint32() {
		uint32_t y;

		if (mti >= N) { /* generate N words at one time */
			int kk;

			for (kk = 0; kk < N-M; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			for (; kk< N-1; kk++) {
				y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
				mt[kk] = mt[kk + (M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
			}
			y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

			mti = 0;
		}
	  
		y = mt[mti++];

		/* Tempering */
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);

		return y;
	}

	// generates a random number on [0,0x7fffffff]-interval
	inline int32_t genrand_int31() {
		return (int32_t)(genrand_uint32() >> 1);
	}

	// generates a random number on [0,1]-real-interval
	inline double genrand_real1() {
		// divided by 2^32-1
		return genrand_uint32() * (1.0 / 4294967295.0);
	}

	// generates a random number on [0,1]-real-interval
	inline double genrand_real2() {
		// divided by 2^32
		return genrand_uint32() * (1.0 / 4294967296.0);
	}

	// generates a random number on [0,1]-real-interval
	inline double genrand_real3() {
		// divided by 2^32
		return (((double)genrand_uint32()) + 0.5) * (1.0 / 4294967296.0);
	}

	// generates a random number on [0,1) with 53-bit resolution
	inline double genrand_res53() {
		uint32_t a = genrand_uint32() >> 5;
		uint32_t b = genrand_uint32() >> 6;
		return (a *67108864.0 + b) * (1.0 / 9007199254740992.0);
	}

	// These real versions are due to Isaku Wada, 2002/01/09 added

	// fills in a buffer of length buflen with random data
	// added 2005/2/5 by Zubin Dittia

};

extern MersenneTwister mt;
#endif // _MERSENNETWISTER_H_