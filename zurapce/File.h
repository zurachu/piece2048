#if !defined( ZURAPCE_FILE_H )
#define ZURAPCE_FILE_H

/** @file
	�t�@�C�� �֘A.
	@author zurachu
*/

#include <piece.h> // FILEACC

/**
	�t�@�C���̈ꕔ����ǂݍ���Ńo�b�t�@�Ɋi�[.
	@param dst �o�͐�o�b�t�@
	@param file_acc �J���ꂽ�t�@�C��
	@param pos �ǂݍ��݊J�n�ʒu
	@param size �ǂݍ��݃T�C�Y�iINVALIDVAL �ōŌ�܂œǂݍ��ށj
	@return �ǂݍ��݃T�C�Y�i���s���O�j
*/
int FileAcc_ReadPosTo( unsigned char* dst, FILEACC* file_acc, int pos, int size );

/**
	�t�@�C���̈ꕔ�����T�C�Y���̃q�[�v���m�ۂ��ēǂݍ���.
	@param file_acc �J���ꂽ�t�@�C��
	@param pos �ǂݍ��݊J�n�ʒu
	@param size �ǂݍ��݃T�C�Y�iINVALIDVAL �ōŌ�܂œǂݍ��ށj
	@return �ǂݍ��񂾃q�[�v�i���s�� NULL�j
	@warning �s�v�ɂȂ����q�[�v�� pceHeapAlloc() �ŉ�����邱�ƁB
*/
unsigned char* FileAcc_ReadPosAlloc( FILEACC* file_acc, int pos, int size );

/**
	�t�@�C����ǂݍ���Ńo�b�t�@�Ɋi�[.
	FileAcc_ReadPosTo( dst, file_acc, 0, INVALIDVAL ) �Ɠ����B
	@param dst �o�͐�o�b�t�@
	@param file_acc �J���ꂽ�t�@�C��
	@return �ǂݍ��݃T�C�Y�i���s���O�j
	@see FileAcc_ReadPosTo()
*/
int FileAcc_ReadTo( unsigned char* dst, FILEACC* file_acc );

/**
	�t�@�C���T�C�Y���̃q�[�v���m�ۂ��ēǂݍ���.
	FileAcc_ReadPosAlloc( file_acc, 0, INVALIDVAL ) �Ɠ����B
	@param file_acc �J���ꂽ�t�@�C��
	@return �ǂݍ��񂾃q�[�v�i���s�� NULL�j
	@warning �s�v�ɂȂ����q�[�v�� pceHeapAlloc() �ŉ�����邱�ƁB
	@see FileAcc_ReadPosAlloc()
*/
unsigned char* FileAcc_ReadAlloc( FILEACC* file_acc );

/**
	�t�@�C����ǂݍ���Ńo�b�t�@�Ɋi�[.
	@param dst �o�͐�o�b�t�@
	@param filename �t�@�C����
	@return �ǂݍ��݃T�C�Y�i���s���O�j
	@see FileAcc_ReadTo()
*/
int File_ReadTo( unsigned char* dst, char const* filename );

/**
	�t�@�C���T�C�Y���̃q�[�v���m�ۂ��ēǂݍ���.
	@param filename �t�@�C����
	@return �ǂݍ��񂾃q�[�v�i���s�� NULL�j
	@warning �s�v�ɂȂ����q�[�v�� pceHeapAlloc() �ŉ�����邱�ƁB
	@see FileAcc_ReadAlloc()
*/
unsigned char* File_ReadAlloc( char const* filename );

#endif // !defined( ZURAPCE_FILE_H )
