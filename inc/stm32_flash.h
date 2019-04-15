#ifndef STM32_FLASH_H
#define STM32_FLASH_H

/*
 * Based on HAL v1.21.0(F4), v1.6.1(F1)
 * */

#include "stm32_inc.h"

#define FLASH_ERROR_NONE         0x00000000U    /*!< No error                      */
#define FLASH_ERROR_RD           0x00000001U    /*!< Read Protection error         */
#define FLASH_ERROR_PGS          0x00000002U    /*!< Programming Sequence error    */
#define FLASH_ERROR_PGP          0x00000004U    /*!< Programming Parallelism error */
#define FLASH_ERROR_PGA          0x00000008U    /*!< Programming Alignment error   */
#define FLASH_ERROR_WRP          0x00000010U    /*!< Write protection error        */
#define FLASH_ERROR_OPERATION    0x00000020U    /*!< Operation Error               */

enum class FLASH_TypeProgram
{
	#if defined(STM32F429xx) || defined(STM32F407xx)
    BYTE,
	#endif
    HALF_WORD,
    WORD,
    DOUBLE_WORD,
};

#define FLASH_FLAG_EOP                 FLASH_SR_EOP            /*!< FLASH End of Operation flag               */
#define FLASH_FLAG_OPERR               FLASH_SR_SOP            /*!< FLASH operation Error flag                */
#ifdef FLASH_SR_WRPERR
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR         /*!< FLASH Write protected error flag          */
#endif
#define FLASH_FLAG_PGAERR              FLASH_SR_PGAERR         /*!< FLASH Programming Alignment error flag    */
#define FLASH_FLAG_PGPERR              FLASH_SR_PGPERR         /*!< FLASH Programming Parallelism error flag  */
#define FLASH_FLAG_PGSERR              FLASH_SR_PGSERR         /*!< FLASH Programming Sequence error flag     */
#if defined(FLASH_SR_RDERR)
#define FLASH_FLAG_RDERR               FLASH_SR_RDERR          /*!< Read Protection error flag (PCROP)        */
#endif /* FLASH_SR_RDERR */
#define FLASH_FLAG_BSY                 FLASH_SR_BSY            /*!< FLASH Busy flag                           */

#define FLASH_IT_EOP                   FLASH_CR_EOPIE          /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_ERR                   0x02000000U             /*!< Error Interrupt source                  */

#define FLASH_PSIZE_BYTE           0x00000000U
#define FLASH_PSIZE_HALF_WORD      0x00000100U
#define FLASH_PSIZE_WORD           0x00000200U
#define FLASH_PSIZE_DOUBLE_WORD    0x00000300U
#define CR_PSIZE_MASK              0xFFFFFCFFU

#ifndef RDP_KEY
#define RDP_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               0x45670123U
#define FLASH_KEY2               0xCDEF89ABU
#endif
#define FLASH_OPT_KEY1           0x08192A3BU
#define FLASH_OPT_KEY2           0x4C5D6E7FU

enum class FLASH_TypeErase
{
    SECTORS,
    MASS_ERASE,
};

enum class FLASH_VoltageRange
{
    V_1P8_TO_2P1 = 0,
    V_2P1_TO_2P7 = 1,
    V_2P7_TO_3P6 = 2,
    V_2P7_TO_3P6_EXT = 3,
};

#define OB_WRPSTATE_DISABLE       0x00000000U  /*!< Disable the write protection of the desired bank 1 sectors */
#define OB_WRPSTATE_ENABLE        0x00000001U  /*!< Enable the write protection of the desired bank 1 sectors  */

#define OPTIONBYTE_WRP        0x00000001U  /*!< WRP option byte configuration  */
#define OPTIONBYTE_RDP        0x00000002U  /*!< RDP option byte configuration  */
#define OPTIONBYTE_USER       0x00000004U  /*!< USER option byte configuration */
#define OPTIONBYTE_BOR        0x00000008U  /*!< BOR option byte configuration  */

#ifdef STM32F1
#define OB_RDP_LEVEL_0            ((uint8_t)0xA5)
#define OB_RDP_LEVEL_1            ((uint8_t)0x00)

#define OB_IWDG_SW                ((uint16_t)0x0001)  /*!< Software IWDG selected */
#define OB_IWDG_HW                ((uint16_t)0x0000)  /*!< Hardware IWDG selected */

#define OB_STOP_NO_RST            ((uint16_t)0x0002) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST               ((uint16_t)0x0000) /*!< Reset generated when entering in STOP */

#define OB_STDBY_NO_RST           ((uint16_t)0x0004) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST              ((uint16_t)0x0000) /*!< Reset generated when entering in STANDBY */

#if defined(FLASH_BANK2_END)
/** @defgroup FLASHEx_OB_BOOT1 Option Byte BOOT1
  * @{
  */
#define OB_BOOT1_RESET            ((uint16_t)0x0000) /*!< BOOT1 Reset */
#define OB_BOOT1_SET              ((uint16_t)0x0008) /*!< BOOT1 Set */
/**
  * @}
  */
#endif /* FLASH_BANK2_END */

#else // STM32F1

#define OB_RDP_LEVEL_0   ((uint8_t)0xAA)
#define OB_RDP_LEVEL_1   ((uint8_t)0x55)
#define OB_RDP_LEVEL_2   ((uint8_t)0xCC) /*!< Warning: When enabling read protection level 2
                                              it s no more possible to go back to level 1 or 0 */
#define OB_IWDG_SW                     ((uint8_t)0x20)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */

