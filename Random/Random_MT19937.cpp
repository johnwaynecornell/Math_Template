//
// Created by jwc on 9/21/23.
//

#include "Random_MT19937.h"

Random_MT19937::Random_MT19937() : Random_Generator()
{
    mt = new uint32_t[N];
    mt2 = new uint32_t[N];
}

Random_MT19937::Random_MT19937(uint32_t seed) : Random_Generator(seed)
{
    mt = new uint32_t[N];
    mt2 = new uint32_t[N];
}

void Random_MT19937::Reset()
{
    for (int i =0; i <N; i++) mt[i] = mt2[i];
    mti = N + 1;
}

Random_MT19937::~Random_MT19937()
{
    delete mt;
    delete mt2;
}

void Random_MT19937::SetSeed(uint32_t seed)
{
    Random_Generator::SetSeed(seed);

    mt[0] = mt2[0] = seed & 0xffffffffU;
    for (mti = 1; mti < N; mti++)
    {
        mt[mti] = mt2[mti] = (1812433253U * (mt2[mti - 1] ^ (mt2[mti - 1] >> 30)) + (uint32_t)mti);
    }
}

uint64_t Random_MT19937::Getuint64_t()
{
    return (((uint64_t)Getuint32_t())<<32) + ((uint64_t)Getuint32_t());
}

uint32_t Random_MT19937::Getuint32_t()
{
    if (mti >= N)
    {
        int kk;
        for (kk = 0; kk < N - M; kk++)
        {
            uint32_t y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ ((y & 1) * MATRIX_A);
        }

        for (; kk < N - 1; kk++)
        {
            uint32_t y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ ((y & 1) * MATRIX_A);
        }

        uint32_t y2 = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y2 >> 1) ^ ((y2 & 1) * MATRIX_A);

        mti = 0;
    }

    uint32_t y3 = mt[mti++];

    y3 ^= (y3 >> 11);
    y3 ^= (y3 << 7) & 0x9d2c5680U;
    y3 ^= (y3 << 15) & 0xefc60000U;
    y3 ^= (y3 >> 18);

    return y3;
}