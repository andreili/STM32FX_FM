#ifndef STM32_SD_H
#define STM32_SD_H

#include "stm32_inc.h"

class STM32_SD
{
public:

    typedef struct
    {
      __IO uint8_t  CSDStruct;            /*!< CSD structure                         */
      __IO uint8_t  SysSpecVersion;       /*!< System specification version          */
      __IO uint8_t  Reserved1;            /*!< Reserved                              */
      __IO uint8_t  TAAC;                 /*!< Data read access time 1               */
      __IO uint8_t  NSAC;                 /*!< Data read access time 2 in CLK cycles */
      __IO uint8_t  MaxBusClkFrec;        /*!< Max. bus clock frequency              */
      __IO uint16_t CardComdClasses;      /*!< Card command classes                  */
      __IO uint8_t  RdBlockLen;           /*!< Max. read data block length           */
      __IO uint8_t  PartBlockRead;        /*!< Partial blocks for read allowed       */
      __IO uint8_t  WrBlockMisalign;      /*!< Write block misalignment              */
      __IO uint8_t  RdBlockMisalign;      /*!< Read block misalignment               */
      __IO uint8_t  DSRImpl;              /*!< DSR implemented                       */
      __IO uint8_t  Reserved2;            /*!< Reserved                              */
      __IO uint32_t DeviceSize;           /*!< Device Size                           */
      __IO uint8_t  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min           */
      __IO uint8_t  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max           */
      __IO uint8_t  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min          */
      __IO uint8_t  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max          */
      __IO uint8_t  DeviceSizeMul;        /*!< Device size multiplier                */
      __IO uint8_t  EraseGrSize;          /*!< Erase group size                      */
      __IO uint8_t  EraseGrMul;           /*!< Erase group size multiplier           */
      __IO uint8_t  WrProtectGrSize;      /*!< Write protect group size              */
      __IO uint8_t  WrProtectGrEnable;    /*!< Write protect group enable            */
      __IO uint8_t  ManDeflECC;           /*!< Manufacturer default ECC              */
      __IO uint8_t  WrSpeedFact;          /*!< Write speed factor                    */
      __IO uint8_t  MaxWrBlockLen;        /*!< Max. write data block length          */
      __IO uint8_t  WriteBlockPaPartial;  /*!< Partial blocks for write allowed      */
      __IO uint8_t  Reserved3;            /*!< Reserved                              */
      __IO uint8_t  ContentProtectAppli;  /*!< Content protection application        */
      __IO uint8_t  FileFormatGrouop;     /*!< File format group                     */
      __IO uint8_t  CopyFlag;             /*!< Copy flag (OTP)                       */
      __IO uint8_t  PermWrProtect;        /*!< Permanent write protection            */
      __IO uint8_t  TempWrProtect;        /*!< Temporary write protection            */
      __IO uint8_t  FileFormat;           /*!< File format                           */
      __IO uint8_t  ECC;                  /*!< ECC code                              */
      __IO uint8_t  CSD_CRC;              /*!< CSD CRC                               */
      __IO uint8_t  Reserved4;            /*!< Always 1                              */

    } CSDTypedef;

    typedef struct
    {
      __IO uint8_t  ManufacturerID;  /*!< Manufacturer ID       */
      __IO uint16_t OEM_AppliID;     /*!< OEM/Application ID    */
      __IO uint32_t ProdName1;       /*!< Product Name part1    */
      __IO uint8_t  ProdName2;       /*!< Product Name part2    */
      __IO uint8_t  ProdRev;         /*!< Product Revision      */
      __IO uint32_t ProdSN;          /*!< Product Serial Number */
      __IO uint8_t  Reserved1;       /*!< Reserved1             */
      __IO uint16_t ManufactDate;    /*!< Manufacturing Date    */
      __IO uint8_t  CID_CRC;         /*!< CID CRC               */
      __IO uint8_t  Reserved2;       /*!< Always 1              */

    } CIDTypedef;

    typedef struct
    {
        CSDTypedef      SD_csd;         /*!< SD card specific data register         */
        CIDTypedef      SD_cid;         /*!< SD card identification number register */
        uint64_t        CardCapacity;   /*!< Card capacity                          */
        uint32_t        CardBlockSize;  /*!< Card block size                        */
        uint16_t        RCA;            /*!< SD relative card address               */
        uint8_t         CardType;       /*!< SD card type                           */
    } CardInfo;

