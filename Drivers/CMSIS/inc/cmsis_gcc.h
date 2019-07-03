/**************************************************************************//**
 * @file     cmsis_gcc.h
 * @brief    CMSIS Cortex-M Core Function/Instruction Header File
 * @version  V4.30
 * @date     20. October 2015
 ******************************************************************************/
/* Copyright (c) 2009 - 2015 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

/* ignore some GCC warnings */
#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

class CMSIS
{
private:
public:
    /* ###########################  Core Function Access  ########################### */
    /** \ingroup  CMSIS_Core_FunctionInterface
        \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
      @{
     */

    /**
      \brief   Enable IRQ Interrupts
      \details Enables IRQ interrupts by clearing the I-bit in the CPSR.
               Can only be executed in Privileged modes.
     */
    static inline void enable_irq() { __asm volatile ("cpsie i" : : : "memory"); }
    /**
      \brief   Disable IRQ Interrupts
      \details Disables IRQ interrupts by setting the I-bit in the CPSR.
      Can only be executed in Privileged modes.
     */
    static inline void disable_irq() { __asm volatile ("cpsid i" : : : "memory"); }
    /**
      \brief   Get Control Register
      \details Returns the content of the Control Register.
      \return               Control Register value
     */
    static inline uint32_t get_CONTROL()
    {
      uint32_t result;
      __asm volatile ("MRS %0, control" : "=r" (result) );
      return result;
    }
    /**
      \brief   Set Control Register
      \details Writes the given value to the Control Register.
      \param [in]    control  Control Register value to set
     */
    static inline void set_CONTROL(uint32_t control) { __asm volatile ("MSR control, %0" : : "r" (control) : "memory"); }
    /**
      \brief   Get IPSR Register
      \details Returns the content of the IPSR Register.
      \return               IPSR Register value
     */
    static inline uint32_t get_IPSR(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, ipsr" : "=r" (result) );
      return(result);
    }
    /**
      \brief   Get APSR Register
      \details Returns the content of the APSR Register.
      \return               APSR Register value
     */
    static inline uint32_t get_APSR(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, apsr" : "=r" (result) );
      return(result);
    }
    /**
      \brief   Get xPSR Register
      \details Returns the content of the xPSR Register.
      \return               xPSR Register value
     */
    static inline uint32_t get_xPSR(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, xpsr" : "=r" (result) );
      return(result);
    }
    /**
      \brief   Get Process Stack Pointer
      \details Returns the current value of the Process Stack Pointer (PSP).
      \return               PSP Register value
     */
    static inline uint32_t get_PSP(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, psp\n"  : "=r" (result) );
      return(result);
    }
    /**
      \brief   Set Process Stack Pointer
      \details Assigns the given value to the Process Stack Pointer (PSP).
      \param [in]    topOfProcStack  Process Stack Pointer value to set
     */
    static inline void set_PSP(uint32_t topOfProcStack) { __asm volatile ("MSR psp, %0\n" : : "r" (topOfProcStack) : "sp"); }
    /**
      \brief   Get Main Stack Pointer
      \details Returns the current value of the Main Stack Pointer (MSP).
      \return               MSP Register value
     */
    static inline uint32_t get_MSP(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, msp\n" : "=r" (result) );
      return(result);
    }
    /**
      \brief   Set Main Stack Pointer
      \details Assigns the given value to the Main Stack Pointer (MSP).

        \param [in]    topOfMainStack  Main Stack Pointer value to set
     */
    static inline void set_MSP(uint32_t topOfMainStack) { __asm volatile ("MSR msp, %0\n" : : "r" (topOfMainStack) : "sp"); }
    /**
      \brief   Get Priority Mask
      \details Returns the current state of the priority mask bit from the Priority Mask Register.
      \return               Priority Mask value
     */
    static inline uint32_t get_PRIMASK(void)
    {
      uint32_t result;
      __asm volatile ("MRS %0, primask" : "=r" (result) );
      return(result);
    }
    /**
      \brief   Set Priority Mask
      \details Assigns the given value to the Priority Mask Register.
      \param [in]    priMask  Priority Mask
     */
    static inline void set_PRIMASK(uint32_t priMask) { __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory"); }
#if       (__CORTEX_M >= 0x03U)

    /**
      \brief   Enable FIQ
      \details Enables FIQ interrupts by clearing the F-bit in the CPSR.
               Can only be executed in Privileged modes.
     */
    static inline void enable_fault_irq(void) { __asm volatile ("cpsie f" : : : "memory"); }
    /**
      \brief   Disable FIQ
      \details Disables FIQ interrupts by setting the F-bit in the CPSR.
               Can only be executed in Privileged modes.
     */
    static inline void disable_fault_irq(void) { __asm volatile ("cpsid f" : : : "memory"); }
    /**
      \brief   Get Base Priority
      \details Returns the current value of the Base Priority register.
      \return               Base Priority register value
     */
    static inline uint32_t get_BASEPRI(void)
    {
        uint32_t result;
        __asm volatile ("MRS %0, basepri" : "=r" (result) );
        return(result);
    }
    /**
      \brief   Set Base Priority
      \details Assigns the given value to the Base Priority register.
      \param [in]    basePri  Base Priority value to set
     */
    static inline void set_BASEPRI(uint32_t value) { __asm volatile ("MSR basepri, %0" : : "r" (value) : "memory"); }
    /**
      \brief   Set Base Priority with condition
      \details Assigns the given value to the Base Priority register only if BASEPRI masking is disabled,
               or the new value increases the BASEPRI priority level.
      \param [in]    basePri  Base Priority value to set
     */
    static inline void set_BASEPRI_MAX(uint32_t value) { __asm volatile ("MSR basepri_max, %0" : : "r" (value) : "memory"); }
    /**
      \brief   Get Fault Mask
      \details Returns the current value of the Fault Mask register.
      \return               Fault Mask register value
     */
    static inline uint32_t get_FAULTMASK(void)
    {
        uint32_t result;
        __asm volatile ("MRS %0, faultmask" : "=r" (result) );
        return(result);
    }
    /**
      \brief   Set Fault Mask
      \details Assigns the given value to the Fault Mask register.
      \param [in]    faultMask  Fault Mask value to set
     */
    static inline void set_FAULTMASK(uint32_t faultMask) { __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory"); }

#endif /* (__CORTEX_M >= 0x03U) */


#if       (__CORTEX_M == 0x04U) || (__CORTEX_M == 0x07U)
    /**
      \brief   Get FPSCR
      \details Returns the current value of the Floating Point Status/Control register.
      \return               Floating Point Status/Control register value
     */
    static inline uint32_t get_FPSCR(void)
    {
    #if (__FPU_PRESENT == 1U) && (__FPU_USED == 1U)
        uint32_t result;
        /* Empty asm statement works as a scheduling barrier */
        __asm volatile ("");
        __asm volatile ("VMRS %0, fpscr" : "=r" (result) );
        __asm volatile ("");
        return(result);
    #else
        return(0);
    #endif
    }
    /**
      \brief   Set FPSCR
      \details Assigns the given value to the Floating Point Status/Control register.
      \param [in]    fpscr  Floating Point Status/Control value to set
     */
    static inline void set_FPSCR(uint32_t fpscr)
    {
    #if (__FPU_PRESENT == 1U) && (__FPU_USED == 1U)
        /* Empty asm statement works as a scheduling barrier */
        __asm volatile ("");
        __asm volatile ("VMSR fpscr, %0" : : "r" (fpscr) : "vfpcc");
        __asm volatile ("");
    #endif
    }
#endif /* (__CORTEX_M == 0x04U) || (__CORTEX_M == 0x07U) */
    /*@} end of CMSIS_Core_RegAccFunctions */

    /* ##########################  Core Instruction Access  ######################### */
    /** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
      Access to dedicated instructions
      @{
    */

    /**
      \brief   No Operation
      \details No Operation does nothing. This instruction can be used for code alignment purposes.
     */
    static inline  void NOP(void) { __asm volatile ("nop"); }
    /**
      \brief   Wait For Interrupt
      \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
     */
    static inline void WFI(void) { __asm volatile ("wfi"); }
    /**
      \brief   Wait For Event
      \details Wait For Event is a hint instruction that permits the processor to enter
        a low-power state until one of a number of events occurs.
     */
    static inline void WFE(void) { __asm volatile ("wfe"); }
    /**
      \brief   Send Event
      \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
     */
    static inline void SEV(void) { __asm volatile ("sev"); }
    /**
      \brief   Instruction Synchronization Barrier
      \details Instruction Synchronization Barrier flushes the pipeline in the processor,
               so that all instructions following the ISB are fetched from cache or memory,
               after the instruction has been completed.
     */
    static inline void ISB(void) { __asm volatile ("isb 0xF":::"memory"); }
    /**
      \brief   Data Synchronization Barrier
      \details Acts as a special kind of Data Memory Barrier.
               It completes when all explicit memory accesses before this instruction complete.
     */
    static inline void DSB(void) { __asm volatile ("dsb 0xF":::"memory"); }
    /**
      \brief   Data Memory Barrier
      \details Ensures the apparent order of the explicit memory operations before
               and after the instruction, without ensuring their completion.
     */
    static inline void DMB(void) { __asm volatile ("dmb 0xF":::"memory"); }
    /**
      \brief   Reverse byte order (32 bit)
      \details Reverses the byte order in integer value.
      \param [in]    value  Value to reverse
      \return               Reversed value
     */
    static inline uint32_t REV(uint32_t value)
    {
    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
        return __builtin_bswap32(value);
    #else
        uint32_t result;
        __asm volatile ("rev %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
        return(result);
    #endif
    }
    /**
      \brief   Reverse byte order (16 bit)
      \details Reverses the byte order in two unsigned short values.
      \param [in]    value  Value to reverse
      \return               Reversed value
     */
    static inline uint32_t REV16(uint32_t value)
    {
        uint32_t result;
        __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
        return(result);
    }
    /**
      \brief   Reverse byte order in signed short value
      \details Reverses the byte order in a signed short value with sign extension to integer.
      \param [in]    value  Value to reverse
      \return               Reversed value
     */
    static inline int32_t REVSH(int32_t value)
    {
    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
        return (short)__builtin_bswap16(value);
    #else
        int32_t result;
        __asm volatile ("revsh %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
        return(result);
    #endif
    }
    /**
      \brief   Rotate Right in unsigned value (32 bit)
      \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
      \param [in]    value  Value to rotate
      \param [in]    value  Number of Bits to rotate
      \return               Rotated value
     */
    static inline uint32_t ROR(uint32_t op1, uint32_t op2)
    {
        return (op1 >> op2) | (op1 << (32U - op2));
    }
    /**
      \brief   Breakpoint
      \details Causes the processor to enter Debug state.
               Debug tools can use this to investigate system state when the instruction at a particular address is reached.
      \param [in]    value  is ignored by the processor.
                     If required, a debugger can use it to store additional information about the breakpoint.
     */
    static inline void BKPT() { __asm volatile ("bkpt "); }
    /**
      \brief   Reverse bit order of value
      \details Reverses the bit order of the given value.
      \param [in]    value  Value to reverse
      \return               Reversed value
     */
    static inline uint32_t RBIT(uint32_t value)
    {
        uint32_t result;
    #if       (__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U)
       __asm volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
    #else
        int32_t s = 4 /*sizeof(v)*/ * 8 - 1; /* extra shift needed at end */
        result = value;                      /* r will be reversed bits of v; first get LSB of v */
        for (value >>= 1U; value; value >>= 1U)
        {
            result <<= 1U;
            result |= value & 1U;
            s--;
        }
        result <<= s;                        /* shift when v's highest bits are zero */
    #endif
        return(result);
    }
    /**
      \brief   Count leading zeros
      \details Counts the number of leading zeros of a data value.
      \param [in]  value  Value to count the leading zeros
      \return             number of leading zeros in value
     */
    #define __CLZ             __builtin_clz

    #if       (__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U)

    /**
      \brief   LDR Exclusive (8 bit)
      \details Executes a exclusive LDR instruction for 8 bit value.
      \param [in]    ptr  Pointer to data
      \return             value of type uint8_t at (*ptr)
     */
    static inline uint8_t LDREXB(volatile uint8_t *addr)
    {
        uint32_t result;

    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
       __asm volatile ("ldrexb %0, %1" : "=r" (result) : "Q" (*addr) );
    #else
        /* Prior to GCC 4.8, "Q" will be expanded to [rx, #0] which is not
           accepted by assembler. So has to use following less efficient pattern.
        */
       __asm volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
    #endif
       return ((uint8_t) result);    /* Add explicit type cast here */
    }
    /**
      \brief   LDR Exclusive (16 bit)
      \details Executes a exclusive LDR instruction for 16 bit values.
      \param [in]    ptr  Pointer to data
      \return        value of type uint16_t at (*ptr)
     */
    static inline uint16_t LDREXH(volatile uint16_t *addr)
    {
        uint32_t result;
    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
       __asm volatile ("ldrexh %0, %1" : "=r" (result) : "Q" (*addr) );
    #else
        /* Prior to GCC 4.8, "Q" will be expanded to [rx, #0] which is not
           accepted by assembler. So has to use following less efficient pattern.
        */
       __asm volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
    #endif
       return ((uint16_t) result);    /* Add explicit type cast here */
    }
    /**
      \brief   LDR Exclusive (32 bit)
      \details Executes a exclusive LDR instruction for 32 bit values.
      \param [in]    ptr  Pointer to data
      \return        value of type uint32_t at (*ptr)
     */
    static inline uint32_t LDREXW(volatile uint32_t *addr)
    {
        uint32_t result;
       __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
       return(result);
    }
    /**
      \brief   STR Exclusive (8 bit)
      \details Executes a exclusive STR instruction for 8 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
      \return          0  Function succeeded
      \return          1  Function failed
     */
    static inline uint32_t STREXB(uint8_t value, volatile uint8_t *addr)
    {
       uint32_t result;

       __asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
       return(result);
    }
    /**
      \brief   STR Exclusive (16 bit)
      \details Executes a exclusive STR instruction for 16 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
      \return          0  Function succeeded
      \return          1  Function failed
     */
    static inline uint32_t STREXH(uint16_t value, volatile uint16_t *addr)
    {
       uint32_t result;

       __asm volatile ("strexh %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
       return(result);
    }
    /**
      \brief   STR Exclusive (32 bit)
      \details Executes a exclusive STR instruction for 32 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
      \return          0  Function succeeded
      \return          1  Function failed
     */
    static inline uint32_t STREXW(uint32_t value, volatile uint32_t *addr)
    {
       uint32_t result;

       __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
       return(result);
    }
    /**
      \brief   Remove the exclusive lock
      \details Removes the exclusive lock which is created by LDREX.
     */
    static inline void CLREX(void)
    {
      __asm volatile ("clrex" ::: "memory");
    }
    /**
      \brief   Signed Saturate
      \details Saturates a signed value.
      \param [in]  value  Value to be saturated
      \param [in]    sat  Bit position to saturate to (1..32)
      \return             Saturated value
     */
    #define SSAT(ARG1,ARG2) \
    ({                          \
      uint32_t __RES, __ARG1 = (ARG1); \
      __asm ("ssat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
      __RES; \
     })
    /**
      \brief   Unsigned Saturate
      \details Saturates an unsigned value.
      \param [in]  value  Value to be saturated
      \param [in]    sat  Bit position to saturate to (0..31)
      \return             Saturated value
     */
    #define USAT(ARG1,ARG2) \
    ({                          \
      uint32_t __RES, __ARG1 = (ARG1); \
      __asm ("usat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
      __RES; \
     })
    /**
      \brief   Rotate Right with Extend (32 bit)
      \details Moves each bit of a bitstring right by one bit.
               The carry input is shifted in at the left end of the bitstring.
      \param [in]    value  Value to rotate
      \return               Rotated value
     */
    static inline uint32_t RRX(uint32_t value)
    {
      uint32_t result;

      __asm volatile ("rrx %0, %1" : "=r" (result) : "r" (value) );
      return(result);
    }
    /**
      \brief   LDRT Unprivileged (8 bit)
      \details Executes a Unprivileged LDRT instruction for 8 bit value.
      \param [in]    ptr  Pointer to data
      \return             value of type uint8_t at (*ptr)
     */
    static inline uint8_t LDRBT(volatile uint8_t *addr)
    {
        uint32_t result;
    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
       __asm volatile ("ldrbt %0, %1" : "=r" (result) : "Q" (*addr) );
    #else
        /* Prior to GCC 4.8, "Q" will be expanded to [rx, #0] which is not
           accepted by assembler. So has to use following less efficient pattern.
        */
       __asm volatile ("ldrbt %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
    #endif
       return ((uint8_t) result);    /* Add explicit type cast here */
    }
    /**
      \brief   LDRT Unprivileged (16 bit)
      \details Executes a Unprivileged LDRT instruction for 16 bit values.
      \param [in]    ptr  Pointer to data
      \return        value of type uint16_t at (*ptr)
     */
    static inline uint16_t LDRHT(volatile uint16_t *addr)
    {
        uint32_t result;
    #if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
       __asm volatile ("ldrht %0, %1" : "=r" (result) : "Q" (*addr) );
    #else
        /* Prior to GCC 4.8, "Q" will be expanded to [rx, #0] which is not
           accepted by assembler. So has to use following less efficient pattern.
        */
       __asm volatile ("ldrht %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );
    #endif
       return ((uint16_t) result);    /* Add explicit type cast here */
    }
    /**
      \brief   LDRT Unprivileged (32 bit)
      \details Executes a Unprivileged LDRT instruction for 32 bit values.
      \param [in]    ptr  Pointer to data
      \return        value of type uint32_t at (*ptr)
     */
    static inline uint32_t LDRT(volatile uint32_t *addr)
    {
        uint32_t result;
       __asm volatile ("ldrt %0, %1" : "=r" (result) : "Q" (*addr) );
       return(result);
    }
    /**
      \brief   STRT Unprivileged (8 bit)
      \details Executes a Unprivileged STRT instruction for 8 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
     */
    static inline void STRBT(uint8_t value, volatile uint8_t *addr)
    {
       __asm volatile ("strbt %1, %0" : "=Q" (*addr) : "r" ((uint32_t)value) );
    }
    /**
      \brief   STRT Unprivileged (16 bit)
      \details Executes a Unprivileged STRT instruction for 16 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
     */
    static inline void STRHT(uint16_t value, volatile uint16_t *addr)
    {
       __asm volatile ("strht %1, %0" : "=Q" (*addr) : "r" ((uint32_t)value) );
    }
    /**
      \brief   STRT Unprivileged (32 bit)
      \details Executes a Unprivileged STRT instruction for 32 bit values.
      \param [in]  value  Value to store
      \param [in]    ptr  Pointer to location
     */
    static inline void STRT(uint32_t value, volatile uint32_t *addr)
    {
       __asm volatile ("strt %1, %0" : "=Q" (*addr) : "r" (value) );
    }
    #endif /* (__CORTEX_M >= 0x03U) || (__CORTEX_SC >= 300U) */

    /*@}*/ /* end of group CMSIS_Core_InstructionInterface */
};


/* ###################  Compiler specific Intrinsics  ########################### */
/** \defgroup CMSIS_SIMD_intrinsics CMSIS SIMD Intrinsics
  Access to dedicated SIMD instructions
  @{
*/

#if (__CORTEX_M >= 0x04U)  /* only for Cortex-M4 and above */

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("sadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHADD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhadd8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}


__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("ssub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __USUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("usub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHSUB8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhsub8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}


__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("sadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHADD16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhadd16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("ssub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __USUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("usub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHSUB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhsub16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("sasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHASX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhasx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("ssax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __QSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("qsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SHSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("shsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __USAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("usax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UQSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uqsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UHSAX(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uhsax %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __USAD8(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("usad8 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __USADA8(uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __ASM volatile ("usada8 %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

#define __SSAT16(ARG1,ARG2) \
({                          \
  int32_t __RES, __ARG1 = (ARG1); \
  __ASM ("ssat16 %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
  __RES; \
 })

#define __USAT16(ARG1,ARG2) \
({                          \
  uint32_t __RES, __ARG1 = (ARG1); \
  __ASM ("usat16 %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
  __RES; \
 })

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UXTB16(uint32_t op1)
{
  uint32_t result;

  __ASM volatile ("uxtb16 %0, %1" : "=r" (result) : "r" (op1));
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __UXTAB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("uxtab16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SXTB16(uint32_t op1)
{
  uint32_t result;

  __ASM volatile ("sxtb16 %0, %1" : "=r" (result) : "r" (op1));
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SXTAB16(uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("sxtab16 %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMUAD  (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("smuad %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMUADX (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("smuadx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMLAD (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __ASM volatile ("smlad %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMLADX (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __ASM volatile ("smladx %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint64_t __SMLALD (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;

#ifndef __ARMEB__   /* Little endian */
  __ASM volatile ("smlald %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );
#else               /* Big endian */
  __ASM volatile ("smlald %0, %1, %2, %3" : "=r" (llr.w32[1]), "=r" (llr.w32[0]): "r" (op1), "r" (op2) , "0" (llr.w32[1]), "1" (llr.w32[0]) );
#endif

  return(llr.w64);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint64_t __SMLALDX (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;

#ifndef __ARMEB__   /* Little endian */
  __ASM volatile ("smlaldx %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );
#else               /* Big endian */
  __ASM volatile ("smlaldx %0, %1, %2, %3" : "=r" (llr.w32[1]), "=r" (llr.w32[0]): "r" (op1), "r" (op2) , "0" (llr.w32[1]), "1" (llr.w32[0]) );
#endif

  return(llr.w64);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMUSD  (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("smusd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMUSDX (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("smusdx %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMLSD (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __ASM volatile ("smlsd %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMLSDX (uint32_t op1, uint32_t op2, uint32_t op3)
{
  uint32_t result;

  __ASM volatile ("smlsdx %0, %1, %2, %3" : "=r" (result) : "r" (op1), "r" (op2), "r" (op3) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint64_t __SMLSLD (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;

#ifndef __ARMEB__   /* Little endian */
  __ASM volatile ("smlsld %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );
#else               /* Big endian */
  __ASM volatile ("smlsld %0, %1, %2, %3" : "=r" (llr.w32[1]), "=r" (llr.w32[0]): "r" (op1), "r" (op2) , "0" (llr.w32[1]), "1" (llr.w32[0]) );
#endif

  return(llr.w64);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint64_t __SMLSLDX (uint32_t op1, uint32_t op2, uint64_t acc)
{
  union llreg_u{
    uint32_t w32[2];
    uint64_t w64;
  } llr;
  llr.w64 = acc;

#ifndef __ARMEB__   /* Little endian */
  __ASM volatile ("smlsldx %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) );
#else               /* Big endian */
  __ASM volatile ("smlsldx %0, %1, %2, %3" : "=r" (llr.w32[1]), "=r" (llr.w32[0]): "r" (op1), "r" (op2) , "0" (llr.w32[1]), "1" (llr.w32[0]) );
#endif

  return(llr.w64);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SEL  (uint32_t op1, uint32_t op2)
{
  uint32_t result;

  __ASM volatile ("sel %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE  int32_t __QADD( int32_t op1,  int32_t op2)
{
  int32_t result;

  __ASM volatile ("qadd %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

__attribute__( ( always_inline ) ) __STATIC_INLINE  int32_t __QSUB( int32_t op1,  int32_t op2)
{
  int32_t result;

  __ASM volatile ("qsub %0, %1, %2" : "=r" (result) : "r" (op1), "r" (op2) );
  return(result);
}

#define __PKHBT(ARG1,ARG2,ARG3) \
({                          \
  uint32_t __RES, __ARG1 = (ARG1), __ARG2 = (ARG2); \
  __ASM ("pkhbt %0, %1, %2, lsl %3" : "=r" (__RES) :  "r" (__ARG1), "r" (__ARG2), "I" (ARG3)  ); \
  __RES; \
 })

#define __PKHTB(ARG1,ARG2,ARG3) \
({                          \
  uint32_t __RES, __ARG1 = (ARG1), __ARG2 = (ARG2); \
  if (ARG3 == 0) \
    __ASM ("pkhtb %0, %1, %2" : "=r" (__RES) :  "r" (__ARG1), "r" (__ARG2)  ); \
  else \
    __ASM ("pkhtb %0, %1, %2, asr %3" : "=r" (__RES) :  "r" (__ARG1), "r" (__ARG2), "I" (ARG3)  ); \
  __RES; \
 })

__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __SMMLA (int32_t op1, int32_t op2, int32_t op3)
{
 int32_t result;

 __ASM volatile ("smmla %0, %1, %2, %3" : "=r" (result): "r"  (op1), "r" (op2), "r" (op3) );
 return(result);
}

#endif /* (__CORTEX_M >= 0x04) */
/*@} end of group CMSIS_SIMD_intrinsics */


#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif /* __CMSIS_GCC_H */