#define OB_STOP_NO_RST                 ((uint8_t)0x40) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP    */

#define OB_STDBY_NO_RST                ((uint8_t)0x80) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY    */

#endif // STM32F1

#define OB_BOR_LEVEL3          ((uint8_t)0x00)  /*!< Supply voltage ranges from 2.70 to 3.60 V */
#define OB_BOR_LEVEL2          ((uint8_t)0x04)  /*!< Supply voltage ranges from 2.40 to 2.70 V */
#define OB_BOR_LEVEL1          ((uint8_t)0x08)  /*!< Supply voltage ranges from 2.10 to 2.40 V */
#define OB_BOR_OFF             ((uint8_t)0x0C)  /*!< Supply voltage ranges from 1.62 to 2.10 V */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define OB_PCROP_STATE_DISABLE       0x00000000U  /*!< Disable PCROP */
#define OB_PCROP_STATE_ENABLE        0x00000001U  /*!< Enable PCROP  */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F401xC || STM32F401xE ||\
          STM32F410xx || STM32F411xE || STM32F446xx || STM32F469xx || STM32F479xx || STM32F412Zx ||\
          STM32F412Vx || STM32F412Rx || STM32F412Cx || STM32F413xx || STM32F423xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OPTIONBYTE_PCROP        0x00000001U  /*!< PCROP option byte configuration      */
#define OPTIONBYTE_BOOTCONFIG   0x00000002U  /*!< BOOTConfig option byte configuration */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define OPTIONBYTE_PCROP        0x00000001U  /*!<PCROP option byte configuration */
#endif /* STM32F401xC || STM32F401xE || STM32F410xx || STM32F411xE || STM32F446xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx ||
          STM32F413xx || STM32F423xx */

#if defined(STM32F1)
#if   defined(FLASH_ACR_LATENCY)
#define FLASH_LATENCY_0            0x00000000U               /*!< FLASH Zero Latency cycle */
#define FLASH_LATENCY_1            FLASH_ACR_LATENCY_0       /*!< FLASH One Latency cycle */
#define FLASH_LATENCY_2            FLASH_ACR_LATENCY_1       /*!< FLASH Two Latency cycles */
#else
#define FLASH_LATENCY_0            0x00000000U    /*!< FLASH Zero Latency cycle */
#endif // FLASH_ACR_LATENCY
#endif // STM32F1

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS   /*!< FLASH Zero Latency cycle      */
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS   /*!< FLASH One Latency cycle       */
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS   /*!< FLASH Two Latency cycles      */
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS   /*!< FLASH Three Latency cycles    */
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS   /*!< FLASH Four Latency cycles     */
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS   /*!< FLASH Five Latency cycles     */
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS   /*!< FLASH Six Latency cycles      */
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS   /*!< FLASH Seven Latency cycles    */
#define FLASH_LATENCY_8                FLASH_ACR_LATENCY_8WS   /*!< FLASH Eight Latency cycles    */
#define FLASH_LATENCY_9                FLASH_ACR_LATENCY_9WS   /*!< FLASH Nine Latency cycles     */
#define FLASH_LATENCY_10               FLASH_ACR_LATENCY_10WS  /*!< FLASH Ten Latency cycles      */
#define FLASH_LATENCY_11               FLASH_ACR_LATENCY_11WS  /*!< FLASH Eleven Latency cycles   */
#define FLASH_LATENCY_12               FLASH_ACR_LATENCY_12WS  /*!< FLASH Twelve Latency cycles   */
#define FLASH_LATENCY_13               FLASH_ACR_LATENCY_13WS  /*!< FLASH Thirteen Latency cycles */
#define FLASH_LATENCY_14               FLASH_ACR_LATENCY_14WS  /*!< FLASH Fourteen Latency cycles */
#define FLASH_LATENCY_15               FLASH_ACR_LATENCY_15WS  /*!< FLASH Fifteen Latency cycles  */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F446xx || STM32F469xx || STM32F479xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS   /*!< FLASH Zero Latency cycle      */
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS   /*!< FLASH One Latency cycle       */
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS   /*!< FLASH Two Latency cycles      */
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS   /*!< FLASH Three Latency cycles    */
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS   /*!< FLASH Four Latency cycles     */
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS   /*!< FLASH Five Latency cycles     */
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS   /*!< FLASH Six Latency cycles      */
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS   /*!< FLASH Seven Latency cycles    */
#endif /* STM32F40xxx || STM32F41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx ||
          STM32F413xx || STM32F423xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_BANK_1     1U /*!< Bank 1   */
#define FLASH_BANK_2     2U /*!< Bank 2   */
#define FLASH_BANK_BOTH  ((uint32_t)FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank1 and Bank2  */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define FLASH_BANK_1     1U /*!< Bank 1   */
#endif /* STM32F40xxx || STM32F41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F446xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx
          STM32F413xx || STM32F423xx */

#if defined(STM32F1)
#if defined(FLASH_BANK2_END)
#define FLASH_BANK_1     1U /*!< Bank 1   */
#define FLASH_BANK_2     2U /*!< Bank 2   */
#define FLASH_BANK_BOTH  ((uint32_t)FLASH_BANK_1 | FLASH_BANK_2) /*!< Bank1 and Bank2  */
#endif // STM32F1

#else
#define FLASH_BANK_1     1U /*!< Bank 1   */
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_MER_BIT     (FLASH_CR_MER1 | FLASH_CR_MER2) /*!< 2 MER bits here to clear */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define FLASH_MER_BIT     (FLASH_CR_MER) /*!< only 1 MER Bit */
#endif /* STM32F40xxx || STM32F41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F446xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx
          STM32F413xx || STM32F423xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#define FLASH_SECTOR_12    12U /*!< Sector Number 12  */
