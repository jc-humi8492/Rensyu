/*===========================================================================================
�T�@���F�e�Q�[�����j�b�g�̐e�N���X
�쐬���F2015�N/5��/27��
�X�V���F
����ҁF���X�؁@���
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "Global.h"
#include <typeinfo.h>
#define UNIT_SIZE	16		//���j�b�g�̑傫��


class UnitBase
{
protected:
	//���j�b�g�̈ʒu
	D3DXVECTOR3	position;

public:
	//�f�X�g���N�^
	virtual ~UnitBase() { };
	//�X�V//�ǂݍ��ݏ���
	virtual HRESULT Load();
	//�X�V����
	virtual HRESULT Update();

	//�Փ˔��菈��
	//�����FpTarget	���肷�鑊�胆�j�b�g
	virtual HRESULT Hit(UnitBase* pTarget);

	//�`�揈��
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	virtual HRESULT Render();

	//���݂̈ʒu���擾
	//�ߒl�F���݂̈ʒu
	D3DXVECTOR3  GetPos()	{ return position; }
};

