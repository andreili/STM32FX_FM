#ifndef _PROFILER_HPP_
#define _PROFILER_HPP_

#include "stm32_inc.h"

#define PROFILER_CELLS_COUNT 10

class Profiler
{
public:
    Profiler();
    static void init();
    static void start();
    static void stop();

    static int add_cell(const char* name);
    static void start_ev(int idx);
    static void end_ev(int idx);

    static inline uint32_t get_size() { return m_cells; }
    static inline const char* get_name(uint32_t idx) { return m_names[idx]; }
    static inline uint32_t get_ticks(uint32_t idx) { return m_ticks[idx]; }
    static inline uint32_t get_events_counter(uint32_t idx) { return m_evs[idx]; }
private:
    static uint32_t     m_cells;
    static uint32_t     m_ev_start[PROFILER_CELLS_COUNT];
    static uint32_t     m_ev_end[PROFILER_CELLS_COUNT];
    static uint32_t     m_ticks[PROFILER_CELLS_COUNT];
    static uint32_t     m_evs[PROFILER_CELLS_COUNT];
    static const char*  m_names[PROFILER_CELLS_COUNT];
};

#endif //_PROFILER_HPP_
