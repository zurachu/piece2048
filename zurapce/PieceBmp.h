#if !defined( ZURAPCE_PIECE_BMP_H )
#define ZURAPCE_PIECE_BMP_H

/** @file
	PIECE_BMP �֘A.
	@author zurachu
*/

#include <piece.h> // PIECE_BMP

/**
	PIECE_BMP �̏�����.
	BMP �R���o�[�^�ŕϊ������f�[�^���APIECE_BMP �ɓo�^���܂��B
	@param p PIECE_BMP �\���̂ւ̃|�C���^
	@param source ���f�[�^
*/
void PieceBmp_Construct( PIECE_BMP* p, unsigned char* source );

/**
	PIECE_BMP �̕`��.
	@param p PIECE_BMP �\���̂ւ̃|�C���^
	@param dx �`��捶�� X ���W
	@param dy �`��捶�� Y ���W
	@param sx �`�挳���� X ���W
	@param sy �`�挳���� Y ���W
	@param width ��
	@param height ����
	@param param �p�����[�^
	@return pceLCDDrawObject() �̖߂�l�i0:�`��Ȃ�, 1:�`�抮���j
*/
int PieceBmp_Draw( PIECE_BMP* p, int dx, int dy, int sx, int sy
				, int width, int height, int param );

/**
	���T�C�Y�̕����̉摜���c���ɕ��ׂ� PIECE_BMP.
*/
struct UnitedPieceBmp
{
	PIECE_BMP bmp; ///< PIECE_BMP �\����
	int width; ///< �摜�P�̕�
	int height; ///< �摜�P�̍���
};
typedef struct UnitedPieceBmp UnitedPieceBmp;

/**
	UnitedPieceBmp �̏�����.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
	@param source ���f�[�^
	@param width �摜�P�̕�
	@param height �摜�P�̍���
*/
void UnitedPieceBmp_Construct( UnitedPieceBmp* p
	, unsigned char* source, int width, int height );

/**
	���������w�肵�Ă� UnitedPieceBmp �̏�����.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
	@param source ���f�[�^
	@param divx X �����̕�����
	@param divy Y �����̕�����
*/
void UnitedPieceBmp_ConstructByDivision( UnitedPieceBmp* p
	, unsigned char* source, int divx, int divy );

/**
	UnitedPieceBmp �̕��������擾.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
*/
int UnitedPieceBmp_NumDivision( UnitedPieceBmp const* p );

/**
	UnitedPieceBmp �̕������� X, Y �������ꂼ��ʂɎ擾.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
	@param [out] x X �����̕������i�[��
	@param [out] y Y �����̕������i�[��
*/
void UnitedPieceBmp_NumDivisionByXY( UnitedPieceBmp const* p, int* x, int* y );

/**
	UnitedPieceBmp �̕`��.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
	@param dx �`��捶�� X ���W
	@param dy �`��捶�� Y ���W
	@param index �`�悷��摜�̃C���f�b�N�X�ԍ�.
	@param param �p�����[�^
	@return pceLCDDrawObject() �̖߂�l�i0:�`��Ȃ�, 1:�`�抮���j
	index �͍��ォ�� 0,1,... �Ɛi�݁A�E�[�܂ōs�����牺�̍s�̍��[���琔���܂��B
@verbatim
X �����S�����A Y �����Q�����̏ꍇ
+-+-+-+-+
|0|1|2|3|
+-+-+-+-+
|4|5|6|7|
+-+-+-+-+
@endverbatim
*/
int UnitedPieceBmp_Draw( UnitedPieceBmp* p
	, int dx, int dy, int index, int param );

/**
	X, Y �����ŌʂɃC���f�b�N�X���w�肵�� UnitedPieceBmp �̕`��.
	@param p UnitedPieceBmp �\���̂ւ̃|�C���^
	@param dx �`��捶�� X ���W
	@param dy �`��捶�� Y ���W
	@param ix X �����C���f�b�N�X
	@param iy Y �����C���f�b�N�X
	@param param �p�����[�^
	@return pceLCDDrawObject() �̖߂�l�i0:�`��Ȃ�, 1:�`�抮���j
*/
int UnitedPieceBmp_DrawByXY( UnitedPieceBmp* p
	, int dx, int dy, int ix, int iy, int param );

#endif // !defined( ZURAPCE_PIECE_BMP_H )