    enum class ESDError: uint32_t
    {
    /**
      * @brief  SD specific error defines
      */
      CMD_CRC_FAIL                    = (1U),   /*!< Command response received (but CRC check failed)              */
      DATA_CRC_FAIL                   = (2U),   /*!< Data block sent/received (CRC check failed)                   */
      CMD_RSP_TIMEOUT                 = (3U),   /*!< Command response timeout                                      */
      DATA_TIMEOUT                    = (4U),   /*!< Data timeout                                                  */
      TX_UNDERRUN                     = (5U),   /*!< Transmit FIFO underrun                                        */
      RX_OVERRUN                      = (6U),   /*!< Receive FIFO overrun                                          */
      START_BIT_ERR                   = (7U),   /*!< Start bit not detected on all data signals in wide bus mode   */
      CMD_OUT_OF_RANGE                = (8U),   /*!< Command's argument was out of range.                          */
      ADDR_MISALIGNED                 = (9U),   /*!< Misaligned address                                            */
      BLOCK_LEN_ERR                   = (10U),  /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
      ERASE_SEQ_ERR                   = (11U),  /*!< An error in the sequence of erase command occurs.            */
      BAD_ERASE_PARAM                 = (12U),  /*!< An invalid selection for erase groups                        */
      WRITE_PROT_VIOLATION            = (13U),  /*!< Attempt to program a write protect block                     */
      LOCK_UNLOCK_FAILED              = (14U),  /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
      COM_CRC_FAILED                  = (15U),  /*!< CRC check of the previous command failed                     */
      ILLEGAL_CMD                     = (16U),  /*!< Command is not legal for the card state                      */
      CARD_ECC_FAILED                 = (17U),  /*!< Card internal ECC was applied but failed to correct the data */
      CC_ERROR                        = (18U),  /*!< Internal card controller error                               */
      GENERAL_UNKNOWN_ERROR           = (19U),  /*!< General or unknown error                                     */
      STREAM_READ_UNDERRUN            = (20U),  /*!< The card could not sustain data transfer in stream read operation. */
      STREAM_WRITE_OVERRUN            = (21U),  /*!< The card could not sustain data programming in stream mode   */
      CID_CSD_OVERWRITE               = (22U),  /*!< CID/CSD overwrite error                                      */
      WP_ERASE_SKIP                   = (23U),  /*!< Only partial address space was erased                        */
      CARD_ECC_DISABLED               = (24U),  /*!< Command has been executed without using internal ECC         */
      ERASE_RESET                     = (25U),  /*!< Erase sequence was cleared before executing because an out of erase sequence command was received */
      AKE_SEQ_ERROR                   = (26U),  /*!< Error in sequence of authentication.                         */
      INVALID_VOLTRANGE               = (27U),
      ADDR_OUT_OF_RANGE               = (28U),
      SWITCH_ERROR                    = (29U),
      SDIO_DISABLED                   = (30U),
      SDIO_FUNCTION_BUSY              = (31U),
      SDIO_FUNCTION_FAILED            = (32U),
      SDIO_UNKNOWN_FUNCTION           = (33U),

    /**
      * @brief  Standard error defines
      */
      INTERNAL_ERROR                  = (34U),
      NOT_CONFIGURED                  = (35U),
      REQUEST_PENDING                 = (36U),
      REQUEST_NOT_APPLICABLE          = (37U),
      INVALID_PARAMETER               = (38U),
      UNSUPPORTED_FEATURE             = (39U),
      UNSUPPORTED_HW                  = (40U),
      ERROR                           = (41U),
      OK                              = (0U)
    };

    enum class ECardType: uint8_t
    {
        STD_CAPACITY_V1_1               = 0x00U,
        STD_CAPACITY_V2_0               = 0x01U,
        HIGH_CAPACITY                   = 0x02U,
        MULTIMEDIA                      = 0x03U,
        SECURE_DIGITAL_IO               = 0x04U,
        HIGH_SPEED_MULTIMEDIA           = 0x05U,
        SECURE_DIGITAL_IO_COMBO         = 0x06U,
        HIGH_CAPACITY_MMC               = 0x07U,
    };

