#include "stm32_sd.h"

#ifdef STM32_USE_SD

#define DATA_BLOCK_SIZE                  EDataBlockSize::_512B

#define SDIO_IT_CCRCFAIL                    SDIO_STA_CCRCFAIL
#define SDIO_IT_DCRCFAIL                    SDIO_STA_DCRCFAIL
#define SDIO_IT_CTIMEOUT                    SDIO_STA_CTIMEOUT
#define SDIO_IT_DTIMEOUT                    SDIO_STA_DTIMEOUT
#define SDIO_IT_TXUNDERR                    SDIO_STA_TXUNDERR
#define SDIO_IT_RXOVERR                     SDIO_STA_RXOVERR
#define SDIO_IT_CMDREND                     SDIO_STA_CMDREND
#define SDIO_IT_CMDSENT                     SDIO_STA_CMDSENT
#define SDIO_IT_DATAEND                     SDIO_STA_DATAEND
#define SDIO_IT_STBITERR                    SDIO_STA_STBITERR
#define SDIO_IT_DBCKEND                     SDIO_STA_DBCKEND
#define SDIO_IT_CMDACT                      SDIO_STA_CMDACT
#define SDIO_IT_TXACT                       SDIO_STA_TXACT
#define SDIO_IT_RXACT                       SDIO_STA_RXACT
#define SDIO_IT_TXFIFOHE                    SDIO_STA_TXFIFOHE
#define SDIO_IT_RXFIFOHF                    SDIO_STA_RXFIFOHF
#define SDIO_IT_TXFIFOF                     SDIO_STA_TXFIFOF
#define SDIO_IT_RXFIFOF                     SDIO_STA_RXFIFOF
#define SDIO_IT_TXFIFOE                     SDIO_STA_TXFIFOE
#define SDIO_IT_RXFIFOE                     SDIO_STA_RXFIFOE
#define SDIO_IT_TXDAVL                      SDIO_STA_TXDAVL
#define SDIO_IT_RXDAVL                      SDIO_STA_RXDAVL
#define SDIO_IT_SDIOIT                      SDIO_STA_SDIOIT
#define SDIO_IT_CEATAEND                    SDIO_STA_CEATAEND

#define SDIO_FLAG_CCRCFAIL                  SDIO_STA_CCRCFAIL
#define SDIO_FLAG_DCRCFAIL                  SDIO_STA_DCRCFAIL
#define SDIO_FLAG_CTIMEOUT                  SDIO_STA_CTIMEOUT
#define SDIO_FLAG_DTIMEOUT                  SDIO_STA_DTIMEOUT
#define SDIO_FLAG_TXUNDERR                  SDIO_STA_TXUNDERR
#define SDIO_FLAG_RXOVERR                   SDIO_STA_RXOVERR
#define SDIO_FLAG_CMDREND                   SDIO_STA_CMDREND
#define SDIO_FLAG_CMDSENT                   SDIO_STA_CMDSENT
#define SDIO_FLAG_DATAEND                   SDIO_STA_DATAEND
#define SDIO_FLAG_STBITERR                  SDIO_STA_STBITERR
#define SDIO_FLAG_DBCKEND                   SDIO_STA_DBCKEND
#define SDIO_FLAG_CMDACT                    SDIO_STA_CMDACT
#define SDIO_FLAG_TXACT                     SDIO_STA_TXACT
#define SDIO_FLAG_RXACT                     SDIO_STA_RXACT
#define SDIO_FLAG_TXFIFOHE                  SDIO_STA_TXFIFOHE
#define SDIO_FLAG_RXFIFOHF                  SDIO_STA_RXFIFOHF
#define SDIO_FLAG_TXFIFOF                   SDIO_STA_TXFIFOF
#define SDIO_FLAG_RXFIFOF                   SDIO_STA_RXFIFOF
#define SDIO_FLAG_TXFIFOE                   SDIO_STA_TXFIFOE
#define SDIO_FLAG_RXFIFOE                   SDIO_STA_RXFIFOE
#define SDIO_FLAG_TXDAVL                    SDIO_STA_TXDAVL
#define SDIO_FLAG_RXDAVL                    SDIO_STA_RXDAVL
#define SDIO_FLAG_SDIOIT                    SDIO_STA_SDIOIT
#define SDIO_FLAG_CEATAEND                  SDIO_STA_CEATAEND

#define SDIO_STATIC_FLAGS                   (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_DCRCFAIL | \
                                             SDIO_FLAG_CTIMEOUT | SDIO_FLAG_DTIMEOUT | \
                                             SDIO_FLAG_TXUNDERR | SDIO_FLAG_RXOVERR | \
                                             SDIO_FLAG_CMDREND | SDIO_FLAG_CMDSENT | \
                                             SDIO_FLAG_DATAEND | SDIO_FLAG_DBCKEND)

#define CLKCR_CLEAR_MASK         (SDIO_CLKCR_CLKDIV  | SDIO_CLKCR_PWRSAV |\
                                  SDIO_CLKCR_BYPASS  | SDIO_CLKCR_WIDBUS |\
                                  SDIO_CLKCR_NEGEDGE | SDIO_CLKCR_HWFC_EN)

#define DCTRL_CLEAR_MASK         (SDIO_DCTRL_DTEN    | SDIO_DCTRL_DTDIR |\
                                  SDIO_DCTRL_DTMODE  | SDIO_DCTRL_DBLOCKSIZE)

#define CMD_CLEAR_MASK           (SDIO_CMD_CMDINDEX | SDIO_CMD_WAITRESP |\
                                  SDIO_CMD_WAITINT  | SDIO_CMD_WAITPEND |\
                                  SDIO_CMD_CPSMEN   | SDIO_CMD_SDIOSUSPEND)

#define SDIO_RESP_ADDR           ((uint32_t)(SDIO_BASE + 0x14U))

#define SDIO_INIT_CLK_DIV 0x76U

#define SDIO_TRANSFER_CLK_DIV ((uint8_t)0x00U)

#define SDIO_CMD0TIMEOUT                0x00010000U

#define SD_VOLTAGE_WINDOW_WALID         0x80000000U
#define SD_VOLTAGE_WINDOW_SD            0x80100000U

#define SD_HIGH_CAPACITY                0x40000000U
#define SD_STD_CAPACITY                 0x00000000U

#define SD_CHECK_PATTERN                0x000001AAU

#define SD_MAX_VOLT_TRIAL               0x0000FFFFU
#define SD_ALLZERO                      0x00000000U

#define SD_WIDE_BUS_SUPPORT             0x00040000U
#define SD_SINGLE_BUS_SUPPORT           0x00010000U

#define SD_CARD_LOCKED                  0x02000000U

#define SD_DATATIMEOUT                  0xFFFFFFFFU
#define SD_0TO7BITS                     0x000000FFU
#define SD_8TO15BITS                    0x0000FF00U
#define SD_16TO23BITS                   0x00FF0000U
#define SD_24TO31BITS                   0xFF000000U
#define SD_MAX_DATA_LENGTH              0x01FFFFFFU

#define SD_HALFFIFO                     ((uint32_t)0x00000008U)
#define SD_HALFFIFOBYTES                ((uint32_t)0x00000020U)

/**
  * @brief  Command Class Supported
  */
#define SD_CCCC_LOCK_UNLOCK             0x00000080U
#define SD_CCCC_WRITE_PROT              0x00000040U
#define SD_CCCC_ERASE                   0x00000020U

STM32_SD::ECardType STM32_SD::m_card_type;
uint16_t STM32_SD::m_RCA;
uint32_t STM32_SD::m_CSD[4];
uint32_t STM32_SD::m_CID[4];
STM32_SD::CardInfo STM32_SD::m_card_info;

