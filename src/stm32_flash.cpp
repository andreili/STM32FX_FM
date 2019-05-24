#include "stm32_flash.h"

#define FLASH_TIMEOUT_VALUE       50000U /* 50 s */

FLASH_Procedure   STM32_FLASH::m_on_going = FLASH_Procedure::NONE;
uint32_t          STM32_FLASH::m_nb_sector_to_erase;
FLASH_VoltageRange STM32_FLASH::m_voltage_for_erase;
uint32_t          STM32_FLASH::m_sector;
uint32_t          STM32_FLASH::m_bank;
uint32_t          STM32_FLASH::m_address;
uint32_t          STM32_FLASH::m_error_code;
uint8_t           STM32_FLASH::m_lock = STM32_UNLOCKED;

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
void STM32_FLASH::reset_instruction_cache()
{
    FLASH->ACR |= FLASH_ACR_ICRST;
    FLASH->ACR &= ~FLASH_ACR_ICRST;
}

void STM32_FLASH::reset_data_cache()
{
    FLASH->ACR |= FLASH_ACR_DCRST;
    FLASH->ACR &= ~FLASH_ACR_DCRST;
}
#endif

void STM32_FLASH::enable_remap_system_flash()
{
#if defined(STM32F4)
    SYSCFG->MEMRMP = SYSCFG_MEMRMP_MEM_MODE;
#else
#error
#endif
}

uint32_t STM32_FLASH::program(FLASH_TypeProgram type_program, uint32_t address, uint64_t data)
{
	uint32_t status;
    STM32_LOCK(m_lock);
	status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
    if (status ==  STM32_RESULT_OK)
    {
        switch (type_program)
        {
		#if defined(STM32F4)
        case FLASH_TypeProgram::BYTE:
            program_byte(address, data);
            break;
		#endif
        case FLASH_TypeProgram::HALF_WORD:
            program_halfword(address, data);
            break;
        case FLASH_TypeProgram::WORD:
            program_word(address, data);
            break;
        case FLASH_TypeProgram::DOUBLE_WORD:
            program_doubleword(address, data);
            break;
        }
        status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
        reset_PG();
    }

    STM32_UNLOCK(m_lock);
    return status;
}

uint32_t STM32_FLASH::program_IT(FLASH_TypeProgram type_program, uint32_t address, uint64_t data)
{
    STM32_LOCK(m_lock);
    enable_IT(FLASH_IT_EOP | FLASH_IT_ERR);

    switch (type_program)
    {
	#if defined(STM32F4)
    case FLASH_TypeProgram::BYTE:
        program_byte(address, data);
        break;
	#endif
    case FLASH_TypeProgram::HALF_WORD:
        program_halfword(address, data);
        break;
    case FLASH_TypeProgram::WORD:
        program_word(address, data);
        break;
    case FLASH_TypeProgram::DOUBLE_WORD:
        program_doubleword(address, data);
        break;
    }

    return STM32_RESULT_OK;
}

uint32_t STM32_FLASH::unlock()
{
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
    {
        WRITE_REG(FLASH->KEYR, FLASH_KEY1);
        WRITE_REG(FLASH->KEYR, FLASH_KEY2);
        if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
            return STM32_RESULT_FAIL;
    }
    return STM32_RESULT_OK;
}

void STM32_FLASH::lock()
{
    FLASH->CR |= FLASH_CR_LOCK;
}

/*uint32_t STM32_FLASH::OB_unlock()
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

void STM32_FLASH::OB_lock()
{
    FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
}

uint32_t STM32_FLASH::OB_launch()
{
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;
    return wait_for_last_operation(FLASH_TIMEOUT_VALUE);
}*/

uint32_t STM32_FLASH::wait_for_last_operation(uint32_t timeout)
{
    m_error_code = FLASH_ERROR_NONE;

    WAIT_TIMEOUT(get_flag(FLASH_FLAG_BSY) != RESET, timeout);

    if (get_flag(FLASH_FLAG_EOP) != RESET)
        clear_flag(FLASH_FLAG_EOP);

#if defined(FLASH_SR_RDERR)
    if (get_glag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR) != RESET)
#elif defined(STM32F4)
    if (get_flag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR) != RESET)
#elif defined(STM32F1)
    if (get_flag(FLASH_FLAG_WRPERR) || get_flag(FLASH_FLAG_OPTVERR) || get_flag(FLASH_FLAG_PGERR))
