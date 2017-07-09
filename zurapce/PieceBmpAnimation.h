#if !defined( ZURAPCE_PIECE_BMP_ANIMATION_H )
#define ZURAPCE_PIECE_BMP_ANIMATION_H

/** @file
	PIECE_BMP ���g�����A�ԃA�j���[�V�����֘A.
	@author zurachu
*/

#include "PieceBmp.h"

/**
	PIECE_BMP ���g�����A�ԃA�j���[�V�����Đ��@�\.
*/
struct PieceBmpAnimation
{
	UnitedPieceBmp* playing; ///< �Đ����̉摜
	int current_index; ///< ���݂̃C���f�b�N�X
	int start_index; ///< �擪�̃C���f�b�N�X
	int end_index; ///< �ŏI�̃C���f�b�N�X
	int delta; ///< �o�ߎ��ԁi�X�V�����ɒB���閈�Ɏ��̃C���f�b�N�X�ɐi�݂܂��j
	int update_period; ///< �X�V����
	BOOL loop; ///< ���[�v���邩�ۂ�
};
typedef struct PieceBmpAnimation PieceBmpAnimation;

/**
	�A�ԃA�j���[�V�����̍Đ����J�n.
*/
void PieceBmpAnimation_Start( PieceBmpAnimation* p
	, UnitedPieceBmp* bmp, int start, int end, int update_period, BOOL loop );

/**
	�摜�S�Ă��g�����A�ԃA�j���[�V�����̍Đ����J�n.
	start = 0, end �� bmp ���玩���ŎZ�o���܂��B
*/
void PieceBmpAnimation_StartToEnd( PieceBmpAnimation* p
	, UnitedPieceBmp* bmp, int update_period, BOOL loop );

/**
	�A�ԃA�j���[�V�������X�V.
	@param p PieceBmpAnimation �\���̂ւ̃|�C���^
	@param delta �O��Ăяo������̌o�ߎ���.
*/
void PieceBmpAnimation_Update(PieceBmpAnimation* p, int delta );

/**
	�Đ����� UnitePieceBmp ��Ԃ�.
	@param p PieceBmpAnimation �\���̂ւ̃|�C���^
	@return �Đ����łȂ��ꍇ NULL
*/
UnitedPieceBmp* PieceBmpAnimation_Playing( PieceBmpAnimation const* p );

/**
	PieceBmpAnimation ���I�����Ă��邩�ǂ���.
	�I�����񃋁[�v�Đ��ōŏI�̃C���f�b�N�X�ɓ��B�������A��Đ������B
	@param p PieceBmpAnimation �\���̂ւ̃|�C���^
*/
BOOL PieceBmpAnimation_IsEnd( PieceBmpAnimation const* p );

/**
	PieceBmpAnimation �̕`��.
	@param p PieceBmpAnimation �\���̂ւ̃|�C���^
	@param dx �`��捶�� X ���W
	@param dy �`��捶�� Y ���W
	@param param �p�����[�^
	@return pceLCDDrawObject() �̖߂�l�i0:�`��Ȃ�, 1:�`�抮���j
*/
int PieceBmpAnimation_Draw( PieceBmpAnimation const* p
	, int dx, int dy, int param );

/**
	PieceBmpAnimation �̍Đ����N���A.
*/
void PieceBmpAnimation_Clear( PieceBmpAnimation* p );

#endif // !defined( ZURAPCE_PIECE_BMP_ANIMATION_H )