STM32_SD::ESDError STM32_SD::init()
{
    init_gpio();
    ///TODO init_DMA();
    STM32_NVIC::enable_and_set_prior_IRQ(SDIO_IRQn, 0, 0);

    init_low(EClockEdge::RISING, EClockBypass::DISABLE,
             EClockPowerSave::DISABLE, EBusWide::_1B,
             EHWFlowControl::DISABLE, SDIO_INIT_CLK_DIV);

    ESDError errorstate;

    disable_SDIO();
    power_state_ON();
    STM32_SYSTICK::delay(1);
    enable_SDIO();
    STM32_SYSTICK::delay(2);

    if ((errorstate = power_ON()) != ESDError::OK)
        return errorstate;

    if ((errorstate = initialize_cards()) != ESDError::OK)
        return errorstate;

    if ((errorstate = get_card_info()) == ESDError::OK)
        select_deselect(static_cast<uint32_t>(m_card_info.RCA << 16));

    init_low(EClockEdge::RISING, EClockBypass::DISABLE,
             EClockPowerSave::DISABLE, EBusWide::_1B,
             EHWFlowControl::DISABLE, STM32_SDIO_CLOCK_DIV);

    return errorstate;
}

void STM32_SD::deinit()
{
    power_OFF();

    STM32_RCC::disable_clk_SDIO();

    deinit_gpio();

    //TODO deinit DMA

    STM32_NVIC::disable_IRQ(SDIO_IRQn);
}

STM32_SD::ESDError STM32_SD::wide_bus_config(EBusWide mode)
{
    ESDError errorstate = ESDError::OK;

    /* MMC Card does not support this feature */
    if (m_card_type == ECardType::MULTIMEDIA)
        return ESDError::UNSUPPORTED_FEATURE;
    else if ((m_card_type == ECardType::STD_CAPACITY_V1_1) ||
             (m_card_type == ECardType::STD_CAPACITY_V2_0) ||
             (m_card_type == ECardType::HIGH_CAPACITY))
    {
        if (mode == EBusWide::_8B)
            errorstate = ESDError::UNSUPPORTED_FEATURE;
        else if (mode == EBusWide::_4B)
            errorstate = wide_bus_enable();
        else if (mode == EBusWide::_1B)
            errorstate = wide_bus_disable();
        else
            /* mode is not a valid argument*/
            errorstate = ESDError::INVALID_PARAMETER;

        if (errorstate == ESDError::OK)
        {
            /* Configure the SDIO peripheral */
            init_low(EClockEdge::RISING, EClockBypass::DISABLE,
                     EClockPowerSave::DISABLE, mode,
                     EHWFlowControl::DISABLE, STM32_SDIO_CLOCK_DIV);
        }
    }

    return errorstate;
}

STM32_SD::ETransferState STM32_SD::get_status()
{
    ECardState cardstate =  ECardState::TRANSFER;

    cardstate = get_state();

    /* Find SD status according to card state*/
    if (cardstate == ECardState::TRANSFER)
        return ETransferState::OK;
    else if(cardstate == ECardState::ERROR)
        return ETransferState::ERROR;
    else
        return ETransferState::BUSY;
}

STM32_SD::ESDError STM32_SD::read_blocks(uint8_t *buf, uint32_t read_addr, uint32_t block_size, uint16_t blocks)
{
    ESDError errorstate = ESDError::OK;
    uint32_t count = 0U, *tempbuff = reinterpret_cast<uint32_t*>(buf);

    /* Initialize data control register */
    SDIO->DCTRL = 0U;

    if (m_card_type == ECardType::HIGH_CAPACITY)
    {
        block_size = 512U;
        read_addr /= 512U;
    }

    /* Set Block Size for Card */
    send_command(block_size, ECMD::SET_BLOCKLEN, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SET_BLOCKLEN);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Configure the SD DPSM (Data Path State Machine) */
    data_config(SD_DATATIMEOUT, blocks * block_size, DATA_BLOCK_SIZE,
                ETransferDir::TO_SDIO, ETransferMode::BLOCK,
                EDPSM::ENABLE);

    if (blocks > 1U)
    {
        /* Send CMD18 READ_MULT_BLOCK with argument data address */
        send_command(read_addr, ECMD::READ_MULT_BLOCK, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);
    }
    else
    {
        /* Send CMD17 READ_SINGLE_BLOCK */
        send_command(read_addr, ECMD::READ_SINGLE_BLOCK, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);
    }

    /* Read block(s) in polling mode */
    if (blocks > 1U)
    {
        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::READ_MULT_BLOCK);

        if (errorstate != ESDError::OK)
            return errorstate;

        /* Poll on SDIO flags */
        #ifdef SDIO_STA_STBITERR
        while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND | SDIO_FLAG_STBITERR))
        #else /* SDIO_STA_STBITERR not defined */
        while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND))
        #endif /* SDIO_STA_STBITERR */
        {
            if (get_flag(SDIO_FLAG_RXFIFOHF))
            {
                /* Read data from SDIO Rx FIFO */
                for (count = 0U; count < 8U; count++)
                    *(tempbuff + count) = read_FIFO();

                tempbuff += 8U;
            }
        }
    }
    else
    {
    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::READ_SINGLE_BLOCK);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* In case of single block transfer, no need of stop transfer at all */
    #ifdef SDIO_STA_STBITERR
    while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))
    #else /* SDIO_STA_STBITERR not defined */
    while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND))
    #endif /* SDIO_STA_STBITERR */
    {
        if (get_flag(SDIO_FLAG_RXFIFOHF))
        {
            /* Read data from SDIO Rx FIFO */
            for (count = 0U; count < 8U; count++)
                *(tempbuff + count) = read_FIFO();

            tempbuff += 8U;
        }
    }
    }

    /* Send stop transmission command in case of multiblock read */
    if (get_flag(SDIO_FLAG_DATAEND) && (blocks > 1U))
    {
        if ((m_card_type == ECardType::STD_CAPACITY_V1_1) ||
            (m_card_type == ECardType::STD_CAPACITY_V2_0) ||
            (m_card_type == ECardType::HIGH_CAPACITY))
            /* Send stop transmission command */
            errorstate = stop_transfer();
    }

    /* Get error state */
    if (get_flag(SDIO_FLAG_DTIMEOUT))
    {
        clear_flag(SDIO_FLAG_DTIMEOUT);
        return ESDError::DATA_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_DCRCFAIL))
    {
        clear_flag(SDIO_FLAG_DCRCFAIL);
        return ESDError::DATA_CRC_FAIL;
    }
    else if (get_flag(SDIO_FLAG_RXOVERR))
    {
        clear_flag(SDIO_FLAG_RXOVERR);
        return ESDError::RX_OVERRUN;
    }
    #ifdef SDIO_STA_STBITERR
    else if (get_flag(SDIO_FLAG_STBITERR))
    {
        clear_flag(SDIO_FLAG_STBITERR);
        return ESDError::START_BIT_ERR;
    }
    #endif /* SDIO_STA_STBITERR */
    else
    {
        /* No error flag set */
    }

    count = SD_DATATIMEOUT;

    /* Empty FIFO if there is still any data */
    while ((get_flag(SDIO_FLAG_RXDAVL)) && (count > 0U))
    {
        *tempbuff = read_FIFO();
        tempbuff++;
        count--;
    }

    /* Clear all the static flags */
    clear_flag(SDIO_STATIC_FLAGS);

    return errorstate;
}