#define FLASH_SECTOR_13    13U /*!< Sector Number 13  */
#define FLASH_SECTOR_14    14U /*!< Sector Number 14  */
#define FLASH_SECTOR_15    15U /*!< Sector Number 15  */
#define FLASH_SECTOR_16    16U /*!< Sector Number 16  */
#define FLASH_SECTOR_17    17U /*!< Sector Number 17  */
#define FLASH_SECTOR_18    18U /*!< Sector Number 18  */
#define FLASH_SECTOR_19    19U /*!< Sector Number 19  */
#define FLASH_SECTOR_20    20U /*!< Sector Number 20  */
#define FLASH_SECTOR_21    21U /*!< Sector Number 21  */
#define FLASH_SECTOR_22    22U /*!< Sector Number 22  */
#define FLASH_SECTOR_23    23U /*!< Sector Number 23  */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F413xx) || defined(STM32F423xx)
#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#define FLASH_SECTOR_12    12U /*!< Sector Number 12  */
#define FLASH_SECTOR_13    13U /*!< Sector Number 13  */
#define FLASH_SECTOR_14    14U /*!< Sector Number 14  */
#define FLASH_SECTOR_15    15U /*!< Sector Number 15  */
#endif /* STM32F413xx || STM32F423xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx */

#if defined(STM32F401xC)
#define FLASH_SECTOR_0     0U /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U /*!< Sector Number 5   */
#endif /* STM32F401xC */

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define FLASH_SECTOR_0     0U /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U /*!< Sector Number 4   */
#endif /* STM32F410Tx || STM32F410Cx || STM32F410Rx */

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define FLASH_SECTOR_0     0U /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U /*!< Sector Number 7   */
#endif /* STM32F401xE || STM32F411xE || STM32F446xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       0x00000020U /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_6       0x00000040U /*!< Write protection of Sector6     */
#define OB_WRP_SECTOR_7       0x00000080U /*!< Write protection of Sector7     */
#define OB_WRP_SECTOR_8       0x00000100U /*!< Write protection of Sector8     */
#define OB_WRP_SECTOR_9       0x00000200U /*!< Write protection of Sector9     */
#define OB_WRP_SECTOR_10      0x00000400U /*!< Write protection of Sector10    */
#define OB_WRP_SECTOR_11      0x00000800U /*!< Write protection of Sector11    */
#define OB_WRP_SECTOR_12      0x00000001U << 12U /*!< Write protection of Sector12    */
#define OB_WRP_SECTOR_13      0x00000002U << 12U /*!< Write protection of Sector13    */
#define OB_WRP_SECTOR_14      0x00000004U << 12U /*!< Write protection of Sector14    */
#define OB_WRP_SECTOR_15      0x00000008U << 12U /*!< Write protection of Sector15    */
#define OB_WRP_SECTOR_16      0x00000010U << 12U /*!< Write protection of Sector16    */
#define OB_WRP_SECTOR_17      0x00000020U << 12U /*!< Write protection of Sector17    */
#define OB_WRP_SECTOR_18      0x00000040U << 12U /*!< Write protection of Sector18    */
#define OB_WRP_SECTOR_19      0x00000080U << 12U /*!< Write protection of Sector19    */
#define OB_WRP_SECTOR_20      0x00000100U << 12U /*!< Write protection of Sector20    */
#define OB_WRP_SECTOR_21      0x00000200U << 12U /*!< Write protection of Sector21    */
#define OB_WRP_SECTOR_22      0x00000400U << 12U /*!< Write protection of Sector22    */
#define OB_WRP_SECTOR_23      0x00000800U << 12U /*!< Write protection of Sector23    */
#define OB_WRP_SECTOR_All     0x00000FFFU << 12U /*!< Write protection of all Sectors */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F413xx) || defined(STM32F423xx)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       0x00000020U /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_6       0x00000040U /*!< Write protection of Sector6     */
#define OB_WRP_SECTOR_7       0x00000080U /*!< Write protection of Sector7     */
#define OB_WRP_SECTOR_8       0x00000100U /*!< Write protection of Sector8     */
#define OB_WRP_SECTOR_9       0x00000200U /*!< Write protection of Sector9     */
#define OB_WRP_SECTOR_10      0x00000400U /*!< Write protection of Sector10    */
#define OB_WRP_SECTOR_11      0x00000800U /*!< Write protection of Sector11    */
#define OB_WRP_SECTOR_12      0x00001000U /*!< Write protection of Sector12    */
#define OB_WRP_SECTOR_13      0x00002000U /*!< Write protection of Sector13    */
#define OB_WRP_SECTOR_14      0x00004000U /*!< Write protection of Sector14    */
#define OB_WRP_SECTOR_15      0x00004000U /*!< Write protection of Sector15    */
#define OB_WRP_SECTOR_All     0x00007FFFU /*!< Write protection of all Sectors */
#endif /* STM32F413xx || STM32F423xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       0x00000020U /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_6       0x00000040U /*!< Write protection of Sector6     */
#define OB_WRP_SECTOR_7       0x00000080U /*!< Write protection of Sector7     */
#define OB_WRP_SECTOR_8       0x00000100U /*!< Write protection of Sector8     */
#define OB_WRP_SECTOR_9       0x00000200U /*!< Write protection of Sector9     */
#define OB_WRP_SECTOR_10      0x00000400U /*!< Write protection of Sector10    */
#define OB_WRP_SECTOR_11      0x00000800U /*!< Write protection of Sector11    */
#define OB_WRP_SECTOR_All     0x00000FFFU /*!< Write protection of all Sectors */
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx */

