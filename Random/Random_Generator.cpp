//
// Created by jwc on 9/21/23.
//

#include "Random_Generator.h"

Random_Generator::Random_Generator()
{

}

Random_Generator::Random_Generator(uint32_t seed)
{
    SetSeed(seed);
}

void Random_Generator::SetSeed(uint32_t seed)
{
    ByesRemain = 0;
}

byte Random_Generator::GetByte()
{
    if (ByesRemain == 0)
    {
        ByteRegister = Getuint64_t();
        ByesRemain = 4;
    }

    ByesRemain--;
    byte R = (byte)(ByteRegister & 0xFF);
    ByteRegister >>= 8;

    return R;
}