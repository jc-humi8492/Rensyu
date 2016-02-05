/*=======================================================================================================
�T�@���F�����o������
�쐬���F2015�N/6��/24��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/
#pragma once
#include "Global.h"
#include <xact3.h>

class Audio

{
	IXACT3Engine* xactEngine;	//����炷�d�g�݂����ϐ�
	IXACT3WaveBank* waveBank;
	void*        mapWaveBank;	//����ȏꏊ�ɃR�s�[�����ꏊ���o���Ă����ϐ�


public:
	//�R���X�g���N�^
	Audio();
	//�f�X�g���N�^
	~Audio();

	//����炷�֐�
	//����:�Ȃ�
	HRESULT InitEngine();
	//���̃t�@�C����ǂݍ��ފ֐�
	//����:�t�@�C����
	HRESULT LoadWaveBank(char* fileName);

};