STM32_SD::ESDError STM32_SD::write_blocks(uint8_t *buf, uint32_t write_addr, uint32_t block_size, uint16_t blocks)
{
    ESDError errorstate = ESDError::OK;
    uint32_t totalnumberofbytes = 0U, bytestransferred = 0U, count = 0U, restwords = 0U;
    uint32_t *tempbuff = reinterpret_cast<uint32_t*>(buf);
    ECardState cardstate  = ECardState::READY;

    /* Initialize data control register */
    SDIO->DCTRL = 0U;

    if (m_card_type == ECardType::HIGH_CAPACITY)
    {
        block_size = 512U;
        write_addr /= 512U;
    }

    /* Set Block Size for Card */
    send_command(block_size, ECMD::SET_BLOCKLEN, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SET_BLOCKLEN);

    if (errorstate != ESDError::OK)
        return errorstate;

    if (blocks > 1U)
        /* Send CMD25 WRITE_MULT_BLOCK with argument data address */
        send_command(write_addr, ECMD::WRITE_MULT_BLOCK, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);
    else
        /* Send CMD24 WRITE_SINGLE_BLOCK */
        send_command(write_addr, ECMD::WRITE_SINGLE_BLOCK, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    if (blocks > 1U)
        errorstate = cmd_resp1_error(ECMD::WRITE_MULT_BLOCK);
    else
        errorstate = cmd_resp1_error(ECMD::WRITE_SINGLE_BLOCK);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Set total number of bytes to write */
    totalnumberofbytes = blocks * block_size;

    /* Configure the SD DPSM (Data Path State Machine) */
    data_config(SD_DATATIMEOUT, blocks * block_size, EDataBlockSize::_512B,
                ETransferDir::TO_CARD, ETransferMode::BLOCK,
                EDPSM::ENABLE);

    /* Write block(s) in polling mode */
    if (blocks > 1U)
    {
        #ifdef SDIO_STA_STBITERR
        while (!get_flag(SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND | SDIO_FLAG_STBITERR))
        #else /* SDIO_STA_STBITERR not defined */
        while (!get_flag(SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND))
        #endif /* SDIO_STA_STBITERR */
        {
            if (get_flag(SDIO_FLAG_TXFIFOHE))
            {
                if ((totalnumberofbytes - bytestransferred) < 32U)
                {
                    restwords = ((totalnumberofbytes - bytestransferred) % 4U == 0U) ?
                                ((totalnumberofbytes - bytestransferred) / 4U) :
                                (( totalnumberofbytes -  bytestransferred) / 4U + 1U);

                    /* Write data to SDIO Tx FIFO */
                    for (count = 0U; count < restwords; count++)
                    {
                        write_FIFO(tempbuff);
                        tempbuff++;
                        bytestransferred += 4U;
                    }
                }
                else
                {
                    /* Write data to SDIO Tx FIFO */
                    for (count = 0U; count < 8U; count++)
                        write_FIFO(tempbuff + count);

                    tempbuff += 8U;
                    bytestransferred += 32U;
                }
            }
        }
    }
    else
    {
        /* In case of single data block transfer no need of stop command at all */
        #ifdef SDIO_STA_STBITERR
        while (!get_flag(SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))
        #else /* SDIO_STA_STBITERR not defined */
        while (!get_flag(SDIO_FLAG_TXUNDERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND))
        #endif /* SDIO_STA_STBITERR */
        {
            if (get_flag(SDIO_FLAG_TXFIFOHE))
            {
                if ((totalnumberofbytes - bytestransferred) < 32U)
                {
                    restwords = ((totalnumberofbytes - bytestransferred) % 4U == 0U) ?
                                ((totalnumberofbytes - bytestransferred) / 4U) :
                                (( totalnumberofbytes -  bytestransferred) / 4U + 1U);

                    /* Write data to SDIO Tx FIFO */
                    for (count = 0U; count < restwords; count++)
                    {
                        write_FIFO(tempbuff);
                        tempbuff++;
                        bytestransferred += 4U;
                    }
                }
                else
                {
                    /* Write data to SDIO Tx FIFO */
                    for (count = 0U; count < 8U; count++)
                        write_FIFO(tempbuff + count);

                    tempbuff += 8U;
                    bytestransferred += 32U;
                }
            }
        }
    }

    /* Send stop transmission command in case of multiblock write */
    if (get_flag(SDIO_FLAG_DATAEND) && (blocks > 1U))
    {
        if ((m_card_type == ECardType::STD_CAPACITY_V1_1) ||
            (m_card_type == ECardType::STD_CAPACITY_V2_0) ||\
            (m_card_type == ECardType::HIGH_CAPACITY))
            /* Send stop transmission command */
            errorstate = stop_transfer();
    }

    /* Get error state */
    if (get_flag(SDIO_FLAG_DTIMEOUT))
    {
        clear_flag(SDIO_FLAG_DTIMEOUT);
        return ESDError::DATA_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_DCRCFAIL))
    {
        clear_flag(SDIO_FLAG_DCRCFAIL);
        return ESDError::DATA_CRC_FAIL;
    }
    else if (get_flag(SDIO_FLAG_TXUNDERR))
    {
        clear_flag(SDIO_FLAG_TXUNDERR);
        return ESDError::TX_UNDERRUN;
    }
    #ifdef SDIO_STA_STBITERR
    else if (get_flag(SDIO_FLAG_STBITERR))
    {
        clear_flag(SDIO_FLAG_STBITERR);
        return ESDError::START_BIT_ERR;
    }
    #endif /* SDIO_STA_STBITERR */
    else
    {
        /* No error flag set */
    }

    /* Clear all the static flags */
    clear_flag(SDIO_STATIC_FLAGS);

    /* Wait till the card is in programming state */
    errorstate = is_card_programming(&cardstate);

    while ((errorstate == ESDError::OK) &&
           ((cardstate == ECardState::PROGRAMMING) ||
            (cardstate == ECardState::RECEIVING)))
        errorstate = is_card_programming(&cardstate);

    return errorstate;
}

STM32_SD::ESDError STM32_SD::erase(uint32_t start_addr, uint32_t end_addr)
{
    ESDError errorstate = ESDError::OK;

    uint32_t delay         = 0U;
    __IO uint32_t maxdelay = 0U;
    ECardState cardstate   = ECardState::READY;

    /* Check if the card command class supports erase command */
    if (((m_CSD[1U] >> 20U) & SD_CCCC_ERASE) == 0U)
        return ESDError::REQUEST_NOT_APPLICABLE;

    /* Get max delay value */
    maxdelay = 120000U / (((SDIO->CLKCR) & 0xFFU) + 2U);

    if ((get_response(EResp::RESP1) & SD_CARD_LOCKED) == SD_CARD_LOCKED)
        return ESDError::LOCK_UNLOCK_FAILED;

    /* Get start and end block for high capacity cards */
    if (m_card_type == ECardType::HIGH_CAPACITY)
    {
        start_addr /= 512U;
        end_addr   /= 512U;
    }

    /* According to sd-card spec 1.0 ERASE_GROUP_START (CMD32) and erase_group_end(CMD33) */
    if ((m_card_type == ECardType::STD_CAPACITY_V1_1) ||
        (m_card_type == ECardType::STD_CAPACITY_V2_0) ||
        (m_card_type == ECardType::HIGH_CAPACITY))
    {
        /* Send CMD32 SD_ERASE_GRP_START with argument as addr  */
        send_command(start_addr, ECMD::SD_ERASE_GRP_START, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::SD_ERASE_GRP_START);

        if (errorstate != ESDError::OK)
            return errorstate;

        /* Send CMD33 SD_ERASE_GRP_END with argument as addr  */
        send_command(end_addr, ECMD::SD_ERASE_GRP_END, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::SD_ERASE_GRP_END);

        if (errorstate != ESDError::OK)
            return errorstate;
    }

    /* Send CMD38 ERASE */
    send_command(0, ECMD::ERASE, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::ERASE);

    if (errorstate != ESDError::OK)
        return errorstate;

    for (; delay < maxdelay; delay++) {}

    /* Wait until the card is in programming state */
    errorstate = is_card_programming(&cardstate);

    delay = SD_DATATIMEOUT;

    while ((delay > 0U) &&
           (errorstate == ESDError::OK) &&
           ((cardstate == ECardState::PROGRAMMING) ||
            (cardstate == ECardState::RECEIVING)))
    {
        errorstate = is_card_programming(&cardstate);
        delay--;
    }

    return errorstate;
}

