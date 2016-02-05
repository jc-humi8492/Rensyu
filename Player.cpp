/*=======================================================================================================
�T�@���F�v���C���[����ł�e�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#pragma once
#include "Player.h"

Player::Player()
{
	//�����ʒu
	position.x = FirstPositionX;
	position.y = FirstPositionY;
	status = STATUS_NORMAL;
	killCount = 0;
	sprite = 0;
	
}


Player::~Player()
{
	SAFE_DELETE(sprite);
}

HRESULT Player::Load()
{
	if (FAILED(sprite->Load("�摜\\player.png")))
	{
		return E_FAIL;
	}
	return S_OK;

	for (int i = 0; i < 10; i++)
	{
		bullet[i].Load();
	}

}

//�X�V
HRESULT Player::Update()
{
	switch (status)
	{
		//�ʏ���
	case STATUS_NORMAL:
		Move();
		Shot();
		break;

		//��_���[�W���
	case STATUS_DEAD:
		Dead();
		break;
	}
	//�e�̍X�V
	BulletUpdata();
	return S_OK;
}



//�Փ˔���
HRESULT Player::Hit(UnitBase* pTarget)

{
	//�������G��������
	if (typeid(*pTarget) == typeid(Enemy))
	{
		D3DXVECTOR3 enemyPosition = pTarget->GetPos(); //�G�̌��݂̈ʒu
		int distance =
			(position.x - enemyPosition.x) * (position.x - enemyPosition.x) + (position.y - enemyPosition.y) * (position.y - enemyPosition.y);

		if (distance <= (16 * 16))
		{
			status = STATUS_DEAD;
			deadCount = 0;
		}

		for (int i = 0; i < 5; i++)
		{
			BOOL b = bullet[i].Hit((Enemy*)pTarget);

			//����������J�E���g�A�b�v
			if (b == TRUE)
			{
				killCount++;
			}

			if (killCount >= 5)
			{
				g_gameScene = SC_CLEAR;
			}
		}

	}
	return S_OK;
}

//�`��
HRESULT Player::Render()
{
	SpriteData data;


	switch (status)
	{
	case STATUS_NORMAL:
		sprite->Draw(&data);

		break;

	case STATUS_DEAD:

		break;
	}
	for (int i = 0; i < 10; i++)
	{
		bullet[i].Render();
	}

	return S_OK;
}

//�ړ�
void Player::Move()
{
	//�E�ړ�
	if (g_pInput->IsKeyPush(DIK_RIGHT))
	{
		position.x += PlayerSpeed;
	}

	//���ړ�
	if (g_pInput->IsKeyPush(DIK_LEFT))
	{
		position.x -= PlayerSpeed;
	}

	//��ړ�
	if (g_pInput->IsKeyPush(DIK_UP))
	{
		position.y -= PlayerSpeed;
	}

	//���ړ�
	if (g_pInput->IsKeyPush(DIK_DOWN))
	{
		position.y += PlayerSpeed;
	}

}

//�e������
void Player::Shot()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (isShotKeyFlg == FALSE)
		{

			for (int i = 0; i < 10; i++)
			{
				BOOL b;
				b = bullet[i].Shot(position);

				//���˂ł���
				if (b == TRUE)
				{
					bullet->Load();
					break; //���[�v��߂�
				}
			}
			isShotKeyFlg = TRUE;
		}
	}
	else
	{
		isShotKeyFlg = FALSE;
	}
	
}

//�u*�v��Ԃ̎��̏���
void Player::Dead()
{

	deadCount++;
	if (deadCount >= 60)
	{
		status = STATUS_NORMAL;
	}

}

//�e�̍X�V
void Player::BulletUpdata()
{
	for (int i = 0; i < 10; i++)
	{
		bullet[i].Update();
	}

}


