#include "Turbo.h"

/** @file
	48 MHz ����֘A�̎���.
*/

// 24MHz/48MHz�ؑ֓��ݒ�I/O�|�[�g
#define	port_P0x	(*(volatile unsigned char*)0x402D1)

#define	reg_A6_4C	(*(volatile unsigned short int*)0x4812A)
#define	reg_A10_9C	(*(volatile unsigned short int*)0x48126)

// 16bit�^�C�}n ���䃌�W�X�^
#define reg_TC0		(*(volatile unsigned short int*)0x48186)
#define reg_TC1		(*(volatile unsigned short int*)0x4818E)
#define reg_TC4		(*(volatile unsigned short int*)0x481A6)

// 16bit�^�C�}0 �R���y�A�f�[�^B �ݒ背�W�X�^ (1ms�^�C�}) �f�t�H���g=5999
#define reg_CR0B	(*(volatile unsigned short int*)0x48182)

// 16bit�^�C�}x �N���b�N�R���g���[�����W�X�^
//---------------------------------------------
// * bit 2:0��������
//   7: f/4096  6: f/1024  5: f/256   4: f/64 
//   3: f/16    2: f/4     1: f/2     0: f/1 
//---------------------------------------------
#define reg_CC1	(*(volatile unsigned char*)0x40148)
#define reg_CC4	(*(volatile unsigned char*)0x4014B)

// * �Q�l *
// PIECE/sysdev/pcekn/snd.c    PWMC      750
// PIECE/sysdev/pcekn/timer.c  TMCOUNTER 6000

static void stop_timer( void )
{
	reg_TC0 &= ~4;
	reg_TC1 &= ~4;
	reg_TC4 &= ~4;
}

static void start_timer( void )
{
	reg_TC0 |= 4;
	reg_TC1 |= 4;
	reg_TC4 |= 4;
}

void Turbo_Init( void )
{	// �x�[�X�N���b�N/������/�R���y�A�f�[�^
	stop_timer();	// �J�E���g�ꎞ��~

	port_P0x &= ~0x80;	// �x�[�X�N���b�N�� 48 MHz ��
	reg_A6_4C  = (reg_A6_4C  & ~0x7) | 1;	// SRAM �A�N�Z�X = 1 �E�F�C�g
	reg_A10_9C = (reg_A10_9C & ~0x7) | 1;	// �t���b�V�� ROM �A�N�Z�X = 1 �E�F�C�g

	reg_CR0B = 11999;				// 48 MHz / 4 / 12000 =  1 kHz ( 1 ms �J�E���^ )
	reg_CC1 = (reg_CC1 & ~0x7) | 1;	// 48 MHz / 2 / 750   = 32 kHz ( PWM �����p )
	reg_CC4 = (reg_CC4 & ~0x7) | 1;	// 48 MHz / 2 / 4     =  6 MHz ( USB �p�N���b�N )

	start_timer();	// �J�E���g�J�n
}

void Turbo_Exit( void )
{
	stop_timer();	// �J�E���g�ꎞ��~

	reg_A6_4C  = (reg_A6_4C  & ~0x7) | 2;	// SRAM �A�N�Z�X = 2 �E�F�C�g
	reg_A10_9C = (reg_A10_9C & ~0x7) | 2;	// �t���b�V�� ROM �A�N�Z�X = 2 �E�F�C�g

	port_P0x |= 0x80;	// �x�[�X�N���b�N��24MHz��.
	reg_CR0B = 5999;				// 24 MHz / 4 / 6000 =  1 kHz ( 1 ms �J�E���^ )
	reg_CC1 = (reg_CC1 & ~0x7) | 0;	// 24 MHz / 1 / 750  = 32 kHz ( PWM �����p )
	reg_CC4 = (reg_CC4 & ~0x7) | 0;	// 24 MHz / 1 / 4    =  6 MHz ( USB �p�N���b�N )

	start_timer();	// �J�E���g�J�n
}