#if defined(STM32F401xC)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       0x00000020U /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_All     0x00000FFFU /*!< Write protection of all Sectors */
#endif /* STM32F401xC */

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_All     0x00000FFFU /*!< Write protection of all Sectors */
#endif /* STM32F410Tx || STM32F410Cx || STM32F410Rx */

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define OB_WRP_SECTOR_0       0x00000001U /*!< Write protection of Sector0     */
#define OB_WRP_SECTOR_1       0x00000002U /*!< Write protection of Sector1     */
#define OB_WRP_SECTOR_2       0x00000004U /*!< Write protection of Sector2     */
#define OB_WRP_SECTOR_3       0x00000008U /*!< Write protection of Sector3     */
#define OB_WRP_SECTOR_4       0x00000010U /*!< Write protection of Sector4     */
#define OB_WRP_SECTOR_5       0x00000020U /*!< Write protection of Sector5     */
#define OB_WRP_SECTOR_6       0x00000040U /*!< Write protection of Sector6     */
#define OB_WRP_SECTOR_7       0x00000080U /*!< Write protection of Sector7     */
#define OB_WRP_SECTOR_All     0x00000FFFU /*!< Write protection of all Sectors */
#endif /* STM32F401xE || STM32F411xE || STM32F446xx */

/* STM32 Low and Medium density devices */
#if  defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6) \
  || defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) \
  || defined(STM32F103xB)
#define OB_WRP_PAGES0TO3               0x00000001U /*!< Write protection of page 0 to 3 */
#define OB_WRP_PAGES4TO7               0x00000002U /*!< Write protection of page 4 to 7 */
#define OB_WRP_PAGES8TO11              0x00000004U /*!< Write protection of page 8 to 11 */
#define OB_WRP_PAGES12TO15             0x00000008U /*!< Write protection of page 12 to 15 */
#define OB_WRP_PAGES16TO19             0x00000010U /*!< Write protection of page 16 to 19 */
#define OB_WRP_PAGES20TO23             0x00000020U /*!< Write protection of page 20 to 23 */
#define OB_WRP_PAGES24TO27             0x00000040U /*!< Write protection of page 24 to 27 */
#define OB_WRP_PAGES28TO31             0x00000080U /*!< Write protection of page 28 to 31 */
#endif /* STM32F101x6 || STM32F102x6 || STM32F103x6 */
       /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
       
/* STM32 Medium-density devices */
#if  defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
#define OB_WRP_PAGES32TO35             0x00000100U   /*!< Write protection of page 32 to 35 */
#define OB_WRP_PAGES36TO39             0x00000200U   /*!< Write protection of page 36 to 39 */
#define OB_WRP_PAGES40TO43             0x00000400U   /*!< Write protection of page 40 to 43 */
#define OB_WRP_PAGES44TO47             0x00000800U   /*!< Write protection of page 44 to 47 */
#define OB_WRP_PAGES48TO51             0x00001000U   /*!< Write protection of page 48 to 51 */
#define OB_WRP_PAGES52TO55             0x00002000U   /*!< Write protection of page 52 to 55 */
#define OB_WRP_PAGES56TO59             0x00004000U   /*!< Write protection of page 56 to 59 */
#define OB_WRP_PAGES60TO63             0x00008000U   /*!< Write protection of page 60 to 63 */
#define OB_WRP_PAGES64TO67             0x00010000U   /*!< Write protection of page 64 to 67 */
#define OB_WRP_PAGES68TO71             0x00020000U   /*!< Write protection of page 68 to 71 */
#define OB_WRP_PAGES72TO75             0x00040000U   /*!< Write protection of page 72 to 75 */
#define OB_WRP_PAGES76TO79             0x00080000U   /*!< Write protection of page 76 to 79 */
#define OB_WRP_PAGES80TO83             0x00100000U   /*!< Write protection of page 80 to 83 */
#define OB_WRP_PAGES84TO87             0x00200000U   /*!< Write protection of page 84 to 87 */
#define OB_WRP_PAGES88TO91             0x00400000U   /*!< Write protection of page 88 to 91 */
#define OB_WRP_PAGES92TO95             0x00800000U   /*!< Write protection of page 92 to 95 */
#define OB_WRP_PAGES96TO99             0x01000000U   /*!< Write protection of page 96 to 99 */
#define OB_WRP_PAGES100TO103           0x02000000U   /*!< Write protection of page 100 to 103 */
#define OB_WRP_PAGES104TO107           0x04000000U   /*!< Write protection of page 104 to 107 */
#define OB_WRP_PAGES108TO111           0x08000000U   /*!< Write protection of page 108 to 111 */
#define OB_WRP_PAGES112TO115           0x10000000U   /*!< Write protection of page 112 to 115 */
#define OB_WRP_PAGES116TO119           0x20000000U   /*!< Write protection of page 115 to 119 */
#define OB_WRP_PAGES120TO123           0x40000000U   /*!< Write protection of page 120 to 123 */
#define OB_WRP_PAGES124TO127           0x80000000U    /*!< Write protection of page 124 to 127 */
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */


/* STM32 High-density, XL-density and Connectivity line devices */
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) \
  || defined(STM32F101xG) || defined(STM32F103xG) \
  || defined(STM32F105xC) || defined(STM32F107xC)
