/*=======================================================================================================
概　略：ゲーム全体の流れを扱う処理
作成日：2015年/5月/27日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

//---------------インクルード-----------------------
#include "Game.h"
#include "TitleScene.h"
#include "PlayScene.h"

//----------------グローバル変数----------------
GAME_SCENE g_gameScene;		//現在のゲームシーン
LPDIRECT3DDEVICE9  g_pDevice;      //Direct3Dデバイスオブジェクト
Input*          g_pInput;    //入力処理オブジェクト

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Game::Game()
{
	//各シーンオブジェクトの生成
	scene[SC_TITLE] = new TitleScene;		//タイトルシーン
	scene[SC_PLAY] = new PlayScene;		//プレイシーン

	//最初はタイトルシーン
	g_gameScene = SC_TITLE;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Game::~Game()
{
	for (int i = 0; i < SC_MAX; i++)
	{
		delete scene[i];
	}

	//Direct3D解放
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(pD3d);

}


//――――――――――――――――――――――

// Direct3D初期化

//――――――――――――――――――――――

HRESULT Game::InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{

		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);

		return E_FAIL;

	}

	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;				//Direct3Dのいろいろな設定を渡す構造体
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//初期化
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;						//TRUE:ウィンドウモード FALSE:フルスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE;		//TRUE:zバッファを使う FALSE:使わない
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))	//g_pDeviceがディスプレイのこと
	{
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);

		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))
		{

			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;

		}

	}
	return S_OK;

}



//――――――――――――――――――――――
//	衝突判定
//――――――――――――――――――――――
HRESULT Game::Hit()
{
	scene[g_gameScene]->Hit();
	return S_OK;
}

//――――――――――――――――――――――
//	更新処理
//――――――――――――――――――――――
HRESULT Game::Update()
{
	g_pInput->Update();

	scene[g_gameScene]->Update();
	return S_OK;
}

//――――――――――――――――――――――
//	描画処理
//――――――――――――――――――――――
HRESULT Game::Render()
{

	//画面をクリア
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pDevice->BeginScene()))
	{
		//ゲーム画面の描画
		scene[g_gameScene]->Render();

		//描画終了
		g_pDevice->EndScene();
	}

	//フリップ
	g_pDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;

}

//――――――――――――――――――――――
// 読み込み処理
//――――――――――――――――――――――

HRESULT Game::Load()
{
	//全シーンのLoad関数を呼ぶ
	for (int i=0; i < SC_MAX; i++)
	if (FAILED(scene[i]->Load()))
	{
		return E_FAIL;
	}
	return S_OK;
}
