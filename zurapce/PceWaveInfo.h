#if !defined( ZURAPCE_PCEWAVEINFO_H )
#define ZURAPCE_PCEWAVEINFO_H

/** @file
	PCEWAVEINFO �֘A.
	@author zurachu
*/

#include <piece.h> // PCEWAVEINFO

/**
	PCEWAVEINFO �̏�����.
	PCM �R���o�[�^�ŕϊ������f�[�^���APCEWAVEINFO �ɓo�^���܂��B
	@param p PCEWAVEINFO �\���̂ւ̃|�C���^
	@param source ���f�[�^
*/
void PceWaveInfo_Construct( PCEWAVEINFO* p, unsigned char* source );

#endif // !defined( ZURAPCE_PCEWAVEINFO_H )
