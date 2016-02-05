/*=======================================================================================================
概　略：プレイヤーからでる弾の処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#pragma once
#include "Player.h"

Player::Player()
{
	//初期位置
	position.x = FirstPositionX;
	position.y = FirstPositionY;
	status = STATUS_NORMAL;
	killCount = 0;
	sprite = 0;
	
}


Player::~Player()
{
	SAFE_DELETE(sprite);
}

HRESULT Player::Load()
{
	if (FAILED(sprite->Load("画像\\player.png")))
	{
		return E_FAIL;
	}
	return S_OK;

	for (int i = 0; i < 10; i++)
	{
		bullet[i].Load();
	}

}

//更新
HRESULT Player::Update()
{
	switch (status)
	{
		//通常状態
	case STATUS_NORMAL:
		Move();
		Shot();
		break;

		//被ダメージ状態
	case STATUS_DEAD:
		Dead();
		break;
	}
	//弾の更新
	BulletUpdata();
	return S_OK;
}



//衝突判定
HRESULT Player::Hit(UnitBase* pTarget)

{
	//引数が敵だったら
	if (typeid(*pTarget) == typeid(Enemy))
	{
		D3DXVECTOR3 enemyPosition = pTarget->GetPos(); //敵の現在の位置
		int distance =
			(position.x - enemyPosition.x) * (position.x - enemyPosition.x) + (position.y - enemyPosition.y) * (position.y - enemyPosition.y);

		if (distance <= (16 * 16))
		{
			status = STATUS_DEAD;
			deadCount = 0;
		}

		for (int i = 0; i < 5; i++)
		{
			BOOL b = bullet[i].Hit((Enemy*)pTarget);

			//当たったらカウントアップ
			if (b == TRUE)
			{
				killCount++;
			}

			if (killCount >= 5)
			{
				g_gameScene = SC_CLEAR;
			}
		}

	}
	return S_OK;
}

//描画
HRESULT Player::Render()
{
	SpriteData data;


	switch (status)
	{
	case STATUS_NORMAL:
		sprite->Draw(&data);

		break;

	case STATUS_DEAD:

		break;
	}
	for (int i = 0; i < 10; i++)
	{
		bullet[i].Render();
	}

	return S_OK;
}

//移動
void Player::Move()
{
	//右移動
	if (g_pInput->IsKeyPush(DIK_RIGHT))
	{
		position.x += PlayerSpeed;
	}

	//左移動
	if (g_pInput->IsKeyPush(DIK_LEFT))
	{
		position.x -= PlayerSpeed;
	}

	//上移動
	if (g_pInput->IsKeyPush(DIK_UP))
	{
		position.y -= PlayerSpeed;
	}

	//下移動
	if (g_pInput->IsKeyPush(DIK_DOWN))
	{
		position.y += PlayerSpeed;
	}

}

//弾を撃つ
void Player::Shot()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (isShotKeyFlg == FALSE)
		{

			for (int i = 0; i < 10; i++)
			{
				BOOL b;
				b = bullet[i].Shot(position);

				//発射できた
				if (b == TRUE)
				{
					bullet->Load();
					break; //ループやめる
				}
			}
			isShotKeyFlg = TRUE;
		}
	}
	else
	{
		isShotKeyFlg = FALSE;
	}
	
}

//「*」状態の時の処理
void Player::Dead()
{

	deadCount++;
	if (deadCount >= 60)
	{
		status = STATUS_NORMAL;
	}

}

//弾の更新
void Player::BulletUpdata()
{
	for (int i = 0; i < 10; i++)
	{
		bullet[i].Update();
	}

}


