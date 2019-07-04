#ifndef STM32_PWR_H
#define STM32_PWR_H

/*
 * Based on HAL v1.21.0(F4), v1.6.1(F1)
 * */

#include "stm32_inc.h"

namespace STM32
{
    class PWR
    {
    public:
         enum class EPVDMode: uint32_t
         {
             NORMAL           = 0x00000000,   /*!< basic mode is used */
             IT               = 0x00010000,
             EVT              = 0x00020000,
             RISING_EDGE      = 0x00000001,
             FALLING_EDGE     = 0x00000002,
             IT_RISING        = 0x00010001,   /*!< External Interrupt Mode with Rising edge trigger detection */
             IT_FALLING       = 0x00010002,   /*!< External Interrupt Mode with Falling edge trigger detection */
             IT_RISING_FALLING= 0x00010003,   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
             EVENT_RISING     = 0x00020001,   /*!< Event Mode with Rising edge trigger detection */
             EVENT_FALLING    = 0x00020002,   /*!< Event Mode with Falling edge trigger detection */
             RISING_FALLING   = 0x00020003,   /*!< Event Mode with Rising/Falling edge trigger detection */
         };
         friend EPVDMode operator&(const EPVDMode v1, const EPVDMode v2)
         {
             return EPVDMode(uint32_t(v1) & uint32_t(v2));
         }
         enum class EVoltageScale: uint32_t
         {
             #if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
             SCALE1 = 1,
             SCALE2 = 0,
             #else
             SCALE1 = 3,
             SCALE2 = 2,
             SCALE3 = 1,
             #endif
         };
         enum class ELowPowerReg: uint32_t
         {
             ON = 1,
             OFF = 0,
         };
         enum class EEntry: uint32_t
         {
             WFI = 1,
             WFE = 2,
         };

     private:
 #if defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F429xx) || defined(STM32F439xx)
         enum class PVDLvl: std::uint8_t
         {
             _2p0V  = 0,
             _2p1V  = 1,
             _2p3V  = 2,
             _2p5V  = 3,
             _2p6V  = 4,
             _2p7V  = 5,
             _2p8V  = 6,
             _2p9V  = 7,
         };
         static constexpr std::uint32_t PWR_CR_BASE              = (PWR_BASE + 0x00);
         static constexpr std::uint32_t PWR_CSR_BASE             = (PWR_BASE + 0x04);

         class CR
         {
         private:
             union CR_t
             {
                 struct
                 {
                     volatile bool    LPDS: 1;    /*!< Low-Power Deepsleep                 */
                     volatile bool    PDDS: 1;    /*!< Power Down Deepsleep                */
                     volatile bool    CWUF: 1;    /*!< Clear Wakeup Flag                   */
                     volatile bool    CSBF: 1;    /*!< Clear Standby Flag                  */
                     volatile bool    PVDE: 1;    /*!< Power Voltage Detector Enable       */
                     volatile uint8_t PVD : 3;    /*!< PLS[2:0] bits (PVD Level Selection) */
                     volatile bool    DBP : 1;    /*!< Disable Backup Domain write protection               */
                     volatile bool    FPDS: 1;    /*!< Flash power down in Stop mode                        */
                     volatile bool    res0: 4;
                     #if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
                     volatile bool    VOS : 1;    /*!< VOS bit (Regulator voltage scaling output selection) */
                     #else
                     volatile bool    VOS : 2;    /*!< VOS bit (Regulator voltage scaling output selection) */
                     #endif
                     volatile uint16_t res1:16;
                 };
                 volatile std::uint32_t RAW;
             };
         public:
             STM32_TYPE_FILED_GET_SET(low_power_deepsleep, PWR_CR_BASE, CR_t, LPDS,ELowPowerReg)
             STM32_BIT_FILED_GET_SET(power_down_deepsleep, PWR_CR_BASE, CR_t, PDDS)
             STM32_BIT_FILED_GET_SET(clear_wakeup, PWR_CR_BASE, CR_t, CWUF)
             STM32_BIT_FILED_GET_SET(clear_standby, PWR_CR_BASE, CR_t, CSBF)
             STM32_BIT_FILED_GET_SET(PVD_enable, PWR_CR_BASE, CR_t, PVDE)
             STM32_TYPE_FILED_GET_SET(PVD_level, PWR_CR_BASE, CR_t, PVD, PVDLvl)
             STM32_BIT_FILED_GET_SET(disable_backup_domain_WP, PWR_CR_BASE, CR_t, DBP)
             STM32_BIT_FILED_GET_SET(flash_pwoer_down_in_sleep, PWR_CR_BASE, CR_t, FPDS)
             STM32_TYPE_FILED_GET_SET(VOS, PWR_CR_BASE, CR_t, VOS, EVoltageScale)
         };
         class CSR
         {
         private:
             union CSR_t
             {
                 struct
                 {
                     volatile bool    WUF : 1;    /*!< Wakeup Flag                                      */
                     volatile bool    SBF : 1;    /*!< Standby Flag                                     */
                     volatile bool    PVDO: 1;    /*!< PVD Output                                       */
                     volatile bool    BRR : 1;    /*!< Backup regulator ready                           */
                     volatile bool    res0: 4;
                     volatile bool    EWUP: 1;    /*!< Enable WKUP pin                                  */
                     volatile bool    BRE : 1;    /*!< Backup regulator enable                          */
                     volatile bool    res1 :1;
                     volatile bool    res11:1;
                     volatile bool    res12:1;
                     volatile bool    res13:1;
                     volatile bool    VOSRDY: 1;  /*!< Regulator voltage scaling output selection ready */
                     volatile uint16_t res: 16;
                 };
                 volatile std::uint32_t RAW;
             };
         public:
             STM32_BIT_FILED_GET_SET(wakeup_flag, PWR_CSR_BASE, CSR_t, WUF)
             STM32_BIT_FILED_GET_SET(standby_flag, PWR_CSR_BASE, CSR_t, SBF)
             STM32_BIT_FILED_GET_SET(PVD_output, PWR_CSR_BASE, CSR_t, PVDO)
             STM32_BIT_FILED_GET_SET(ready_backup_regulator, PWR_CSR_BASE, CSR_t, BRR)
             STM32_BIT_FILED_GET_SET(enable_wakeup, PWR_CSR_BASE, CSR_t, EWUP)
             STM32_BIT_FILED_GET_SET(enable_backup_regulator, PWR_CSR_BASE, CSR_t, BRE)
             STM32_BIT_FILED_GET_SET(ready_voltage_scaling, PWR_CSR_BASE, CSR_t, VOSRDY)
         };

