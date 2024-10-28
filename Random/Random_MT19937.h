//
// Created by jwc on 9/21/23.
//

#ifndef HASHPRNG_RANDOM_MT19937_H
#define HASHPRNG_RANDOM_MT19937_H

#include "Random_Generator.h"

class Random_MT19937 : public Random_Generator
{
private:
    const int N = 624;
    const int M = 397;
    const uint32_t MATRIX_A = 0x9908b0dfU;
    const uint32_t UPPER_MASK = 0x80000000U;
    const uint32_t LOWER_MASK = 0x7fffffffU;

    uint32_t *mt;
    uint32_t *mt2;
    int mti = N + 1;
public:

    Random_MT19937();
    explicit Random_MT19937(uint32_t seed);
    ~Random_MT19937();
    void SetSeed(uint32_t seed) override;
    virtual void Reset();
    uint32_t Getuint32_t() override;
    uint64_t Getuint64_t() override;
};

#endif //HASHPRNG_RANDOM_MT19937_H
