/*=======================================================================================================
�T�@���F�G�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"
class Enemy :public UnitBase
{

	D3DXVECTOR3 move;		//�ړ���
	BOOL isLive;	//�����Ă�t���O(���ꂪFALSE�̂Ƃ��͎���ł���)
	Sprite sprite;	//�R�����g

public:
	Enemy(); //�R���X�g���N�^
	~Enemy(); //�f�X�g���N�^

	HRESULT Update(); //�X�V
	HRESULT Render(); //�`��
	HRESULT Load();
	void Kill();
};
