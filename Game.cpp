/*=======================================================================================================
�T�@���F�Q�[���S�̗̂������������
�쐬���F2015�N/5��/27��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Game.h"
#include "TitleScene.h"
#include "PlayScene.h"

//----------------�O���[�o���ϐ�----------------
GAME_SCENE g_gameScene;		//���݂̃Q�[���V�[��
LPDIRECT3DDEVICE9  g_pDevice;      //Direct3D�f�o�C�X�I�u�W�F�N�g
Input*          g_pInput;    //���͏����I�u�W�F�N�g

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::Game()
{
	//�e�V�[���I�u�W�F�N�g�̐���
	scene[SC_TITLE] = new TitleScene;		//�^�C�g���V�[��
	scene[SC_PLAY] = new PlayScene;		//�v���C�V�[��

	//�ŏ��̓^�C�g���V�[��
	g_gameScene = SC_TITLE;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::~Game()
{
	for (int i = 0; i < SC_MAX; i++)
	{
		delete scene[i];
	}

	//Direct3D���
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(pD3d);

}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

// Direct3D������

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

HRESULT Game::InitD3d(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{

		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);

		return E_FAIL;

	}

	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;				//Direct3D�̂��낢��Ȑݒ��n���\����
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//������
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;						//TRUE:�E�B���h�E���[�h FALSE:�t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE;		//TRUE:z�o�b�t�@���g�� FALSE:�g��Ȃ�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))	//g_pDevice���f�B�X�v���C�̂���
	{
		MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);

		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))
		{

			MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
			return E_FAIL;

		}

	}
	return S_OK;

}



//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�Փ˔���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Hit()
{
	scene[g_gameScene]->Hit();
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�X�V����
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Update()
{
	g_pInput->Update();

	scene[g_gameScene]->Update();
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�`�揈��
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Render()
{

	//��ʂ��N���A
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pDevice->BeginScene()))
	{
		//�Q�[����ʂ̕`��
		scene[g_gameScene]->Render();

		//�`��I��
		g_pDevice->EndScene();
	}

	//�t���b�v
	g_pDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;

}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �ǂݍ��ݏ���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

HRESULT Game::Load()
{
	//�S�V�[����Load�֐����Ă�
	for (int i=0; i < SC_MAX; i++)
	if (FAILED(scene[i]->Load()))
	{
		return E_FAIL;
	}
	return S_OK;
}
