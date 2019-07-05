#ifndef STM32_FLASH_H
#define STM32_FLASH_H

/*
 * Based on HAL v1.21.0(F4), v1.6.1(F1)
 * */

#include "stm32_inc.h"

namespace STM32
{

class FLASH
{
public:
    enum class EError: uint32_t
    {
        NONE = 0,
        RD = 0x01,
        PGS = 0x02,
        PGP = 0x04,
        PGA = 0x08,
        WRP = 0x10,
        OPERATION = 0x20,
    };
    friend EError operator|=(EError v1, EError v2)
    {
        return static_cast<EError>(static_cast<uint32_t>(v1) | static_cast<uint32_t>(v2));
    }
    enum class ELatency: uint32_t
    {
        WS_0    = 0,
        WS_1    = 1,
        WS_2    = 2,
        WS_3    = 3,
        WS_4    = 4,
        WS_5    = 5,
        WS_6    = 6,
        WS_7    = 7,
    };
    enum class EProgramSize: uint32_t
    {
        x8  = 0,
        x16 = 1,
        x32 = 2,
        x64 = 3,
    };
    enum class EVoltageRange
    {
        V_1P8_TO_2P1 = 0,
        V_2P1_TO_2P7 = 1,
        V_2P7_TO_3P6 = 2,
        V_2P7_TO_3P6_EXT = 3,
    };
    enum class ESectorNumber: uint32_t
    {
        S_0     = 0,
        S_1     = 1,
        S_2     = 2,
        S_3     = 3,
        S_4     = 4,
        S_5     = 5,
        S_6     = 6,
        S_7     = 7,
        S_8     = 8,
        S_9     = 9,
        S_10    = 10,
        S_11    = 11,
        NONE    = 0xffffffff
    };
    friend ESectorNumber operator+(ESectorNumber v1, uint32_t v2)
    {
        return static_cast<ESectorNumber>(static_cast<uint32_t>(v1) + v2);
    }
    friend ESectorNumber operator++(ESectorNumber& v1)
    {
        return (v1 = v1 + 1);
    }
    enum class ETypeErase
    {
        SECTORS,
        MASS_ERASE,
    };
    enum class ETypeProgram
    {
        #if defined(STM32F429xx) || defined(STM32F407xx)
        BYTE,
        #endif
        HALF_WORD,
        WORD,
        DOUBLE_WORD,
    };
    enum class EBank: uint32_t
    {
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
        _1 = 1,
        _2 = 2,
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
        _1 = 1,
#endif /* STM32F40xxx || STM32F41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F446xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx
          STM32F413xx || STM32F423xx */
#if defined(STM32F1)
        _1 = 1,
        _2 = 2,
#endif
    };

private:
    #if defined(STM32F407xx) || defined(STM32F417xx)
    static constexpr std::uint32_t FLASH_ACR_BASE           = (FLASH_R_BASE + 0x00);
    static constexpr std::uint32_t FLASH_KEYR_BASE          = (FLASH_R_BASE + 0x04);
    static constexpr std::uint32_t FLASH_OPTKEYR_BASE       = (FLASH_R_BASE + 0x08);
    static constexpr std::uint32_t FLASH_SR_BASE            = (FLASH_R_BASE + 0x0C);
    static constexpr std::uint32_t FLASH_CR_BASE            = (FLASH_R_BASE + 0x10);
    static constexpr std::uint32_t FLASH_OPTCR_BASE         = (FLASH_R_BASE + 0x14);
    static constexpr std::uint32_t FLASH_OPTCR1_BASE        = (FLASH_R_BASE + 0x18);
#define ACR_LATENCY 1
#define ACR_ICEN 1
    class ACR
    {
    private:
        union ACR_t
        {
            struct
            {
                uint32_t LATENCY    : 3;
                uint32_t res0       : 5;
                bool     PRFTEN     : 1;
                bool     ICEN       : 1;
                bool     DCEN       : 1;
                bool     ICRST      : 1;
                bool     DCRST      : 1;
                uint32_t res1       :18;
            };
            uint32_t RAW;
        };
    public:
        STM32_TYPE_FIELD_GET_SET(latency, FLASH_ACR_BASE, ACR_t, LATENCY, ELatency)
        STM32_BIT_FIELD_GET_SET(prefetch_enable, FLASH_ACR_BASE, ACR_t, PRFTEN)
        STM32_BIT_FIELD_GET_SET(instruction_cache_enable, FLASH_ACR_BASE, ACR_t, ICEN)
        STM32_BIT_FIELD_GET_SET(data_cache_enable, FLASH_ACR_BASE, ACR_t, DCEN)
        STM32_BIT_FIELD_GET_SET(instruction_cache_reset, FLASH_ACR_BASE, ACR_t, ICRST)
        STM32_BIT_FIELD_GET_SET(data_cache_reset, FLASH_ACR_BASE, ACR_t, DCRST)
    };
    class KEYR
    {
    public:
        enum class EKey: uint32_t
        {
            KEY1 = 0x45670123,
            KEY2 = 0xCDEF89AB,
        };
        static inline void set(EKey val) { *reinterpret_cast<volatile EKey*>(FLASH_KEYR_BASE) = val; }
    };
    class OPTKEYR
    {
    public:
        enum class EKey: uint32_t
        {
            KEY1 = 0x08192A3B,
            KEY2 = 0x4C5D6E7F,
        };
        static inline void set(EKey val) { *reinterpret_cast<volatile EKey*>(FLASH_OPTKEYR_BASE) = val; }
    };
    class SR
    {
    private:
        union SR_t
        {
            struct
            {
                bool     EOP        : 1;
                bool     OPERR      : 1;
                uint32_t res0       : 2;
                bool     WRPERR     : 1;
                bool     PGAERR     : 1;
                bool     PGPERR     : 1;
                bool     PGSERR     : 1;
                uint32_t res1       : 8;
                bool     BSY        : 1;
                uint32_t res2       :16;
            };
            uint32_t RAW;
        };
    public:
        STM32_BIT_FIELD_GET_SET(end_of_operation, FLASH_SR_BASE, SR_t, EOP)
        STM32_BIT_FIELD_GET_SET(operation_error, FLASH_SR_BASE, SR_t, OPERR)
        STM32_BIT_FIELD_GET_SET(write_protection_error, FLASH_SR_BASE, SR_t, WRPERR)
        STM32_BIT_FIELD_GET_SET(programming_alignment_error, FLASH_SR_BASE, SR_t, PGAERR)
        STM32_BIT_FIELD_GET_SET(programming_parallelism_error, FLASH_SR_BASE, SR_t, PGPERR)
        STM32_BIT_FIELD_GET_SET(programming_sequence_error, FLASH_SR_BASE, SR_t, PGSERR)
        static inline bool is_busy() { return reinterpret_cast<volatile SR_t*>(FLASH_SR_BASE)->BSY; }
    };
    class CR
    {
    private:
        union CR_t
        {
            struct
            {
                bool     PG         : 1;
                bool     SER        : 1;
                bool     MER        : 1;
                uint32_t SNB        : 4;
                uint32_t res0       : 1;
                uint32_t PSIZE      : 2;
                uint32_t res1       : 6;
                bool     STRT       : 1;
                uint32_t res2       : 7;
                bool     EOPIE      : 1;
                bool     ERRIE      : 1;
                uint32_t res3       : 5;
                bool     LOCK       : 1;
            };
            uint32_t RAW;
        };
    public:
        STM32_BIT_FIELD_GET_SET(programming, FLASH_CR_BASE, CR_t, PG)
        STM32_BIT_FIELD_GET_SET(sector_erase, FLASH_CR_BASE, CR_t, SER)
        STM32_BIT_FIELD_GET_SET(mass_erase, FLASH_CR_BASE, CR_t, MER)
        STM32_TYPE_FIELD_GET_SET(sector_number, FLASH_CR_BASE, CR_t, SNB, ESectorNumber)
        STM32_TYPE_FIELD_GET_SET(program_size, FLASH_CR_BASE, CR_t, PSIZE, EProgramSize)
        STM32_BIT_FIELD_GET_SET(start, FLASH_CR_BASE, CR_t, STRT)
        STM32_BIT_FIELD_GET_SET(end_of_operation_enable, FLASH_CR_BASE, CR_t, EOPIE)
        STM32_BIT_FIELD_GET_SET(error_interrupt_enable, FLASH_CR_BASE, CR_t, ERRIE)
        STM32_BIT_FIELD_GET_SET(lock, FLASH_CR_BASE, CR_t, LOCK)
    };

