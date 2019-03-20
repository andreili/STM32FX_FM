#include "fifo.h"

void FIFO::init(uint8_t* data, uint16_t size)
{
    m_head = 0;
    m_tail = 0;
    m_lock = 0;
    m_size = size;
    m_data = data;
}

uint16_t FIFO::read(void* buf, uint16_t nbytes)
{
    uint8_t* p = reinterpret_cast<uint8_t*>(buf);
    if (m_lock == 0)
    {
        m_lock = 1;
        for (uint16_t i=0 ; i<nbytes ; ++i)
        {
            if (m_tail != m_head)
            {
                *p++ = m_data[m_tail++];
                if (m_tail == m_size)
                    m_tail = 0;
            }
            else
            {
                m_lock = 0;
                return i;
            }
        }
    }
    m_lock = 0;
    return nbytes;
}

uint16_t FIFO::write(void* buf, uint16_t nbytes)
{
    uint8_t* p = reinterpret_cast<uint8_t*>(buf);
    if (m_lock == 0)
    {
        m_lock = 1;
        for (uint16_t i=0 ; i<nbytes ; ++i)
        {
            if (((m_head + 1) == m_tail) ||
                (((m_head + 1) == m_size) && (m_tail == 0)))
            {
                m_lock = 0;
                return i;
            }
            else
            {
                m_data[m_head++] = *p++;
                if (m_head == m_size)
                    m_head = 0;
            }
        }
    }
    m_lock = 0;
    return nbytes;
}
