#include "zurapce/zurapce.h"

static BOOL s_initialize_succeed = FALSE;

extern BYTE PANEL[], PANEL_ANIM[];
static UnitedPieceBmp s_panel_bmp, s_panel_anim_bmp;
static PieceBmpAnimation s_panel_anim;
static int const s_period = 33;

PrecisionTimer g_timer;
unsigned long g_period_us, g_proc_us;

static void SetupUnitedPieceBmp( UnitedPieceBmp* p, BYTE* source )
{
	static int const s_width = 22;
	UnitedPieceBmp_Construct( p, source, s_width, s_width );
}

/// èâä˙âª.
void pceAppInit( void )
{
	FramObject_Init();
	pceAppSetProcPeriod( s_period );
	Configure_Init();
	FontProxy_Hook_Set();
	
	if( Lcd_Init() )
	{
		SetupUnitedPieceBmp( &s_panel_bmp, PANEL );
		SetupUnitedPieceBmp( &s_panel_anim_bmp, PANEL_ANIM );
		PrecisionTimer_Construct( &g_timer );
		
		s_initialize_succeed = TRUE;
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
	
	Lcd_Update();
	Lcd_Trans();

	g_period_us = PrecisionTimer_Count( &g_timer );
	g_proc_us = PrecisionTimer_Count( &timer );
}

/// èIóπ.
void pceAppExit( void )
{
	FontProxy_Unhook_Set();
	Configure_Exit();
}

