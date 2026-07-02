/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "main.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

static int MMC_disk_read(BYTE *buff, LBA_t sector, UINT count);
static int MMC_disk_write(const BYTE *buff, LBA_t sector, UINT count);

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
//		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
//		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
//		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
//		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
//		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
//		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_OK;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

//		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);
    
		// translate the reslut code here
    if(result == 1)
    {
      res = RES_NOTRDY;
    }
		return res;

	case DEV_USB :
		// translate the arguments here

//		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}

static int MMC_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
  if(SPIIsLocked() == SPI_LOCKED)
  {
    return 1;
  }
  SPILock();
  APP_P25Q128_ReadData(sector * BLOCK_SIZE, buff, count * BLOCK_SIZE);
  SPIUnlock();
  return 0;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_OK;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

//		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);
    
		// translate the reslut code here
    if(result == 1)
    {
      res = RES_NOTRDY;
    }
		return res;

	case DEV_USB :
		// translate the arguments here

//		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}

static int MMC_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
  if(SPIIsLocked() == SPI_LOCKED)
  {
    return 1;
  }
  SPILock();
  
  uint32_t tempadr = sector * BLOCK_SIZE;
  uint32_t writecnt = count * BLOCK_SIZE;
  uint8_t *pbuf  = (uint8_t *)buff;
  
  for(uint32_t i = 0; i < count; i++)
    {
      APP_P25Q128_SectorErase(tempadr);
      tempadr += BLOCK_SIZE;
    }

    tempadr = sector * BLOCK_SIZE;
    while(writecnt > 0)
    {
      if(writecnt > DISK_PAGE_SIZE)
      {
        APP_P25Q128_PageProgram(tempadr, pbuf, DISK_PAGE_SIZE);
        writecnt -= DISK_PAGE_SIZE;
        tempadr += DISK_PAGE_SIZE;
        pbuf += DISK_PAGE_SIZE;
      }
      else
      {
        APP_P25Q128_PageProgram(tempadr, pbuf, writecnt);
        tempadr += writecnt;
        pbuf += writecnt;
        writecnt = 0;
        break;
      }
    }
  SPIUnlock();
  return 0;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

    // Process of the command for the MMC/SD card
    switch(cmd)
    {
      //Return sector size.
      case GET_SECTOR_SIZE:
          *(WORD *)buff = 4096 ;
      break;
    }

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}
