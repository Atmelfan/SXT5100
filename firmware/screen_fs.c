#include "screen.h"
#include "gfx_driver.h"
#include "ff.h"
#include <time.h>

FATFS FatFs;		/* FatFs work area needed for each volume */
FRESULT status;
DIR dir;
uint8_t select_file = 0;

DWORD get_fattime (void)
{
	/* Returns current time packed into a DWORD variable */
	//2038-00-19 03:14:07
	time_t t;
	time(&t);
	struct tm* timeinfo = localtime(&t);
	return fatfs_time(timeinfo);				
}

void print_err(FRESULT err, uint8_t i){
	switch(err){
		case FR_OK:
		gfx_drawstring(0,i,"OK",GFX_NONE);
		break;
		case FR_INT_ERR:
		gfx_drawstring(0,i,"ERR: INT",GFX_NONE);
		break;
		case FR_DISK_ERR:
		gfx_drawstring(0,i,"ERR: DISK",GFX_NONE);
		break;
		case FR_INVALID_OBJECT:
		gfx_drawstring(0,i,"ERR: INVALID",GFX_NONE);
		break;
		case FR_TIMEOUT:
		gfx_drawstring(0,i,"ERR: TIMEOUT",GFX_NONE);
		break;
		case FR_NOT_ENOUGH_CORE:
		gfx_drawstring(0,i,"ERR: NO CORE",GFX_NONE);
		break;
		case FR_NO_FILESYSTEM:
		gfx_drawstring(0,i,"ERR: NO FS",GFX_NONE);
		break;
		case FR_NOT_READY:
		gfx_drawstring(0,i,"ERR: FOUND CAT",GFX_NONE);
		break;
		case FR_INVALID_DRIVE:
		gfx_drawstring(0,i,"ERR: INVDRV",GFX_NONE);
		break;
		default:
		gfx_drawstring(0,i,"ERR: UNKNOWN ,':(",GFX_NONE);
		break;
	}
}

uint8_t print_fs(uint8_t select){
	FILINFO fno;
	status = f_opendir(&dir, "");
	if (status != FR_OK)
	{
		print_err(status, 1);
	}else{
		for (int i = 0; i < 6; ++i)
		{
			status = f_readdir(&dir, &fno);
			if (fno.fname[0] == 0){
				break; 
			}
			if(status != FR_OK)
			{
				print_err(status, 1+i);
			}
			if (fno.fattrib & AM_SYS || fno.fattrib & AM_HID) {   /* It is a system/hidden file */
                i--;
                continue;
            } else if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                gfx_drawstring(0,i+1,fno.fname,GFX_UNDERLINE);
            } else {                                       /* It is a file. */
                gfx_drawstring(0,i+1,fno.fname,GFX_NONE);
            }
		}
	}
	f_closedir(&dir);
	return select;
}

void update_fs(keyboard_keys key){
	if (key == KEYBORD_F3)
	{
		set_screen(&screen_clock);
		return;
	}else if (key == KEYBORD_LEFT)
	{
		if (select_file > 0)
		{
			select_file--;
		}
	}else if (key == KEYBORD_RIGHT)
	{
		select_file++;
	}else if (key == KEYBORD_DELETE)
	{
		
	}
	print_fs(select_file);
}

void setup_fs(){
	select_file = 0;
	gfx_drawstring(62 ,0,"DEL",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"NEW",GFX_UNDERLINE);
	gfx_drawstring(110,0,"RET",GFX_UNDERLINE);
	status = f_mount(&FatFs, "", 0);
	if(status == FR_OK){
		print_fs(select_file);
	}else{
		print_err(status, 1);
	}

}

void close_fs(){

}

screen screen_fs = {
	.update = &update_fs,
	.setup = &setup_fs,
	.close = &close_fs
};