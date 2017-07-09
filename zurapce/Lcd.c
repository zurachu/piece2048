#include "Lcd.h"

/**
	LCD �֘A�̎���.
	@author zurachu
*/

#include <piece.h>
#include <string.h>

/// ���z��ʃo�b�t�@
static unsigned char* s_vbuff = NULL;

/// LCD �X�V�t���O
static BOOL s_lcd_update;

int Lcd_Init( void )
{
	pceLCDDispStop();
	s_vbuff = pceHeapAlloc( DISP_X * DISP_Y );
	if( s_vbuff )
	{
		memset( s_vbuff, 0, DISP_X * DISP_Y );
		pceLCDSetBuffer( s_vbuff );
		s_lcd_update = TRUE;
	}
	pceLCDDispStart();
	return s_vbuff? 1 : 0;
}

void Lcd_Update( void )
{
	s_lcd_update = TRUE;
}

void Lcd_Trans( void )
{
	if( s_lcd_update )
	{
		pceLCDTrans();
		s_lcd_update = FALSE;
	}
}

