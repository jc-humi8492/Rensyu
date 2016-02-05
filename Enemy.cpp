/*=======================================================================================================
�T�@���F�G�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/
#include "Enemy.h"


Enemy::Enemy()
{
	//�����ʒu
	position.x = rand() % WINDOW_WIDTH - 16; //�����_��
	position.y = 0;

	move.x = rand() % 7 - 3;
	move.y = rand() % 4;

	isLive = TRUE;
}


Enemy::~Enemy()
{
}

HRESULT Enemy::Load()
{
	if (FAILED(sprite.Load("�摜\\enemy.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}

//�X�V
HRESULT Enemy::Update()
{
	if (isLive)
	{

		//�ړ�
		position.x += move.x;
		position.y += move.y;

		//��ʍ��[
		if (position.x <= 1)
			move.x *= -1; //���˕Ԃ�

		//��ʉE�[
		if (position.x >= WINDOW_WIDTH - 16)
			move.x *= -1; //���˕Ԃ�


		//��ʉ�
		if (position.y >= WINDOW_HEIGHT)
			position.y = 0; //��Ɉړ� 
	}
	return S_OK;
}


//�`��
HRESULT Enemy::Render()
{
	if (isLive)
	{
		SpriteData data;
		data.pos = position;
		sprite.Draw(&data);
	}
	return S_OK;
	
}


void Enemy::Kill()
{
	isLive = FALSE;
	position.y = -999;

}

