#include "stm32_flash.hpp"

#define FLASH_TIMEOUT_VALUE       50000U /* 50 s */

namespace STM32
{

FLASH::EProcedure FLASH::m_on_going = FLASH::EProcedure::NONE;
uint32_t          FLASH::m_nb_sector_to_erase;
FLASH::EVoltageRange FLASH::m_voltage_for_erase;
FLASH::ESectorNumber FLASH::m_sector;
FLASH::EBank      FLASH::m_bank;
uint32_t          FLASH::m_address;
FLASH::EError     FLASH::m_error_code;
uint8_t           FLASH::m_lock = STM32_UNLOCKED;

#define FLASH_SIZE_DATA_REGISTER     0x1FFFF7E0U
#define OBR_REG_INDEX                1U
#define SR_FLAG_MASK                 ((uint32_t)(FLASH_SR_BSY | FLASH_SR_PGERR | FLASH_SR_WRPRTERR | FLASH_SR_EOP))
 #define FLASH_FLAG_OPTVERR         ((OBR_REG_INDEX << 8U | FLASH_OBR_OPTERR)) /*!< Option Byte Error        */

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

#if defined(STM32F4)
void FLASH::reset_instruction_cache()
{
    ACR::set_instruction_cache_reset(true);
    ACR::set_instruction_cache_reset(false);
}

void FLASH::reset_data_cache()
{
    ACR::set_data_cache_reset(true);
    ACR::set_data_cache_reset(false);
}
#endif

void FLASH::enable_remap_system_flash()
{
#if defined(STM32F4)
    SYSCFG::MEMRMP::set_memory_mode(SYSCFG::MEMRMP::EMemMode::SRAM_AT_0);
#else
#error
#endif
}

uint32_t FLASH::program(ETypeProgram type_program, uint32_t address, uint64_t data)
{
	uint32_t status;
    STM32_LOCK(m_lock);
	status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
    if (status ==  STM32_RESULT_OK)
    {
        switch (type_program)
        {
		#if defined(STM32F4)
        case ETypeProgram::BYTE:
            program_byte(address, data);
            break;
		#endif
        case ETypeProgram::HALF_WORD:
            program_halfword(address, data);
            break;
        case ETypeProgram::WORD:
            program_word(address, data);
            break;
        case ETypeProgram::DOUBLE_WORD:
            program_doubleword(address, data);
            break;
        }
        status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
        reset_PG();
    }

    STM32_UNLOCK(m_lock);
    return status;
}

uint32_t FLASH::program_IT(ETypeProgram type_program, uint32_t address, uint64_t data)
{
    STM32_LOCK(m_lock);
    CR::set_end_of_operation_enable(true);
    CR::set_error_interrupt_enable(true);

    switch (type_program)
    {
	#if defined(STM32F4)
    case ETypeProgram::BYTE:
        program_byte(address, data);
        break;
	#endif
    case ETypeProgram::HALF_WORD:
        program_halfword(address, data);
        break;
    case ETypeProgram::WORD:
        program_word(address, data);
        break;
    case ETypeProgram::DOUBLE_WORD:
        program_doubleword(address, data);
        break;
    }

    return STM32_RESULT_OK;
}

uint32_t FLASH::unlock()
{
    if (CR::get_lock())
    {
        KEYR::set(KEYR::EKey::KEY1);
        KEYR::set(KEYR::EKey::KEY2);
        if (CR::get_lock())
            return STM32_RESULT_FAIL;
    }
    return STM32_RESULT_OK;
}

void FLASH::lock()
{
    CR::set_lock(true);
}

/*uint32_t FLASH::OB_unlock()
{
    if (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) != RESET)
    {
        FLASH->OPTKEYR = FLASH_OPT_KEY1;
        FLASH->OPTKEYR = FLASH_OPT_KEY2;
        return STM32_RESULT_OK;
    }
    else
        return STM32_RESULT_FAIL;
}

void FLASH::OB_lock()
{
    FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
}

uint32_t FLASH::OB_launch()
{
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;
    return wait_for_last_operation(FLASH_TIMEOUT_VALUE);
}*/

uint32_t FLASH::wait_for_last_operation(uint32_t timeout)
{
    m_error_code = EError::NONE;

    WAIT_TIMEOUT(SR::is_busy(), timeout);

    if (SR::get_end_of_operation())
        SR::set_end_of_operation(true);

#if defined(FLASH_SR_RDERR)
    if (get_glag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR) != RESET)
#elif defined(STM32F4)
    if (SR::get_operation_error() ||
        SR::get_write_protection_error() ||
        SR::get_programming_alignment_error() ||
        SR::get_programming_parallelism_error() ||
        SR::get_programming_sequence_error())
#elif defined(STM32F1)
    if (get_flag(FLASH_FLAG_WRPERR) || get_flag(FLASH_FLAG_OPTVERR) || get_flag(FLASH_FLAG_PGERR))
#endif
    {
        set_error_code();
        return STM32_RESULT_FAIL;
    }

