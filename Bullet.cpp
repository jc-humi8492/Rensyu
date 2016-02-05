/*=======================================================================================================
概　略：プレイヤーからでる弾の処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#include "Bullet.h"


Bullet::Bullet()
{
	isShot = FALSE;
	sprite = 0;
}


Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

HRESULT Bullet::Load()
{
	sprite = new Sprite;
	if (FAILED(sprite->Load("画像\\bullet.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}
void Bullet::Update()
{
	position.y -= 15;

	if (position.y <= -16)
	{
		isShot = FALSE;
	}
	
}

void Bullet::Render()
{
	if (isShot == TRUE)
	{
		SpriteData data;
		data.pos = position;
		sprite->Draw(&data);
	}

}


BOOL Bullet::Hit(Enemy* pEnemy)
{
	D3DXVECTOR3 enemyPosition = pEnemy->GetPos();
	if (isShot == TRUE)
	{
		int dist = (position.x - enemyPosition.x) * (position.x - enemyPosition.x) +
			(position.y - enemyPosition.y) * (position.y - enemyPosition.y);
		if (dist <= 16 * 16)
		{
			isShot = FALSE;
			pEnemy->Kill();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Bullet::Shot(D3DXVECTOR3 playerPos)
{
	//未発射だった場合
	if (isShot == FALSE)
	{
		//発射状態にする
		isShot = TRUE;

		//位置をプレイヤーの位置の少し上にする
		position.x = playerPos.x;
		position.y = playerPos.y - 5;

		return TRUE;
	}
	return FALSE;
}
