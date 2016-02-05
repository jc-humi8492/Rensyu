/*=======================================================================================================
�T�@���F�v���C���[�̏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#pragma once
#include "Global.h"
#include "Bullet.h" 
#include "Enemy.h"
#include "UnitBase.h"
#include "Sprite.h"
class Player :public UnitBase
{
	//���
	enum STATUS
	{
		STATUS_NORMAL,		//�ʏ�
		STATUS_DEAD,		//����
	}status;				//���݂̏��	

	Bullet bullet[10];
	BOOL isShotKeyFlg;		//���˃{�^������������
	Sprite *sprite;
	

	//private�֐�
	void Move();			//�ړ�����
	void Shot();			//�e�̔���
	void Dead();			//�u���v��Ԃ̎��̏���
	void BulletUpdata();	//�e�̍X�V����

	int deadCount;			//����ł���̎��Ԃ��J�E���g

	int killCount;			//�G�����̓|������

public:
	Player();				//�R���X�g���N�^
	~Player();				//�f�X�g���N�^

	HRESULT Update();								//�X�V
	HRESULT Hit(UnitBase* pTarget);						//�Փ˔���
	HRESULT Render();	//�`�� 
	HRESULT Load();
	
};

