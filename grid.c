#include "grid.h"

int g_grid[GRID_WIDTH * GRID_WIDTH];
int g_score;

static int pow2( int n )
{
	int result = 1, i;
	for( i = 0; i < n; i++ )
	{
		result *= 2;
	}
	return result;
}

static void CopyGrid( int source[] )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		g_grid[i] = source[i];
	}
}

static void FlipGridHorizontal( void )
{
	int flipped[GRID_WIDTH * GRID_WIDTH], i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		int const x = i % GRID_WIDTH, y = i / GRID_WIDTH;
		flipped[i] = g_grid[( GRID_WIDTH - x - 1 ) + GRID_WIDTH * y];
	}
	CopyGrid(flipped);
}

static void TransposeGrid( void )
{
	int transposed[GRID_WIDTH * GRID_WIDTH], i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		int const x = i % GRID_WIDTH, y = i / GRID_WIDTH;
		transposed[i] = g_grid[y + GRID_WIDTH * x];
	}
	CopyGrid(transposed);
}

static int NumEmptyGrids( void )
{
	int num_empty = 0, i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( g_grid[i] == 0 )
		{
			++num_empty;
		}
	}
	return num_empty;
}

void InitGrid( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		g_grid[i] = 0;
	}
	g_score = 0;
}

int AddRandomPanel( void )
{
	int rest = rand() % NumEmptyGrids(), i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( g_grid[i] == 0 )
		{
			if( rest <= 0 )
			{
				break;
			}
			--rest;
		}
	}
	g_grid[i] = ( rand() % 10 < 1 ) ? 2 : 1; // 4:2 = 1:9
	return i;
}

BOOL MoveLeft( void )
{
	BOOL moved = FALSE;
	int x, xx, y;
	for( y = 0; y < GRID_WIDTH; y++ )
	{
		for( x = 0; x < GRID_WIDTH; x++ )
		{
			for( xx = x + 1; xx < GRID_WIDTH && g_grid[xx + GRID_WIDTH * y] == 0; xx++ ) {}
			if( GRID_WIDTH <= xx )
			{
				break;
			}
			if( g_grid[x + GRID_WIDTH * y] == 0 )
			{
				g_grid[x + GRID_WIDTH * y] = g_grid[xx + GRID_WIDTH * y];
				g_grid[xx + GRID_WIDTH * y] = 0;
				--x;
				moved = TRUE;
			}
			else if( g_grid[x + GRID_WIDTH * y] == g_grid[xx + GRID_WIDTH * y] )
			{
				++g_grid[x + GRID_WIDTH * y];
				g_grid[xx + GRID_WIDTH * y] = 0;
				g_score += pow2( g_grid[x + GRID_WIDTH * y] );
				moved = TRUE;
			}
		}
	}
	return moved;
}

BOOL MoveRight( void )
{
	BOOL moved;
	FlipGridHorizontal();
	moved = MoveLeft();
	FlipGridHorizontal();
	return moved;
}

BOOL MoveUp( void )
{
	BOOL moved;
	TransposeGrid();
	moved = MoveLeft();
	TransposeGrid();
	return moved;
}

BOOL MoveDown( void )
{
	BOOL moved;
	TransposeGrid();
	moved = MoveRight();
	TransposeGrid();
	return moved;
}

BOOL Movable( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( g_grid[i] == 0
			|| ( ( i + 1 ) % GRID_WIDTH != 0 && g_grid[i] == g_grid[i + 1] )
			|| ( i / GRID_WIDTH + 1 < GRID_WIDTH && g_grid[i] == g_grid[i + GRID_WIDTH] ) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Win( void )
{
	int i;
	for( i = 0; i < GRID_WIDTH * GRID_WIDTH; i++ )
	{
		if( g_grid[i] == 11 )
		{
			return TRUE;
		}
	}
	return FALSE;
}
