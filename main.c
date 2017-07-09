#include "zurapce/zurapce.h"

static BOOL s_initialize_succeed = FALSE;

extern BYTE PANEL[], PANEL_ANIM[];
static UnitedPieceBmp s_panel_bmp, s_panel_anim_bmp;
static PieceBmpAnimation s_panel_anim;
static int const s_panel_width = 22;
static int const s_period = 33;

PrecisionTimer g_timer;
unsigned long g_period_us, g_proc_us;

#define GRID_WIDTH (4)
int s_grid[GRID_WIDTH * GRID_WIDTH];
int s_score;

static void SetupUnitedPieceBmp( UnitedPieceBmp* p, BYTE* source )
{
	UnitedPieceBmp_Construct( p, source, s_panel_width, s_panel_width );
}

void InitGrid( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		s_grid[i] = 0;
	}
	s_score = 0;
}

void DrawGrid( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		int const x = i % GRID_WIDTH;
		int const y = i / GRID_WIDTH;
		UnitedPieceBmp_Draw( &s_panel_bmp
			, DISP_X / 2 + s_panel_width * ( x - GRID_WIDTH / 2 )
			, s_panel_width * y
			, s_grid[i], DRW_NOMAL );
	}
}

void DrawScore( void )
{
	FontProxy_SetType( 2 );
	pceFontSetPos( 0, 0 );
	pceFontPutStr( "SCORE\n" );
	pceFontPrintf( "%5d", s_score );
}

/// ‰Šú‰».
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
		InitGrid();
		DrawGrid();
		DrawScore();
		PrecisionTimer_Construct( &g_timer );
		
		s_initialize_succeed = TRUE;
	}
}

/// ƒƒCƒ“.
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

/// I—¹.
void pceAppExit( void )
{
	FontProxy_Unhook_Set();
	Configure_Exit();
}