    return STM32_RESULT_OK;
}

void FLASH::program_doubleword(uint32_t address, uint64_t data)
{
#if defined(STM32F4)
    CR::set_program_size(EProgramSize::x64);
    CR::set_programming(true);

    *(__IO uint64_t*)address = data;
#endif
}

void FLASH::program_word(uint32_t address, uint32_t data)
{
#if defined(STM32F4)
    CR::set_program_size(EProgramSize::x32);
    CR::set_programming(true);

    *(__IO uint32_t*)address = data;
#endif
}

void FLASH::program_halfword(uint32_t address, uint16_t data)
{
#if defined(STM32F1)
	SET_BIT(FLASH->CR, FLASH_CR_PG);
    *(__IO uint16_t*)address = data;
#elif defined(STM32F4)
    CR::set_program_size(EProgramSize::x16);
    CR::set_programming(true);

    *(__IO uint16_t*)address = data;
#endif
}

void FLASH::program_byte(uint32_t address, uint8_t data)
{
#if defined(STM32F4)
    CR::set_program_size(EProgramSize::x8);
    CR::set_programming(true);

    *(__IO uint8_t*)address = data;
#endif
}

void FLASH::set_error_code()
{
    if (SR::get_write_protection_error())
    {
        m_error_code |= EError::WRP;
        SR::set_write_protection_error(true);
    }

	#if defined(STM32F1)
    if (get_flag(FLASH_FLAG_PGERR) != RESET)
    {
        m_error_code |= FLASH_FLAG_PGERR;
        clear_flag(FLASH_FLAG_PGERR);
    }
	
    if (get_flag(FLASH_FLAG_OPTVERR) != RESET)
    {
        m_error_code |= FLASH_FLAG_OPTVERR;
        clear_flag(FLASH_FLAG_PGERR);
    }
	#elif defined(STM32F4)
    if (SR::get_programming_alignment_error())
    {
        m_error_code |= EError::PGA;
        SR::set_programming_alignment_error(true);
    }

    if (SR::get_programming_parallelism_error())
    {
        m_error_code |= EError::PGP;
        SR::set_programming_parallelism_error(true);
    }

    if (SR::get_programming_sequence_error())
    {
        m_error_code |= EError::PGS;
        SR::set_programming_sequence_error(true);
    }
	#endif

#if defined(FLASH_SR_RDERR)
    if (get_flag(FLASH_FLAG_OPERR) != RESET)
    {
        m_error_code |= FLASH_ERROR_OPERATION;
        clear_flag(FLASH_FLAG_OPERR);
    }
#endif
}

