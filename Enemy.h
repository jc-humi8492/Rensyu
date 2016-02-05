/*=======================================================================================================
概　略：敵の処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"
class Enemy :public UnitBase
{

	D3DXVECTOR3 move;		//移動量
	BOOL isLive;	//生きてるフラグ(これがFALSEのときは死んでいる)
	Sprite sprite;	//コメント

public:
	Enemy(); //コンストラクタ
	~Enemy(); //デストラクタ

	HRESULT Update(); //更新
	HRESULT Render(); //描画
	HRESULT Load();
	void Kill();
};
