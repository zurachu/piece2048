#include "zurapce/zurapce.h"

#include "grid.h"

static BOOL s_initialize_succeed = FALSE;

extern BYTE PANEL[], PANEL_ANIM[];
static UnitedPieceBmp s_panel_bmp, s_panel_anim_bmp;
static PieceBmpAnimation s_panel_anim;
static int const s_panel_width = 22;
static int const s_period = 33;

static int s_adding_panel;

enum Phase
{
	Phase_Title,
	Phase_Game,
	Phase_GameOver,
	Phase_Win,
};
typedef enum Phase Phase;
static Phase s_phase;

static void SetupUnitedPieceBmp( UnitedPieceBmp* p, BYTE* source )
{
	UnitedPieceBmp_Construct( p, source, s_panel_width, s_panel_width );
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
			UnitedPieceBmp_Draw( &s_panel_bmp, x, y, g_grid[i], DRW_NOMAL );
		}
	}
}

static void DrawScore( void )
{
	FontProxy_SetType( 2 );
	pceFontSetPos( 0, 0 );
	pceFontPutStr( "SCORE\n" );
	pceFontPrintf( "%5d", g_score );
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

static int CenteringX( char const* message, int font_width )
{
	return ( DISP_X - strlen( message ) * font_width ) / 2;
}

static void DrawTitle( char const* message )
{
	FontFuchi_SetType( 1 );
	FontFuchi_SetPos( CenteringX( message, 8 ), 24 );
	FontFuchi_PutStr( message );
}

static void DrawPushButton( char const* message )
{
	FontFuchi_SetType( 0 );
	FontFuchi_SetPos( CenteringX( message, 5 ), 54 );
	FontFuchi_PutStr( message );
}

static void DrawRestartMessage( void )
{
	DrawPushButton( "PUSH A BUTTON TO RESTART" );
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
		s_phase = Phase_Title;
		DrawGrid();
		DrawScore();
		
		s_initialize_succeed = TRUE;
	}
}

/// ƒƒCƒ“.
void pceAppProc( int cnt )
{
	BOOL moved = FALSE;

	if( !s_initialize_succeed || pcePadGet() & TRG_D )
	{
		pceAppReqExit( 0 );
	}
	
	switch( s_phase )
	{
	case Phase_Title:
	case Phase_GameOver:
	case Phase_Win:
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
				if( Win() )
				{
					s_phase = Phase_Win;
				}
				else
				{
					s_adding_panel = AddRandomPanel();
					PieceBmpAnimation_StartToEnd( &s_panel_anim, &s_panel_anim_bmp
						, s_period, FALSE );
				}
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
		DrawTitle( "2048 for P/ECE" );
		DrawPushButton( "PUSH A BUTTON TO START" );
		break;
	case Phase_Game:
		break;
	case Phase_GameOver:
		DrawTitle( "GAME OVER" );
		DrawRestartMessage();
		break;
	case Phase_Win:
		DrawTitle( "YOU WIN !!" );
		DrawRestartMessage();
		break;
	}
	
	Lcd_Update();
	Lcd_Trans();
	rand(); // ‹ó‰ñ‚µ
}

/// I—¹.
void pceAppExit( void )
{
	FontProxy_Unhook_Set();
	Configure_Exit();
}

