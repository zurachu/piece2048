#if !defined( ZURAPCDE_TURBO_H )
#define ZURAPCDE_TURBO_H

/** @file
	48 MHz ����֘A.
	���������́uP/ECE��48MHz���[�h�œ��������߂̏��׍H ver0.9b�v����荞�݁B
	http://junkbox.info/piece/
@code
//---------------------------------------------------------------------
//  - ���̃\�[�X�͉����E�Ĕz�z�Ȃǎ��R�ɂ��g�����������B���͕s�v�ł��B
//  - ����m�F�́ABIOS ver1.18 2002.01.16 ��ōs���Ă��܂��B
//  - �g�p�͎��ȐӔC�ł��肢���܂��B
//  - �����_�ł́A48MHz���[�h�ɂ�����LCD/�T�E���h�Đ�/1ms�^�C�}�̐�����
//    ����ƁA48MHz���[�h����24MHz���[�h�ɕ��A�����ꍇ�ɐ����USB�A�N�Z
//    �X���s���邱�Ƃ̂݊m�F���Ă��܂��B
//  - �\�[�X�𑗂��Ă���������΁A��L�ȊO�ɂ��Ă��Ή����Ă����܂��B
//---------------------------------------------------------------------
//  pceCPUSetSpeed()���߂ƕ��p����ꍇ�ɂ́ATurbo_Init/Exit��K���ȉ��̏���
//  �s���Ă��������B
//
//  pceCPUSetSpeed(n); �̌�� Turbo_Init();
//  Turbo_Exit(); �̌�� pceCPUSetSpeed(n);
//---------------------------------------------------------------------
@endcode

	@author zurachu
*/

/**
	48 MHz ���[�h�ɐ؂�ւ��܂�.
*/
void Turbo_Init( void );

/**
	�W�� ( 24 MHz ) ���[�h�ɐ؂�ւ��܂�.
	pceAppExit() �ɂ� �K�� Turbo_Exit(); �������悤�ɂ��Ă�������
*/
void Turbo_Exit( void );

#endif // !defined( ZURAPCDE_TURBO_H )