STM32_SD::ESDError STM32_SD::high_speed()
{
    ESDError errorstate = ESDError::OK;

    uint8_t SD_hs[64U]  = {0U};
    uint32_t SD_scr[2U] = {0U, 0U};
    uint32_t SD_SPEC    = 0U;
    uint32_t count = 0U, *tempbuff = reinterpret_cast<uint32_t*>(SD_hs);

    /* Initialize the Data control register */
    SDIO->DCTRL = 0U;

    /* Get SCR Register */
    errorstate = find_SCR(SD_scr);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Test the Version supported by the card*/
    SD_SPEC = (SD_scr[1U]  & 0x01000000U) | (SD_scr[1U]  & 0x02000000U);

    if (SD_SPEC != SD_ALLZERO)
    {
        /* Set Block Size for Card */
        send_command(64U, ECMD::SET_BLOCKLEN, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::SET_BLOCKLEN);

        if (errorstate != ESDError::OK)
            return errorstate;

        /* Configure the SD DPSM (Data Path State Machine) */
        data_config(SD_DATATIMEOUT, 64U, EDataBlockSize::_64B,
                    ETransferDir::TO_SDIO, ETransferMode::BLOCK,
                    EDPSM::ENABLE);

        /* Send CMD6 switch mode */
        send_command(0x80FFFF01U, ECMD::HS_SWITCH, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::HS_SWITCH);

        if (errorstate != ESDError::OK)
            return errorstate;
        #ifdef SDIO_STA_STBITERR
        while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))
        #else /* SDIO_STA_STBITERR */
        while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND))
        #endif /* SDIO_STA_STBITERR */
        {
            if (get_flag(SDIO_FLAG_RXFIFOHF))
            {
                for (count = 0U; count < 8U; count++)
                    *(tempbuff + count) = read_FIFO();

                tempbuff += 8U;
            }
        }

        if (get_flag(SDIO_FLAG_DTIMEOUT))
        {
            clear_flag(SDIO_FLAG_DTIMEOUT);
            return ESDError::DATA_TIMEOUT;
        }
        else if (get_flag(SDIO_FLAG_DCRCFAIL))
        {
            clear_flag(SDIO_FLAG_DCRCFAIL);
            return ESDError::DATA_CRC_FAIL;
        }
        else if (get_flag(SDIO_FLAG_RXOVERR))
        {
            clear_flag(SDIO_FLAG_RXOVERR);
            return ESDError::RX_OVERRUN;
        }
        #ifdef SDIO_STA_STBITERR
        else if (get_flag(SDIO_FLAG_STBITERR))
        {
            clear_flag(SDIO_FLAG_STBITERR);
            return ESDError::START_BIT_ERR;
        }
        #endif /* SDIO_STA_STBITERR */
        else
        {
            /* No error flag set */
        }

        count = SD_DATATIMEOUT;

        while ((get_flag(SDIO_FLAG_RXDAVL)) && (count > 0U))
        {
            *tempbuff = read_FIFO();
            tempbuff++;
            count--;
        }

        /* Clear all the static flags */
        clear_flag(SDIO_STATIC_FLAGS);

        /* Test if the switch mode HS is ok */
        if ((SD_hs[13U]& 2U) != 2U)
            errorstate = ESDError::UNSUPPORTED_FEATURE;
    }

    return errorstate;
}

STM32_SD::ESDError STM32_SD::send_SD_status(uint32_t *status)
{
    ESDError errorstate = ESDError::OK;
    uint32_t count = 0U;

    /* Check SD response */
    if ((get_response(EResp::RESP1) & SD_CARD_LOCKED) == SD_CARD_LOCKED)
        return ESDError::LOCK_UNLOCK_FAILED;

    /* Set block size for card if it is not equal to current block size for card */
    send_command(64U, ECMD::SET_BLOCKLEN, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SET_BLOCKLEN);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Send CMD55 */
    send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::APP_CMD, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::APP_CMD);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Configure the SD DPSM (Data Path State Machine) */
    data_config(SD_DATATIMEOUT, 64U, EDataBlockSize::_64B,
                ETransferDir::TO_SDIO, ETransferMode::BLOCK,
                EDPSM::ENABLE);

    /* Send ACMD13 (SD_APP_STATUS)  with argument as card's RCA */
    send_command(0, ECMD::SD_APP_STATUS, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SD_APP_STATUS);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Get status data */
    #ifdef SDIO_STA_STBITERR
    while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))
    #else /* SDIO_STA_STBITERR not defined */
    while (!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND))
    #endif /* SDIO_STA_STBITERR */
    {
        if (get_flag(SDIO_FLAG_RXFIFOHF))
        {
            for (count = 0U; count < 8U; count++)
                *(status + count) = read_FIFO();

            status += 8U;
        }
    }

    if (get_flag(SDIO_FLAG_DTIMEOUT))
    {
        clear_flag(SDIO_FLAG_DTIMEOUT);
        return ESDError::DATA_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_DCRCFAIL))
    {
        clear_flag(SDIO_FLAG_DCRCFAIL);
        return ESDError::DATA_CRC_FAIL;
    }
    else if (get_flag(SDIO_FLAG_RXOVERR))
    {
        clear_flag(SDIO_FLAG_RXOVERR);
        return ESDError::RX_OVERRUN;
    }
    #ifdef SDIO_STA_STBITERR
    else if (get_flag(SDIO_FLAG_STBITERR))
    {
        clear_flag(SDIO_FLAG_STBITERR);
        return ESDError::START_BIT_ERR;
    }
    #endif /* SDIO_STA_STBITERR */
    else
    {
        /* No error flag set */
    }

    count = SD_DATATIMEOUT;
    while ((get_flag(SDIO_FLAG_RXDAVL)) && (count > 0U))
    {
        *status = read_FIFO();
        status++;
        count--;
    }

    /* Clear all the static status flags*/
    clear_flag(SDIO_STATIC_FLAGS);

    return errorstate;
}

void STM32_SD::init_gpio()
{
    STM32_RCC::enable_clk_SDIO();

    gpioc.set_config(STM32_GPIO::PIN_8 | STM32_GPIO::PIN_9 | STM32_GPIO::PIN_10 |
                     STM32_GPIO::PIN_11 | STM32_GPIO::PIN_12, STM32_GPIO::EMode::AF_PP,
                     STM32_GPIO::EAF::AF12_SDIO, STM32_GPIO::ESpeed::VERY_HIGH,
                     STM32_GPIO::EPull::NOPULL);

    gpiod.set_config(STM32_GPIO::PIN_2, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF12_SDIO,
                     STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::NOPULL);
}

void STM32_SD::deinit_gpio()
{
    gpioc.unset_config(STM32_GPIO::PIN_8 | STM32_GPIO::PIN_9 | STM32_GPIO::PIN_10 |
                       STM32_GPIO::PIN_11 | STM32_GPIO::PIN_12);
    gpiod.unset_config(STM32_GPIO::PIN_2);
}

void STM32_SD::init_low(EClockEdge clock_edge, EClockBypass clock_bypass,
                        EClockPowerSave clock_power_save, EBusWide bus_wide,
                        EHWFlowControl hw_control, uint32_t clock_div)
{
    uint32_t tmpreg = static_cast<uint32_t>(clock_edge) |
            static_cast<uint32_t>(clock_bypass) |
            static_cast<uint32_t>(clock_power_save) |
            static_cast<uint32_t>(bus_wide) |
            static_cast<uint32_t>(hw_control) | clock_div;
    MODIFY_REG(SDIO->CLKCR, CLKCR_CLEAR_MASK, tmpreg);
}

STM32_SD::ESDError STM32_SD::power_ON()
{
    /* CMD0: GO_IDLE_STATE */
    send_command(0, ECMD::GO_IDLE_STATE, EResponse::NO,
                 EWait::NO, ECPSM::ENABLE);
    ESDError errorstate = cmd_error();
    if (errorstate != ESDError::OK)
    {
        clear_flag(SDIO_STATIC_FLAGS);
        return errorstate;
    }

    /* CMD8: SEND_IF_COND ------------------------------------------------------*/
    /* Send CMD8 to verify SD card interface operating condition */
    /* Argument: - [31:12]: Reserved (shall be set to '0')
    - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
    - [7:0]: Check Pattern (recommended 0xAA) */
    uint32_t sdtype = SD_STD_CAPACITY;
    send_command(SD_CHECK_PATTERN, ECMD::HS_SEND_EXT_CSD, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);
    errorstate = cmd_resp7_error();
    if (errorstate != ESDError::OK)
    {
        m_card_type = ECardType::STD_CAPACITY_V1_1;
        sdtype = SD_STD_CAPACITY;
    }
    else
    {
        /* SD Card 2.0 */
        m_card_type = ECardType::STD_CAPACITY_V2_0;
        sdtype = SD_HIGH_CAPACITY;
    }

    /* Send CMD55 */
    send_command(0, ECMD::APP_CMD, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);
    /* If errorstate is Command Timeout, it is a MMC card */
    /* If errorstate is ESDError::OK it is a SD card: SD card 2.0 (voltage range mismatch)
        or SD card 1.x */
    uint32_t response = 0;
    errorstate = cmd_resp1_error(ECMD::APP_CMD);
    if (errorstate == ESDError::OK)
    {
        /* SD CARD */
        /* Send ACMD41 SD_APP_OP_COND with Argument 0x80100000 */
        uint32_t validvoltage = 0;
        uint32_t count = 0;
        while ((!validvoltage) && (count <SD_MAX_VOLT_TRIAL))
        {
            /* SEND CMD55 APP_CMD with RCA as 0 */
            send_command(0, ECMD::APP_CMD, EResponse::SHORT,
                         EWait::NO, ECPSM::ENABLE);
            errorstate = cmd_resp1_error(ECMD::APP_CMD);
            if (errorstate != ESDError::OK)
                return errorstate;

            /* Send CMD41 */
            send_command(SD_VOLTAGE_WINDOW_SD | sdtype, ECMD::SD_APP_OP_COND,
                         EResponse::SHORT, EWait::NO, ECPSM::ENABLE);
            errorstate = cmd_resp3_error();
            if (errorstate != ESDError::OK)
                return errorstate;

            /* Get command response */
            response = get_response(EResp::RESP1);
            validvoltage = ((response & SD_VOLTAGE_WINDOW_WALID) == SD_VOLTAGE_WINDOW_WALID);

            ++count;
        }

        if (count >= SD_MAX_VOLT_TRIAL)
            return ESDError::INVALID_VOLTRANGE;

        if ((response & SD_HIGH_CAPACITY) == SD_HIGH_CAPACITY)
            m_card_type = ECardType::HIGH_CAPACITY;
        else
            m_card_type = ECardType::STD_CAPACITY_V2_0;
    } /* else MMC Card */
    else
    {
    }

    return errorstate;
}

