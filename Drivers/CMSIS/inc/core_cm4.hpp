#ifndef __CORE_CM4_HPP_GENERIC
#define __CORE_CM4_HPP_GENERIC

#include <cstdint>

/*  CMSIS CM4 definitions */
#define __CM4_CMSIS_VERSION_MAIN  (0x04U)                                      /*!< [31:16] CMSIS HAL main version */
#define __CM4_CMSIS_VERSION_SUB   (0x1EU)                                      /*!< [15:0]  CMSIS HAL sub version */
#define __CM4_CMSIS_VERSION       ((__CM4_CMSIS_VERSION_MAIN << 16U) | \
                                    __CM4_CMSIS_VERSION_SUB           )        /*!< CMSIS HAL version number */

#define __CORTEX_M                (0x04U)                                      /*!< Cortex-M Core */


#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __ICCARM__ )
  #define __ASM            __asm                                      /*!< asm keyword for IAR Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __STATIC_INLINE  static inline

#elif defined ( __TMS470__ )
  #define __ASM            __asm                                      /*!< asm keyword for TI CCS Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __CSMC__ )
  #define __packed
  #define __ASM            _asm                                      /*!< asm keyword for COSMIC Compiler */
  #define __INLINE         inline                                    /*!< inline keyword for COSMIC Compiler. Use -pc99 on compile line */
  #define __STATIC_INLINE  static inline

#else
  #error Unknown compiler
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    For this, __FPU_PRESENT has to be checked prior to making use of FPU specific registers and functions.
*/
#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined __ARM_PCS_VFP
    #if (__FPU_PRESENT == 1)
      #define __FPU_USED       1U
    #else
      #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TMS470__ )
  #if defined __TI_VFP_SUPPORT__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TASKING__ )
  #if defined __FPU_VFP__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#endif

#include "cmsis_gcc.h"

#endif /* __CORE_CM4_HPP_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CM4_HPP_DEPENDANT
#define __CORE_CM4_HPP_DEPENDANT

namespace CM4
{
    constexpr std::uint32_t ITM_BASE         = 0xE0000000UL;
    constexpr std::uint32_t DWT_BASE         = 0xE0001000UL;
    constexpr std::uint32_t SCS_BASE         = 0xE000E000UL;
    constexpr std::uint32_t SysTick_BASE     = (SCS_BASE + 0x0010UL);
    constexpr std::uint32_t NVIC_BASE        = (SCS_BASE + 0x0100UL);
    constexpr std::uint32_t SCB_BASE         = (SCS_BASE + 0x0D00UL);
    constexpr std::uint32_t CoreDebug_BASE   = 0xE000EDF0UL;
    constexpr std::uint32_t TPI_BASE         = 0xE0040000UL;

    /**
      \ingroup    CMSIS_core_register
      \defgroup   CMSIS_CORE  Status and Control Registers
      \brief      Core Register type definitions.
      @{
     */

    /**
      \brief  Union type to access the Application Program Status Register (APSR).
     */
    class APSR
    {
    private:
        union APSR_Reg
        {
            struct
            {
                std::uint32_t _reserved0:16;              /*!< bit:  0..15  Reserved */
                std::uint32_t GE:4;                       /*!< bit: 16..19  Greater than or Equal flags */
                std::uint32_t _reserved1:7;               /*!< bit: 20..26  Reserved */
                std::uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
                std::uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
                std::uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
                std::uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
                std::uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
            };                                                /*!< Structure used for bit  access */
            std::uint32_t w;                              /*!< Type      used for word access */
        };
    public:
    };

    /**
      \brief  Union type to access the Interrupt Program Status Register (IPSR).
     */
    class IPSR
    {
    private:
        union IPSR_Reg
        {
            struct
            {
                std::int32_t ISR:9;                      /*!< bit:  0.. 8  Exception number */
                std::uint32_t _reserved0:23;              /*!< bit:  9..31  Reserved */
            };                                                /*!< Structure used for bit  access */
            std::uint32_t w;                              /*!< Type      used for word access */
        };
    public:
    };

    /**
      \brief  Union type to access the Special-Purpose Program Status Registers (xPSR).
     */
    class xPSR
    {
    private:
        union xPSR_Reg
        {
            struct
            {
                std::uint32_t ISR:9;                      /*!< bit:  0.. 8  Exception number */
                std::uint32_t _reserved0:7;               /*!< bit:  9..15  Reserved */
                std::uint32_t GE:4;                       /*!< bit: 16..19  Greater than or Equal flags */
                std::uint32_t _reserved1:4;               /*!< bit: 20..23  Reserved */
                std::uint32_t T:1;                        /*!< bit:     24  Thumb bit        (read 0) */
                std::uint32_t IT:2;                       /*!< bit: 25..26  saved IT state   (read 0) */
                std::uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
                std::uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
                std::uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
                std::uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
                std::uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
            };                                                /*!< Structure used for bit  access */
            std::uint32_t w;                              /*!< Type      used for word access */
        };
    public:
    };

    /**
      \brief  Union type to access the Control Registers (CONTROL).
     */
    class CONTROL
    {
    private:
        static constexpr std::uint32_t CONTROL_BASE   = (SCB_BASE + 0x00);
        union CONTROL_Reg
        {
            struct
            {
                std::uint32_t nPRIV:1;                    /*!< bit:      0  Execution privilege in Thread mode */
                std::uint32_t SPSEL:1;                    /*!< bit:      1  Stack to be used */
                std::uint32_t FPCA:1;                     /*!< bit:      2  FP extension active flag */
                std::uint32_t _reserved0:29;              /*!< bit:  3..31  Reserved */
            };                                                /*!< Structure used for bit  access */
            std::uint32_t w;                              /*!< Type      used for word access */
        };
    public:
        static inline void set(uint32_t val) { CMSIS::set_CONTROL(val); }
    };