#if defined(STM32F4)
#include "xprintf.h"
uint32_t FLASH::erase(ETypeErase type_erase, EVoltageRange voltage_range, EBank banks,
                      ESectorNumber sector_start, uint32_t nb_sectors, ESectorNumber &sector_error)
{
    STM32_LOCK(m_lock);
    SR::set_end_of_operation(true);
    SR::set_end_of_operation(true);
    SR::set_write_protection_error(true);
    SR::set_programming_alignment_error(true);
    SR::set_programming_parallelism_error(true);
    SR::set_programming_sequence_error(true);

    uint32_t status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);

    if (status == STM32_RESULT_OK)
    {
        sector_error = ESectorNumber::NONE;
        if (type_erase == ETypeErase::MASS_ERASE)
        {
            mass_erase(voltage_range, banks);
            status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
            /* if the erase operation is completed, disable the MER Bit */
            CR::set_mass_erase(false);
        }
        else
        {
            for (ESectorNumber index=sector_start ; index<(sector_start + nb_sectors) ; ++index)
            {
                xprintf("\tErase sector %d\n\r", index);
                erase_sector(index, voltage_range);
                status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
                /* If the erase operation is completed, disable the SER and SNB Bits */
                CR::set_sector_erase(false);
                CR::set_sector_number(ESectorNumber::S_0);
                if (status != STM32_RESULT_OK)
                {
                    sector_error = index;
                    break;
                }
            }
        }
        flush_caches();
    }

    STM32_UNLOCK(m_lock);

    return status;
}

uint32_t FLASH::erase_IT(ETypeErase type_erase, EVoltageRange voltage_range, EBank banks,
                         ESectorNumber sector_start, uint32_t nb_sectors)
{
    STM32_LOCK(m_lock);

    CR::set_end_of_operation_enable(true);
    CR::set_error_interrupt_enable(true);
    SR::set_end_of_operation(true);
    SR::set_end_of_operation(true);
    SR::set_write_protection_error(true);
    SR::set_programming_alignment_error(true);
    SR::set_programming_parallelism_error(true);
    SR::set_programming_sequence_error(true);
    if (type_erase == ETypeErase::MASS_ERASE)
    {
        m_on_going = EProcedure::MASS_ERASE;
        m_bank = banks;
        mass_erase(voltage_range, banks);
    }
    else
    {
        m_on_going = EProcedure::SECTERASE;
        m_nb_sector_to_erase = nb_sectors;
        m_sector = sector_start;
        m_voltage_for_erase = voltage_range;
        erase_sector(sector_start, voltage_range);
    }

    STM32_UNLOCK(m_lock);

    return STM32_RESULT_OK;
}
#endif // STM32F4

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
void FLASH::mass_erase(uint32_t voltage_range, uint32_t banks)
{
    /* if the previous operation is completed, proceed to erase all sectors */
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);

    if (banks == FLASH_BANK_BOTH)
        /* bank1 & bank2 will be erased*/
        FLASH->CR |= FLASH_MER_BIT;
    else if (banks == FLASH_BANK_1)
        FLASH->CR |= FLASH_CR_MER1;
    else
        FLASH->CR |= FLASH_CR_MER2;
    FLASH->CR |= FLASH_CR_STRT | (voltage_range << 8);
}
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
void FLASH::mass_erase(EVoltageRange voltage_range, EBank banks)
{
    UNUSED(banks);
    /* If the previous operation is completed, proceed to erase all sectors */
    CR::set_program_size(EProgramSize::x8);
    CR::set_mass_erase(true);
    CR::set_start(true);
    CR::set_program_size(static_cast<EProgramSize>(voltage_range));
}
#endif

#if defined(STM32F1)
void FLASH::mass_erase(FLASH_VoltageRange voltage_range, uint32_t banks)
{
	UNUSED(voltage_range);
	UNUSED(banks);
    FLASH->CR |= FLASH_CR_MER;
    FLASH->CR |= FLASH_CR_STRT;
}
#endif

void FLASH::erase_sector(ESectorNumber sector, EVoltageRange voltage_range)
{
#ifdef STM32F1
	SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, sector);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
