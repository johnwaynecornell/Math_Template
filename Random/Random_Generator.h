//
// Created by jwc on 9/21/23.
//

#ifndef HASHPRNG_RANDOM_GENERATOR_H
#define HASHPRNG_RANDOM_GENERATOR_H

#include <cstdint>
#include <cstdlib>

typedef unsigned char byte;

class Random_Generator
{
public:

    Random_Generator();
    Random_Generator(uint32_t seed);
    virtual void SetSeed(uint32_t seed);
    virtual uint32_t Getuint32_t() = 0;
    virtual uint64_t Getuint64_t() = 0;
    virtual void Reset() = 0;

    uint32_t ByteRegister;
    int ByesRemain;

    byte GetByte();
};

#endif