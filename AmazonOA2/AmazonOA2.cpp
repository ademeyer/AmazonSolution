// AmazonOA2.cpp : This file contains the 'main' function. Program execution begins and ends there.

//! READ Carefully!!!
/*
* AmazonOA2 Question: 
* Problem Statement: Given a byte array in networkbyte order, write an algorithm to find 
* the starting bit positionof the first occurrence of the 32-bit, big-endian pattern (OxFE6B2840) 
* ﻿in the byte array.The pattern may or may not bebyte aligned 1in the input.The function htonl() ﻿
* and ntohl() ﻿are provided in the C library to convert the endian order from
* Given a byte array in network byte order, write an algorithm to find the starting bit position 
* of the first occurrence of the 32-bit, big-endian pattern (OxFE6B2840) ﻿in thebyte array.
* 
* 
* Example 1 - ﻿Byte Aligned:
* numBytes: 8
* data:     [Ox00,0x01,OxFE,0x6B,0x28,0x40,0x02,0x03]
* Answer:   16-bit
* 
* 
* Example 2 - ﻿Non-byte Aligned:
* ﻿numBytes:    8
* data:        [0x00,0x03,OxFC,0xD6,0x50,0x80,0x04,0x06]
* Answer:      15-bit
* 
* Write int findPattern(const uint32_t numBytes, const uint8_t data[]) to solve this

*/

// Approach: Using Knuth Morris Pratt (KMP) algorithm: more like finding binary Needle in binary Haystack  


#include <cstdint>
#include <iostream>
#define USECHATGPTSOLUTION 0


#if USECHATGPSOLUTION
// Extracts a 32-bit value starting from a specific bit position in a byte array
uint32_t extract32BitFromBitPosition(const uint8_t* data, uint32_t bitStart, uint32_t numBytes) 
{
    uint32_t value = 0;
    int bitCount = 32; // Number of bits we want to extract

    // Read bit by bit
    for (int i = 0; i < bitCount; ++i) 
    {
        // Calculate byte and bit index
        uint32_t byteIndex = (bitStart + i) / 8;
        uint32_t bitIndex = (bitStart + i) % 8;

        if (byteIndex >= numBytes) break; // Prevent reading past the array

        // Get the specific bit and set it in 'value'
        uint32_t bit = (data[byteIndex] >> (7 - bitIndex)) & 0x01;
        value |= (bit << (31 - i));
    }

    return value;
}

int GPTfindPattern(const uint32_t numBytes, const uint8_t data[])
{
    const uint32_t targetPattern = 0xFE6B2840;

    // Total bits in the data array 
    uint32_t totalBits = numBytes * 8;

    // Check each possible starting bit position up to the last possible starting bit for a 32-bit number
    for (uint32_t bitStart = 0; bitStart <= totalBits - 32; ++bitStart)
    {
        uint32_t value = extract32BitFromBitPosition(data, bitStart, numBytes);

        if (value == targetPattern)
        {
            return bitStart;
        }
    }

    return -1; // Return -1 if the pattern is not found
}

#else

unsigned countBits(uint32_t number)
{
    return (int)log2(number) + 1;
}

int alFindPattern(const uint32_t numBytes, const uint8_t data[])
{
    if (numBytes * 8 > 64)
    {
        return -1;
    }
    const uint32_t pattern = 0xFE6B2840;
    // Combine data 
    uint64_t bigData = 0;
    const uint8_t mPos[] = {56, 48, 40, 32, 24, 16, 8, 0};
    int k = 0;
    for (int i = 0; k < numBytes && i < 8; ++i)
    {
        bigData |= uint64_t(data[k++]) << mPos[8 - numBytes + i];
    }

    // Generate 32-bit mask and set only number of pattern bits
    int bitNo = 32 - countBits(pattern);
    if (bitNo < 0) 
            return -1;

    uint64_t mask = (0xFFFFFFFF >> bitNo);

    for (int i = 0; i < 31; i++)
    {
        uint64_t value = (mask << i);
        if (pattern == uint32_t((value & bigData) >> i))
        {
            return (32 - i);
        }
    } 

    return -1;
}

#endif



int main() 
{
    // Example 1 - Byte Aligned
    const uint8_t data1[] = { 0x00, 0x01, 0xFE, 0x6B, 0x28, 0x40, 0x02, 0x03 };
    uint32_t numBytes1 = sizeof(data1) / sizeof(data1[0]);
#if USECHATGPSOLUTION
    std::cout << "Byte Aligned Position: " << findPattern(numBytes1, data1) << "-bit - GPT solution\n";
#else
    std::cout << "Byte Aligned Position: " << alFindPattern(numBytes1, data1) << "-bit - Human solution\n";
#endif
    // Example 2 - Non-byte Aligned
    const uint8_t data2[] = { 0x00, 0x03, 0xFC, 0xD6, 0x50, 0x80, 0x04, 0x06 };
    uint32_t numBytes2 = sizeof(data2) / sizeof(data2[0]);
#if USECHATGPSOLUTION
    std::cout << "Non-byte Aligned Position: " << findPattern(numBytes2, data2) << "-bit - GPT solution\n";
#else
    std::cout << "Non-byte Aligned Position: " << alFindPattern(numBytes2, data2) << "-bit - Human solution\n";
#endif
    return 0;
}
