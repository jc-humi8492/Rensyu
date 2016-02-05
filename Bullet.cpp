/*=======================================================================================================
�T�@���F�v���C���[����ł�e�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#include "Bullet.h"


Bullet::Bullet()
{
	isShot = FALSE;
	sprite = 0;
}


Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

HRESULT Bullet::Load()
{
	sprite = new Sprite;
	if (FAILED(sprite->Load("�摜\\bullet.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}
void Bullet::Update()
{
	position.y -= 15;

	if (position.y <= -16)
	{
		isShot = FALSE;
	}
	
}

void Bullet::Render()
{
	if (isShot == TRUE)
	{
		SpriteData data;
		data.pos = position;
		sprite->Draw(&data);
	}

}


BOOL Bullet::Hit(Enemy* pEnemy)
{
	D3DXVECTOR3 enemyPosition = pEnemy->GetPos();
	if (isShot == TRUE)
	{
		int dist = (position.x - enemyPosition.x) * (position.x - enemyPosition.x) +
			(position.y - enemyPosition.y) * (position.y - enemyPosition.y);
		if (dist <= 16 * 16)
		{
			isShot = FALSE;
			pEnemy->Kill();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Bullet::Shot(D3DXVECTOR3 playerPos)
{
	//�����˂������ꍇ
	if (isShot == FALSE)
	{
		//���ˏ�Ԃɂ���
		isShot = TRUE;

		//�ʒu���v���C���[�̈ʒu�̏�����ɂ���
		position.x = playerPos.x;
		position.y = playerPos.y - 5;

		return TRUE;
	}
	return FALSE;
}