    enum class ECMD: uint32_t
    {
        GO_IDLE_STATE                       = 0U,   /*!< Resets the SD memory card.                                                               */
        SEND_OP_COND                        = 1U,   /*!< Sends host capacity support information and activates the card's initialization process. */
        ALL_SEND_CID                        = 2U,   /*!< Asks any card connected to the host to send the CID numbers on the CMD line.             */
        SET_REL_ADDR                        = 3U,   /*!< Asks the card to publish a new relative address (RCA).                                   */
        SET_DSR                             = 4U,   /*!< Programs the DSR of all cards.                                                           */
        SDIO_SEN_OP_COND                    = 5U,   /*!< Sends host capacity support information (HCS) and asks the accessed card to send its
                                                                               operating condition register (OCR) content in the response on the CMD line.              */
        HS_SWITCH                           = 6U,   /*!< Checks switchable function (mode 0) and switch card function (mode 1).                   */
        SEL_DESEL_CARD                      = 7U,   /*!< Selects the card by its own relative address and gets deselected by any other address    */
        HS_SEND_EXT_CSD                     = 8U,   /*!< Sends SD Memory Card interface condition, which includes host supply voltage information
                                                                               and asks the card whether card supports voltage.                                         */
        SEND_CSD                            = 9U,   /*!< Addressed card sends its card specific data (CSD) on the CMD line.                       */
        SEND_CID                            = 10U,  /*!< Addressed card sends its card identification (CID) on the CMD line.                      */
        READ_DAT_UNTIL_STOP                 = 11U,  /*!< SD card doesn't support it.                                                              */
        STOP_TRANSMISSION                   = 12U,  /*!< Forces the card to stop transmission.                                                    */
        SEND_STATUS                         = 13U,  /*!< Addressed card sends its status register.                                                */
        HS_BUSTEST_READ                     = 14U,
        GO_INACTIVE_STATE                   = 15U,  /*!< Sends an addressed card into the inactive state.                                         */
        SET_BLOCKLEN                        = 16U,  /*!< Sets the block length (in bytes for SDSC) for all following block commands
                                                                               (read, write, lock). Default block length is fixed to 512 Bytes. Not effective
                                                                               for SDHS and SDXC.                                                                       */
        READ_SINGLE_BLOCK                   = 17U,  /*!< Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of
                                                                               fixed 512 bytes in case of SDHC and SDXC.                                                */
        READ_MULT_BLOCK                     = 18U,  /*!< Continuously transfers data blocks from card to host until interrupted by
                                                                               STOP_TRANSMISSION command.                                                               */
        HS_BUSTEST_WRITE                    = 19U,  /*!< 64 bytes tuning pattern is sent for SDR50 and SDR104.                                    */
        WRITE_DAT_UNTIL_STOP                = 20U,  /*!< Speed class control command.                                                             */
        SET_BLOCK_COUNT                     = 23U,  /*!< Specify block count for CMD18 and CMD25.                                                 */
        WRITE_SINGLE_BLOCK                  = 24U,  /*!< Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of
                                                                               fixed 512 bytes in case of SDHC and SDXC.                                                */
        WRITE_MULT_BLOCK                    = 25U,  /*!< Continuously writes blocks of data until a STOP_TRANSMISSION follows.                    */
        PROG_CID                            = 26U,  /*!< Reserved for manufacturers.                                                              */
        PROG_CSD                            = 27U,  /*!< Programming of the programmable bits of the CSD.                                         */
        SET_WRITE_PROT                      = 28U,  /*!< Sets the write protection bit of the addressed group.                                    */
        CLR_WRITE_PROT                      = 29U,  /*!< Clears the write protection bit of the addressed group.                                  */
        SEND_WRITE_PROT                     = 30U,  /*!< Asks the card to send the status of the write protection bits.                           */
        SD_ERASE_GRP_START                  = 32U,  /*!< Sets the address of the first write block to be erased. (For SD card only).              */
        SD_ERASE_GRP_END                    = 33U,  /*!< Sets the address of the last write block of the continuous range to be erased.           */
        ERASE_GRP_START                     = 35U,  /*!< Sets the address of the first write block to be erased. Reserved for each command
                                                                               system set by switch function command (CMD6).                                            */
        ERASE_GRP_END                       = 36U,  /*!< Sets the address of the last write block of the continuous range to be erased.
                                                                               Reserved for each command system set by switch function command (CMD6).                  */
        ERASE                               = 38U,  /*!< Reserved for SD security applications.                                                   */
        FAST_IO                             = 39U,  /*!< SD card doesn't support it (Reserved).                                                   */
        GO_IRQ_STATE                        = 40U,  /*!< SD card doesn't support it (Reserved).                                                   */
        LOCK_UNLOCK                         = 42U,  /*!< Sets/resets the password or lock/unlock the card. The size of the data block is set by
                                                                               the SET_BLOCK_LEN command.                                                               */
        APP_CMD                             = 55U,  /*!< Indicates to the card that the next command is an application specific command rather
                                                                               than a standard command.                                                                 */
        GEN_CMD                             = 56U,  /*!< Used either to transfer a data block to the card or to get a data block from the card
                                                                               for general purpose/application specific commands.                                       */
        NO_CMD                              = 64U,

