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
static int s_adding_panel;
static int s_score;

enum Phase
{
	Phase_Title,
	Phase_Game,
	Phase_GameOver,
};
typedef enum Phase Phase;
static Phase s_phase;

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

static void CopyGrid( int source[] )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		s_grid[i] = source[i];
	}
}

static void FlipGridHorizontal( void )
{
	int flipped[GRID_WIDTH * GRID_WIDTH], i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		int const x = i % GRID_WIDTH, y = i / GRID_WIDTH;
		flipped[i] = s_grid[( GRID_WIDTH - x - 1 ) + GRID_WIDTH * y];
	}
	CopyGrid(flipped);
}

static void TransposeGrid( void )
{
	int transposed[GRID_WIDTH * GRID_WIDTH], i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		int const x = i % GRID_WIDTH, y = i / GRID_WIDTH;
		transposed[i] = s_grid[y + GRID_WIDTH * x];
	}
	CopyGrid(transposed);
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
		int const x = DISP_X / 2 + s_panel_width * ( ( i % GRID_WIDTH ) - GRID_WIDTH / 2 );
		int const y = s_panel_width * ( i / GRID_WIDTH );
		if( i == s_adding_panel
			&& PieceBmpAnimation_Playing( &s_panel_anim ) )
		{
			PieceBmpAnimation_Draw( &s_panel_anim, x, y, DRW_NOMAL );
		}
		else
		{
			UnitedPieceBmp_Draw( &s_panel_bmp, x, y, s_grid[i], DRW_NOMAL );
		}
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
	PieceBmpAnimation_Clear( &s_panel_anim );
	s_phase = Phase_Game;
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

static BOOL MoveRight( void )
{
	BOOL moved;
	FlipGridHorizontal();
	moved = MoveLeft();
	FlipGridHorizontal();
	return moved;
}

static BOOL MoveUp( void )
{
	BOOL moved;
	TransposeGrid();
	moved = MoveLeft();
	TransposeGrid();
	return moved;
}

static BOOL MoveDown( void )
{
	BOOL moved;
	TransposeGrid();
	moved = MoveRight();
	TransposeGrid();
	return moved;
}

static BOOL Movable( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( s_grid[i] == 0
			|| ( ( i + 1 ) % GRID_WIDTH != 0 && s_grid[i] == s_grid[i + 1] )
			|| ( i / GRID_WIDTH + 1 < GRID_WIDTH && s_grid[i] == s_grid[i + GRID_WIDTH] ) )
		{
			return TRUE;
		}
	}
	return FALSE;
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
	BOOL moved = FALSE;
	PrecisionTimer_Construct( &timer );

	if( !s_initialize_succeed || pcePadGet() & TRG_D )
	{
		pceAppReqExit( 0 );
	}
	
	switch( s_phase )
	{
	case Phase_Title:
	case Phase_GameOver:
		if( pcePadGet() & TRG_A )
		{
			StartGame();
		}
		break;
	case Phase_Game:
		if( PieceBmpAnimation_Playing( &s_panel_anim ) )
		{
			if( PieceBmpAnimation_IsEnd( &s_panel_anim ) )
			{
				PieceBmpAnimation_Clear( &s_panel_anim );
				if( !Movable() )
				{
					s_phase = Phase_GameOver;
				}
			}
			PieceBmpAnimation_Update( &s_panel_anim, s_period );
		}
		else
		{
			if( pcePadGet() & TRG_LF )
			{
				moved = MoveLeft();
			}
			else if( pcePadGet() & TRG_RI )
			{
				moved = MoveRight();
			}
			else if( pcePadGet() & TRG_UP )
			{
				moved = MoveUp();
			}
			else if( pcePadGet() & TRG_DN )
			{
				moved = MoveDown();
			}
			if( moved )
			{
				s_adding_panel = AddRandomPanel();
				PieceBmpAnimation_StartToEnd( &s_panel_anim, &s_panel_anim_bmp
					, s_period, FALSE );
			}
		}
		break;
	}

	pceLCDPaint( 0, 0, 0, DISP_X, DISP_Y );
	DrawGrid();
	DrawScore();
	switch( s_phase )
	{
	case Phase_Title:
	case Phase_Game:
		break;
	case Phase_GameOver:
		FontFuchi_SetType( 1 );
		FontFuchi_SetPos( 28, 24 );
		FontFuchi_PutStr( "GAME OVER" );
		FontFuchi_SetType( 0 );
		FontFuchi_SetPos( 4, 54 );
		FontFuchi_PutStr( "PUSH A BUTTON TO RESTART" );
		break;
	}
	FontFuchi_SetType( 2 );
	FontFuchi_SetPos( 1, 80 );
	FontFuchi_Printf( "%6lu/%6luus FREE:%8d", g_proc_us, g_period_us, pceHeapGetMaxFreeSize() );
	
	Lcd_Update();
	Lcd_Trans();
	rand(); // ‹ó‰ñ‚µ

	g_period_us = PrecisionTimer_Count( &g_timer );
	g_proc_us = PrecisionTimer_Count( &timer );
}

/// I—¹.
void pceAppExit( void )
{
	FontProxy_Unhook_Set();
	Configure_Exit();
}

