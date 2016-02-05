/*===========================================================================================
概　略：各シーンの親クラス
作成日：2015年/5月/27日
更新日：
制作者：佐々木　郁哉
=============================================================================================*/

//---------------インクルード-----------------------
#include "SceneBase.h"


//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
SceneBase::~SceneBase()
{
	//登場したユニットを全て開放
	for (WORD i = 0; i < unit.size(); i++)
	{
		delete unit[i];
	}
}

//――――――――――――――――――――――
//	衝突判定
//――――――――――――――――――――――
HRESULT SceneBase::Hit()
{
	//全ユニットの総当り
	for (WORD i = 0; i < unit.size(); i++)
	{
		for (WORD j = 0; j < unit.size(); j++)
		{
			//自分同士はパス
			if (i == j)
			{
				continue;
			}

			//ユニット同士の衝突判定
			unit[i]->Hit(unit[j]);
		}
	}
	return S_OK;
}

//――――――――――――――――――――――
//	更新処理
//――――――――――――――――――――――
HRESULT SceneBase::Update()
{
	//全ユニットを処理する
	for (WORD i = 0; i < unit.size(); i++)
	{
		unit[i]->Update();
		
	}
	return S_OK;
}

//――――――――――――――――――――――
//	描画処理
//――――――――――――――――――――――
HRESULT SceneBase::Render()
{
	//全ユニットを処理する
	for (WORD i = 0; i < unit.size(); i++)
	{
		unit[i]->Render();
	}
	return S_OK;
}

//――――――――――――――――――――――
// 読み込み処理
//――――――――――――――――――――――

HRESULT SceneBase::Load()
{

	//全ユニットを処理する
	for (WORD i = 0; i < unit.size(); i++)
	{
		if (FAILED(unit[i]->Load()))
		{
			return E_FAIL;
		}
	}
	return S_OK;

}
