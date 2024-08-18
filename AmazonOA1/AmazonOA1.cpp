// AmazonOA1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int read_8b(uint8_t* buf, uint8_t* mask)
{
    return 0;
}

int read(uint8_t* buffer, uint32_t n_bytes, uint32_t offset)
{
    /* Use read_8b(uint8_t* buf, uint8_t* mask) to implement this function*/

    if (buffer == NULL || n_bytes <= 0 || offset >= n_bytes || offset < 0) return 0;
    // allocate memeory space enough to hold 8 bytes of data
    // read set of 8 bytes using read_8b
    // if read_8b return 0, we process data else we return break the loop
    // check mask for valid data and process only value data into buffer
    int read_cnt = 0;// i&1 ((a >> 3)  & 0x01)
    uint8_t* buf = new uint8_t[8];
    int amt = n_bytes, off = offset;
    while (true)
    {
        uint8_t mask = 0;
        int ret = read_8b(buf, &mask);
        if (ret == 1) break;

        //get amount of valid data        
        for (int i = 0; i < 8; i++)
        {
            if (off > 0) //skip byte
            {
                off--;
                continue;
            }

            if (!((mask >> i) & 0x01))
            {
                buffer[read_cnt++] = buf[i];
                amt--;
                if (amt == 0) break;
            }
        }
    }

    delete[] buf;

    return read_cnt > n_bytes ? n_bytes : read_cnt;
}

int main()
{
    std::cout << "Hello World!\n";
}

