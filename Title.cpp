/*=======================================================================================================
概　略：タイトル画面
作成日：2015年/6月/2日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/
#include "Title.h"


Title::Title()
{
	
}


Title::~Title()
{
	
}

HRESULT Title::Load()
{
	
	if (FAILED(sprite.Load("画像\\title.bmp")))
	{
		return E_FAIL;
	}
	return S_OK;
}


HRESULT Title::Update()
{

	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		g_gameScene = SC_PLAY;
	}

	return S_OK;
}



HRESULT Title::Render()
{
	SpriteData data;
	sprite.Draw(&data);
	return S_OK;
}