    /*@} end of group CMSIS_CORE */


    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_SCB     System Control Block (SCB)
      \brief    Type definitions for the System Control Block Registers
      @{
     */

    /**
      \brief  Structure type to access the System Control Block (SCB).
     */
    class SCB
    {
    private:
        static constexpr std::uint32_t CPUID_BASE   = (SCB_BASE + 0x00);
        static constexpr std::uint32_t ICSR_BASE    = (SCB_BASE + 0x04);
        static constexpr std::uint32_t VTOR_BASE    = (SCB_BASE + 0x08);
        static constexpr std::uint32_t AIRCR_BASE   = (SCB_BASE + 0x0C);
        static constexpr std::uint32_t SCR_BASE     = (SCB_BASE + 0x10);
        static constexpr std::uint32_t CCR_BASE     = (SCB_BASE + 0x14);
        static constexpr std::uint32_t SHP_BASE     = (SCB_BASE + 0x18);
        static constexpr std::uint32_t SHCSR_BASE   = (SCB_BASE + 0x24);
        static constexpr std::uint32_t CFSR_BASE    = (SCB_BASE + 0x28);
        static constexpr std::uint32_t HFSR_BASE    = (SCB_BASE + 0x2C);
        static constexpr std::uint32_t DFSR_BASE    = (SCB_BASE + 0x30);
        static constexpr std::uint32_t MMFAR_BASE   = (SCB_BASE + 0x34);
        static constexpr std::uint32_t BFAR_BASE    = (SCB_BASE + 0x38);
        static constexpr std::uint32_t AFSR_BASE    = (SCB_BASE + 0x3C);
        static constexpr std::uint32_t PFR_BASE     = (SCB_BASE + 0x40);
        static constexpr std::uint32_t DFR_BASE     = (SCB_BASE + 0x48);
        static constexpr std::uint32_t ADR_BASE     = (SCB_BASE + 0x4C);
        static constexpr std::uint32_t MMFR_BASE    = (SCB_BASE + 0x50);
        static constexpr std::uint32_t ISAR_BASE    = (SCB_BASE + 0x60);
        static constexpr std::uint32_t CPACR_BASE   = (SCB_BASE + 0x88);
    public:
        class CPUID
        {
        private:
            union CPUID_t
            {
                struct
                {
                    std::uint32_t    REVISION    : 4;
                    std::uint32_t    PART_NO     :12;
                    std::uint32_t    ARCHITECRURE: 4;
                    std::uint32_t    VARIANT     : 4;
                    std::uint32_t    IMPLEMENTER : 8;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CPUID_t*>(CPUID_BASE)->RAW; }
        };
        class ICSR
        {
        private:
            union ICSR_t
            {
                struct
                {
                    std::uint32_t    VECTACTIVE  : 9;
                    std::uint32_t    res0        : 2;
                    std::uint32_t    RETOBASE    : 1;
                    std::uint32_t    VECTPENDING : 9;
                    std::uint32_t    res1        : 3;
                    std::uint32_t    ISRPENDING  : 1;
                    std::uint32_t    res2        : 2;
                    std::uint32_t    PENDSTCLR   : 1;
                    std::uint32_t    PENDSTSET   : 1;
                    std::uint32_t    PENDSVCLR   : 1;
                    std::uint32_t    PENDSVSET   : 1;
                    std::uint32_t    res3        : 2;
                    std::uint32_t    NMIPENDSET  : 1;
                };
                std::uint32_t RAW;
            };
        public:
            static inline void set_pend_NMI() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->NMIPENDSET = true; }
            static inline void set_pend_SV() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->PENDSVSET = true; }
            static inline void clear_pend_SV() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->PENDSVCLR = true; }
            static inline void set_pend_ST() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->PENDSTSET = true; }
            static inline void clear_pend_ST() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->PENDSTCLR = true; }
            static inline void get_pend_ISR() { reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->ISRPENDING = true; }
            static inline uint32_t get_pend_vector() { return reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->VECTPENDING; }
            static inline bool get_return_to_base() { return reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->RETOBASE; }
            static inline uint32_t get_active_vector() { return reinterpret_cast<volatile ICSR_t*>(ICSR_BASE)->VECTACTIVE; }
        };
        class VTOR
        {
        private:
            union VTOR_t
            {
                struct
                {
                    std::uint32_t    res0        : 9;
                    std::uint32_t    TBLOFF      :21;
                    std::uint32_t    res1        : 2;
                };
                std::uint32_t RAW;
            };
        public:
            static inline void set(std::uint32_t val) { reinterpret_cast<volatile VTOR_t*>(VTOR_BASE)->RAW = (val & 0x3FFFFE00); }
            static inline std::uint32_t get() { return reinterpret_cast<volatile VTOR_t*>(VTOR_BASE)->RAW; }
        };
        class AIRCR
        {
        private:
        public:
            union AIRCR_t
            {
                struct
                {
                    std::uint32_t    VECTRESET       : 1;
                    std::uint32_t    VECTCLRACTIVE   : 1;
                    std::uint32_t    SYSRESETREQ     : 1;
                    std::uint32_t    res0            : 5;
                    std::uint32_t    PRIGROUP        : 3;
                    std::uint32_t    res1            : 4;
                    std::uint32_t    ENDIANESS       : 1;
                    std::uint32_t    VECTKEYSTAT     :16;
                };
                std::uint32_t RAW;
            };

            static inline AIRCR_t& get() { return *reinterpret_cast<AIRCR_t*>(AIRCR_BASE); }
            static inline void set(std::uint32_t val) { reinterpret_cast<volatile AIRCR_t*>(AIRCR_BASE)->RAW = val; }
            static inline std::uint32_t get_prior_group() { return reinterpret_cast<volatile AIRCR_t*>(AIRCR_BASE)->PRIGROUP; }
        };
        class SCR
        {
        private:
            union SCR_t
            {
                struct
                {
                    std::uint32_t    res0        : 1;
                    std::uint32_t    SLEEPONEXIT : 1;
                    std::uint32_t    SLEEPDEEP   : 1;
                    std::uint32_t    res1        : 1;
                    std::uint32_t    SEVEONPEND  : 1;
                    std::uint32_t    res2        :27;
                };
                std::uint32_t RAW;
            };
        public:
            static inline void set_sleep_on_exit(bool val) { reinterpret_cast<volatile SCR_t*>(SCR_BASE)->SLEEPONEXIT = val; }
            static inline void set_sleep_deep(bool val) { reinterpret_cast<volatile SCR_t*>(SCR_BASE)->SLEEPDEEP = val; }
            static inline void set_SEV_on_pend(bool val) { reinterpret_cast<volatile SCR_t*>(SCR_BASE)->SEVEONPEND = val; }

        };
        class CCR
        {
        private:
            union CCR_t
            {
                struct
                {
                    std::uint32_t    res0        : 1;
                    std::uint32_t    SLEEPONEXIT : 1;
                    std::uint32_t    SLEEPDEEP   : 1;
                    std::uint32_t    res1        : 1;
                    std::uint32_t    SEVEONPEND  : 1;
                    std::uint32_t    res2        :27;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CCR_t*>(CCR_BASE)->RAW; }
        };
        class SHPx
        {
        private:
        public:
            static std::uint32_t get(ARM::IRQn idx)
            {
                return *reinterpret_cast<volatile uint8_t*>(SHP_BASE + ((static_cast<uint32_t>(idx) & 0xF) - 4));
            }
            static void set(ARM::IRQn idx, std::uint32_t val)
            {
                *reinterpret_cast<volatile uint8_t*>(SHP_BASE + ((static_cast<uint32_t>(idx) & 0xF) - 4)) = val;
            }
        };
        class SHCSR
        {
        private:
            union SHCSR_t
            {
                struct
                {
                    std::uint32_t    MEMFAULTACT      : 1;
                    std::uint32_t    BUSFAULTACT     : 1;
                    std::uint32_t    res0            : 1;
                    std::uint32_t    USGFAULTACT     : 1;
                    std::uint32_t    res1            : 3;
                    std::uint32_t    SVCALLACT       : 1;
                    std::uint32_t    MONITORACT      : 1;
                    std::uint32_t    res2            : 1;
                    std::uint32_t    PENDSVACT       : 1;
                    std::uint32_t    SYSTICKACT      : 1;
                    std::uint32_t    USGFAULTPENDED  : 1;
                    std::uint32_t    MEMFAULTPENDED  : 1;
                    std::uint32_t    BUSFAULTPENDED  : 1;
                    std::uint32_t    SVCALLPENDED    : 1;
                    std::uint32_t    MEMFAULTENA     : 1;
                    std::uint32_t    BUSFAULTENA     : 1;
                    std::uint32_t    USGFAULTENA     : 1;
                    std::uint32_t    res3            :12;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile SHCSR_t*>(SHCSR_BASE)->RAW; }
        };
        class CFSR
        {
        private:
            union CFSR_t
            {
                struct
                {
                    union
                    {
                        struct
                        {
                            std::uint32_t    IACCVIOL    : 1; // Instruction access violation flag
                            std::uint32_t    DACCVIOL    : 1; // Data access violation flag
                            std::uint32_t    res0        : 1; //
                            std::uint32_t    MUNSTKERR   : 1; // Memory manager fault on unstacking for a return from exception
                            std::uint32_t    MSTKERR     : 1; // Memory manager fault on stacking for exception entry
                            std::uint32_t    MLSPERR     : 1; // 1: A MemManage fault occurred during floating-point lazy state preservation
                            std::uint32_t    res1        : 1; //
                            std::uint32_t    MMARVALID   : 1; // Memory Management Fault Address Register (MMAR) valid flag
                        };
                        std::uint32_t    MMFSR       : 8;
                    };
                    union
                    {
                        struct
                        {
                            std::uint32_t    IBUSERR     : 1; // Instruction bus error
                            std::uint32_t    PRECISERR   : 1; // Precise data bus error
                            std::uint32_t    IMPRECISERR : 1; // Imprecise data bus error
                            std::uint32_t    UNSTKERR    : 1; // Bus fault on unstacking for a return from exception
                            std::uint32_t    STKERR      : 1; // Bus fault on stacking for exception entry
                            std::uint32_t    LSPERR      : 1; // Bus fault on floating-point lazy state preservation
                            std::uint32_t    res2        : 1; //
                            std::uint32_t    BFARVALID   : 1; // Bus Fault Address Register (BFAR) valid flag
                        };
                        std::uint32_t    BFSR        : 8;
                    };
                    union
                    {
                        struct
                        {
                            std::uint32_t    UNDEFINSTR  : 1; // Undefined instruction usage fault
                            std::uint32_t    INVSTATE    : 1; // Invalid state usage fault
                            std::uint32_t    INVPC       : 1; // Invalid PC load usage fault, caused by an invalid PC load by EXC_RETURN
                            std::uint32_t    NOCP        : 1; // No coprocessor usage fault
                            std::uint32_t    res3        : 4; // Bus fault on stacking for exception entry
                            std::uint32_t    UNALIGNED   : 1; // Unaligned access usage fault
                            std::uint32_t    DIVBYZERO   : 1; // Divide by zero usage fault
                            std::uint32_t    res4        : 6;
                        };
                        std::uint32_t    UFSR        :16;
                    };
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CFSR_t*>(CFSR_BASE)->RAW; }
        };
        class HFSR
        {
        private:
            union HFSR_t
            {
                struct
                {
                    std::uint32_t    res0        : 1;
                    std::uint32_t    VECTTBL     : 1; // Vector table hard fault
                    std::uint32_t    res1        :28;
                    std::uint32_t    FORCED      : 1; // Forced hard fault
                    std::uint32_t    DEBUG_VT    : 1; // Reserved for Debug use
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile HFSR_t*>(HFSR_BASE)->RAW; }
        };
        class DFSR
        {
        private:
            union DFSR_t
            {
                struct
                {
                    std::uint32_t    HALTED      : 1;
                    std::uint32_t    BKPT        : 1;
                    std::uint32_t    DWTTRAP     : 1;
                    std::uint32_t    VCATCH      : 1;
                    std::uint32_t    EXTERNAL    : 1;
                    std::uint32_t    res         :27;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile DFSR_t*>(DFSR_BASE)->RAW; }
        };
        class MMFAR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(MMFAR_BASE); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(MMFAR_BASE) = val; }
        };
        class BFAR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(BFAR_BASE); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(BFAR_BASE) = val; }
        };
        class AFSR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(AFSR_BASE); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(AFSR_BASE) = val; }
        };
        volatile std::uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
        volatile std::uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
        volatile std::uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
        volatile std::uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
        volatile std::uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        volatile std::uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
    };

    /*@} end of group CMSIS_SCB */

    /**
      \ingroup    CMSIS_core_register
      \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
      \brief      Type definitions for the NVIC Registers
      @{
     */

    /**
      \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
     */
    class NVIC
    {
    private:
        static constexpr std::uint32_t ISER_BASE    = (NVIC_BASE + 0x000);
        static constexpr std::uint32_t ICER_BASE    = (NVIC_BASE + 0x080);
        static constexpr std::uint32_t ISPR_BASE    = (NVIC_BASE + 0x100);
        static constexpr std::uint32_t ICPR_BASE    = (NVIC_BASE + 0x180);
        static constexpr std::uint32_t IABR_BASE    = (NVIC_BASE + 0x200);
        static constexpr std::uint32_t IP_BASE      = (NVIC_BASE + 0x300);
        static constexpr std::uint32_t STIR_BASE    = (NVIC_BASE + 0xE00);

        template <uint32_t offset>
        class ManReg
        {
        public:
            void set_flag(ARM::IRQn IRQn)
            {
                *reinterpret_cast<volatile std::uint32_t*>(NVIC_BASE + offset + ((static_cast<uint32_t>(IRQn) >> 5) * 4)) |=
                        (1 << (static_cast<uint32_t>(IRQn) & 0x1F));
            }
            bool get_flag(ARM::IRQn IRQn)
            {
                return ((*reinterpret_cast<volatile std::uint32_t*>(NVIC_BASE + offset + ((static_cast<uint32_t>(IRQn) >> 5) * 4))) >>
                        (static_cast<uint32_t>(IRQn) & 0x1F)) & 0x01;
            }
            void set(uint32_t idx, uint32_t val)
            {
                *reinterpret_cast<volatile std::uint32_t*>(NVIC_BASE + offset + idx) = val;
            }
        };
        class IP
        {
        public:
            static uint8_t get(ARM::IRQn idx) { return *reinterpret_cast<volatile uint8_t*>(IP_BASE + static_cast<uint32_t>(idx)); }
            static void set(ARM::IRQn idx, uint8_t val) { *reinterpret_cast<volatile uint8_t*>(IP_BASE + static_cast<uint32_t>(idx)) = val; }
        };
        class STIR
        {
        public:
            static std::uint32_t get() { return *reinterpret_cast<volatile std::uint32_t*>(STIR_BASE); }
            static void set(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(STIR_BASE) = val; }
        };

        static ManReg<0x000>   ISER;   /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        static ManReg<0x080>   ICER;   /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        static ManReg<0x100>   ISPR;   /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        static ManReg<0x180>   ICPR;   /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        static ManReg<0x200>   IABR;   /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
    public:

        static void set_priority_grouping(uint32_t prioruty_group)
        {
            prioruty_group = (prioruty_group & (uint32_t)0x07UL);             /* only values 0..7 are used          */

            SCB::AIRCR::AIRCR_t reg_value = SCB::AIRCR::get();
            reg_value.VECTKEYSTAT = 0x5FAUL;
            reg_value.PRIGROUP = prioruty_group;

            SCB::AIRCR::set(reg_value.RAW);
        }
        static std::uint32_t get_priority_grouping()
        {
            return SCB::AIRCR::get_prior_group();
        }
        static void enable_IRQ(ARM::IRQn IRQn)
        {
            ISER.set_flag(IRQn);
        }
        static void disable_IRQ(ARM::IRQn IRQn)
        {
            ICER.set_flag(IRQn);
        }
        static void disable_all_IRQs()
        {
            ICER.set(0, 0xFFFFFFFF);
            ICER.set(1, 0xFFFFFFFF);
            ICER.set(2, 0xFFFFFFFF);
        }
        static bool get_pending_IRQ(ARM::IRQn IRQn)
        {
            return ISPR.get_flag(IRQn);
        }
        static void set_pending_IRQ(ARM::IRQn IRQn)
        {
            ISPR.set_flag(IRQn);
        }
        static void clear_pending_IRQ(ARM::IRQn IRQn)
        {
            ICPR.set_flag(IRQn);
        }
        static void clear_all_pending_IRQs()
        {
            ICPR.set(0, 0xFFFFFFFF);
            ICPR.set(1, 0xFFFFFFFF);
            ICPR.set(2, 0xFFFFFFFF);
        }
        static bool get_active_IRQ(ARM::IRQn IRQn)
        {
            return IABR.get_flag(IRQn);
        }
        static void set_priority(ARM::IRQn IRQn, std::uint32_t priority)
        {
            priority = (priority << NVIC_PRIO_BITS) & 0xff;
            if (static_cast<int32_t>(IRQn) < 0)
                SCB::SHPx::set(IRQn, priority);
            else
                IP::set(IRQn, priority);
        }
        static std::uint32_t get_priority(ARM::IRQn IRQn)
        {
            std::uint32_t priority;
            if (static_cast<int32_t>(IRQn) < 0)
            {
                priority = SCB::SHPx::get(IRQn);
            }
            else
                priority = IP::get(IRQn);
            return (priority >> NVIC_PRIO_BITS);
        }
        static std::uint32_t encode_priority(uint32_t group, std::uint32_t preemt, std::uint32_t sub)
        {
            std::uint32_t GroupTmp = (group & (uint32_t)0x07UL);   /* only values 0..7 are used          */
            std::uint32_t PreemptBits;
            std::uint32_t SubBits;

            PreemptBits = ((7UL - GroupTmp) > NVIC_PRIO_BITS) ? NVIC_PRIO_BITS : (uint32_t)(7UL - GroupTmp);
            SubBits     = ((GroupTmp + NVIC_PRIO_BITS) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((GroupTmp - 7UL) + NVIC_PRIO_BITS);

            return (
                ((preemt & (uint32_t)((1UL << (PreemptBits)) - 1UL)) << SubBits) |
                ((sub    & (uint32_t)((1UL << (SubBits    )) - 1UL)))
            );
        }
        static void decode_priority(uint32_t priority, std::uint32_t group, std::uint32_t &preemt, std::uint32_t &sub)
        {
            std::uint32_t GroupTmp = (group & (uint32_t)0x07UL);   /* only values 0..7 are used          */
            std::uint32_t PreemptBits;
            std::uint32_t SubBits;

            PreemptBits = ((7UL - GroupTmp) > NVIC_PRIO_BITS) ? NVIC_PRIO_BITS : (uint32_t)(7UL - GroupTmp);
            SubBits     = ((GroupTmp + NVIC_PRIO_BITS) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((GroupTmp - 7UL) + NVIC_PRIO_BITS);

            preemt = (priority >> SubBits) & (uint32_t)((1UL << (PreemptBits)) - 1UL);
            sub    = (priority           ) & (uint32_t)((1UL << (SubBits    )) - 1UL);
        }
        static __attribute__((noreturn)) void system_reset()
        {
            CMSIS::DSB();                                                          /* Ensure all outstanding memory accesses included
                                                                                      buffered write are completed before reset */

            SCB::AIRCR::AIRCR_t reg_value;
            reg_value.VECTKEYSTAT = 0x5FAUL;
            reg_value.SYSRESETREQ = true;
            reg_value.PRIGROUP = SCB::AIRCR::get().PRIGROUP;
            SCB::AIRCR::set(reg_value.RAW);

            CMSIS::DSB();                                                     /* Ensure completion of memory access */

            for(;;)                                                           /* wait until reset */
                CMSIS::NOP();
        }
    };
    /*@} end of group CMSIS_NVIC */


    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_SCnSCB System Controls not in SCB (SCnSCB)
      \brief    Type definitions for the System Control and ID Register not in the SCB
      @{
     */

    /**
      \brief  Structure type to access the System Control and ID Register not in the SCB.
     */
    class SCnSCB
    {
    private:
        static constexpr std::uint32_t ICTR_BASE    = (SCS_BASE + 0x04);
        static constexpr std::uint32_t ACTLR_BASE   = (SCS_BASE + 0x08);
        class ICTR_Reg
        {
        private:
            union ICTR_t
            {
                struct
                {
                    std::uint32_t    INTLINESNUM : 4;
                    std::uint32_t    res         :28;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile ICTR_t*>(ICTR_BASE)->RAW; }
        };
        class ACTLR_Reg
        {
        private:
            union ACTLR_t
            {
                struct
                {
                    std::uint32_t    DISMCYCINT  : 1;
                    std::uint32_t    DISDEFWBUF  : 1;
                    std::uint32_t    DISFOLD     : 1;
                    std::uint32_t    res0        : 5;
                    std::uint32_t    DISFPCA     : 1;
                    std::uint32_t    DISOOFP     : 1;
                    std::uint32_t    res1        :22;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile ACTLR_t*>(ACTLR_BASE)->RAW; }
        };
    public:
        ICTR_Reg    ICTR;
        ACTLR_Reg   ACTLR;
    };

    /*@} end of group CMSIS_SCnotSCB */


    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
      \brief    Type definitions for the System Timer Registers.
      @{
     */

    /**
      \brief  Structure type to access the System Timer (SysTick).
     */
    class SysTick
    {
    private:
        static constexpr std::uint32_t CTRL_BASE    = (SysTick_BASE + 0x00);
        static constexpr std::uint32_t LOAD_BASE    = (SysTick_BASE + 0x04);
        static constexpr std::uint32_t VAL_BASE     = (SysTick_BASE + 0x08);
        static constexpr std::uint32_t CALIB_BASE    = (SysTick_BASE + 0x0C);
    public:
        class CTRL
        {
        public:
            union CTRL_t
            {
                struct
                {
                    std::uint32_t    ENABLE      : 1;
                    std::uint32_t    TICKINT     : 1;
                    std::uint32_t    CLKSOURCE   : 1;
                    std::uint32_t    res0        :12;
                    std::uint32_t    COUNTFLAG   : 1;
                    std::uint32_t    res1        :14;
                };
                std::uint32_t RAW;
            };
            static inline std::uint32_t get() { return reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW; }
            static inline void set(uint32_t val) { reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW = val; }
            static inline void set_source_HCLK(bool val) { reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->CLKSOURCE = val; }
        };
        class LOAD
        {
        private:
            union LOAD_t
            {
                struct
                {
                    std::uint32_t    RELOAD      :24;
                    std::uint32_t    res         : 8;
                };
                std::uint32_t RAW;
            };
        public:
            static inline std::uint32_t get() { return reinterpret_cast<volatile LOAD_t*>(LOAD_BASE)->RELOAD; }
            static inline void set(uint32_t val) { reinterpret_cast<volatile LOAD_t*>(LOAD_BASE)->RAW = (val & 0x00ffffff); }
        };
        class VAL
        {
        private:
            union VAL_t
            {
                struct
                {
                    std::uint32_t    CURRENT     :24;
                    std::uint32_t    res         : 8;
                };
                std::uint32_t RAW;
            };
        public:
            static inline std::uint32_t get() { return reinterpret_cast<volatile VAL_t*>(VAL_BASE)->CURRENT; }
            static inline void set(uint32_t val) { reinterpret_cast<volatile VAL_t*>(VAL_BASE)->RAW = (val & 0x00ffffff); }
        };
        class CALIB
        {
        private:
            union CALIB_t
            {
                struct
                {
                    std::uint32_t    TENMS       :24;
                    std::uint32_t    res         : 6;
                    std::uint32_t    SKEW        : 1;
                    std::uint32_t    NOREF       : 1;
                };
                std::uint32_t RAW;
            };
        public:
            static inline std::uint32_t get() { return reinterpret_cast<volatile CALIB_t*>(CALIB_BASE)->RAW; }
        };

        static inline void start()
        {
            CTRL::CTRL_t ctrl;
            ctrl.ENABLE = true;
            ctrl.TICKINT = true;
            ctrl.CLKSOURCE = true;
            *reinterpret_cast<CTRL::CTRL_t*>(CTRL_BASE) = ctrl;
        }
        static inline void suspend()
        {
            reinterpret_cast<volatile CTRL::CTRL_t*>(CTRL_BASE)->TICKINT = false;
        }
        static inline void resume()
        {
            reinterpret_cast<volatile CTRL::CTRL_t*>(CTRL_BASE)->TICKINT = true;
        }
        static void config(uint32_t ticks)
        {
            if ((ticks - 1UL) > 0x00ffffff)
                return;
            LOAD::set(ticks - 1);
            NVIC::set_priority(ARM::IRQn::SysTick, (1UL << NVIC_PRIO_BITS) - 1UL);
            VAL::set(0);
            start();
        }
    };
    /*@} end of group CMSIS_SysTick */

    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_ITM     Instrumentation Trace Macrocell (ITM)
      \brief    Type definitions for the Instrumentation Trace Macrocell (ITM)
      @{
     */

    /**
      \brief  Structure type to access the Instrumentation Trace Macrocell Register (ITM).
     */
    class ITM
    {
    private:
        static constexpr std::uint32_t PORT_BASE        = (ITM_BASE + 0x000UL);
        static constexpr std::uint32_t TER_BASE         = (ITM_BASE + 0xE00UL);
        static constexpr std::uint32_t TPR_BASE         = (ITM_BASE + 0xE40UL);
        static constexpr std::uint32_t TCR_BASE         = (ITM_BASE + 0xE80UL);
        static constexpr std::uint32_t IWR_BASE         = (ITM_BASE + 0xEF8UL);
        static constexpr std::uint32_t IRR_BASE         = (ITM_BASE + 0xEFCUL);
        static constexpr std::uint32_t IMCR_BASE        = (ITM_BASE + 0xF00UL);
        static constexpr std::uint32_t LAR_BASE         = (ITM_BASE + 0xFB0UL);
        static constexpr std::uint32_t LSR_BASE         = (ITM_BASE + 0xFB4UL);
        class PORT
        {
        private:
            union PORT_t
            {
                uint8_t    u8;                   /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 8-bit */
                uint16_t   u16;                  /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 16-bit */
                std::uint32_t   u32;                  /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 32-bit */
            };
        public:
            static inline PORT_t& get(uint32_t idx) { return *reinterpret_cast<PORT_t*>(PORT_BASE + idx * 4); }
        };
        class TER
        {
        public:
            static inline std::uint32_t get() { return *reinterpret_cast<volatile std::uint32_t*>(TER_BASE); }
            static inline void set(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(TER_BASE) = val; }

            static inline bool enabled(uint32_t channel) { return ((*reinterpret_cast<volatile std::uint32_t*>(TER_BASE) & channel) != 0); }
        };
        class TPR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(TPR_BASE); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(TPR_BASE) = val; }
        };
        class TCR
        {
        private:
            union TCR_t
            {
                struct
                {
                    std::uint32_t    ITMENA      : 1;
                    std::uint32_t    TSENA       : 1;
                    std::uint32_t    SYNCENA     : 1;
                    std::uint32_t    DWTENA      : 1;
                    std::uint32_t    SWOENA      : 1;
                    std::uint32_t    res0        : 3;
                    std::uint32_t    TSPrescale  : 2;
                    std::uint32_t    GTSFREQ     : 2;
                    std::uint32_t    res1        : 4;
                    std::uint32_t    TraceBusID  : 7;
                    std::uint32_t    BUSY        : 1;
                    std::uint32_t    res2        : 8;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile TCR_t*>(TCR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile TCR_t*>(TCR_BASE)->RAW = val; }

            static inline bool enabled() { return reinterpret_cast<volatile TCR_t*>(TCR_BASE)->ITMENA; }
        };
        class IWR
        {
        private:
            union IWR_t
            {
                struct
                {
                    std::uint32_t    ATVALIDM    : 1;
                    std::uint32_t    res         :31;
                };
                std::uint32_t RAW;
            };
        public:
            inline void operator=(uint32_t val) { reinterpret_cast<volatile IWR_t*>(IWR_BASE)->RAW = val; }
        };
        class IRR
        {
        private:
            union IRR_t
            {
                struct
                {
                    std::uint32_t    ATREADYM    : 1;
                    std::uint32_t    res         :31;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile IRR_t*>(IRR_BASE)->RAW; }
        };
        class IMCR
        {
        private:
            union IMCR_t
            {
                struct
                {
                    std::uint32_t    INTEGRATION : 1;
                    std::uint32_t    res         :31;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile IMCR_t*>(IMCR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile IMCR_t*>(IMCR_BASE)->RAW = val; }
        };
        class LAR
        {
        public:
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(LAR_BASE) = val; }
        };
        class LSR
        {
        private:
            union LSR_t
            {
                struct
                {
                    std::uint32_t    Present     : 1;
                    std::uint32_t    Access      : 1;
                    std::uint32_t    ByteAcc     : 1;
                    std::uint32_t    res         :29;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile LSR_t*>(LSR_BASE)->RAW; }
        };
        template<uint32_t offset>
        class RegR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(ITM_BASE + offset); }
        };
    public:
        RegR<0xFD0> PID4;                                   /*!< Offset: 0xFD0 (R/ )  ITM Peripheral Identification Register #4 */
        RegR<0xFD4> PID5;                                   /*!< Offset: 0xFD4 (R/ )  ITM Peripheral Identification Register #5 */
        RegR<0xFD8> PID6;                                   /*!< Offset: 0xFD8 (R/ )  ITM Peripheral Identification Register #6 */
        RegR<0xFDC> PID7;                                   /*!< Offset: 0xFDC (R/ )  ITM Peripheral Identification Register #7 */
        RegR<0xFE0> PID0;                                   /*!< Offset: 0xFE0 (R/ )  ITM Peripheral Identification Register #0 */
        RegR<0xFE4> PID1;                                   /*!< Offset: 0xFE4 (R/ )  ITM Peripheral Identification Register #1 */
        RegR<0xFE8> PID2;                                   /*!< Offset: 0xFE8 (R/ )  ITM Peripheral Identification Register #2 */
        RegR<0xFEC> PID3;                                   /*!< Offset: 0xFEC (R/ )  ITM Peripheral Identification Register #3 */
        RegR<0xFF0> CID0;                                   /*!< Offset: 0xFF0 (R/ )  ITM Component  Identification Register #0 */
        RegR<0xFF4> CID1;                                   /*!< Offset: 0xFF4 (R/ )  ITM Component  Identification Register #1 */
        RegR<0xFF8> CID2;                                   /*!< Offset: 0xFF8 (R/ )  ITM Component  Identification Register #2 */
        RegR<0xFFC> CID3;                                   /*!< Offset: 0xFFC (R/ )  ITM Component  Identification Register #3 */

        static inline char send_char(char ch)
        {
            if (TCR::enabled() && TER::enabled(1))
            {
                while (PORT::get(0).u32 == 0)
                    CMSIS::NOP();
                PORT::get(0).u8 = ch;
            }
            return ch;
        }
    };
    /*@}*/ /* end of group CMSIS_ITM */


    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_DWT     Data Watchpoint and Trace (DWT)
      \brief    Type definitions for the Data Watchpoint and Trace (DWT)
      @{
     */

    /**
      \brief  Structure type to access the Data Watchpoint and Trace Register (DWT).
     */
    class DWT
    {
    private:
        static constexpr std::uint32_t CTRL_BASE        = (DWT_BASE + 0x000UL);
        static constexpr std::uint32_t CYCCNT_BASE      = (DWT_BASE + 0x004UL);
        static constexpr std::uint32_t CPICNT_BASE      = (DWT_BASE + 0x008UL);
        static constexpr std::uint32_t EXCCNT_BASE      = (DWT_BASE + 0x00CUL);
        static constexpr std::uint32_t SLEEPCNT_BASE    = (DWT_BASE + 0x010UL);
        static constexpr std::uint32_t LSUCNT_BASE      = (DWT_BASE + 0x014UL);
        static constexpr std::uint32_t FOLDCNT_BASE     = (DWT_BASE + 0x018UL);
        static constexpr std::uint32_t PCSR_BASE        = (DWT_BASE + 0x01CUL);
        class CTRL_Reg
        {
        private:
            union CTRL_t
            {
                struct
                {
                    std::uint32_t    CYCCNTENA   : 1;
                    std::uint32_t    POSTPRESET  : 4;
                    std::uint32_t    POSTINIT    : 4;
                    std::uint32_t    CYCTAP      : 1;
                    std::uint32_t    SYNCTAP     : 2;
                    std::uint32_t    PCSAMPLENA  : 1;
                    std::uint32_t    res0        : 3;
                    std::uint32_t    EXCTRCENA   : 1;
                    std::uint32_t    CPIEVTENA   : 1;
                    std::uint32_t    EXCEVTENA   : 1;
                    std::uint32_t    SLEEPEVTENA : 1;
                    std::uint32_t    LSUEVTENA   : 1;
                    std::uint32_t    FOLDEVTENA  : 1;
                    std::uint32_t    res1        : 1;
                    std::uint32_t    NOPRFCNT    : 1;
                    std::uint32_t    NOCYCCNT    : 1;
                    std::uint32_t    NOEXTTRIG   : 1;
                    std::uint32_t    NOTRCPKT    : 1;
                    std::uint32_t    NUMCOMP     : 4;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW = val; }
        };
        template<uint32_t offset>
        class FUNCTION_Reg
        {
            union FUNCTION_t
            {
                struct
                {
                    std::uint32_t    FUNCTION    : 4;
                    std::uint32_t    EMITRANGE   : 1;
                    std::uint32_t    res0        : 1;
                    std::uint32_t    CYCMATCH    : 1;
                    std::uint32_t    DATAVMATCH  : 1;
                    std::uint32_t    LNK1ENA     : 1;
                    std::uint32_t    DATAVSIZE   : 2;
                    std::uint32_t    DATAVADDR0  : 4;
                    std::uint32_t    DATAVADDR1  : 4;
                    std::uint32_t    res1        : 4;
                    std::uint32_t    MATCHED     : 1;
                    std::uint32_t    res2        : 7;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile FUNCTION_t*>(DWT_BASE + offset)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile FUNCTION_t*>(DWT_BASE + offset)->RAW = val; }
        };

        template<uint32_t offset>
        class RegRW5
        {
            union CNT_t
            {
                struct
                {
                    std::uint32_t    val5        : 5;
                    std::uint32_t    res0        :27;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CNT_t*>(DWT_BASE + offset)->val5; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile CNT_t*>(DWT_BASE + offset)->val5 = val; }
        };
        template<uint32_t offset>
        class RegRW16
        {
            union CNT_t
            {
                struct
                {
                    std::uint32_t    val8        : 8;
                    std::uint32_t    res0        :24;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CNT_t*>(DWT_BASE + offset)->val8; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile CNT_t*>(DWT_BASE + offset)->val8 = val; }
        };
        template<uint32_t offset>
        class RegRW
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(DWT_BASE + offset); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(DWT_BASE + offset) = val; }
        };
        template<uint32_t offset>
        class RegR
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(DWT_BASE + offset); }
        };
    public:
        CTRL_Reg            CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
        RegRW<0x004>        CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
        RegRW16<0x008>      CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
        RegRW16<0x00c>      EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
        RegRW16<0x010>      SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
        RegRW16<0x014>      LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
        RegRW16<0x018>      FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
        RegR<0x01C>         PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
        RegRW<0x020>        COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
        RegRW5<0x024>       MASK0;                  /*!< Offset: 0x024 (R/W)  Mask Register 0 */
        FUNCTION_Reg<0x028> FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
        RegRW<0x030>        COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
        RegRW5<0x034>       MASK1;                  /*!< Offset: 0x034 (R/W)  Mask Register 1 */
        FUNCTION_Reg<0x038> FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
        RegRW<0x040>       COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
        RegRW5<0x044>       MASK2;                  /*!< Offset: 0x044 (R/W)  Mask Register 2 */
        FUNCTION_Reg<0x048> FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
        RegRW<0x050>        COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
        RegRW5<0x054>       MASK3;                  /*!< Offset: 0x054 (R/W)  Mask Register 3 */
        FUNCTION_Reg<0x058> FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
        RegR<0xFD0> PID4;                           /*!< Offset: 0xFD0 (R/ )  PWD Peripheral Identification Register #4 */
        RegR<0xFD4> PID5;                           /*!< Offset: 0xFD4 (R/ )  PWD Peripheral Identification Register #5 */
        RegR<0xFD8> PID6;                           /*!< Offset: 0xFD8 (R/ )  PWD Peripheral Identification Register #6 */
        RegR<0xFDC> PID7;                           /*!< Offset: 0xFDC (R/ )  PWD Peripheral Identification Register #7 */
        RegR<0xFE0> PID0;                           /*!< Offset: 0xFE0 (R/ )  PWD Peripheral Identification Register #0 */
        RegR<0xFE4> PID1;                           /*!< Offset: 0xFE4 (R/ )  PWD Peripheral Identification Register #1 */
        RegR<0xFE8> PID2;                           /*!< Offset: 0xFE8 (R/ )  PWD Peripheral Identification Register #2 */
        RegR<0xFEC> PID3;                           /*!< Offset: 0xFEC (R/ )  PWD Peripheral Identification Register #3 */
        RegR<0xFF0> CID0;                           /*!< Offset: 0xFF0 (R/ )  PWD Component  Identification Register #0 */
        RegR<0xFF4> CID1;                           /*!< Offset: 0xFF4 (R/ )  PWD Component  Identification Register #1 */
        RegR<0xFF8> CID2;                           /*!< Offset: 0xFF8 (R/ )  PWD Component  Identification Register #2 */
        RegR<0xFFC> CID3;                           /*!< Offset: 0xFFC (R/ )  PWD Component  Identification Register #3 */
    };
    /*@}*/ /* end of group CMSIS_DWT */


#if (__MPU_PRESENT == 1U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_MPU     Memory Protection Unit (MPU)
  \brief    Type definitions for the Memory Protection Unit (MPU)
  @{
 */

/**
  \brief  Structure type to access the Memory Protection Unit (MPU).
 */
    class MPU
    {
    private:
        static constexpr std::uint32_t MPU_BASE         = (SCS_BASE + 0xD90UL);
        static constexpr std::uint32_t TYPE_BASE        = (MPU_BASE + 0x000UL);
        static constexpr std::uint32_t CTRL_BASE        = (MPU_BASE + 0x004UL);
        static constexpr std::uint32_t RNR_BASE         = (MPU_BASE + 0x008UL);
        static constexpr std::uint32_t RBAR_BASE        = (MPU_BASE + 0x00CUL);
        static constexpr std::uint32_t RASR_BASE        = (MPU_BASE + 0x010UL);

        class TYPE_Reg
        {
            union TYPE_t
            {
                struct
                {
                    std::uint32_t    SEPARATE    : 1;
                    std::uint32_t    res0        : 7;
                    std::uint32_t    DREGION     : 8;
                    std::uint32_t    IREGION     : 8;
                    std::uint32_t    res1        : 8;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile TYPE_t*>(TYPE_BASE)->RAW; }
        };
        class CTRL_Reg
        {
            union CTRL_t
            {
                struct
                {
                    std::uint32_t    REGION      : 8;
                    std::uint32_t    HFNMIENA    : 1;
                    std::uint32_t    PRIVDEFENA  : 1;
                    std::uint32_t    res         :28;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile CTRL_t*>(CTRL_BASE)->RAW = val; }
        };
        class RNR_Reg
        {
            union RNR_t
            {
                struct
                {
                    std::uint32_t    REGION      : 4;
                    std::uint32_t    res         :24;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile RNR_t*>(RNR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile RNR_t*>(RNR_BASE)->RAW = val; }
        };
        template<uint32_t offset>
        class RBAR_Reg
        {
            union RBAR_t
            {
                struct
                {
                    std::uint32_t    REGION      : 4;
                    std::uint32_t    VALID       : 1;
                    std::uint32_t    ADDR        :23;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile RBAR_t*>(MPU_BASE + offset)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile RBAR_t*>(MPU_BASE + offset)->RAW = val; }
        };
        template<uint32_t offset>
        class RASR_Reg
        {
            union RASR_t
            {
                struct
                {
                    std::uint32_t    ENABLE      : 1;
                    std::uint32_t    SIZE        : 5;
                    std::uint32_t    res0        : 2;
                    std::uint32_t    SRD         : 8;
                    std::uint32_t    B           : 1;
                    std::uint32_t    C           : 1;
                    std::uint32_t    S           : 1;
                    std::uint32_t    TEX         : 3;
                    std::uint32_t    res1        : 2;
                    std::uint32_t    AP          : 3;
                    std::uint32_t    res2        : 1;
                    std::uint32_t    XN          : 1;
                    std::uint32_t    res3        : 3;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile RASR_t*>(MPU_BASE + offset)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile RASR_t*>(MPU_BASE + offset)->RAW = val; }
        };
    public:
        TYPE_Reg        TYPE;                   /*!< Offset: 0x000 (R/ )  MPU Type Register */
        CTRL_Reg        CTRL;                   /*!< Offset: 0x004 (R/W)  MPU Control Register */
        RNR_Reg         RNR;                    /*!< Offset: 0x008 (R/W)  MPU Region RNRber Register */
        RBAR_Reg<0x00C> RBAR;                   /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register */
        RASR_Reg<0x010> RASR;                   /*!< Offset: 0x010 (R/W)  MPU Region Attribute and Size Register */
        RBAR_Reg<0x014> RBAR_A1;                /*!< Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register */
        RASR_Reg<0x018> RASR_A1;                /*!< Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
        RBAR_Reg<0x01C> RBAR_A2;                /*!< Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register */
        RASR_Reg<0x020> RASR_A2;                /*!< Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
        RBAR_Reg<0x024> RBAR_A3;                /*!< Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register */
        RASR_Reg<0x028> RASR_A3;                /*!< Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
    };
    /*@} end of group CMSIS_MPU */
#endif //__MPU_PRESENT

#if (__FPU_PRESENT == 1U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_FPU     Floating Point Unit (FPU)
  \brief    Type definitions for the Floating Point Unit (FPU)
  @{
 */

/**
  \brief  Structure type to access the Floating Point Unit (FPU).
 */
    class FPU
    {
    private:
        static constexpr std::uint32_t FPU_BASE         = (SCB_BASE + 0x088UL);
        static constexpr std::uint32_t CPACR_BASE       = (FPU_BASE + 0x000UL);
        static constexpr std::uint32_t FPCCR_BASE       = (FPU_BASE + 0x004UL);
        static constexpr std::uint32_t FPCAR_BASE       = (FPU_BASE + 0x008UL);
        static constexpr std::uint32_t FPDSCR_BASE      = (FPU_BASE + 0x00CUL);
        static constexpr std::uint32_t MVFR0_BASE       = (FPU_BASE + 0x010UL);
        static constexpr std::uint32_t MVFR1_BASE       = (FPU_BASE + 0x014UL);

    public:
        class CPACR
        {
            union CPACR_t
            {
                struct
                {
                    std::uint32_t    res0        :20;
                    std::uint32_t    CP10        : 2;
                    std::uint32_t    CP11        : 2;
                    std::uint32_t    res         : 8;
                };
                std::uint32_t RAW;
            };
        public:
            enum class ECP
            {
                DENIED = 0,
                PRIV_ONLY = 1,
                RESERVED = 2,
                FULL_ACCESS = 3,
            };
            static inline void set_CP10(ECP value) { reinterpret_cast<volatile CPACR_t*>(CPACR_BASE)->CP10 = static_cast<uint32_t>(value); }
            static inline void set_CP11(ECP value) { reinterpret_cast<volatile CPACR_t*>(CPACR_BASE)->CP11 = static_cast<uint32_t>(value); }
            static inline void set_CP10_CP11(ECP value) { reinterpret_cast<volatile CPACR_t*>(CPACR_BASE)->RAW |=
                        (((static_cast<uint32_t>(value) << 2) | static_cast<uint32_t>(value)) << 20); }
        };
        class FPCCR
        {
            union FPCCR_t
            {
                struct
                {
                    std::uint32_t    LSPACT      : 1;
                    std::uint32_t    USER        : 1;
                    std::uint32_t    res0        : 1;
                    std::uint32_t    THREAD      : 1;
                    std::uint32_t    HFRDY       : 1;
                    std::uint32_t    MMRDY       : 1;
                    std::uint32_t    BFRDY       : 1;
                    std::uint32_t    res1        : 1;
                    std::uint32_t    MONRDY      : 1;
                    std::uint32_t    res2        :21;
                    std::uint32_t    LSPEN       : 1;
                    std::uint32_t    ASPEN       : 1;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile FPCCR_t*>(FPCCR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile FPCCR_t*>(FPCCR_BASE)->RAW = val; }
        };
        class FPCAR
        {
            union FPCAR_t
            {
                struct
                {
                    std::uint32_t    res0        : 3;
                    std::uint32_t    ADDRESS     :29;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile FPCAR_t*>(FPCAR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile FPCAR_t*>(FPCAR_BASE)->RAW = val; }
        };
        class FPDSCR
        {
            union FPDSCR_t
            {
                struct
                {
                    std::uint32_t    res0        :22;
                    std::uint32_t    RMode       : 2;
                    std::uint32_t    FZ          : 1;
                    std::uint32_t    DN          : 1;
                    std::uint32_t    AHP         : 1;
                    std::uint32_t    res1        : 5;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile FPDSCR_t*>(FPDSCR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile FPDSCR_t*>(FPDSCR_BASE)->RAW = val; }
        };
        class MVFR0
        {
            union MVFR0_t
            {
                struct
                {
                    std::uint32_t    A_SIMD      : 4;
                    std::uint32_t    SinglePrec  : 4;
                    std::uint32_t    DblPrec     : 4;
                    std::uint32_t    FPExceptTrap: 4;
                    std::uint32_t    Divide      : 4;
                    std::uint32_t    SquareRoot  : 4;
                    std::uint32_t    ShortVectors: 4;
                    std::uint32_t    FPRoundingM : 4;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile MVFR0_t*>(MVFR0_BASE)->RAW; }
        };
        class MVFR1
        {
            union MVFR1_t
            {
                struct
                {
                    std::uint32_t    FtZMode     : 4;
                    std::uint32_t    D_NaNMode   : 4;
                    std::uint32_t    res0        :16;
                    std::uint32_t    FPHPFP      : 4;
                    std::uint32_t    FPUsedMAC   : 4;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile MVFR1_t*>(MVFR1_BASE)->RAW; }
        };
    };
    /*@} end of group CMSIS_FPU */
#endif //__FPU_PRESENT

    /**
      \ingroup  CMSIS_core_register
      \defgroup CMSIS_CoreDebug       Core Debug Registers (CoreDebug)
      \brief    Type definitions for the Core Debug Registers
      @{
     */

    /**
      \brief  Structure type to access the Core Debug Register (CoreDebug).
     */
    class CoreDebug
    {
    private:
        static constexpr std::uint32_t DHCSR_BASE       = (CoreDebug_BASE + 0x000UL);
        static constexpr std::uint32_t DCRSR_BASE       = (CoreDebug_BASE + 0x004UL);
        static constexpr std::uint32_t DCRDR_BASE       = (CoreDebug_BASE + 0x008UL);
        static constexpr std::uint32_t DEMCR_BASE       = (CoreDebug_BASE + 0x00CUL);

        class DHCSR_Reg
        {
            union DHCSR_t
            {
                struct
                {
                    std::uint32_t    C_DEBUGEN   : 1;
                    std::uint32_t    C_HALT      : 1;
                    std::uint32_t    C_STEP      : 1;
                    std::uint32_t    C_MASKINTS  : 1;
                    std::uint32_t    C_SNAPSTALL : 1;
                    std::uint32_t    res0        :10;
                    union
                    {
                        std::uint32_t    DBGKEY      :16;
                        struct
                        {
                            std::uint32_t    S_REGRDY    : 1;
                            std::uint32_t    S_HALT      : 1;
                            std::uint32_t    S_SLEEP     : 1;
                            std::uint32_t    S_LOCKUP    : 1;
                            std::uint32_t    res0        : 4;
                            std::uint32_t    S_RETIRE_ST : 1;
                            std::uint32_t    S_RESET_ST  : 1;
                            std::uint32_t    res1        : 6;
                        } read;
                    };
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile DHCSR_t*>(DHCSR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile DHCSR_t*>(DHCSR_BASE)->RAW = val; }
        };
        class DCRSR_Reg
        {
            union DCRSR_t
            {
                struct
                {
                    std::uint32_t    REGSEL      : 5;
                    std::uint32_t    res0        :11;
                    std::uint32_t    REGWnR      : 1;
                    std::uint32_t    res1        :15;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile DCRSR_t*>(DCRSR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile DCRSR_t*>(DCRSR_BASE)->RAW = val; }
        };
        class DCRDR_Reg
        {
        public:
            inline std::uint32_t operator()() { return *reinterpret_cast<volatile std::uint32_t*>(DCRDR_BASE); }
            inline void operator=(uint32_t val) { *reinterpret_cast<volatile std::uint32_t*>(DCRDR_BASE) = val; }
        };
        class DEMCR_Reg
        {
            union DEMCR_t
            {
                struct
                {
                    std::uint32_t    VC_CORERESET: 1;
                    std::uint32_t    res0        : 3;
                    std::uint32_t    VC_MMERR    : 1;
                    std::uint32_t    VC_NOCPERR  : 1;
                    std::uint32_t    VC_CHKERR   : 1;
                    std::uint32_t    VC_STATERR  : 1;
                    std::uint32_t    VC_BUSERR   : 1;
                    std::uint32_t    VC_INTERR   : 1;
                    std::uint32_t    VC_HARDERR  : 1;
                    std::uint32_t    res1        : 5;
                    std::uint32_t    MON_EN      : 1;
                    std::uint32_t    MON_PEND    : 1;
                    std::uint32_t    MON_STEP    : 1;
                    std::uint32_t    MON_REQ     : 1;
                    std::uint32_t    res2        : 3;
                    std::uint32_t    TRCENA      : 1;
                    std::uint32_t    res3        : 7;
                };
                std::uint32_t RAW;
            };
        public:
            inline std::uint32_t operator()() { return reinterpret_cast<volatile DEMCR_t*>(DEMCR_BASE)->RAW; }
            inline void operator=(uint32_t val) { reinterpret_cast<volatile DEMCR_t*>(DEMCR_BASE)->RAW = val; }
        };
    public:
        DHCSR_Reg DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
        DCRSR_Reg DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
        DCRDR_Reg DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
        DEMCR_Reg DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
    };
    /*@} end of group CMSIS_CoreDebug */

}

#endif /* __CORE_CM4_HPP_DEPENDANT */

#endif /* __CMSIS_GENERIC */
