#if !defined( GRID_H )
#define GRID_H

#include <piece.h> // BOOL

#define GRID_WIDTH (4)
extern int g_grid[GRID_WIDTH * GRID_WIDTH];
extern int g_score;

void InitGrid( void );


int AddRandomPanel( void );

BOOL MoveLeft( void );

BOOL MoveRight( void );

BOOL MoveUp( void );

BOOL MoveDown( void );

BOOL Movable( void );

BOOL Win( void );

#endif // GRID_H
