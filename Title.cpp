/*=======================================================================================================
�T�@���F�^�C�g�����
�쐬���F2015�N/6��/2��
�X�V���F
����ҁF���X�؁@���
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
	
	if (FAILED(sprite.Load("�摜\\title.bmp")))
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
