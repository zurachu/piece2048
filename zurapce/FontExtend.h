#if !defined( ZURAPCE_FONT_EXTEND_H )
#define ZURAPCE_FONT_EXTEND_H

/** @file
	�g���t�H���g�֘A.
	API ���t�b�N���邱�ƂŁApceFont �n API �Ɋg���t�H���g��ǉ����܂��B
	�g���t�H���g�́AAQUAPLUS ���Q�[���̎d�l�ɏ�����\��ł��B
@verbatim
	�g���t�H���g�̕����R�[�h
	- 0xF040 - �u!?�v
	- 0xF041 - �u!!�v
	- 0xF042 - �n�[�g�}�[�N
	- 0xF046 - �Q�������́u�`�v�̍���
	- 0xF047 - �Q�������́u�`�v�̉E��
@endverbatim
	
	@author zurachu
*/

/**
	�t�H���g�̃A�h���X���擾.
	�g���t�H���g�����R�[�h�Əƍ�������A�ʏ�� pceFontGetAdrs() ���Ăт܂��B
	@param code �����R�[�h
	@return �t�H���g�̃A�h���X
*/
unsigned char const* FontExtend_GetAdrs( unsigned short code );

/**
	�t�H���g�A�h���X�擾�� FontExtend_GetAdrs() ���g���悤�AAPI ���t�b�N���܂�.
*/
void FontExtend_Hook_GetAdrs( void );

/**
	�t�H���g�A�h���X�擾�ɒʏ�� pceFontGetAdrs() ���g���悤�AAPI �̃t�b�N���������܂�.
*/
void FontExtend_Unhook_GetAdrs( void );

#endif // !defined( ZURAPCE_FONT_EXTEND_H )

