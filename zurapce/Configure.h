#if !defined( ZURAPCE_CONFIGURE_H )
#define ZURAPCE_CONFIGURE_H

/** @file
	�ݒ�ۑ��֘A.
	PIECE API ���t�@�����X��
	pceLCDSetBright() �����
	pceWaveSetMasterAtt() �̐�����
@verbatim
���ӁI
���̃p�����[�^�̓��[�U���V�X�e�����j���[�Œ����E�ݒ肷��
�p�����[�^�Ȃ̂ŁA�ʏ�̃A�v���P�[�V�������g�p����̂�
�D�܂�������܂���B
@endverbatim
	�Ƃ���̂ŁA�A�v���P�[�V�������ł����ύX����ꍇ�A�I�����ɋN���O�̐ݒ�ɖ߂����߂̎����B
	
	@author zurachu
*/

/**
	������.
	�N���O�̃R���g���X�g�A���ʐݒ��ۑ����܂��B
*/
void Configure_Init( void );

/**
	�I��.
	�N���O�̃R���g���X�g�A���ʐݒ�ɖ߂��܂��B
*/
void Configure_Exit( void );

#endif // !defined( ZURAPCE_CONFIGURE_H )
