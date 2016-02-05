/*=======================================================================================================
�T�@���F�����o������
�쐬���F2015�N/6��/24��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#include "Audio.h"

//�R���X�g���N�^
Audio::Audio()
{
}

//�f�X�g���N�^
Audio::~Audio()
{
}

//����炷����
HRESULT Audio::InitEngine()
{

	//COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//�G���W���쐬
	if (FAILED(XACT3CreateEngine(0, &xactEngine)))
	{
		MessageBox(0, "XACT�G���W���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}



	//�p�����[�^�ݒ�
	XACT_RUNTIME_PARAMETERS xactParam = { 0 };
	xactParam.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;

	if (FAILED(xactEngine->Initialize(&xactParam)))
	{
		MessageBox(0, "XACT�G���W���̃p�����[�^�ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//���̃t�@�C����ǂݍ��ޏ���
HRESULT Audio::LoadWaveBank(char* fileName)
{

	//�t�@�C�����J��
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//�t�@�C���T�C�Y�𒲂ׂ�
	DWORD  fileSize = GetFileSize(hFile, NULL);

	//�}�b�s���O
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	//�E�F�[�u�o���N�쐬
	if (FAILED(xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank)))
	{
		MessageBox(0, "�E�F�[�u�o���N�쐬�Ɏ��s���܂���", fileName, MB_OK);
		return E_FAIL;
	}

	CloseHandle(hMapFile);
	CloseHandle(hFile);

	return S_OK;

}



