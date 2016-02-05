/*=======================================================================================================
概　略：タイトル画面
作成日：2015年/6月/2日
更新日：
制作者：佐々木　郁哉
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