#define OB_WRP_PAGES0TO1               0x00000001U  /*!< Write protection of page 0 TO 1 */
#define OB_WRP_PAGES2TO3               0x00000002U  /*!< Write protection of page 2 TO 3 */
#define OB_WRP_PAGES4TO5               0x00000004U  /*!< Write protection of page 4 TO 5 */
#define OB_WRP_PAGES6TO7               0x00000008U  /*!< Write protection of page 6 TO 7 */
#define OB_WRP_PAGES8TO9               0x00000010U  /*!< Write protection of page 8 TO 9 */
#define OB_WRP_PAGES10TO11             0x00000020U  /*!< Write protection of page 10 TO 11 */
#define OB_WRP_PAGES12TO13             0x00000040U  /*!< Write protection of page 12 TO 13 */
#define OB_WRP_PAGES14TO15             0x00000080U  /*!< Write protection of page 14 TO 15 */
#define OB_WRP_PAGES16TO17             0x00000100U  /*!< Write protection of page 16 TO 17 */
#define OB_WRP_PAGES18TO19             0x00000200U  /*!< Write protection of page 18 TO 19 */
#define OB_WRP_PAGES20TO21             0x00000400U  /*!< Write protection of page 20 TO 21 */
#define OB_WRP_PAGES22TO23             0x00000800U  /*!< Write protection of page 22 TO 23 */
#define OB_WRP_PAGES24TO25             0x00001000U  /*!< Write protection of page 24 TO 25 */
#define OB_WRP_PAGES26TO27             0x00002000U  /*!< Write protection of page 26 TO 27 */
#define OB_WRP_PAGES28TO29             0x00004000U  /*!< Write protection of page 28 TO 29 */
#define OB_WRP_PAGES30TO31             0x00008000U  /*!< Write protection of page 30 TO 31 */
#define OB_WRP_PAGES32TO33             0x00010000U  /*!< Write protection of page 32 TO 33 */
#define OB_WRP_PAGES34TO35             0x00020000U  /*!< Write protection of page 34 TO 35 */
#define OB_WRP_PAGES36TO37             0x00040000U  /*!< Write protection of page 36 TO 37 */
#define OB_WRP_PAGES38TO39             0x00080000U  /*!< Write protection of page 38 TO 39 */
#define OB_WRP_PAGES40TO41             0x00100000U  /*!< Write protection of page 40 TO 41 */
#define OB_WRP_PAGES42TO43             0x00200000U  /*!< Write protection of page 42 TO 43 */
#define OB_WRP_PAGES44TO45             0x00400000U  /*!< Write protection of page 44 TO 45 */
#define OB_WRP_PAGES46TO47             0x00800000U  /*!< Write protection of page 46 TO 47 */
#define OB_WRP_PAGES48TO49             0x01000000U  /*!< Write protection of page 48 TO 49 */
#define OB_WRP_PAGES50TO51             0x02000000U  /*!< Write protection of page 50 TO 51 */
#define OB_WRP_PAGES52TO53             0x04000000U  /*!< Write protection of page 52 TO 53 */
#define OB_WRP_PAGES54TO55             0x08000000U  /*!< Write protection of page 54 TO 55 */
#define OB_WRP_PAGES56TO57             0x10000000U  /*!< Write protection of page 56 TO 57 */
#define OB_WRP_PAGES58TO59             0x20000000U  /*!< Write protection of page 58 TO 59 */
#define OB_WRP_PAGES60TO61             0x40000000U  /*!< Write protection of page 60 TO 61 */
#define OB_WRP_PAGES62TO127            0x80000000U   /*!< Write protection of page 62 TO 127 */
#define OB_WRP_PAGES62TO255            0x80000000U   /*!< Write protection of page 62 TO 255 */
#define OB_WRP_PAGES62TO511            0x80000000U   /*!< Write protection of page 62 TO 511 */
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
       /* STM32F101xG || STM32F103xG */ 
       /* STM32F105xC || STM32F107xC */

#define OB_WRP_ALLPAGES                0xFFFFFFFFU  /*!< Write protection of all Pages */
 
/* Low Density */
#if  defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6)
#define OB_WRP_PAGES0TO31MASK          0x000000FFU 
#endif /* STM32F101x6 || STM32F102x6 || STM32F103x6 */

/* Medium Density */
#if  defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
#define OB_WRP_PAGES0TO31MASK          0x000000FFU
#define OB_WRP_PAGES32TO63MASK         0x0000FF00U
#define OB_WRP_PAGES64TO95MASK         0x00FF0000U
#define OB_WRP_PAGES96TO127MASK        0xFF000000U
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB*/
       
/* High Density */
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE)  
#define OB_WRP_PAGES0TO15MASK          0x000000FFU
#define OB_WRP_PAGES16TO31MASK         0x0000FF00U
#define OB_WRP_PAGES32TO47MASK         0x00FF0000U
#define OB_WRP_PAGES48TO255MASK        0xFF000000U
#endif /* STM32F100xE || STM32F101xE || STM32F103xE */

/* XL Density */
#if  defined(STM32F101xG) || defined(STM32F103xG) 
#define OB_WRP_PAGES0TO15MASK          0x000000FFU
#define OB_WRP_PAGES16TO31MASK         0x0000FF00U
#define OB_WRP_PAGES32TO47MASK         0x00FF0000U
#define OB_WRP_PAGES48TO511MASK        0xFF000000U
#endif /* STM32F101xG || STM32F103xG */
      