STM32_SD::ESDError STM32_SD::power_OFF()
{
    SDIO->POWER = 0x00000000U;
    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::send_status(uint32_t *card_status)
{
    ESDError errorstate = ESDError::OK;

    if(card_status == nullptr)
        return ESDError::INVALID_PARAMETER;

    /* Send Status command */
    send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::SEND_STATUS, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SEND_STATUS);

    if(errorstate != ESDError::OK)
        return errorstate;

    /* Get SD card status */
    *card_status = get_response(EResp::RESP1);

    return errorstate;
}

STM32_SD::ESDError STM32_SD::initialize_cards()
{
    ESDError errorstate = ESDError::OK;
    uint16_t sd_rca = 1;

    if (get_power_state() == 0)
        /* Power off */
        return ESDError::REQUEST_NOT_APPLICABLE;

    if (m_card_type != ECardType::SECURE_DIGITAL_IO)
    {
        /* Send CMD2 ALL_SEND_CID */
        send_command(0, ECMD::ALL_SEND_CID, EResponse::LONG,
                     EWait::NO, ECPSM::ENABLE);
        if ((errorstate = cmd_resp2_error()) != ESDError::OK)
            return errorstate;

        m_CID[0] = get_response(EResp::RESP1);
        m_CID[1] = get_response(EResp::RESP2);
        m_CID[2] = get_response(EResp::RESP3);
        m_CID[3] = get_response(EResp::RESP4);
    }

    if ((m_card_type == ECardType::STD_CAPACITY_V1_1) ||
        (m_card_type == ECardType::STD_CAPACITY_V2_0) ||
        (m_card_type == ECardType::SECURE_DIGITAL_IO_COMBO) ||
        (m_card_type == ECardType::HIGH_CAPACITY))
    {
        /* Send CMD3 SET_REL_ADDR with argument 0 */
        /* SD Card publishes its RCA. */
        send_command(0, ECMD::SET_REL_ADDR, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);
        if ((errorstate = cmd_resp6_error(ECMD::SET_REL_ADDR, &sd_rca)) != ESDError::OK)
            return errorstate;
    }

    if (m_card_type != ECardType::SECURE_DIGITAL_IO)
    {
        /* Get the SD card RCA */
        m_RCA = sd_rca;

        /* Send CMD9 SEND_CSD with argument as card's RCA */
        send_command(static_cast<uint32_t>(m_RCA << 16), ECMD::SEND_CSD, EResponse::LONG,
                     EWait::NO, ECPSM::ENABLE);
        if ((errorstate = cmd_resp2_error()) != ESDError::OK)
            return errorstate;

        m_CSD[0] = get_response(EResp::RESP1);
        m_CSD[1] = get_response(EResp::RESP2);
        m_CSD[2] = get_response(EResp::RESP3);
        m_CSD[3] = get_response(EResp::RESP4);
    }

    return errorstate;
}

void STM32_SD::send_command(uint32_t arg, ECMD cmd,
                            EResponse resp, EWait wait_IT,
                            ECPSM cpsm)
{
    SDIO->ARG = arg;
    MODIFY_REG(SDIO->CMD, CMD_CLEAR_MASK, (static_cast<uint32_t>(cmd) |
                                           static_cast<uint32_t>(resp) |
                                           static_cast<uint32_t>(wait_IT) |
                                           static_cast<uint32_t>(cpsm)));
}

STM32_SD::ESDError STM32_SD::cmd_error()
{
    WAIT_TIMEOUT_EX((!get_flag(SDIO_FLAG_CMDSENT)), SDIO_CMD0TIMEOUT, ESDError::CMD_RSP_TIMEOUT);
    clear_flag(SDIO_STATIC_FLAGS);
    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::cmd_resp7_error()
{
    WAIT_TIMEOUT_EX((!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)),
                 SDIO_CMD0TIMEOUT, ESDError::CMD_RSP_TIMEOUT);

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        /* Card is not V2.0 compliant or card does not support the set voltage range */
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }
    if (get_flag(SDIO_FLAG_CMDREND))
    {
        /* Card is SD V2.0 compliant */
        clear_flag(SDIO_FLAG_CMDREND);
        return ESDError::OK;
    }

    return ESDError::ERROR;
}

STM32_SD::ESDError STM32_SD::cmd_resp1_error(ECMD cmd)
{
    while (!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) {}

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_CCRCFAIL))
    {
        clear_flag(SDIO_FLAG_CCRCFAIL);
        return ESDError::CMD_CRC_FAIL;
    }

    /* Check response received is of desired command */
    if (get_cmd_response() != cmd)
        return ESDError::CMD_CRC_FAIL;

    /* Clear all the static flags */
    clear_flag(SDIO_STATIC_FLAGS);

    uint32_t response_r1 = get_response(EResp::RESP1);

    if ((response_r1 & EOCRMasks::ERRORBITS) == SD_ALLZERO)
        return ESDError::OK;

    if ((response_r1 & EOCRMasks::ADDR_OUT_OF_RANGE))
        return ESDError::ADDR_OUT_OF_RANGE;

    if ((response_r1 & EOCRMasks::ADDR_MISALIGNED))
        return ESDError::ADDR_MISALIGNED;

    if ((response_r1 & EOCRMasks::BLOCK_LEN_ERR))
        return ESDError::BLOCK_LEN_ERR;

    if ((response_r1 & EOCRMasks::ERASE_SEQ_ERR))
        return ESDError::ERASE_SEQ_ERR;

    if ((response_r1 & EOCRMasks::BAD_ERASE_PARAM))
        return ESDError::BAD_ERASE_PARAM;

    if ((response_r1 & EOCRMasks::WRITE_PROT_VIOLATION))
        return ESDError::WRITE_PROT_VIOLATION;

    if ((response_r1 & EOCRMasks::LOCK_UNLOCK_FAILED))
        return ESDError::LOCK_UNLOCK_FAILED;

    if ((response_r1 & EOCRMasks::COM_CRC_FAILED))
        return ESDError::COM_CRC_FAILED;

    /*if ((response_r1 & EOCRMasks::ILLEGAL_CMD))
        return ESDError::ILLEGAL_CMD;*/

    if ((response_r1 & EOCRMasks::CARD_ECC_FAILED))
        return ESDError::CARD_ECC_FAILED;

    if ((response_r1 & EOCRMasks::CC_ERROR))
        return ESDError::CC_ERROR;

    if ((response_r1 & EOCRMasks::GENERAL_UNKNOWN_ERROR))
        return ESDError::GENERAL_UNKNOWN_ERROR;

    if ((response_r1 & EOCRMasks::STREAM_READ_UNDERRUN))
        return ESDError::STREAM_READ_UNDERRUN;

    if ((response_r1 & EOCRMasks::STREAM_WRITE_OVERRUN))
        return ESDError::STREAM_WRITE_OVERRUN;

    if ((response_r1 & EOCRMasks::CID_CSD_OVERWRITE))
        return ESDError::CID_CSD_OVERWRITE;

    if ((response_r1 & EOCRMasks::WP_ERASE_SKIP))
        return ESDError::WP_ERASE_SKIP;

    if ((response_r1 & EOCRMasks::CARD_ECC_DISABLED))
        return ESDError::CARD_ECC_DISABLED;

    if ((response_r1 & EOCRMasks::ERASE_RESET))
        return ESDError::ERASE_RESET;

    if ((response_r1 & EOCRMasks::AKE_SEQ_ERROR))
        return ESDError::AKE_SEQ_ERROR;

    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::cmd_resp3_error()
{
    while (!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) {}

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }

    clear_flag(SDIO_STATIC_FLAGS);
    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::cmd_resp2_error()
{
    while (!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) {}

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_CCRCFAIL))
    {
        clear_flag(SDIO_FLAG_CCRCFAIL);
        return ESDError::CMD_CRC_FAIL;
    }

    clear_flag(SDIO_STATIC_FLAGS);
    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::cmd_resp6_error(ECMD cmd, uint16_t *pRCA)
{
    while (!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) {}

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_CCRCFAIL))
    {
        clear_flag(SDIO_FLAG_CCRCFAIL);
        return ESDError::CMD_CRC_FAIL;
    }

    if (get_cmd_response() != cmd)
        return ESDError::ILLEGAL_CMD;

    clear_flag(SDIO_STATIC_FLAGS);

    ER6Msk response_r1 = static_cast<ER6Msk>(get_response(EResp::RESP1));

    if (response_r1 & ER6Msk::GENERAL_UNKNOWN_ERROR_6)
        return ESDError::GENERAL_UNKNOWN_ERROR;
    if (response_r1 & ER6Msk::ILLEGAL_CMD_6)
        return ESDError::ILLEGAL_CMD;
    if (response_r1 & ER6Msk::COM_CRC_FAILED_6)
        return ESDError::COM_CRC_FAILED;
    *pRCA = response_r1 >> 16;

    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::data_config(uint32_t time_out, uint32_t dat_len,
                                        EDataBlockSize block_size, ETransferDir transf_dir,
                                        ETransferMode transf_mode, EDPSM DPSM)
{
    SDIO->DTIMER = time_out;
    SDIO->DLEN = dat_len;
    uint32_t tmpreg = static_cast<uint32_t>(block_size) |
                      static_cast<uint32_t>(transf_dir) |
                      static_cast<uint32_t>(transf_mode) |
                      static_cast<uint32_t>(DPSM);
    MODIFY_REG(SDIO->DCTRL, DCTRL_CLEAR_MASK, tmpreg);
    return ESDError::OK;
}

