/*=======================================================================================================
�T�@���F�^�C�g�����
�쐬���F2015�N/6��/2��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/
#pragma once

#include "UnitBase.h"
#include "Sprite.h"


class Title : public UnitBase
{

	Sprite sprite;
	
public:
	Title();
	~Title();
	HRESULT Load();
	HRESULT Update();
	HRESULT Render();

};