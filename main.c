#include "zurapce/zurapce.h"

static BOOL s_initialize_succeed = FALSE;

extern BYTE GRP[];
static PIECE_BMP s_bmp;

PrecisionTimer g_timer;
unsigned long g_period_us, g_proc_us;

/// èâä˙âª.
void pceAppInit( void )
{
	FramObject_Init();
	pceAppSetProcPeriod( 33 );
	Configure_Init();
	FontProxy_Hook_Set();
	FontExtend_Hook_GetAdrs();
	
	if( Lcd_Init() )
	{
		if( Ldirect_Init() )
		{
			PieceBmp_Construct( &s_bmp, FilePack_Data( "B001000.pgx", GRP ) );
			Ldirect_DrawObject( &s_bmp, 0, 0, 0, 0, s_bmp.header.w, s_bmp.header.h );
			Ldirect_VBuffView( TRUE );
			
			FontFuchi_SetType( 0 );
			FontFuchi_SetTxColor( 0 );
			FontFuchi_SetBdColor( 3 );
			FontFuchi_SetPos( 1, 1 );
			FontFuchi_SetRange( 1, 0, DISP_X - 1, DISP_Y - 1 );
			FontFuchi_Printf( "Hello, World\n"
								"\xF0\x40\xF0\x41\xF0\x42\xF0\x46\xF0\x47" );
			PrecisionTimer_Construct( &g_timer );
			
			s_initialize_succeed = TRUE;
		}
	}
}

/// ÉÅÉCÉì.
void pceAppProc( int cnt )
{
	PrecisionTimer timer;
	PrecisionTimer_Construct( &timer );

	if( !s_initialize_succeed || pcePadGet() & TRG_D )
	{
		pceAppReqExit( 0 );
	}
	
	pceLCDPaint( 0, 0, 80, DISP_X, 8 );
	FontFuchi_SetType( 2 );
	FontFuchi_SetPos( 1, 80 );
	FontFuchi_Printf( "%6lu/%6luus FREE:%8d", g_proc_us, g_period_us, pceHeapGetMaxFreeSize() );
	
	Ldirect_Update();
	Ldirect_Trans();

	g_period_us = PrecisionTimer_Count( &g_timer );
	g_proc_us = PrecisionTimer_Count( &timer );
}

/// èIóπ.
void pceAppExit( void )
{
	FontExtend_Unhook_GetAdrs();
	FontProxy_Unhook_Set();
	Configure_Exit();
}

