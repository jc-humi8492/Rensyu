/*=======================================================================================================
概　略：プレイヤーからでる弾の処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Enemy.h"

class Bullet
{
	D3DXVECTOR3 position;
	BOOL  isShot;				 //未発射：FALSE 発射後：TRUE 
	Sprite *sprite;

public:
	Bullet();
	~Bullet();

	void Update();
	BOOL Hit(Enemy* pEnemy);
	void Render();
	HRESULT Load();
	BOOL  Shot(D3DXVECTOR3 playerPos); //戻り値は発射できた場合 TRUE 
};

