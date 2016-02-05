/*===========================================================================================
概　略：ゲーム全体の流れを扱う処理
作成日：2015年/5月/27日
更新日：
制作者：佐々木　郁哉
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "Global.h"
#include "SceneBase.h"


//―――――――――――――――――――――
//	ゲームクラス
//―――――――――――――――――――――
class Game
{
	//Direct3Dオブジェクト
	LPDIRECT3D9 pD3d;

	//シーンオブジェクト
	SceneBase* scene[SC_MAX];


public:
	//コンストラクタ
	Game();

	//デストラクタ
	~Game();

	//DirectX初期化
	HRESULT InitD3d(HWND);

	//読み込み処理
	HRESULT Load();

	//衝突判定処理
	HRESULT Hit();

	//更新処理
	HRESULT Update();

	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	HRESULT Render();


};