    #endif

public:
    enum class EProcedure
    {
      NONE = 0U,
      SECTERASE,
      MASS_ERASE,
      PROGRAM
    };

    #if defined(ACR_LATENCY)
    static inline void set_latency(ELatency latency) { ACR::set_latency(latency); }
    static inline ELatency get_latency() { return ACR::get_latency(); }
    #endif

    static void set_prefetch_enable(bool val) { ACR::set_prefetch_enable(val); }
    #ifdef ACR_ICEN
    static void set_instruction_cache_enable(bool val) { ACR::set_instruction_cache_enable(val); }
    static void set_data_cache_enable(bool val) { ACR::set_data_cache_enable(val); }
    #endif

    #if defined(STM32F4)
    static void reset_instruction_cache();
    static void reset_data_cache();
    #endif

    static void enable_remap_system_flash();

    //static inline void enable_IT(uint32_t it_vector) { CR::se ((FLASH_TypeDef *) FLASH_R_BASE)->CR |= it_vector; }
    //static inline void disable_IT(uint32_t it_vector) { ((FLASH_TypeDef *) FLASH_R_BASE)->CR &= ~it_vector; }

    //static inline uint8_t get_flag(uint32_t flag_mask) { return ((FLASH_TypeDef *) FLASH_R_BASE)->SR & flag_mask; }
    //static inline void clear_flag(uint32_t flag_mask) { ((FLASH_TypeDef *) FLASH_R_BASE)->SR = flag_mask; }

