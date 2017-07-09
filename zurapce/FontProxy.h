#if !defined( ZURAPCE_FONT_PROXY_H )
#define ZURAPCE_FONT_PROXY_H

/** @file
	�t�H���g�ݒ�̑�s����.
	pceFontSet �n API �Őݒ肵�����e���擾���� API �����J����Ă��Ȃ����߁A
	API ���t�b�N���Đݒ�l��ۑ����Ă����A�擾�ł���悤�ɂ��܂��B
	@warning
	API ���t�b�N���Ȃ���Ԃ� pceFontSet�`() �𒼐ڌĂяo���ƁA
	�ݒ���e�̐����������Ȃ��Ȃ�̂Œ��ӂ��ĉ������B
	@author zurachu
*/

/**
	�t�H���g�̎�ނ�\���������w��.
	@param type
		- bit0�`6 : �t�H���g�̎��
			- 0 �ʏ�t�H���g ���p5�~10�h�b�g �S�p10�~10�h�b�g
			- 1 �g��t�H���g ���p8�~16�h�b�g �{�[���h (ASCII�̂�)
			- 2 �ɏ��t�H���g ���p4�~ 6�h�b�g (ASCII�̂�)
		- bit7 :
			 - 0 �̎��́A��ʉE�[�Ŏ������s����
			 - 1 �̎��́A�������s���Ȃ�
*/
void FontProxy_SetType( int type );

/**
	�t�H���g�̎�ނ�\���������擾.
*/
int FontProxy_GetType( void );

/**
	�����F���w��.
	@param color �F�i�O�`�R�j
*/
void FontProxy_SetTxColor( int color );

/**
	�����F���擾.
*/
int FontProxy_GetTxColor( void );

/**
	�w�i�F���w��.
	@param color �F�i�O�`�R�jFC_SPRITE �̏ꍇ�͓���
*/
void FontProxy_SetBkColor( int color );

/**
	�w�i�F���擾.
*/
int FontProxy_GetBkColor( void );

/**
	�t�H���g�ݒ�� FontProxy_Set�`() ���g���悤�AAPI ���t�b�N���܂�.
*/
void FontProxy_Hook_Set( void );

/**
	�t�H���g�ݒ�ɒʏ�� pceFontSet�`() ���g���悤�AAPI �̃t�b�N���������܂�.
*/
void FontProxy_Unhook_Set( void );

#endif // !defined( ZURAPCE_FONT_PROXY_H )