/* Connectivity line devices */
#if defined(STM32F105xC) || defined(STM32F107xC)
#define OB_WRP_PAGES0TO15MASK          0x000000FFU
#define OB_WRP_PAGES16TO31MASK         0x0000FF00U
#define OB_WRP_PAGES32TO47MASK         0x00FF0000U
#define OB_WRP_PAGES48TO127MASK        0xFF000000U
#endif /* STM32F105xC || STM32F107xC */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_PCROP_SECTOR_0        0x00000001U /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_SECTOR_1        0x00000002U /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_SECTOR_2        0x00000004U /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_SECTOR_3        0x00000008U /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_SECTOR_4        0x00000010U /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_SECTOR_5        0x00000020U /*!< PC Read/Write protection of Sector5      */
#define OB_PCROP_SECTOR_6        0x00000040U /*!< PC Read/Write protection of Sector6      */
#define OB_PCROP_SECTOR_7        0x00000080U /*!< PC Read/Write protection of Sector7      */
#define OB_PCROP_SECTOR_8        0x00000100U /*!< PC Read/Write protection of Sector8      */
#define OB_PCROP_SECTOR_9        0x00000200U /*!< PC Read/Write protection of Sector9      */
#define OB_PCROP_SECTOR_10       0x00000400U /*!< PC Read/Write protection of Sector10     */
#define OB_PCROP_SECTOR_11       0x00000800U /*!< PC Read/Write protection of Sector11     */
#define OB_PCROP_SECTOR_12       0x00000001U /*!< PC Read/Write protection of Sector12     */
#define OB_PCROP_SECTOR_13       0x00000002U /*!< PC Read/Write protection of Sector13     */
#define OB_PCROP_SECTOR_14       0x00000004U /*!< PC Read/Write protection of Sector14     */
#define OB_PCROP_SECTOR_15       0x00000008U /*!< PC Read/Write protection of Sector15     */
#define OB_PCROP_SECTOR_16       0x00000010U /*!< PC Read/Write protection of Sector16     */
#define OB_PCROP_SECTOR_17       0x00000020U /*!< PC Read/Write protection of Sector17     */
#define OB_PCROP_SECTOR_18       0x00000040U /*!< PC Read/Write protection of Sector18     */
#define OB_PCROP_SECTOR_19       0x00000080U /*!< PC Read/Write protection of Sector19     */
#define OB_PCROP_SECTOR_20       0x00000100U /*!< PC Read/Write protection of Sector20     */
#define OB_PCROP_SECTOR_21       0x00000200U /*!< PC Read/Write protection of Sector21     */
#define OB_PCROP_SECTOR_22       0x00000400U /*!< PC Read/Write protection of Sector22     */
#define OB_PCROP_SECTOR_23       0x00000800U /*!< PC Read/Write protection of Sector23     */
#define OB_PCROP_SECTOR_All      0x00000FFFU /*!< PC Read/Write protection of all Sectors  */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F413xx) || defined(STM32F423xx)
#define OB_PCROP_SECTOR_0        0x00000001U /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_SECTOR_1        0x00000002U /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_SECTOR_2        0x00000004U /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_SECTOR_3        0x00000008U /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_SECTOR_4        0x00000010U /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_SECTOR_5        0x00000020U /*!< PC Read/Write protection of Sector5      */
#define OB_PCROP_SECTOR_6        0x00000040U /*!< PC Read/Write protection of Sector6      */
#define OB_PCROP_SECTOR_7        0x00000080U /*!< PC Read/Write protection of Sector7      */
#define OB_PCROP_SECTOR_8        0x00000100U /*!< PC Read/Write protection of Sector8      */
#define OB_PCROP_SECTOR_9        0x00000200U /*!< PC Read/Write protection of Sector9      */
#define OB_PCROP_SECTOR_10       0x00000400U /*!< PC Read/Write protection of Sector10     */
#define OB_PCROP_SECTOR_11       0x00000800U /*!< PC Read/Write protection of Sector11     */
#define OB_PCROP_SECTOR_12       0x00001000U /*!< PC Read/Write protection of Sector12     */
#define OB_PCROP_SECTOR_13       0x00002000U /*!< PC Read/Write protection of Sector13     */
#define OB_PCROP_SECTOR_14       0x00004000U /*!< PC Read/Write protection of Sector14     */
#define OB_PCROP_SECTOR_15       0x00004000U /*!< PC Read/Write protection of Sector15     */
#define OB_PCROP_SECTOR_All      0x00007FFFU /*!< PC Read/Write protection of all Sectors  */
#endif /* STM32F413xx || STM32F423xx */

