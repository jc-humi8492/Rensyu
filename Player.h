/*=======================================================================================================
概　略：プレイヤーの処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "Bullet.h" 
#include "Enemy.h"
#include "UnitBase.h"
#include "Sprite.h"
class Player :public UnitBase
{
	//状態
	enum STATUS
	{
		STATUS_NORMAL,		//通常
		STATUS_DEAD,		//爆発
	}status;				//現在の状態	

	Bullet bullet[10];
	BOOL isShotKeyFlg;		//発射ボタンを押したか
	Sprite *sprite;
	

	//private関数
	void Move();			//移動処理
	void Shot();			//弾の発射
	void Dead();			//「＊」状態の時の処理
	void BulletUpdata();	//弾の更新処理

	int deadCount;			//死んでからの時間をカウント

	int killCount;			//敵を何体倒したか

public:
	Player();				//コンストラクタ
	~Player();				//デストラクタ

	HRESULT Update();								//更新
	HRESULT Hit(UnitBase* pTarget);						//衝突判定
	HRESULT Render();	//描画 
	HRESULT Load();
	
};

