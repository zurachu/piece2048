#include "FramObject.h"

/** @file
	���� RAM �z�u�I�u�W�F�N�g�֘A�̎���.
*/

#include <string.h>

void FramObject_Init( void )
{
	extern unsigned long __START_00001000[]; // �]����
	extern unsigned long __SIZEOF_00001000[]; // �R�[�h�T�C�Y
	extern unsigned long __START_FramObject_Top_code[]; // �]����
	memcpy( __START_00001000, __START_FramObject_Top_code, (int)__SIZEOF_00001000 );
}

