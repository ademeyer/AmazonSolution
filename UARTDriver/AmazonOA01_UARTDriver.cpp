// UARTDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class UARTDriver
{
public:
    UARTDriver(const unsigned int baudrate, const unsigned int databits = 8, const bool parity = false)
        : m_DataBit(databits), m_ParityBit(parity), m_BitLength(CalculateBitLength(baudrate))
    {}
    ~UARTDriver() {}

    //Functions
    void Uart_Transmit(uint8_t* data, uint16_t datalen)
    {
        //disable all interrupt and tasksheduler
        for (size_t i = 0; i < datalen; i++)
        {
            uint8_t ch = data[i];

            //pull down tx line as start bit
            writeLow();
            delay_us(m_BitLength);

            for (int j = 0; j < m_DataBit; j++)
            {
                if (ch & 0x01)
                {
                    writeHigh();
                }
                else
                {
                    writeLow();
                }
                delay_us(m_BitLength);
                ch >>= 1;
            }

            if (m_ParityBit)
            {
                uint8_t parity = CalculateParity(ch);
                if (parity & 0x01)
                    writeHigh();
                else
                    writeLow();
                delay_us(m_BitLength);
            }

            //pull up  the tx pin to mark stop bit
            writeHigh();
            delay_us(m_BitLength);
        }
        // enable interrupt and task scheduler
    }

    void Uart_Receive(uint8_t* data, uint16_t datalen)
    {
        // disable all interrupt and tasksheduler
        for (size_t i = 0; i < datalen; i++)
        {
            int c = 0;

            // wait for start bit
            while (readSate() == 1);
            /*
            * // why divide by 2??
            * If the bit was sampled at the beginning or the end of the bit and the delay timer timer
            * ISR/scheduler task was not serviced immediately, invalid data could be detected. Sampling at the half bit
            * time also allows some margin if there is latency in the detection of the start bit or in the
            * servicing of future timer ISRs or scheduler tasks.
            */
            delay_us(m_BitLength/2); 

            for (int j = 0; j < m_DataBit; j++)
            {
                delay_us(m_BitLength);
                c |= (readSate() ? 1 : 0) << j;
            }

            if (m_ParityBit)
            {
                delay_us(m_BitLength);
                uint8_t tp = readSate() ? 1 : 0;
                uint8_t p = CalculateParity(c);
                if(tp == p)
                    data[i] = c;
            }
            else
                data[i] = c;

            // wait for stop bit
            while (readSate() == 0);
        }
        // enable interrupt and task scheduler
    }
    
    // uC specific funtions
    virtual void delay_us(unsigned long length) {}
    virtual void writeLow() {}
    virtual void writeHigh() {}
    virtual uint8_t readSate() { return 0; }

    // Test APIs
    int GetDataBits() const { return m_DataBit; }
    int GetBitLength() const { return m_BitLength; }
    bool IsParityBitSet() const { return m_ParityBit; }

private:
    int CalculateBitLength(unsigned int baudrate)
    {
        return (1000000 / baudrate);
    }

    uint8_t CalculateParity(uint8_t data)
    {
        int parity = 0;
        while (data)
        {
            parity ^= (data & 0x01);
            data >>= 1;
        }
        return parity;
    }

    int m_DataBit;
    bool m_ParityBit;
    int m_BitLength;
};

int main()
{
    UARTDriver uart1(9600);
    std::cout << "Data Bits: " << uart1.GetDataBits() << std::endl;
    std::cout << "Bits Length: " << uart1.GetBitLength() << std::endl;
    std::cout << "Parity Check Set: " << (uart1.IsParityBitSet() ? "True" : "False") << std::endl;
    std::cout << "\n";

    UARTDriver uart2(19200, 5, false);
    std::cout << "Data Bits: " << uart2.GetDataBits() << std::endl;
    std::cout << "Bits Length: " << uart2.GetBitLength() << std::endl;
    std::cout << "Parity Check Set: " << (uart2.IsParityBitSet() ? "True" : "False") << std::endl;
    std::cout << "\n";

    UARTDriver uart3(38400, 7, true);
    std::cout << "Data Bits: " << uart3.GetDataBits() << std::endl;
    std::cout << "Bits Length: " << uart3.GetBitLength() << std::endl;
    std::cout << "Parity Check Set: " << (uart3.IsParityBitSet() ? "True" : "False") << std::endl;
    std::cout << "\n";

    UARTDriver uart4(115200, 9, true);
    std::cout << "Data Bits: " << uart4.GetDataBits() << std::endl;
    std::cout << "Bits Length: " << uart4.GetBitLength() << std::endl;
    std::cout << "Parity Check Set: " << (uart4.IsParityBitSet() ? "True" : "False") << std::endl;
    std::cout << "\n";
}

