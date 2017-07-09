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
static int s_grid[GRID_WIDTH * GRID_WIDTH];
static int s_score;

static int pow2( int n )
{
	int result = 1, i;
	for( i = 0; i < n; i++ )
	{
		result *= 2;
	}
	return result;
}

static void SetupUnitedPieceBmp( UnitedPieceBmp* p, BYTE* source )
{
	UnitedPieceBmp_Construct( p, source, s_panel_width, s_panel_width );
}

static void InitGrid( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		s_grid[i] = 0;
	}
	s_score = 0;
}

static int NumEmptyGrids( void )
{
	int num_empty = 0, i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( s_grid[i] == 0 )
		{
			++num_empty;
		}
	}
	return num_empty;
}

static int AddRandomPanel( void )
{
	int rest = rand() % NumEmptyGrids(), i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( s_grid[i] == 0 )
		{
			if( rest <= 0 )
			{
				break;
			}
			--rest;
		}
	}
	s_grid[i] = ( rand() % 10 < 1 ) ? 2 : 1; // 4:2 = 1:9
	return i;
}

static void DrawGrid( void )
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

static void DrawScore( void )
{
	FontProxy_SetType( 2 );
	pceFontSetPos( 0, 0 );
	pceFontPutStr( "SCORE\n" );
	pceFontPrintf( "%5d", s_score );
}

static void StartGame( void )
{
	int i;
	InitGrid();
	for( i = 0; i < 2; i++ )
	{
		AddRandomPanel();
	}
}

static BOOL MoveLeft( void )
{
	BOOL moved = FALSE;
	int x, xx, y;
	for( y = 0; y < GRID_WIDTH; y++ )
	{
		for( x = 0; x < GRID_WIDTH; x++ )
		{
			for( xx = x + 1; xx < GRID_WIDTH && s_grid[xx + GRID_WIDTH * y] == 0; xx++ ) {}
			if( GRID_WIDTH <= xx )
			{
				break;
			}
			if( s_grid[x + GRID_WIDTH * y] == 0 )
			{
				s_grid[x + GRID_WIDTH * y] = s_grid[xx + GRID_WIDTH * y];
				s_grid[xx + GRID_WIDTH * y] = 0;
				--x;
				moved = TRUE;
			}
			else if( s_grid[x + GRID_WIDTH * y] == s_grid[xx + GRID_WIDTH * y] )
			{
				++s_grid[x + GRID_WIDTH * y];
				s_grid[xx + GRID_WIDTH * y] = 0;
				s_score += pow2( s_grid[x + GRID_WIDTH * y] );
				moved = TRUE;
			}
		}
	}
	return moved;
}

/// 初期化.
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

/// メイン.
void pceAppProc( int cnt )
{
	PrecisionTimer timer;
	PrecisionTimer_Construct( &timer );

	if( !s_initialize_succeed || pcePadGet() & TRG_D )
	{
		pceAppReqExit( 0 );
	}
	
	if( pcePadGet() & TRG_A )
	{
		StartGame();
		pceLCDPaint( 0, 0, 0, DISP_X, DISP_Y );
		DrawGrid();
		DrawScore();
	}
	
	if( pcePadGet() & TRG_LF )
	{
		if( MoveLeft() )
		{
			AddRandomPanel();
			pceLCDPaint( 0, 0, 0, DISP_X, DISP_Y );
			DrawGrid();
			DrawScore();
		}
	}
	
	pceLCDPaint( 0, 0, 80, DISP_X, 8 );
	FontFuchi_SetType( 2 );
	FontFuchi_SetPos( 1, 80 );
	FontFuchi_Printf( "%6lu/%6luus FREE:%8d", g_proc_us, g_period_us, pceHeapGetMaxFreeSize() );
	
	Lcd_Update();
	Lcd_Trans();
	rand(); // 空回し

	g_period_us = PrecisionTimer_Count( &g_timer );
	g_proc_us = PrecisionTimer_Count( &timer );
}

/// 終了.
void pceAppExit( void )
{
	FontProxy_Unhook_Set();
	Configure_Exit();
}