    #if defined(STM32F4)
    static uint32_t erase(ETypeErase type_erase, EVoltageRange voltage_range,
                          EBank banks, ESectorNumber sector_start, uint32_t nb_sectors, ESectorNumber &sector_error);
    static uint32_t erase_IT(ETypeErase type_erase, EVoltageRange voltage_range,
                             EBank banks, ESectorNumber sector_start, uint32_t nb_sectors);
    #endif

    /*static inline uint8_t OB_get_RDP() { return ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->RDP; }
    static inline void OB_set_RDP(uint8_t level) { ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->RDP = level; }

    static inline void OB_set_User(uint8_t Iwdg, uint8_t Stop, uint8_t Stdby)
        {   ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->WDG = Iwdg;
            ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->RSTS = Stop;
            ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->RSTB = Stdby; }

    static inline uint8_t OB_get_WRP() { return ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->WRP; }

    static inline uint8_t OB_get_BOR() { return ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->BOR; }
    static inline void OB_set_BOR(uint8_t level) { ((FLASH_OPTCR_Typedef*)&FLASH->OPTCR)->BOR = level; }*/

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    static uint32_t Adv_OB_Program (FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
    static void     Adv_OB_GetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
    static uint32_t OB_Select_PCROP(void);
    static uint32_t OB_deselect_PCROP(void);
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F401xC || STM32F401xE ||\
          STM32F410xx || STM32F411xE || STM32F446xx || STM32F469xx || STM32F479xx || STM32F412Zx ||\
          STM32F412Vx || STM32F412Rx || STM32F412Cx || STM32F413xx || STM32F423xx */
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
   static  uint16_t OB_get_bank2_WRP();
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

    static void erase_sector(ESectorNumber sector, EVoltageRange voltage_range);
    #ifdef STM32F4
    static void flush_caches();
    #endif

   static uint32_t program(ETypeProgram type_program, uint32_t address, uint64_t data);
   static uint32_t program_IT(ETypeProgram type_program, uint32_t address, uint64_t data);

   static uint32_t unlock();
   static void lock();
   static uint32_t OB_unlock();
   static void OB_lock();
   static uint32_t OB_launch();

   static inline EError get_error() { return m_error_code; }

   static uint32_t wait_for_last_operation(uint32_t timeout);

   static void irq_proc();
private:
   static EProcedure        m_on_going;
   static uint32_t          m_nb_sector_to_erase;
   static EVoltageRange     m_voltage_for_erase;
   static ESectorNumber     m_sector;
   static EBank             m_bank;
   static uint32_t          m_address;
   static EError            m_error_code;
   static uint8_t           m_lock;

   static void program_byte(uint32_t address, uint8_t data);
   static void program_halfword(uint32_t address, uint16_t data);
   static void program_word(uint32_t address, uint32_t data);
   static void program_doubleword(uint32_t address, uint64_t data);

   static void set_error_code();

   static void mass_erase(EVoltageRange voltage_range, EBank banks);

   static inline void reset_PG() { CR::set_programming(false); }
};

}

void FLASH_end_of_operation_cb(uint32_t return_value);
void FLASH_operation_error_cb(uint32_t return_value);

#endif