STM32_SD::ESDError STM32_SD::stop_transfer()
{
    send_command(0, ECMD::STOP_TRANSMISSION, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    return cmd_resp1_error(ECMD::STOP_TRANSMISSION);
}

STM32_SD::ESDError STM32_SD::get_card_info()
{
    ESDError errorstate = ESDError::OK;

    m_card_info.CardType = static_cast<uint8_t>(m_card_type);
    m_card_info.RCA = m_RCA;

    /* Byte 1 */
    uint32_t tmp = (m_CSD[0U] & 0x00FF0000U) >> 16U;
    m_card_info.SD_csd.TAAC = static_cast<uint8_t>(tmp);

    /* Byte 2 */
    tmp = (m_CSD[0U] & 0x0000FF00U) >> 8U;
    m_card_info.SD_csd.NSAC = static_cast<uint8_t>(tmp);

    /* Byte 3 */
    tmp = m_CSD[0U] & 0x000000FFU;
    m_card_info.SD_csd.MaxBusClkFrec = static_cast<uint8_t>(tmp);

    /* Byte 4 */
    tmp = (m_CSD[1U] & 0xFF000000U) >> 24U;
    m_card_info.SD_csd.CardComdClasses = static_cast<uint16_t>(tmp << 4U);

    /* Byte 5 */
    tmp = (m_CSD[1U] & 0x00FF0000U) >> 16U;
    m_card_info.SD_csd.CardComdClasses |= static_cast<uint16_t>((tmp & 0xF0) >> 4U);
    m_card_info.SD_csd.RdBlockLen       = static_cast<uint8_t>(tmp & 0x0FU);

    /* Byte 6 */
    tmp = (m_CSD[1U] & 0x0000FF00U) >> 8U;
    m_card_info.SD_csd.PartBlockRead   = static_cast<uint8_t>((tmp & 0x80U) >> 7U);
    m_card_info.SD_csd.WrBlockMisalign = static_cast<uint8_t>((tmp & 0x40U) >> 6U);
    m_card_info.SD_csd.RdBlockMisalign = static_cast<uint8_t>((tmp & 0x20U) >> 5U);
    m_card_info.SD_csd.DSRImpl         = static_cast<uint8_t>((tmp & 0x10U) >> 4U);
    m_card_info.SD_csd.Reserved2       = 0U; /*!< Reserved */

    if ((m_card_type == ECardType::STD_CAPACITY_V1_1) || (m_card_type == ECardType::STD_CAPACITY_V2_0))
    {
        m_card_info.SD_csd.DeviceSize = (tmp & 0x03U) << 10U;

        /* Byte 7 */
        tmp = static_cast<uint8_t>(m_CSD[1U] & 0x000000FFU);
        m_card_info.SD_csd.DeviceSize |= (tmp) << 2U;

        /* Byte 8 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0xFF000000U) >> 24U);
        m_card_info.SD_csd.DeviceSize |= (tmp & 0xC0U) >> 6U;

        m_card_info.SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38U) >> 3U;
        m_card_info.SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07U);

        /* Byte 9 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0x00FF0000U) >> 16U);
        m_card_info.SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0U) >> 5U;
        m_card_info.SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1CU) >> 2U;
        m_card_info.SD_csd.DeviceSizeMul      = static_cast<uint8_t>((tmp & 0x03U) << 1U);
        /* Byte 10 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0x0000FF00U) >> 8U);
        m_card_info.SD_csd.DeviceSizeMul |= (tmp & 0x80U) >> 7U;

        m_card_info.CardCapacity  = (m_card_info.SD_csd.DeviceSize + 1U) ;
        m_card_info.CardCapacity *= (1U << (m_card_info.SD_csd.DeviceSizeMul + 2U));
        m_card_info.CardBlockSize = 1U << (m_card_info.SD_csd.RdBlockLen);
        m_card_info.CardCapacity *= m_card_info.CardBlockSize;
    }
    else if (m_card_type == ECardType::HIGH_CAPACITY)
    {
        /* Byte 7 */
        tmp = static_cast<uint8_t>(m_CSD[1U] & 0x000000FFU);
        m_card_info.SD_csd.DeviceSize = (tmp & 0x3FU) << 16U;

        /* Byte 8 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0xFF000000U) >> 24U);

        m_card_info.SD_csd.DeviceSize |= (tmp << 8U);

        /* Byte 9 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0x00FF0000U) >> 16U);

        m_card_info.SD_csd.DeviceSize |= (tmp);

        /* Byte 10 */
        tmp = static_cast<uint8_t>((m_CSD[2U] & 0x0000FF00U) >> 8U);

        m_card_info.CardCapacity = static_cast<uint64_t>((m_card_info.SD_csd.DeviceSize + 1U) * 512U * 1024U);
        m_card_info.CardBlockSize = 512U;
    }
    else
    {
        /* Not supported card type */
        errorstate = ESDError::ERROR;
    }

    m_card_info.SD_csd.EraseGrSize = (tmp & 0x40U) >> 6U;
    m_card_info.SD_csd.EraseGrMul  = static_cast<uint8_t>((tmp & 0x3FU) << 1U);

    /* Byte 11 */
    tmp = static_cast<uint8_t>(m_CSD[2U] & 0x000000FFU);
    m_card_info.SD_csd.EraseGrMul     |= (tmp & 0x80U) >> 7U;
    m_card_info.SD_csd.WrProtectGrSize = (tmp & 0x7FU);

    /* Byte 12 */
    tmp = static_cast<uint8_t>((m_CSD[3U] & 0xFF000000U) >> 24U);
    m_card_info.SD_csd.WrProtectGrEnable = (tmp & 0x80U) >> 7U;
    m_card_info.SD_csd.ManDeflECC        = (tmp & 0x60U) >> 5U;
    m_card_info.SD_csd.WrSpeedFact       = (tmp & 0x1CU) >> 2U;
    m_card_info.SD_csd.MaxWrBlockLen     = static_cast<uint8_t>((tmp & 0x03U) << 2U);

    /* Byte 13 */
    tmp = static_cast<uint8_t>((m_CSD[3U] & 0x00FF0000U) >> 16U);
    m_card_info.SD_csd.MaxWrBlockLen      |= (tmp & 0xC0U) >> 6U;
    m_card_info.SD_csd.WriteBlockPaPartial = (tmp & 0x20U) >> 5U;
    m_card_info.SD_csd.Reserved3           = 0U;
    m_card_info.SD_csd.ContentProtectAppli = (tmp & 0x01U);

    /* Byte 14 */
    tmp = static_cast<uint8_t>((m_CSD[3U] & 0x0000FF00U) >> 8U);
    m_card_info.SD_csd.FileFormatGrouop = (tmp & 0x80U) >> 7U;
    m_card_info.SD_csd.CopyFlag         = (tmp & 0x40U) >> 6U;
    m_card_info.SD_csd.PermWrProtect    = (tmp & 0x20U) >> 5U;
    m_card_info.SD_csd.TempWrProtect    = (tmp & 0x10U) >> 4U;
    m_card_info.SD_csd.FileFormat       = (tmp & 0x0CU) >> 2U;
    m_card_info.SD_csd.ECC              = (tmp & 0x03U);

    /* Byte 15 */
    tmp = static_cast<uint8_t>(m_CSD[3U] & 0x000000FFU);
    m_card_info.SD_csd.CSD_CRC   = (tmp & 0xFEU) >> 1U;
    m_card_info.SD_csd.Reserved4 = 1U;

    /* Byte 0 */
    tmp = static_cast<uint8_t>((m_CID[0U] & 0xFF000000U) >> 24U);
    m_card_info.SD_cid.ManufacturerID = static_cast<uint8_t>(tmp);

    /* Byte 1 */
    tmp = static_cast<uint8_t>((m_CID[0U] & 0x00FF0000U) >> 16U);
    m_card_info.SD_cid.OEM_AppliID = static_cast<uint8_t>(tmp << 8U);

    /* Byte 2 */
    tmp = static_cast<uint8_t>((m_CID[0U] & 0x0000FF00U) >> 8U);
    m_card_info.SD_cid.OEM_AppliID |= tmp;

    /* Byte 3 */
    tmp = static_cast<uint8_t>(m_CID[0U] & 0x000000FFU);
    m_card_info.SD_cid.ProdName1 = tmp << 24U;

    /* Byte 4 */
    tmp = static_cast<uint8_t>((m_CID[1U] & 0xFF000000U) >> 24U);
    m_card_info.SD_cid.ProdName1 |= tmp << 16U;

    /* Byte 5 */
    tmp = static_cast<uint8_t>((m_CID[1U] & 0x00FF0000U) >> 16U);
    m_card_info.SD_cid.ProdName1 |= tmp << 8U;

    /* Byte 6 */
    tmp = static_cast<uint8_t>((m_CID[1U] & 0x0000FF00U) >> 8U);
    m_card_info.SD_cid.ProdName1 |= tmp;

    /* Byte 7 */
    tmp = static_cast<uint8_t>(m_CID[1U] & 0x000000FFU);
    m_card_info.SD_cid.ProdName2 = static_cast<uint8_t>(tmp);

    /* Byte 8 */
    tmp = static_cast<uint8_t>((m_CID[2U] & 0xFF000000U) >> 24U);
    m_card_info.SD_cid.ProdRev = static_cast<uint8_t>(tmp);

    /* Byte 9 */
    tmp = static_cast<uint8_t>((m_CID[2U] & 0x00FF0000U) >> 16U);
    m_card_info.SD_cid.ProdSN = tmp << 24U;

    /* Byte 10 */
    tmp = static_cast<uint8_t>((m_CID[2U] & 0x0000FF00U) >> 8U);
    m_card_info.SD_cid.ProdSN |= tmp << 16U;

    /* Byte 11 */
    tmp = static_cast<uint8_t>(m_CID[2U] & 0x000000FFU);
    m_card_info.SD_cid.ProdSN |= tmp << 8U;

    /* Byte 12 */
    tmp = static_cast<uint8_t>((m_CID[3U] & 0xFF000000U) >> 24U);
    m_card_info.SD_cid.ProdSN |= tmp;

    /* Byte 13 */
    tmp = static_cast<uint8_t>((m_CID[3U] & 0x00FF0000U) >> 16U);
    m_card_info.SD_cid.Reserved1   |= (tmp & 0xF0U) >> 4U;
    m_card_info.SD_cid.ManufactDate = static_cast<uint16_t>((tmp & 0x0FU) << 8U);

    /* Byte 14 */
    tmp = static_cast<uint8_t>((m_CID[3U] & 0x0000FF00U) >> 8U);
    m_card_info.SD_cid.ManufactDate |= tmp;

    /* Byte 15 */
    tmp = static_cast<uint8_t>(m_CID[3U] & 0x000000FFU);
    m_card_info.SD_cid.CID_CRC   = (tmp & 0xFEU) >> 1U;
    m_card_info.SD_cid.Reserved2 = 1U;

    return errorstate;
}

STM32_SD::ESDError STM32_SD::select_deselect(uint32_t addr)
{
    send_command(addr, ECMD::SEL_DESEL_CARD, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);
    return cmd_resp1_error(ECMD::SEL_DESEL_CARD);
}

STM32_SD::ESDError STM32_SD::is_card_programming(ECardState *status)
{
    ESDError errorstate = ESDError::OK;
    __IO uint32_t responseR1 = 0U;

    send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::SEND_STATUS, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    while (!get_flag(SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)) {}

    if (get_flag(SDIO_FLAG_CTIMEOUT))
    {
        clear_flag(SDIO_FLAG_CTIMEOUT);
        return ESDError::CMD_RSP_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_CCRCFAIL))
    {
        clear_flag(SDIO_FLAG_CCRCFAIL);
        return ESDError::CMD_CRC_FAIL;
    }
    else
    {
        /* No error flag set */
    }

    /* Check response received is of desired command */
    if (get_cmd_response() != ECMD::SEND_STATUS)
        return ESDError::ILLEGAL_CMD;

    /* Clear all the static flags */
    clear_flag(SDIO_STATIC_FLAGS);


    /* We have received response, retrieve it for analysis */
    responseR1 = get_response(EResp::RESP1);

    /* Find out card status */
    *status = static_cast<ECardState>((responseR1 >> 9U) & 0x0000000FU);

    if ((responseR1 & EOCRMasks::ERRORBITS) == SD_ALLZERO)
        return errorstate;

    if ((responseR1 & EOCRMasks::ADDR_OUT_OF_RANGE) == EOCRMasks::ADDR_OUT_OF_RANGE)
        return(ESDError::ADDR_OUT_OF_RANGE);

    if ((responseR1 & EOCRMasks::ADDR_MISALIGNED) == EOCRMasks::ADDR_MISALIGNED)
        return(ESDError::ADDR_MISALIGNED);

    if ((responseR1 & EOCRMasks::BLOCK_LEN_ERR) == EOCRMasks::BLOCK_LEN_ERR)
        return(ESDError::BLOCK_LEN_ERR);

    if ((responseR1 & EOCRMasks::ERASE_SEQ_ERR) == EOCRMasks::ERASE_SEQ_ERR)
        return(ESDError::ERASE_SEQ_ERR);

    if ((responseR1 & EOCRMasks::BAD_ERASE_PARAM) == EOCRMasks::BAD_ERASE_PARAM)
        return(ESDError::BAD_ERASE_PARAM);

    if ((responseR1 & EOCRMasks::WRITE_PROT_VIOLATION) == EOCRMasks::WRITE_PROT_VIOLATION)
        return(ESDError::WRITE_PROT_VIOLATION);

    if ((responseR1 & EOCRMasks::LOCK_UNLOCK_FAILED) == EOCRMasks::LOCK_UNLOCK_FAILED)
        return(ESDError::LOCK_UNLOCK_FAILED);

    if ((responseR1 & EOCRMasks::COM_CRC_FAILED) == EOCRMasks::COM_CRC_FAILED)
        return(ESDError::COM_CRC_FAILED);

    if ((responseR1 & EOCRMasks::ILLEGAL_CMD) == EOCRMasks::ILLEGAL_CMD)
        return(ESDError::ILLEGAL_CMD);

    if ((responseR1 & EOCRMasks::CARD_ECC_FAILED) == EOCRMasks::CARD_ECC_FAILED)
        return(ESDError::CARD_ECC_FAILED);

    if ((responseR1 & EOCRMasks::CC_ERROR) == EOCRMasks::CC_ERROR)
        return(ESDError::CC_ERROR);

    if ((responseR1 & EOCRMasks::GENERAL_UNKNOWN_ERROR) == EOCRMasks::GENERAL_UNKNOWN_ERROR)
        return(ESDError::GENERAL_UNKNOWN_ERROR);

    if ((responseR1 & EOCRMasks::STREAM_READ_UNDERRUN) == EOCRMasks::STREAM_READ_UNDERRUN)
        return(ESDError::STREAM_READ_UNDERRUN);

    if ((responseR1 & EOCRMasks::STREAM_WRITE_OVERRUN) == EOCRMasks::STREAM_WRITE_OVERRUN)
        return(ESDError::STREAM_WRITE_OVERRUN);

    if ((responseR1 & EOCRMasks::CID_CSD_OVERWRITE) == EOCRMasks::CID_CSD_OVERWRITE)
        return(ESDError::CID_CSD_OVERWRITE);

    if ((responseR1 & EOCRMasks::WP_ERASE_SKIP) == EOCRMasks::WP_ERASE_SKIP)
        return(ESDError::WP_ERASE_SKIP);

    if ((responseR1 & EOCRMasks::CARD_ECC_DISABLED) == EOCRMasks::CARD_ECC_DISABLED)
        return(ESDError::CARD_ECC_DISABLED);

    if ((responseR1 & EOCRMasks::ERASE_RESET) == EOCRMasks::ERASE_RESET)
        return(ESDError::ERASE_RESET);

    if ((responseR1 & EOCRMasks::AKE_SEQ_ERROR) == EOCRMasks::AKE_SEQ_ERROR)
        return(ESDError::AKE_SEQ_ERROR);

    return errorstate;
}

