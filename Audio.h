/*=======================================================================================================
概　略：音を出す処理
作成日：2015年/6月/24日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/
#pragma once
#include "Global.h"
#include <xact3.h>

class Audio

{
	IXACT3Engine* xactEngine;	//音を鳴らす仕組みを作る変数
	IXACT3WaveBank* waveBank;
	void*        mapWaveBank;	//特殊な場所にコピーした場所を覚えておく変数


public:
	//コンストラクタ
	Audio();
	//デストラクタ
	~Audio();

	//音を鳴らす関数
	//引数:なし
	HRESULT InitEngine();
	//音のファイルを読み込む関数
	//引数:ファイル名
	HRESULT LoadWaveBank(char* fileName);

};

