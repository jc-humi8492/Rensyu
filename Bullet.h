/*=======================================================================================================
�T�@���F�v���C���[����ł�e�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Enemy.h"

class Bullet
{
	D3DXVECTOR3 position;
	BOOL  isShot;				 //�����ˁFFALSE ���ˌ�FTRUE 
	Sprite *sprite;

public:
	Bullet();
	~Bullet();

	void Update();
	BOOL Hit(Enemy* pEnemy);
	void Render();
	HRESULT Load();
	BOOL  Shot(D3DXVECTOR3 playerPos); //�߂�l�͔��˂ł����ꍇ TRUE 
};