#if defined(STM32F401xC)
#define OB_PCROP_SECTOR_0        0x00000001U /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_SECTOR_1        0x00000002U /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_SECTOR_2        0x00000004U /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_SECTOR_3        0x00000008U /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_SECTOR_4        0x00000010U /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_SECTOR_5        0x00000020U /*!< PC Read/Write protection of Sector5      */
#define OB_PCROP_SECTOR_All      0x00000FFFU /*!< PC Read/Write protection of all Sectors  */
#endif /* STM32F401xC */

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define OB_PCROP_SECTOR_0        0x00000001U /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_SECTOR_1        0x00000002U /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_SECTOR_2        0x00000004U /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_SECTOR_3        0x00000008U /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_SECTOR_4        0x00000010U /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_SECTOR_All      0x00000FFFU /*!< PC Read/Write protection of all Sectors  */
#endif /* STM32F410Tx || STM32F410Cx || STM32F410Rx */

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define OB_PCROP_SECTOR_0        0x00000001U /*!< PC Read/Write protection of Sector0      */
#define OB_PCROP_SECTOR_1        0x00000002U /*!< PC Read/Write protection of Sector1      */
#define OB_PCROP_SECTOR_2        0x00000004U /*!< PC Read/Write protection of Sector2      */
#define OB_PCROP_SECTOR_3        0x00000008U /*!< PC Read/Write protection of Sector3      */
#define OB_PCROP_SECTOR_4        0x00000010U /*!< PC Read/Write protection of Sector4      */
#define OB_PCROP_SECTOR_5        0x00000020U /*!< PC Read/Write protection of Sector5      */
#define OB_PCROP_SECTOR_6        0x00000040U /*!< PC Read/Write protection of Sector6      */
#define OB_PCROP_SECTOR_7        0x00000080U /*!< PC Read/Write protection of Sector7      */
#define OB_PCROP_SECTOR_All      0x00000FFFU /*!< PC Read/Write protection of all Sectors  */
#endif /* STM32F401xE || STM32F411xE || STM32F446xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_DUAL_BOOT_ENABLE   ((uint8_t)0x10) /*!< Dual Bank Boot Enable                             */
#define OB_DUAL_BOOT_DISABLE  ((uint8_t)0x00) /*!< Dual Bank Boot Disable, always boot on User Flash */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */


#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define OB_PCROP_DESELECTED     ((uint8_t)0x00) /*!< Disabled PcROP, nWPRi bits used for Write Protection on sector i */
#define OB_PCROP_SELECTED       ((uint8_t)0x80) /*!< Enable PcROP, nWPRi bits used for PCRoP Protection on sector i   */
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F401xC || STM32F401xE ||\
          STM32F410xx || STM32F411xE || STM32F446xx || STM32F469xx || STM32F479xx || STM32F412Zx ||\
          STM32F412Vx || STM32F412Rx || STM32F412Cx || STM32F413xx || STM32F423xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_SECTOR_TOTAL  24U
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */

#if defined(STM32F413xx) || defined(STM32F423xx)
#define FLASH_SECTOR_TOTAL  16U
#endif /* STM32F413xx || STM32F423xx */

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_TOTAL  12U
#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx */

#if defined(STM32F401xC)
#define FLASH_SECTOR_TOTAL  6U
#endif /* STM32F401xC */

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define FLASH_SECTOR_TOTAL  5U
#endif /* STM32F410Tx || STM32F410Cx || STM32F410Rx */

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define FLASH_SECTOR_TOTAL  8U
#endif /* STM32F401xE || STM32F411xE || STM32F446xx */

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define OPTCR1_BYTE2_ADDRESS         0x40023C1AU
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */

#define ACR_BYTE0_ADDRESS           (FLASH_R_BASE + 0)
#define OPTCR_BYTE0_ADDRESS         (FLASH_R_BASE + 4*5 + 0)
#define OPTCR_BYTE1_ADDRESS         (FLASH_R_BASE + 4*5 + 1)
#define OPTCR_BYTE2_ADDRESS         (FLASH_R_BASE + 4*5 + 2)
#define OPTCR_BYTE3_ADDRESS         (FLASH_R_BASE + 4*5 + 3)

#if defined(FLASH_BANK2_END)
 #define FLASH_FLAG_BSY             FLASH_FLAG_BSY_BANK1       /*!< FLASH Bank1 Busy flag                   */ 
 #define FLASH_FLAG_PGERR           FLASH_FLAG_PGERR_BANK1     /*!< FLASH Bank1 Programming error flag      */
 #define FLASH_FLAG_WRPERR          FLASH_FLAG_WRPERR_BANK1    /*!< FLASH Bank1 Write protected error flag  */
 #define FLASH_FLAG_EOP             FLASH_FLAG_EOP_BANK1       /*!< FLASH Bank1 End of Operation flag       */

 #define FLASH_FLAG_BSY_BANK1       FLASH_SR_BSY               /*!< FLASH Bank1 Busy flag                   */ 
 #define FLASH_FLAG_PGERR_BANK1     FLASH_SR_PGERR             /*!< FLASH Bank1 Programming error flag      */
 #define FLASH_FLAG_WRPERR_BANK1    FLASH_SR_WRPRTERR          /*!< FLASH Bank1 Write protected error flag  */
 #define FLASH_FLAG_EOP_BANK1       FLASH_SR_EOP               /*!< FLASH Bank1 End of Operation flag       */
       
 #define FLASH_FLAG_BSY_BANK2       (FLASH_SR2_BSY << 16U)      /*!< FLASH Bank2 Busy flag                   */ 
 #define FLASH_FLAG_PGERR_BANK2     (FLASH_SR2_PGERR << 16U)    /*!< FLASH Bank2 Programming error flag      */
 #define FLASH_FLAG_WRPERR_BANK2    (FLASH_SR2_WRPRTERR << 16U) /*!< FLASH Bank2 Write protected error flag  */
 #define FLASH_FLAG_EOP_BANK2       (FLASH_SR2_EOP << 16U)      /*!< FLASH Bank2 End of Operation flag       */

#else  

 #define FLASH_FLAG_BSY             FLASH_SR_BSY              /*!< FLASH Busy flag                          */ 
 #define FLASH_FLAG_PGERR           FLASH_SR_PGERR            /*!< FLASH Programming error flag             */
#ifndef FLASH_FLAG_WRPERR
 #define FLASH_FLAG_WRPERR          FLASH_SR_WRPRTERR         /*!< FLASH Write protected error flag         */
#endif
 #define FLASH_FLAG_EOP             FLASH_SR_EOP              /*!< FLASH End of Operation flag              */

