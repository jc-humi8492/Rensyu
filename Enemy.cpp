/*=======================================================================================================
概　略：敵の処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/
#include "Enemy.h"


Enemy::Enemy()
{
	//初期位置
	position.x = rand() % WINDOW_WIDTH - 16; //ランダム
	position.y = 0;

	move.x = rand() % 7 - 3;
	move.y = rand() % 4;

	isLive = TRUE;
}


Enemy::~Enemy()
{
}

HRESULT Enemy::Load()
{
	if (FAILED(sprite.Load("画像\\enemy.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}

//更新
HRESULT Enemy::Update()
{
	if (isLive)
	{

		//移動
		position.x += move.x;
		position.y += move.y;

		//画面左端
		if (position.x <= 1)
			move.x *= -1; //跳ね返る

		//画面右端
		if (position.x >= WINDOW_WIDTH - 16)
			move.x *= -1; //跳ね返る


		//画面下
		if (position.y >= WINDOW_HEIGHT)
			position.y = 0; //上に移動 
	}
	return S_OK;
}


//描画
HRESULT Enemy::Render()
{
	if (isLive)
	{
		SpriteData data;
		data.pos = position;
		sprite.Draw(&data);
	}
	return S_OK;
	
}


void Enemy::Kill()
{
	isLive = FALSE;
	position.y = -999;

}