STM32_SD::ESDError STM32_SD::wide_bus_enable()
{
    ESDError errorstate = ESDError::OK;

    uint32_t scr[2U] = {0U, 0U};

    if ((get_response(EResp::RESP1) & SD_CARD_LOCKED) == SD_CARD_LOCKED)
        return ESDError::LOCK_UNLOCK_FAILED;

    /* Get SCR Register */
    errorstate = find_SCR(scr);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* If requested card supports wide bus operation */
    if ((scr[1U] & SD_WIDE_BUS_SUPPORT) != SD_ALLZERO)
    {
        /* Send CMD55 APP_CMD with argument as card's RCA.*/
        send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::APP_CMD, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::APP_CMD);

        if(errorstate != ESDError::OK)
            return errorstate;

        /* Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
        send_command(2, ECMD::APP_SD_SET_BUSWIDTH, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::APP_SD_SET_BUSWIDTH);
    }
    else
        return ESDError::REQUEST_NOT_APPLICABLE;

    return errorstate;
}

STM32_SD::ESDError STM32_SD::wide_bus_disable()
{
    ESDError errorstate = ESDError::OK;

    uint32_t scr[2U] = {0U, 0U};

    if ((get_response(EResp::RESP1) & SD_CARD_LOCKED) == SD_CARD_LOCKED)
        return ESDError::LOCK_UNLOCK_FAILED;

    /* Get SCR Register */
    errorstate = find_SCR(scr);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* If requested card supports 1 bit mode operation */
    if ((scr[1U] & SD_SINGLE_BUS_SUPPORT) != SD_ALLZERO)
    {
        /* Send CMD55 APP_CMD with argument as card's RCA */
        send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::APP_CMD, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::APP_CMD);

        if(errorstate != ESDError::OK)
            return errorstate;

        /* Send ACMD6 APP_CMD with argument as 0 for single bus mode */
        send_command(0, ECMD::APP_SD_SET_BUSWIDTH, EResponse::SHORT,
                     EWait::NO, ECPSM::ENABLE);

        /* Check for error conditions */
        errorstate = cmd_resp1_error(ECMD::APP_SD_SET_BUSWIDTH);
    }
    else
        return ESDError::REQUEST_NOT_APPLICABLE;

    return errorstate;
}

