/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
/*
移植说明：
时间：2015-2-5 by slan
*/
#include "diskio.h"
#include "sdio_sdcard.h"
#include "ff.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define SD_CARD	 0  //SD卡,卷标为0
#define EX_FLASH 1	//外部flash,卷标为1



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	switch(drv)
	{
		case SD_CARD://SD卡
			if(SD_Init() == SD_OK)
			{
				return RES_OK;
			}
			else
			{
				return RES_NOTRDY;
			}
		//default:
		//	return RES_NOTRDY;
	}
	return RES_NOTRDY;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	switch (drv) {
		case SD_CARD :
		/*
			if(SD_ReadBlock(buff, sector<< 9, _MAX_SS) == SD_OK)
			{
				return RES_OK;
			}
			else
			{
				return RES_NOTRDY;
			}
		*/
			for(;count>0;count--)
			{
				if(SD_ReadBlock(buff, sector<< 9, _MAX_SS) != SD_OK)
				{
					break;
				}
				sector++;
				buff+=_MAX_SS;
				/* Wait until end of DMA transfer */
				SD_WaitReadOperation(); 
			
				/* Check if the Transfer is finished */
				while(SD_GetStatus() != SD_TRANSFER_OK);
			}
			if(count == 0)
			{
				return RES_OK;
			}else{
				return RES_ERROR;
			}	
		//default:
		//	return RES_NOTRDY;
	}
	return RES_NOTRDY;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	switch (drv) {
		case SD_CARD :
		/*
			if(SD_WriteBlock((uint8_t *)buff, sector, count) == SD_OK)
			{
				return RES_OK;
			}
			else
			{
				return RES_NOTRDY;
			}
		*/
			for(;count>0;count--)
			{
				if(SD_WriteBlock((uint8_t *)buff,sector<<9, _MAX_SS) != SD_OK)
				{
					break;
				}
				sector++;
				buff+=_MAX_SS;
				/* Wait until end of DMA transfer */
				SD_WaitWriteOperation(); 
				/* Check if the Transfer is finished */
				while(SD_GetStatus() != SD_TRANSFER_OK);
			}
			if(count == 0)
			{
				return RES_OK;
			}else{
				return RES_ERROR;
			}	
		//default:
		//	return RES_NOTRDY;
	}
	return RES_PARERR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}

#if !_FS_READONLY
DWORD get_fattime (void)
{
	return 0;
}
#endif