        /**
          * @brief Following commands are SD Card Specific commands.
          *        SDIO_APP_CMD should be sent before sending these commands.
          */
        APP_SD_SET_BUSWIDTH                 = 6U,   /*!< (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus
                                                                               widths are given in SCR register.                                                          */
        SD_APP_STATUS                       = 13U,  /*!< (ACMD13) Sends the SD status.                                                              */
        SD_APP_SEND_NUM_WRITE_BLOCKS        = 22U,  /*!< (ACMD22) Sends the number of the written (without errors) write blocks. Responds with
                                                                               32bit+CRC data block.                                                                      */
        SD_APP_OP_COND                      = 41U,  /*!< (ACMD41) Sends host capacity support information (HCS) and asks the accessed card to
                                                                               send its operating condition register (OCR) content in the response on the CMD line.       */
        SD_APP_SET_CLR_CARD_DETECT          = 42U,  /*!< (ACMD42) Connects/Disconnects the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card. */
        SD_APP_SEND_SCR                     = 51U,  /*!< Reads the SD Configuration Register (SCR).                                                 */
        SDIO_RW_DIRECT                      = 52U,  /*!< For SD I/O card only, reserved for security specification.                                 */
        SDIO_RW_EXTENDED                    = 53U,  /*!< For SD I/O card only, reserved for security specification.                                 */

        /**
          * @brief Following commands are SD Card Specific security commands.
          *        APP_CMD should be sent before sending these commands.
          */
        SD_APP_GET_MKB                      = 43U,  /*!< For SD card only */
        SD_APP_GET_MID                      = 44U,  /*!< For SD card only */
        SD_APP_SET_CER_RN1                  = 45U,  /*!< For SD card only */
        SD_APP_GET_CER_RN2                  = 46U,  /*!< For SD card only */
        SD_APP_SET_CER_RES2                 = 47U,  /*!< For SD card only */
        SD_APP_GET_CER_RES1                 = 48U,  /*!< For SD card only */
        SD_APP_SECURE_READ_MULTIPLE_BLOCK   = 18U,  /*!< For SD card only */
        SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  = 25U,  /*!< For SD card only */
        SD_APP_SECURE_ERASE                 = 38U,  /*!< For SD card only */
        SD_APP_CHANGE_SECURE_AREA           = 49U,  /*!< For SD card only */
        SD_APP_SECURE_WRITE_MKB             = 48U,  /*!< For SD card only */
    };

    enum class ETransferState: uint32_t
    {
        OK    = 0U,     /*!< Transfer success      */
        BUSY  = 1U,     /*!< Transfer is occurring */
        ERROR = 2U      /*!< Transfer failed       */
    };

    enum class ECardState: uint32_t
    {
        READY           = 0x00000001U,  /*!< Card state is ready                     */
        IDENTIFICATION  = 0x00000002U,  /*!< Card is in identification state         */
        STANDBY         = 0x00000003U,  /*!< Card is in standby state                */
        TRANSFER        = 0x00000004U,  /*!< Card is in transfer state               */
        SENDING         = 0x00000005U,  /*!< Card is sending an operation            */
        RECEIVING       = 0x00000006U,  /*!< Card is receiving operation information */
        PROGRAMMING     = 0x00000007U,  /*!< Card is in programming state            */
        DISCONNECTED    = 0x00000008U,  /*!< Card is disconnected                    */
        ERROR           = 0x000000FFU   /*!< Card is in error state                  */
    };

