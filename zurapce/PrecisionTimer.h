#if !defined( ZURAPCE_PRECISION_TIMER_H )
#define ZURAPCE_PRECISION_TIMER_H

/** @file
	�����x�^�C�}�[�֘A.
	@author zurachu
*/

/// �����x�^�C�}�[�\����.
/// �����o�𒼐ڐG��Ȃ����ƁB
struct PrecisionTimer
{
	unsigned long count; ///< �O��v���l
};
typedef struct PrecisionTimer PrecisionTimer;

/**
	�����x�^�C�}�[�̏�����.
	���݂̍����x�^�C�}�[�l���l�����A���Ԍv���̊�Ƃ��܂��B
	@param p
*/
void PrecisionTimer_Construct( PrecisionTimer* p );

/**
	�����x�^�C�}�[�̃J�E���g.
	���݂̍����x�^�C�}�[�l���l�����A�O��v���l�Ƃ̍���Ԃ��܂��B
	�܂��A���݂̍����x�^�C�}�[�l�����񎞊Ԍv���̊�Ƃ��܂��B
	pceAppProc() ���ɌĂяo���āA���������̊m�F�ɗp����Ȃǂ��ĉ������B
	@param p
	@return �O��v��������̌o�ߎ��� [��sec]
	@warning pceTimerGetPrecisionCount() �̎d�l�ŁA�� 65 �b�ȏ�̎��Ԃ̑���ɂ͎g���܂���B
*/
unsigned long PrecisionTimer_Count( PrecisionTimer* p );

#endif // !defined( ZURAPCE_PRECISION_TIMER_H )

