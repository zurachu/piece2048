#include "Ldirect.h"

/** @file
	16�K���\���֘A�̎���.
	
	@author zurachu
*/

#include <piece.h>
#include <string.h>

#define LDIRECT_PAGE_NUM	5 ///< �؂�ւ��y�[�W��
#define LDIRECT_COLOR_NUM	16 ///< �K�����iLDIRECT_PAGE_NUM * 3 + 1�j

/// 16�K���p���z��ʃo�b�t�@
BYTE* g_lbuff = NULL;

/// LCD �_�C���N�g�]���p�o�b�t�@
BYTE* g_dbuff[ LDIRECT_PAGE_NUM ] = { NULL };

/// �S�K���o�b�t�@�`��t���O
static BOOL s_vbuff_view = FALSE;

/// �c��X�V�y�[�W���J�E���g
static int s_dbuff_update_count = 0;

int Ldirect_Init( void )
{
	int i;
	
	g_lbuff = pceHeapAlloc( DISP_X * DISP_Y );
	if( !g_lbuff ) { return 0; }
	
	for( i = 0; i < LDIRECT_PAGE_NUM; i++ )
	{
		g_dbuff[ i ] = pceHeapAlloc( DISP_X * DISP_Y / 4 );
		if( !g_dbuff[ i ] )
		{
			while( --i >= 0 )
			{
				pceHeapFree( g_dbuff[ i ] );
				g_dbuff[ i ] = NULL;
			}
			pceHeapFree( g_lbuff );
			g_lbuff = NULL;
			return 0;
		}
	}
	Ldirect_VBuffClear( 0, 0, DISP_X, DISP_Y );
	memset( g_lbuff, 0, DISP_X * DISP_Y );
	for( i = 0; i < LDIRECT_PAGE_NUM; i++ )
	{
		memset( g_dbuff[ i ], 0, DISP_X * DISP_Y / 4 );
	}
	return 1;
}

BYTE* Ldirect_Buffer( void )
{
	return g_lbuff;
}

/**
	16�K���p���z��ʃo�b�t�@����w��y�[�W�̃_�C���N�g�]���p�o�b�t�@�Ƀ}�X�N�Ȃ��]��.
	@param page �_�C���N�g�]���p�o�b�t�@�̃y�[�W�ԍ�
*/
static void lbuff_trans( int const page )
{
	static WORD const s_color_table[ LDIRECT_PAGE_NUM ][ LDIRECT_COLOR_NUM ] =
	{
		{ 0x000, 0x100, 0x000, 0x100, 0x100, 0x100, 0x001, 0x100, 0x001, 0x001, 0x001, 0x101, 0x001, 0x101, 0x101, 0x101 },
		{ 0x000, 0x000, 0x100, 0x000, 0x100, 0x100, 0x100, 0x001, 0x100, 0x001, 0x001, 0x001, 0x101, 0x001, 0x101, 0x101 },
		{ 0x000, 0x000, 0x000, 0x100, 0x100, 0x100, 0x100, 0x100, 0x001, 0x001, 0x001, 0x001, 0x001, 0x101, 0x101, 0x101 },
		{ 0x000, 0x000, 0x100, 0x000, 0x100, 0x100, 0x100, 0x001, 0x100, 0x001, 0x001, 0x001, 0x101, 0x001, 0x101, 0x101 },
		{ 0x000, 0x000, 0x000, 0x100, 0x000, 0x100, 0x100, 0x100, 0x001, 0x100, 0x001, 0x001, 0x001, 0x101, 0x001, 0x101 },
		//    0,     1,     2,     3,     4,     5,     6,     7,     8,     9,     A,     B,     C,     D,     E,     F
	};
	int xx, yy;
	WORD* dbuff_ptr = (WORD*)g_dbuff[ page ];
	BYTE const* lbuff_ptr = g_lbuff;
	WORD const* const color_table_ptr = s_color_table[ page ];
	WORD c;

	for( xx = 0; xx < DISP_X / 8; xx += 1 )
	{
		for( yy = 0; yy < DISP_Y; yy += 1 )
		{
			c = color_table_ptr[ *lbuff_ptr++ ];
			c |= color_table_ptr[ *lbuff_ptr++ ] << 1;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 2;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 3;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 4;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 5;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 6;
			c |= color_table_ptr[ *lbuff_ptr++ ] << 7;
			*dbuff_ptr++ = c;
			lbuff_ptr += DISP_X - 8;
		}
		lbuff_ptr += -( DISP_X * DISP_Y ) + 8;
	}
}

/**
	�S�K���p���z��ʃo�b�t�@����w��y�[�W�̃_�C���N�g�]���p�o�b�t�@�Ƀ}�X�N����]��.
	@param page �_�C���N�g�]���p�o�b�t�@�̃y�[�W�ԍ�
*/
static void vbuff_trans( int const page )
{
	static WORD const s_color_table[] = { 0x000, 0x100, 0x001, 0x101 };
	int xx, yy;
	WORD* dbuff_ptr = (WORD*)g_dbuff[page];
	BYTE const* vbuff_ptr = pceLCDSetBuffer( INVALIDPTR );
	BYTE c;
	WORD color, mask_bit;

	for( xx = 0; xx < DISP_X / 8; xx += 1 )
	{
		for( yy = 0; yy < DISP_Y; yy += 1 )
		{
			// �}�X�N�̃r�b�g���Z�� COLOR_MASK = 4 �ł���O��
			c = *vbuff_ptr++; mask_bit = ( c & COLOR_MASK ) >> 2; color = s_color_table[ c ];
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) >> 1; color |= s_color_table[ c ] << 1;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ); color |= s_color_table[ c ] << 2;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) << 1; color |= s_color_table[ c ] << 3;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) << 2; color |= s_color_table[ c ] << 4;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) << 3; color |= s_color_table[ c ] << 5;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) << 4; color |= s_color_table[ c ] << 6;
			c = *vbuff_ptr++; mask_bit |= ( c & COLOR_MASK ) << 5; color |= s_color_table[ c ] << 7;
			mask_bit |= mask_bit << 8;
			*dbuff_ptr &= mask_bit;	*dbuff_ptr++ |= color & ~mask_bit;
			vbuff_ptr += DISP_X - 8;
		}
		vbuff_ptr += -( DISP_X * DISP_Y ) + 8;
	}
}