    enum class ETransferDir: uint32_t
    {
        TO_CARD         = 0x00000000U,
        TO_SDIO         = SDIO_DCTRL_DTDIR
    };

    enum class EDataBlockSize: uint32_t
    {
        _1B             = 0x00000000U,
        _2B             = 0x00000010U,
        _4B             = 0x00000020U,
        _8B             = 0x00000030U,
        _16B            = 0x00000040U,
        _32B            = 0x00000050U,
        _64B            = 0x00000060U,
        _128B           = 0x00000070U,
        _256B           = 0x00000080U,
        _512B           = 0x00000090U,
        _1024B          = 0x000000A0U,
        _2048B          = 0x000000B0U,
        _4096B          = 0x000000C0U,
        _8192B          = 0x000000D0U,
        _16384B         = 0x000000E0U,
    };

    enum ER6Msk: uint32_t
    {
        GENERAL_UNKNOWN_ERROR_6   = 0x00002000U,
        ILLEGAL_CMD_6             = 0x00004000U,
        COM_CRC_FAILED_6          = 0x00008000U,
    };

    enum class EClockEdge: uint32_t
    {
        RISING  = 0x00000000U,
        FALLING = SDIO_CLKCR_NEGEDGE,
    };

    enum class EClockBypass: uint32_t
    {
        DISABLE = 0x00000000U,
        ENABLE  = SDIO_CLKCR_BYPASS,
    };

    enum class EClockPowerSave: uint32_t
    {
        DISABLE = 0x00000000U,
        ENABLE  = SDIO_CLKCR_PWRSAV,
    };

    enum class EHWFlowControl: uint32_t
    {
        DISABLE = 0x00000000U,
        ENABLE  = SDIO_CLKCR_HWFC_EN,
    };

    enum class EBusWide: uint32_t
    {
        _1B     = 0x00000000U,
        _4B     = SDIO_CLKCR_WIDBUS_0,
        _8B     = SDIO_CLKCR_WIDBUS_1,
    };

    enum class EResponse: uint32_t
    {
        NO      = 0x00000000U,
        SHORT   = SDIO_CMD_WAITRESP_0,
        LONG    = SDIO_CMD_WAITRESP,
    };

    enum class EWait: uint32_t
    {
        NO      = 0x00000000U,
        IT      = SDIO_CMD_WAITINT,
        PEND    = SDIO_CMD_WAITPEND,
    };

    enum class ECPSM: uint32_t
    {
        DISABLE = 0x00000000U,
        ENABLE  = SDIO_CMD_CPSMEN,
    };

    enum class EDPSM: uint32_t
    {
        DISABLE = 0x00000000U,
        ENABLE  = SDIO_DCTRL_DTEN,
    };

    enum class EResp: uint32_t
    {
        RESP1   = 0x00000000U,
        RESP2   = 0x00000004U,
        RESP3   = 0x00000008U,
        RESP4   = 0x0000000CU,
    };

    enum class ETransferMode: uint32_t
    {
        BLOCK   = 0x00000000U,
        STREAM  = SDIO_DCTRL_DTMODE,
    };

    /*enum class EReadWaitMode: uint32_t
    {
        DATA2   = 0x00000000U,
        CLK     = 0x00000001U,
    };*/

    enum EOCRMasks: uint32_t
    {
        ADDR_OUT_OF_RANGE        = 0x80000000U,
        ADDR_MISALIGNED          = 0x40000000U,
        BLOCK_LEN_ERR            = 0x20000000U,
        ERASE_SEQ_ERR            = 0x10000000U,
        BAD_ERASE_PARAM          = 0x08000000U,
        WRITE_PROT_VIOLATION     = 0x04000000U,
        LOCK_UNLOCK_FAILED       = 0x01000000U,
        COM_CRC_FAILED           = 0x00800000U,
        ILLEGAL_CMD              = 0x00400000U,
        CARD_ECC_FAILED          = 0x00200000U,
        CC_ERROR                 = 0x00100000U,
        GENERAL_UNKNOWN_ERROR    = 0x00080000U,
        STREAM_READ_UNDERRUN     = 0x00040000U,
        STREAM_WRITE_OVERRUN     = 0x00020000U,
        CID_CSD_OVERWRITE        = 0x00010000U,
        WP_ERASE_SKIP            = 0x00008000U,
        CARD_ECC_DISABLED        = 0x00004000U,
        ERASE_RESET              = 0x00002000U,
        AKE_SEQ_ERROR            = 0x00000008U,
        ERRORBITS                = 0xFDFFE008U,
    };

