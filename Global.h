/*===========================================================================================
概　略：プロジェクト全体で必要なものをまとめたファイル
作成日：2015年/5月/27日
更新日：
制作者：佐々木　郁哉
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include <windows.h>
#include <d3dx9.h>
#include "Input.h"

//-------------------マクロ------------------
#define SAFE_DELETE(p)     {delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) {delete[] (p);  (p) = NULL;}
#define SAFE_RELEASE(p)      { if(p != NULL) { (p)->Release(); (p) = NULL; } }

//----------ライブラリファイルのロード--------------
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//-------------------定数宣言------------------
//ウィンドウサイズ
#define WINDOW_WIDTH	800	//ウィンドウの幅
#define WINDOW_HEIGHT	600		//ウィンドウ高さ

//---------------------------------------
#define PlayerSpeed 5	//プレイヤーの速度
#define FirstPositionX 180  //プレイヤー位置Xの初期位置
#define FirstPositionY 250  //プレイヤー位置Yの初期位置




//-------------------グローバル変数------------------

//シーン
enum GAME_SCENE
{
	SC_TITLE,	//タイトルシーン
	SC_PLAY,	//プレイシーン
	SC_CLEAR,	//クリアシーン
	SC_MAX,
};
extern GAME_SCENE	g_gameScene;		//実態はGame.cppで宣言

//Direct3Dデバイスオブジェクト
extern LPDIRECT3DDEVICE9 g_pDevice;

//入力処理オブジェクト
extern Input* g_pInput;