void Ldirect_Update( void )
{
	s_dbuff_update_count = LDIRECT_PAGE_NUM;
}

void Ldirect_Trans( void )
{
	static int page = 0;
	
	if( s_dbuff_update_count )
	{
		lbuff_trans( page );
		if( s_vbuff_view )
		{
			vbuff_trans( page );
		}
		s_dbuff_update_count--;
	}
	pceLCDTransDirect( g_dbuff[ page ] );
	page = ( page + 1 ) % LDIRECT_PAGE_NUM;
}

void Ldirect_VBuffView( BOOL visible )
{
	s_vbuff_view = visible;
}

void Ldirect_VBuffClear( int x, int y, int width, int height )
{
	BYTE* vbuff_ptr = pceLCDSetBuffer( INVALIDPTR );
	int yy;

	if( x >= DISP_X || y >= DISP_Y ) return;
	if( x < 0 ) { width += x; x = 0; }
	if( y < 0 ) { height += y; y = 0; }
	if( width <= 0 || height <= 0 ) return;
	if( x + width >= DISP_X ) { width = DISP_X - x; }
	if( y + height >= DISP_Y ) { height = DISP_Y - y; }

	vbuff_ptr += x + DISP_X * y;
	for( yy = 0; yy < height; yy += 1 )
	{
		memset( vbuff_ptr, COLOR_MASK, width );
		vbuff_ptr += DISP_X;
	}
}

int Ldirect_DrawObject( PIECE_BMP const* p, int dx, int dy, int sx, int sy
						, int width, int height )
{
	int const mask_bit = p->header.mask;
	int const sw = p->header.w;
	int const sh = p->header.h;
	int xx, yy, x_bit;
	BYTE* const buff_base = p->buf;
	BYTE* const mask_base = p->mask;
	BYTE* lbuff_ptr;
	BYTE* buff_ptr;
	BYTE* mask_ptr;
	BYTE b = 0, m = 0;
	
	if( dx >= DISP_X || dy >= DISP_Y ) return 0;
	if( dx < 0 ) { width += dx; sx -= dx; dx = 0; }
	if( dy < 0 ) { height += dy; sy -= dy; dy = 0; }
	if( sx < 0 ) { width += sx; sx = 0; }
	if( sy < 0 ) { height += sy; sy = 0; }
	if( width <= 0 || height <= 0 ) return 0;
	if( width > sw ) { width = sw; }
	if( height > sh ) { height = sh; }
	if( dx + width > DISP_X ) { width = DISP_X - dx; }
	if( dy + height > DISP_Y ) { height = DISP_Y - dy; }

	lbuff_ptr = g_lbuff + ( dx + DISP_X * dy );

	for( yy = 0; yy < height; yy += 1 )
	{
		buff_ptr = buff_base + ( ( sx + sw * ( sy + yy ) ) >> 1 );
		mask_ptr = mask_base + ( ( sx + sw * ( sy + yy ) ) >> 3 );
		x_bit = sx & 7;
		if( x_bit & 1 ) { b = *buff_ptr++ << 4; }
		if( x_bit ) { m = ( mask_bit )? ( *mask_ptr++ << x_bit ) : 0; }
		for( xx = 0; xx < width; xx += 1 )
		{
			if( !( x_bit & 1 ) ) { b = *buff_ptr++; }
			if( !x_bit ) { m = ( mask_bit )? *mask_ptr++ : 0; }
			*lbuff_ptr++ = ( m & 0x80 )? *lbuff_ptr : ( b >> 4 );
			x_bit = ( x_bit + 1 ) & 7;
			b <<= 4;
			m <<= 1;
		}
		lbuff_ptr += DISP_X - width;
	}
	return 1;
}

void Ldirect_Point( BYTE color, int const x, int const y )
{
	if( x >= DISP_X ) return;
	if( x < 0 ) return;
	if( y >= DISP_Y ) return;
	if( y < 0 ) return;
	
	*( g_lbuff + ( x + DISP_X * y ) ) = color;
}

void Ldirect_Paint( BYTE color, int x, int y, int width, int height )
{
	BYTE* lbuff_ptr;
	int yy;

	if( x >= DISP_X || y >= DISP_Y ) return;
	if( x < 0 ) { width += x; x = 0; }
	if( y < 0 ) { height += y; y = 0; }
	if( width <= 0 || height <= 0 ) return;
	if( x + width > DISP_X ) { width = DISP_X - x; }
	if( y + height > DISP_Y ) { height = DISP_Y - y; }

	lbuff_ptr = g_lbuff + ( x + DISP_X * y );
	for( yy = 0; yy < height; yy += 1 )
	{
		memset( lbuff_ptr, color, width );
		lbuff_ptr += DISP_X;
	}
}

