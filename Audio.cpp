/*=======================================================================================================
概　略：音を出す処理
作成日：2015年/6月/24日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#include "Audio.h"

//コンストラクタ
Audio::Audio()
{
}

//デストラクタ
Audio::~Audio()
{
}

//音を鳴らす処理
HRESULT Audio::InitEngine()
{

	//COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//エンジン作成
	if (FAILED(XACT3CreateEngine(0, &xactEngine)))
	{
		MessageBox(0, "XACTエンジンの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}



	//パラメータ設定
	XACT_RUNTIME_PARAMETERS xactParam = { 0 };
	xactParam.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;

	if (FAILED(xactEngine->Initialize(&xactParam)))
	{
		MessageBox(0, "XACTエンジンのパラメータ設定に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//音のファイルを読み込む処理
HRESULT Audio::LoadWaveBank(char* fileName)
{

	//ファイルを開く
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//ファイルサイズを調べる
	DWORD  fileSize = GetFileSize(hFile, NULL);

	//マッピング
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	//ウェーブバンク作成
	if (FAILED(xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank)))
	{
		MessageBox(0, "ウェーブバンク作成に失敗しました", fileName, MB_OK);
		return E_FAIL;
	}

	CloseHandle(hMapFile);
	CloseHandle(hFile);

	return S_OK;

}



