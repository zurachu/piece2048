#if !defined( ZURAPCE_FONT_FUCHI_H )
#define ZURAPCE_FONT_FUCHI_H

/** @file
	�����t�H���g�֘A.
	���z��ʂɕ���������肵���t�H���g��\�����܂��B
	�g�p���@�́A�ق� pceFont �n�֐��݊��ł��B

	�����������d���ł����A�R�[�h������ RAM �ɔz�u���邱�Ƃō������ł��܂��B
	project.mak �� USE_FONT_FUCHI_ON_FRAM := true ��L���ɂ��āA
	pceAppInit() �̐擪�� FramObject_Init() ���Ăяo���ĉ������B

	@author zurachu
*/

/**
	�����\�����W���w��.
	@param x x���W
	@param y y���W
*/
void FontFuchi_SetPos( int x, int y );

/**
	�����\���͈͂��w��.
	@param left ���[x���W
	@param top ��[y���W
	@param right �E�[x���W
	@param bottom ���[y���W
*/
void FontFuchi_SetRange( int left, int top, int right, int bottom );

/**
	������ނ��w��.
	@param type ��ށi�O�`�Q�j
*/
void FontFuchi_SetType( int type );

/**
	�����F���w��.
	@param color �F�i�O�`�R�j
*/
void FontFuchi_SetTxColor( int color );

/**
	�����F���w��.
	@param color �F�i�O�`�R�j
*/
void FontFuchi_SetBdColor( int color );

/**
	�����t�H���g�����z��ʂɕ\��.
	@param x x���W
	@param y y���W
	@param code �����R�[�h
	@return 
			- b0-7 x�����̕�
			- b8-15 y�����̕�
	@warning
	���[�U���� FontProxy �𗘗p���Ȃ��ꍇ�A�t�H���g��ނ��㏑������Ă��܂��܂��B
*/
unsigned short FontFuchi_Put( int x, int y, unsigned short code );

/**
	����蕶��������z��ʂɏ������݂܂�.
	@param p ������̃A�h���X�B0 �ŏI�[�B
	@return �����Ō�̂P�o�C�g���V�t�g JIS �̑�P�o�C�g�������ꍇ���̃R�[�h��Ԃ��܂��B
			���̑��̏ꍇ�� 0 �ł��B
	@warning
	���[�U���� FontProxy �𗘗p���Ȃ��ꍇ�A�t�H���g��ނ��㏑������Ă��܂��܂��B
*/
int FontFuchi_PutStr( char const* p );

/**
	����蕶��������z��ʂɏ������݂܂��i�����w��j.
	@param fmt ����������
	@return �o�͂����o�C�g��
	@warning
	���[�U���� FontProxy �𗘗p���Ȃ��ꍇ�A�t�H���g��ނ��㏑������Ă��܂��܂��B
*/
int FontFuchi_Printf( char const* fmt, ... );

#endif // !defined( ZURAPCE_FONT_FUCHI_H )