#endif
    {
        set_error_code();
        return STM32_RESULT_FAIL;
    }

    return STM32_RESULT_OK;
}

void STM32_FLASH::program_doubleword(uint32_t address, uint64_t data)
{
#if defined(STM32F4)
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint64_t*)address = data;
#endif
}

void STM32_FLASH::program_word(uint32_t address, uint32_t data)
{
#if defined(STM32F4)
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= FLASH_PSIZE_WORD;
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint32_t*)address = data;
#endif
}

void STM32_FLASH::program_halfword(uint32_t address, uint16_t data)
{
#if defined(STM32F1)
	SET_BIT(FLASH->CR, FLASH_CR_PG);
    *(__IO uint16_t*)address = data;
#elif defined(STM32F4)
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= FLASH_PSIZE_HALF_WORD;
    FLASH->CR |= FLASH_CR_PG;
    *(__IO uint16_t*)address = data;
#endif
}

void STM32_FLASH::program_byte(uint32_t address, uint8_t data)
{
#if defined(STM32F4)
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= FLASH_PSIZE_BYTE;
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint8_t*)address = data;
#endif
}

void STM32_FLASH::set_error_code()
{
    if (get_flag(FLASH_FLAG_WRPERR) != RESET)
    {
        m_error_code |= FLASH_ERROR_WRP;
        clear_flag(FLASH_FLAG_WRPERR);
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
    if (get_flag(FLASH_FLAG_PGAERR) != RESET)
    {
        m_error_code |= FLASH_ERROR_PGA;
        clear_flag(FLASH_FLAG_PGAERR);
    }

    if (get_flag(FLASH_FLAG_PGPERR) != RESET)
    {
        m_error_code |= FLASH_ERROR_PGP;
        clear_flag(FLASH_FLAG_PGPERR);
    }

    if (get_flag(FLASH_FLAG_PGSERR) != RESET)
    {
        m_error_code |= FLASH_ERROR_PGS;
        clear_flag(FLASH_FLAG_PGSERR);
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
uint32_t STM32_FLASH::erase(FLASH_TypeErase type_erase, FLASH_VoltageRange voltage_range, uint32_t banks,
                            uint32_t sector_start, uint32_t nb_sectors, uint32_t &sector_error)
{
    STM32_LOCK(m_lock);
    clear_flag(FLASH_FLAG_EOP    | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
               FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR);

    uint32_t status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);

    if (status == STM32_RESULT_OK)
    {
        sector_error = 0xffffffff;
        if (type_erase == FLASH_TypeErase::MASS_ERASE)
        {
            mass_erase(voltage_range, banks);
            status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
            /* if the erase operation is completed, disable the MER Bit */
            FLASH->CR &= (~FLASH_MER_BIT);
        }
        else
        {
            for (uint32_t index=sector_start ; index<(sector_start + nb_sectors) ; ++index)
            {
                erase_sector(index, voltage_range);
                status = wait_for_last_operation(FLASH_TIMEOUT_VALUE);
                /* If the erase operation is completed, disable the SER and SNB Bits */
                CLEAR_BIT(FLASH->CR, (FLASH_CR_SER | FLASH_CR_SNB));
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

uint32_t STM32_FLASH::erase_IT(FLASH_TypeErase type_erase, FLASH_VoltageRange voltage_range, uint32_t banks,
                               uint32_t sector_start, uint32_t nb_sectors)
{
    STM32_LOCK(m_lock);

    enable_IT(FLASH_IT_EOP | FLASH_IT_ERR);
    clear_flag(FLASH_FLAG_EOP    | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
               FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR);
    if (type_erase == FLASH_TypeErase::MASS_ERASE)
    {
        m_on_going = FLASH_Procedure::MASS_ERASE;
        m_bank = banks;
        mass_erase(voltage_range, banks);
    }
    else
    {
        m_on_going = FLASH_Procedure::SECTERASE;
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
void STM32_FLASH::mass_erase(uint32_t voltage_range, uint32_t banks)
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
void STM32_FLASH::mass_erase(FLASH_VoltageRange voltage_range, uint32_t banks)
{
    UNUSED(banks);
    /* If the previous operation is completed, proceed to erase all sectors */
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= FLASH_CR_MER;
    FLASH->CR |= FLASH_CR_STRT | ((uint32_t)voltage_range <<8U);
}
#endif

#if defined(STM32F1)
void STM32_FLASH::mass_erase(FLASH_VoltageRange voltage_range, uint32_t banks)
{
	UNUSED(voltage_range);
	UNUSED(banks);
    FLASH->CR |= FLASH_CR_MER;
    FLASH->CR |= FLASH_CR_STRT;
}
#endif

void STM32_FLASH::erase_sector(uint32_t sector, FLASH_VoltageRange voltage_range)
{
#ifdef STM32F1
	SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, sector);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
#else
    uint32_t tmp_psize = 0;
    if (voltage_range == FLASH_VoltageRange::V_1P8_TO_2P1)
        tmp_psize = FLASH_PSIZE_BYTE;
    else if (voltage_range == FLASH_VoltageRange::V_2P1_TO_2P7)
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    else if (voltage_range == FLASH_VoltageRange::V_2P7_TO_3P6)
        tmp_psize = FLASH_PSIZE_WORD;
    else
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;

    if (sector > FLASH_SECTOR_11)
        sector += 4;

    /* If the previous operation is completed, proceed to erase the sector */
    CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
    FLASH->CR |= tmp_psize;
    CLEAR_BIT(FLASH->CR, FLASH_CR_SNB);
    FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);
    FLASH->CR |= FLASH_CR_STRT;
#endif
}

#ifdef STM32F4
void STM32_FLASH::flush_caches()
{
    if (READ_BIT(FLASH->ACR, FLASH_ACR_ICEN) != RESET)
    {
        disable_instruction_cache();
        reset_instruction_cache();
        enable_instruction_cache();
    }

    if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != RESET)
    {
        disable_data_cache();
        reset_data_cache();
        enable_data_cache();
    }
}
#endif

void STM32_FLASH::irq_proc()
{
    /* Check FLASH operation error flags */
#ifdef FLASH_SR_RDERR
    if (get_glag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR) != RESET)
#else
#if defined(STM32F1)
    if (get_flag(FLASH_FLAG_WRPERR) || get_flag(FLASH_FLAG_PGERR))
#elif defined(STM32F4)
    if (get_flag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
                 FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR) != RESET)
#endif // STM32F1, STM32F4
#endif
    {
        uint32_t addr;

        if (m_on_going == FLASH_Procedure::SECTERASE)
        {
            addr = m_sector;
            m_sector = 0xffffffff;
        }
        else if (m_on_going == FLASH_Procedure::MASS_ERASE)
            addr = m_bank;
        else
            addr = m_address;

        set_error_code();

        FLASH_operation_error_cb(addr);

        m_on_going = FLASH_Procedure::NONE;
    }

    /* Check FLASH End of Operation flag  */
    if (get_flag(FLASH_FLAG_EOP) != RESET)
    {
        clear_flag(FLASH_FLAG_EOP);

        if (m_on_going == FLASH_Procedure::SECTERASE)
        {
            if ((--m_nb_sector_to_erase) != 0)
            {
                FLASH_end_of_operation_cb(m_sector);
                erase_sector(++m_sector, m_voltage_for_erase);
            }
            else
            {
                m_sector = 0xffffffff;
                m_on_going = FLASH_Procedure::NONE;
				#ifdef STM32F4
                flush_caches();
				#endif
                FLASH_end_of_operation_cb(0xffffffff);
            }
        }
        else
        {
            if (m_on_going == FLASH_Procedure::MASS_ERASE)
            {
				#ifdef STM32F4
                flush_caches();
				#endif
                FLASH_end_of_operation_cb(m_bank);
            }
            else
            {
                FLASH_end_of_operation_cb(m_address);
            }
            m_on_going = FLASH_Procedure::NONE;
        }
    }

    if (m_on_going == FLASH_Procedure::NONE)
    {
		#if defined(STM32F1)
        CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_PER));
		#elif defined(STM32F4)
        CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_SER | FLASH_CR_SNB | FLASH_MER_BIT));
		#endif
        disable_IT(FLASH_IT_EOP | FLASH_IT_ERR);
        STM32_UNLOCK(m_lock);
    }
}

void ISR::FLASH_IRQ()
{
#ifdef STM32_USE_FLASH
    STM32_FLASH::irq_proc();
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