STM32_SD::ESDError STM32_SD::find_SCR(uint32_t *scr)
{
    ESDError errorstate = ESDError::OK;
    uint32_t index = 0U;
    uint32_t tempscr[2U] = {0U, 0U};

    /* Set Block Size To 8 Bytes */
    /* Send CMD55 APP_CMD with argument as card's RCA */
    send_command(8, ECMD::SET_BLOCKLEN, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SET_BLOCKLEN);

    if (errorstate != ESDError::OK)
        return errorstate;

    /* Send CMD55 APP_CMD with argument as card's RCA */
    send_command(static_cast<uint32_t>(m_RCA << 16U), ECMD::APP_CMD, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::APP_CMD);

    if (errorstate != ESDError::OK)
        return errorstate;

    data_config(SD_DATATIMEOUT, 8U,
                EDataBlockSize::_8B, ETransferDir::TO_SDIO,
                ETransferMode::BLOCK, EDPSM::ENABLE);

    /* Send ACMD51 SD_APP_SEND_SCR with argument as 0 */
    send_command(0, ECMD::SD_APP_SEND_SCR, EResponse::SHORT,
                 EWait::NO, ECPSM::ENABLE);

    /* Check for error conditions */
    errorstate = cmd_resp1_error(ECMD::SD_APP_SEND_SCR);

    if (errorstate != ESDError::OK)
        return errorstate;

    #ifdef SDIO_STA_STBITERR
    while(!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR))
    #else /* SDIO_STA_STBITERR not defined */
    while(!get_flag(SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND))
    #endif /* SDIO_STA_STBITERR */
    {
        if(get_flag(SDIO_FLAG_RXDAVL))
        {
            *(tempscr + index) = read_FIFO();
            index++;
        }
    }

    if (get_flag(SDIO_FLAG_DTIMEOUT))
    {
        clear_flag(SDIO_FLAG_DTIMEOUT);
        return ESDError::DATA_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_DCRCFAIL))
    {
        clear_flag(SDIO_FLAG_DCRCFAIL);
        return ESDError::DATA_TIMEOUT;
    }
    else if (get_flag(SDIO_FLAG_RXOVERR))
    {
        clear_flag(SDIO_FLAG_RXOVERR);
        return ESDError::RX_OVERRUN;
    }
    #ifdef SDIO_STA_STBITERR
    else if (get_flag(SDIO_FLAG_STBITERR))
    {
        clear_flag(SDIO_FLAG_STBITERR);
        return ESDError::START_BIT_ERR;
    }
    #endif /* SDIO_STA_STBITERR */
    else
    {
        /* No error flag set */
    }

    /* Clear all the static flags */
    clear_flag(SDIO_STATIC_FLAGS);

    *(scr + 1U) = ((tempscr[0U] & SD_0TO7BITS) << 24U)  | ((tempscr[0U] & SD_8TO15BITS) << 8U) |
                  ((tempscr[0U] & SD_16TO23BITS) >> 8U) | ((tempscr[0U] & SD_24TO31BITS) >> 24U);

    *(scr) = ((tempscr[1U] & SD_0TO7BITS) << 24U)  | ((tempscr[1U] & SD_8TO15BITS) << 8U) |
             ((tempscr[1U] & SD_16TO23BITS) >> 8U) | ((tempscr[1U] & SD_24TO31BITS) >> 24U);

    return errorstate;
}

STM32_SD::ECardState STM32_SD::get_state()
{
    uint32_t resp1 = 0U;

    if (send_status(&resp1) != ESDError::OK)
        return ECardState::ERROR;
    else
        return static_cast<ECardState>((resp1 >> 9U) & 0x0FU);
}

void ISR::SDIO_IRQ()
{
    ///TODO
}

#endif //STM32_USE_SD