         static constexpr STM32::EXTI::ELine    PVD_EXTI_LINE    = STM32::EXTI::ELine::LINE_16;
 #endif
    public:
        static void deinit();

        static inline void set_backup_access(bool value) { CR::set_disable_backup_domain_WP(value); }
        static inline bool is_backup_acces_RO() { return CR::get_disable_backup_domain_WP(); }

         static void config_PVD();
         static inline void set_PVD_enable(bool value) { CR::set_PVD_enable(value); }

         //static void set_wakeup_pin(uint32_t pin, bool value) { reinterpret_cast<CR*>(PWR_CSR_BASE)->CSR = value; } // FIX!!!

         static void enter_sleep_mode(EEntry entry);
         static void enter_stop_mode(ELowPowerReg Regulator, EEntry entry);
         static void enter_standby_mode();

         static inline void set_sleep_on_exit(bool val) { CORTEX::SCB::SCR::set_sleep_on_exit(val); }
         static inline void set_SEV_on_pend(bool val) { CORTEX::SCB::SCR::set_SEV_on_pend(val); }

         static inline void set_PVD_interrupt_enable(bool val) { STM32::EXTI::set_interrupt_enable(PVD_EXTI_LINE, val); }
         static inline void set_PVD_event_enable(bool val) { STM32::EXTI::set_event_enable(PVD_EXTI_LINE, val); }
         static inline void set_PVD_rising_edge_enable(bool val) { STM32::EXTI::set_rising_edge_enable(PVD_EXTI_LINE, val); }
         static inline void set_PVD_falling_edge_enable(bool val) { STM32::EXTI::set_falling_edge_enable(PVD_EXTI_LINE, val); }

         static inline bool get_EXTI_flag() { return EXTI::get_flag(PVD_EXTI_LINE); }
         static inline void clear_EXTI_flag() { EXTI::clear_flag(PVD_EXTI_LINE); }

         static inline void set_EXTI_generate_swit() { EXTI::generate_SWIT(PVD_EXTI_LINE); }

         #ifdef STM32F4
         static inline void set_voltage_scaling_enabled(EVoltageScale val) { CR::set_VOS(val); }
         #endif

         #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
             defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
         static uint32_t enable_overdrive();
         static uint32_t disable_overdrive();

         ENDIS_REG_FLAG(overdrive_switching, PWR->CR, PWR_CR_ODSWEN)
         ENDIS_REG_FLAG(underdrive, PWR->CR, PWR_CR_UDEN)

         static uint32_t enter_underdrive_stop_mode(uint32_t Regulator, uint8_t STOPEntry);

         static inline bool get_odrudr_flag(uint32_t flag_msk) { return ((PWR->CSR & flag_msk) == flag_msk); }
         static inline void clear_odrudr_flag() { BIT_BAND_PER(PWR->CSR, PWR_FLAG_UDRDY) = ENABLE; }
         #endif

         #ifdef STM32F4
         static inline EVoltageScale get_voltage_range() { return CR::get_VOS(); }

         static uint32_t control_voltage_scaling(EVoltageScale voltage_scaling);

         static uint32_t enable_backup_regulator();
         static uint32_t disable_backup_regulator();

         static inline void set_flash_power_down(bool val) { CR::set_flash_pwoer_down_in_sleep(val); }
         #endif
    };
}

#endif // STM32_PWR_H