#endif
 #define FLASH_FLAG_OPTVERR         ((OBR_REG_INDEX << 8U | FLASH_OBR_OPTERR)) /*!< Option Byte Error        */
 
#if defined(FLASH_BANK2_END)
 #define FLASH_IT_EOP               FLASH_IT_EOP_BANK1        /*!< End of FLASH Operation Interrupt source Bank1 */
 #define FLASH_IT_ERR               FLASH_IT_ERR_BANK1        /*!< Error Interrupt source Bank1                  */

 #define FLASH_IT_EOP_BANK1         FLASH_CR_EOPIE            /*!< End of FLASH Operation Interrupt source Bank1 */
 #define FLASH_IT_ERR_BANK1         FLASH_CR_ERRIE            /*!< Error Interrupt source Bank1                  */

 #define FLASH_IT_EOP_BANK2         (FLASH_CR2_EOPIE << 16U)   /*!< End of FLASH Operation Interrupt source Bank2 */
 #define FLASH_IT_ERR_BANK2         (FLASH_CR2_ERRIE << 16U)   /*!< Error Interrupt source Bank2                  */

#else

 #define FLASH_IT_EOP               FLASH_CR_EOPIE          /*!< End of FLASH Operation Interrupt source */
#if  defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6) \
  || defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) \
  || defined(STM32F103xB)
 #define FLASH_IT_ERR               FLASH_CR_ERRIE          /*!< Error Interrupt source                  */
#endif

#endif

enum class FLASH_Procedure
{
  NONE = 0U,
  SECTERASE,
  MASS_ERASE,
  PROGRAM
};

/*typedef struct
{
    uint8_t  Lock:1;
    uint8_t  OPTS:1;
    uint8_t  BOR: 2;
    uint8_t  WDG: 1;
    uint8_t  RSTS:1;
    uint8_t  RSTB:1;
    uint8_t  RDP: 8;
    uint16_t WRP:12;
} FLASH_OPTCR_Typedef;*/

class STM32_FLASH
{
public:
    #if defined(FLASH_ACR_LATENCY)
    static inline void set_latency(uint8_t latency) { *((__IO uint8_t *)(FLASH_R_BASE + 0)) = latency; }
    static inline uint8_t get_latency() { return FLASH->ACR & FLASH_ACR_LATENCY; }
    #endif

    #if defined(FLASH_ACR_PRFTBE)
    ENDIS_REG_FLAG(prefetch_buffer, FLASH->ACR, FLASH_ACR_PRFTBE)
		#elif defined (FLASH_ACR_PRFTEN)
    ENDIS_REG_FLAG(prefetch_buffer, FLASH->ACR, FLASH_ACR_PRFTEN)
    #endif
    #ifdef FLASH_ACR_ICEN
    ENDIS_REG_FLAG(instruction_cache, FLASH->ACR, FLASH_ACR_ICEN)
    ENDIS_REG_FLAG(data_cache, FLASH->ACR, FLASH_ACR_DCEN)
    #endif

    #if defined(STM32F4)
    static void reset_instruction_cache();
    static void reset_data_cache();
    #endif

    static inline void enable_IT(uint32_t it_vector) { FLASH->CR |= it_vector; }
    static inline void disable_IT(uint32_t it_vector) { FLASH->CR &= ~it_vector; }

    static inline uint8_t get_flag(uint32_t flag_mask) { return FLASH->SR & flag_mask; }
    static inline void clear_flag(uint32_t flag_mask) { FLASH->SR = flag_mask; }

    #if defined(STM32F4)
    static uint32_t erase(FLASH_TypeErase type_erase, FLASH_VoltageRange voltage_range,
                          uint32_t banks, uint32_t sector_start, uint32_t nb_sectors, uint32_t &sector_error);
    static uint32_t erase_IT(FLASH_TypeErase type_erase, FLASH_VoltageRange voltage_range,
                             uint32_t banks, uint32_t sector_start, uint32_t nb_sectors);
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

    static void erase_sector(uint32_t sector, FLASH_VoltageRange voltage_range);
    #ifdef STM32F4
    static void flush_caches();
    #endif

   static uint32_t program(FLASH_TypeProgram type_program, uint32_t address, uint64_t data);
   static uint32_t program_IT(FLASH_TypeProgram type_program, uint32_t address, uint64_t data);

   static uint32_t unlock();
   static void lock();
   static uint32_t OB_unlock();
   static void OB_lock();
   static uint32_t OB_launch();

   static inline uint32_t get_error() { return m_error_code; }

   static uint32_t wait_for_last_operation(uint32_t timeout);

   static void irq_proc();
private:
   static FLASH_Procedure   m_on_going;
   static uint32_t          m_nb_sector_to_erase;
   static FLASH_VoltageRange m_voltage_for_erase;
   static uint32_t          m_sector;
   static uint32_t          m_bank;
   static uint32_t          m_address;
   static uint32_t          m_error_code;
   static uint8_t           m_lock;

   static void program_byte(uint32_t address, uint8_t data);
   static void program_halfword(uint32_t address, uint16_t data);
   static void program_word(uint32_t address, uint32_t data);
   static void program_doubleword(uint32_t address, uint64_t data);

   static void set_error_code();

   static void mass_erase(FLASH_VoltageRange voltage_range, uint32_t banks);

   static inline void reset_PG() { FLASH->CR &= ~(FLASH_CR_PG); }
};

void FLASH_end_of_operation_cb(uint32_t return_value);
void FLASH_operation_error_cb(uint32_t return_value);

#endif