#else

    if (sector > ESectorNumber::S_11)
        sector = static_cast<ESectorNumber>(sector + 4);

    /* If the previous operation is completed, proceed to erase the sector */
    CR::set_program_size(static_cast<EProgramSize>(voltage_range));
    CR::set_sector_number(sector);
    CR::set_sector_erase(true);
    CR::set_start(true);
#endif
}

#ifdef STM32F4
void FLASH::flush_caches()
{
    if (ACR::get_instruction_cache_enable())
    {
        ACR::set_instruction_cache_enable(false);
        ACR::set_instruction_cache_reset(true);
        ACR::set_instruction_cache_enable(false);
    }

    if (ACR::get_data_cache_enable())
    {
        ACR::set_data_cache_enable(false);
        ACR::set_data_cache_reset(true);
        ACR::set_data_cache_enable(false);
    }
}
#endif

void FLASH::irq_proc()
{
    /* Check FLASH operation error flags */
#ifdef FLASH_SR_RDERR
    if (get_glag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR) != RESET)
#else
#if defined(STM32F1)
    if (get_flag(FLASH_FLAG_WRPERR) || get_flag(FLASH_FLAG_PGERR))
#elif defined(STM32F4)
    if (!SR::get_operation_error() ||
        !SR::get_write_protection_error() ||
        !SR::get_programming_alignment_error() ||
        !SR::get_programming_parallelism_error() ||
        !SR::get_programming_sequence_error())
#endif // STM32F1, STM32F4
#endif
    {
        uint32_t addr;

        if (m_on_going == EProcedure::SECTERASE)
        {
            addr = static_cast<uint32_t>(m_sector);
            m_sector = ESectorNumber::NONE;
        }
        else if (m_on_going == EProcedure::MASS_ERASE)
            addr = static_cast<uint32_t>(m_bank);
        else
            addr = m_address;

        set_error_code();

        FLASH_operation_error_cb(addr);

        m_on_going = EProcedure::NONE;
    }

    /* Check FLASH End of Operation flag  */
    if (SR::get_operation_error())
    {
        SR::set_end_of_operation(true);

        if (m_on_going == EProcedure::SECTERASE)
        {
            if ((--m_nb_sector_to_erase) != 0)
            {
                FLASH_end_of_operation_cb(static_cast<uint32_t>(m_sector));
                erase_sector(++m_sector, m_voltage_for_erase);
            }
            else
            {
                m_sector = ESectorNumber::NONE;
                m_on_going = EProcedure::NONE;
				#ifdef STM32F4
                flush_caches();
				#endif
                FLASH_end_of_operation_cb(0xffffffff);
            }
        }
        else
        {
            if (m_on_going == EProcedure::MASS_ERASE)
            {
				#ifdef STM32F4
                flush_caches();
				#endif
                FLASH_end_of_operation_cb(static_cast<uint32_t>(m_bank));
            }
            else
            {
                FLASH_end_of_operation_cb(m_address);
            }
            m_on_going = EProcedure::NONE;
        }
    }

    if (m_on_going == EProcedure::NONE)
    {
		#if defined(STM32F1)
        CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_PER));
        #elif defined(STM32F4)
        CR::set_programming(false);
        CR::set_sector_erase(false);
        CR::set_sector_number(ESectorNumber::S_0);
        CR::set_mass_erase(false);
        #endif
        CR::set_end_of_operation_enable(false);
        CR::set_error_interrupt_enable(false);
        STM32_UNLOCK(m_lock);
    }
}

}

void ISR::FLASH_IRQ()
{
#ifdef STM32_USE_FLASH
    FLASH::irq_proc();
#else
    while (1);
#endif
}

__attribute__((weak)) void FLASH_end_of_operation_cb(uint32_t return_value)
{
    UNUSED(return_value);
}

__attribute__((weak)) void FLASH_operation_error_cb(uint32_t return_value)
{
    UNUSED(return_value);
}
