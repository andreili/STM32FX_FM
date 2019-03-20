#ifndef FIFO_H
#define FIFO_H

#include <inttypes.h>

class FIFO
{
public:
    void init(uint8_t* data, uint16_t size);
    uint16_t read(void* buf, uint16_t nbytes);
    uint16_t write(void* buf, uint16_t nbytes);
private:
    uint8_t     m_lock;
    uint16_t    m_head;
    uint16_t    m_tail;
    uint16_t    m_size;
    uint8_t*    m_data;
};

#endif //FIFO_H
