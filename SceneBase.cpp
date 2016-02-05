/*===========================================================================================
�T�@���F�e�V�[���̐e�N���X
�쐬���F2015�N/5��/27��
�X�V���F
����ҁF���X�؁@���
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "SceneBase.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
SceneBase::~SceneBase()
{
	//�o�ꂵ�����j�b�g��S�ĊJ��
	for (WORD i = 0; i < unit.size(); i++)
	{
		delete unit[i];
	}
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�Փ˔���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT SceneBase::Hit()
{
	//�S���j�b�g�̑�����
	for (WORD i = 0; i < unit.size(); i++)
	{
		for (WORD j = 0; j < unit.size(); j++)
		{
			//�������m�̓p�X
			if (i == j)
			{
				continue;
			}

			//���j�b�g���m�̏Փ˔���
			unit[i]->Hit(unit[j]);
		}
	}
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�X�V����
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT SceneBase::Update()
{
	//�S���j�b�g����������
	for (WORD i = 0; i < unit.size(); i++)
	{
		unit[i]->Update();
		
	}
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�`�揈��
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT SceneBase::Render()
{
	//�S���j�b�g����������
	for (WORD i = 0; i < unit.size(); i++)
	{
		unit[i]->Render();
	}
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �ǂݍ��ݏ���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

HRESULT SceneBase::Load()
{

	//�S���j�b�g����������
	for (WORD i = 0; i < unit.size(); i++)
	{
		if (FAILED(unit[i]->Load()))
		{
			return E_FAIL;
		}
	}
	return S_OK;

}