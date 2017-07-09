#if !defined( ZURAPCE_TERMINAL_H )
#define ZURAPCE_TERMINAL_H

/**	@file
	�g���[�q�֘A.
	P/ECE HAND BOOK Vol.2 �Œ񏥂��ꂽ�g���[�q�ւ̓��o�͂�񋟂��܂��B
	P/ECE HAND BOOK Vol.2 �f�ڃ\�[�X�R�[�h�̊ԈႢ���C�����Ď�荞�݁B

@verbatim

�wP/ECE Hand Book VOL.2�x�́uLED�����v�Ŋg���[�q�̎g������m��v�̋L���������Ă����Ƃ���A������ƊԈႢ�������܂����B
081�y�[�W�Ɍf�ڂ���Ă���LED TEST�A�v���P�[�V�����̃\�[�X�R�[�h�A29�`30�s�ڂ́g�|�[�g�̏������h�̂Ƃ���A
	P0CFP = ( P0IOC & 0x8F ) | 0x00; // �|�[�g�Ƃ��Ĉ���
	P1CFP = ( P1IOC & 0xEB ) | 0x00; // �|�[�g�Ƃ��Ĉ���
�͊ԈႢ�ŁA��������
	P0CFP = ( P0CFP & 0x8F ) | 0x00; // �|�[�g�Ƃ��Ĉ���
	P1CFP = ( P1CFP & 0xEB ) | 0x00; // �|�[�g�Ƃ��Ĉ���
�ł��ˁB
�t��CD-ROM�ɓ����Ă���\�[�X�R�[�h�Ǝ��s�t�@�C���ɂ������ԈႢ������悤�ŁA���s���P/ECE�̓��삪�s����ɂȂ�ꍇ������܂��B
@endverbatim
	P/ECE�������insawa���j2004/05/09 20:54 ���
	http://www.piece-me.org/
	
	@author zurachu
*/

/// ����
#define T_IN (0)

/// �o��
#define T_OUT (1)

/**
	�g���[�q�̓��o�͂�������.
	���ꂼ�� T_IN �܂��� T_OUT ���w�肵�Ă��������B
	@param p1 �|�[�g�P�i�g���[�q�P�j
	@param p2 �|�[�g�Q�i�g���[�q�S�j
	@param p3 �|�[�g�R�i�g���[�q�U�j
	@param p4 �|�[�g�S�i�g���[�q�V�j
	@param p5 �|�[�g�T�i�g���[�q�W�j
*/
void Terminal_Init( unsigned char p1
				  , unsigned char p2
				  , unsigned char p3
				  , unsigned char p4
				  , unsigned char p5 );

/**
	�g���[�q�Ƀf�[�^���o��.
	@param port �o�͐�|�[�g�i�P�`�T�j
	@param data �f�[�^�i�O�^�P�j
*/
void Terminal_Set( int port, unsigned char data );

/**
	�g���[�q����f�[�^�����.
	@param port ���͌��|�[�g�i�P�`�T�j
	@return �f�[�^�i�O�^�P�j
*/
int Terminal_Get( int port );

#endif // !defined( ZURAPCE_TERMINAL_H )

