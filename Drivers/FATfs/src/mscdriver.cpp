#include "mscdriver.h"

#ifdef STM32_USE_USB
#include "usbh_msc.h"

/* Block Size in Bytes */
#define USB_DEFAULT_BLOCK_SIZE  512

uint8_t MSCDriver::status(uint8_t lun)
{
    if (m_msc->unit_is_ready(lun))
        return RES_OK;
    else
        return RES_ERROR;
}

DSTATUS MSCDriver::read(uint8_t lun, uint8_t* buf, uint32_t sector, uint16_t count)
{
    if (m_msc->read(lun, sector, buf, count) == USBHCore::EStatus::OK)
        return RES_OK;

    USBH_MSC::MSC_LUN info;
    m_msc->get_LUN_info(lun, &info);
    switch (info.sense.asc)
    {
    case SCSI_ASC_LOGICAL_UNIT_NOT_READY:
    case SCSI_ASC_MEDIUM_NOT_PRESENT:
    case SCSI_ASC_NOT_READY_TO_READY_CHANGE:
        USBH_ErrLog("USB Disk is not ready!");
        return RES_NOTRDY;
    default:
        return RES_ERROR;
    }
}

#if _USE_WRITE == 1
DSTATUS MSCDriver::write(uint8_t lun, uint8_t* buf, uint32_t sector, uint16_t count)
{
    if (m_msc->write(lun, sector, buf, count) == USBHCore::EStatus::OK)
        return RES_OK;

    USBH_MSC::MSC_LUN info;
    m_msc->get_LUN_info(lun, &info);
    switch (info.sense.asc)
    {
    case SCSI_ASC_WRITE_PROTECTED:
        USBH_ErrLog("USB Disk is Write protected!");
        return RES_WRPRT;
    case SCSI_ASC_LOGICAL_UNIT_NOT_READY:
    case SCSI_ASC_MEDIUM_NOT_PRESENT:
    case SCSI_ASC_NOT_READY_TO_READY_CHANGE:
        USBH_ErrLog("USB Disk is not ready!");
        return RES_NOTRDY;
    default:
        return RES_ERROR;
    }
}
#endif

#if _USE_IOCTL == 1
uint8_t MSCDriver::ioctl(uint8_t lun, FAT_FS::ECTRL cmd, void* buf)
{
    switch (cmd)
    {
    case FAT_FS::ECTRL::SYNC:
        return RES_OK;
    case FAT_FS::ECTRL::GET_SECTOR_COUNT:
        if (m_msc->get_LUN_block_nbr(lun, reinterpret_cast<uint32_t*>(buf)) == USBHCore::EStatus::OK)
            return RES_OK;
        else
            return RES_ERROR;
    case FAT_FS::ECTRL::GET_SECTOR_SIZE:
        if (m_msc->get_LUN_block_size(lun, reinterpret_cast<uint16_t*>(buf)) == USBHCore::EStatus::OK)
            return RES_OK;
        else
            return RES_ERROR;
    case FAT_FS::ECTRL::GET_BLOCK_SIZE:
        if (m_msc->get_LUN_block_size(lun, reinterpret_cast<uint16_t*>(buf)) == USBHCore::EStatus::OK)
        {
            *reinterpret_cast<uint16_t*>(buf) = *reinterpret_cast<uint16_t*>(buf) / USB_DEFAULT_BLOCK_SIZE;
            return RES_OK;
        }
        else
            return RES_ERROR;
    default:
        return RES_PARERR;
    }
}
#endif

#endif //STM32_USE_USB
