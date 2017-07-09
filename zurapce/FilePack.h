#if !defined( ZURAPCE_FILE_PACK_H )
#define ZURAPCE_FILE_PACK_H

/** @file
	�t�@�C���p�b�N �֘A.
	P/ECE �J�����t���� FilePack.exe �Ő��������p�b�N�f�[�^����t�@�C���𒊏o���܂��B
	@author zurachu
*/

#include <piece.h> // FILEACC

/// �p�b�N�t�@�C���ǂݍ��݃n���h��
struct FilePackHandle
{
	FILEACC file_acc; ///< �t�@�C���\����
	int file_amount; ///< �t�@�C����
	/**
		16bit CRC.
		�t�@�C���T�����A�܂��t�@�C��������擾���� CRC �����ꂩ��r���A
		����Ȃ���ۂɃt�@�C�������r���邱�ƂŁA�ǂݍ��݂̍�������}��B
		�n���h�����J���ƁA�t�@�C�����~2�o�C�g�m�ۂ���܂��B
		�iAutch���� libfpk �� pceth2 �� nsawa�����{�������ǂ���荞�݁j
	*/
	unsigned short* crc;
};
typedef struct FilePackHandle FilePackHandle;

/**
	�n���h�����J��.
	@param handle �n���h��
	@param filename �p�b�N�t�@�C����
	@retval 0 ����I��
	@retval 1 �p�b�N�t�@�C��������
*/
int FilePackHandle_Open( FilePackHandle* handle, char const* filename );

/**
	�n���h�������.
	@param handle �n���h��
	@retval 0 ��ɐ���I��
*/
int FilePackHandle_Close( FilePackHandle* handle );

/**
	�p�b�N�t�@�C������P�t�@�C����ǂݍ���Ńo�b�t�@�Ɋi�[.
	@param dst �o�͐�o�b�t�@
	@param handle �n���h��
	@param filename �t�@�C����
	@return �ǂݍ��݃T�C�Y�i���s���O�j
	@see FileAcc_ReadPosTo()
*/
int FilePackHandle_ReadTo( unsigned char* dst, FilePackHandle* handle, char const* filename );

/**
	�t�@�C���T�C�Y���̃q�[�v���m�ۂ��ēǂݍ���.
	@param handle �n���h��
	@param filename �t�@�C����
	@return �ǂݍ��񂾃q�[�v�i���s�� NULL�j
	@warning �s�v�ɂȂ����q�[�v�� pceHeapAlloc() �ŉ�����邱�ƁB
	@see FileAcc_ReadPosAlloc()
*/
unsigned char* FilePackHandle_ReadAlloc( FilePackHandle* handle, char const* filename );

/**
	��������̃p�b�N�f�[�^����A�w��t�@�C���ւ̃|�C���^���擾.
	�f�R�[�hsrc �� FPK_FindPackData() �Ɠ����B
	@param filename �t�@�C����
	@param source �p�b�N�f�[�^
	@return �w��t�@�C���ւ̃|�C���^�i���s�� NULL�j
*/
unsigned char* FilePack_Data( char const* filename, unsigned char* source );

#endif // !defined( ZURAPCE_FILE_PACK_H )