    static ESDError init();
    static void deinit();

    static ESDError wide_bus_config(EBusWide mode);
    static ETransferState get_status();

    static ESDError read_blocks(uint8_t *buf, uint32_t read_addr, uint32_t block_size, uint32_t blocks);
    /// TODO read_blocks_DMA
    /// TODO HAL_SD_CheckReadOperation

    static ESDError write_blocks(uint8_t *buf, uint32_t write_addr, uint32_t block_size, uint32_t blocks);
    /// TODO write_blocks_DMA
    /// TODO HAL_SD_CheckWriteOperation

    static ESDError erase(uint32_t start_addr, uint32_t end_addr);

    static ESDError high_speed();

    static ESDError send_SD_status(uint32_t *status);
private:
    static ECardType m_card_type;
    static uint16_t m_RCA;
    static uint32_t m_CSD[4];
    static uint32_t m_CID[4];
    static CardInfo m_card_info;

    static void init_gpio();
    static void deinit_gpio();
    static void init_low(EClockEdge clock_edge, EClockBypass clock_bypass,
                         EClockPowerSave clock_power_save, EBusWide bus_wide,
                         EHWFlowControl hw_control, uint32_t clock_div);

    static ESDError power_ON();
    static ESDError power_OFF();

    static ESDError send_status(uint32_t *card_status);

    static ESDError initialize_cards();

    static void send_command(uint32_t arg, ECMD cmd, EResponse resp,
                             EWait wait_IT, ECPSM cpsm);
    static ESDError cmd_error();
    static ESDError cmd_resp7_error();
    static ESDError cmd_resp1_error(ECMD cmd);
    static ESDError cmd_resp3_error();
    static ESDError cmd_resp2_error();
    static ESDError cmd_resp6_error(ECMD cmd, uint16_t *pRCA);

    static ESDError data_config(uint32_t time_out, uint32_t dat_len,
                                EDataBlockSize block_size, ETransferDir transf_dir,
                                ETransferMode transf_mode, EDPSM DPSM);
    static ESDError stop_transfer();

    static ESDError get_card_info();

    static ESDError select_deselect(uint32_t addr);

    static ESDError is_card_programming(ECardState *status);

    static inline void enable_SDIO() { BIT_BAND_PER(SDIO->CLKCR, SDIO_CLKCR_CLKEN) = ENABLE; }
    static inline void disable_SDIO() { BIT_BAND_PER(SDIO->CLKCR, SDIO_CLKCR_CLKEN) = DISABLE; }

    static inline void power_state_ON() { SDIO->POWER = SDIO_POWER_PWRCTRL; }
    static inline void power_state_OFF() { SDIO->POWER = 0; }

    static inline uint32_t get_flag(uint32_t flag_msk) { return (SDIO->STA & flag_msk); }
    static inline void clear_flag(uint32_t flag_msk) { SDIO->ICR = flag_msk; }

    static inline ECMD get_cmd_response() { return static_cast<ECMD>(SDIO->RESPCMD); }
    static inline uint32_t get_response(EResp resp) { return (&SDIO->RESP1)[static_cast<uint32_t>(resp) >> 2]; }

    static inline uint32_t get_power_state() { return (SDIO->POWER & SDIO_POWER_PWRCTRL); }

    static inline uint32_t read_FIFO() { return SDIO->FIFO; }
    static inline void write_FIFO(uint32_t *val) { SDIO->FIFO = *val; }

    static ESDError wide_bus_enable();
    static ESDError wide_bus_disable();

    static ESDError find_SCR(uint32_t *scr);

    static ECardState get_state();
};

#endif // STM32_SD_H
