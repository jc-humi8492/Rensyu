/*=======================================================================================================
�T�@���F���͏���
�쐬���F2015�N/6��/15��
�X�V���F
����ҁF���X�؁@���
=======================================================================================================*/

#include "Input.h"


Input::Input()
{
	ZeroMemory(keyState, sizeof(keyState));
}


Input::~Input()
{
	//�L�[�{�[�h�̃A�N�Z�X�������
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}

	//DirectInput���
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(pDinput);

}



HRESULT Input::Init(HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̍쐬 
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return E_FAIL;
	}
	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))

	{
		return E_FAIL;
	}
	// �������x���̐ݒ�
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))

	{
		return E_FAIL;
	}

	return S_OK;

}

HRESULT  Input::Update()
{
	//�O��̃R���g���[���[�̏�Ԃ��m��
	for (int i = 0; i < 4; i++)
	{
		memcpy(&prevControllerState[i], &controllerState[i], sizeof(controllerState[i]));
	}


	//�R���g���[���[�̏�Ԃ��擾
	//����:�R���g���[���[�̔ԍ�
	//����:�R���g���[���[�̏��
	for (int i = 0; i < 4; i++)
	{
		XInputGetState(i, &controllerState[i]);
	}



	// �f�o�C�X�̃A�N�Z�X�����擾����
	HRESULT hr = pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		

		//prevKeystate�ɑO��̃L�[��������
		memcpy(prevKeyState, keyState, sizeof(keyState));

		//�S�ẴL�[�̏�Ԃ��擾
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		return S_OK;
	}
	return E_FAIL;
}

BOOL Input::IsKeyPush(DWORD keyCode)

{
	if (keyState[keyCode] & 0x80)
	{
		return TRUE; //�����Ă���
	}
	return FALSE;      //�����ĂȂ�
}

//�L�[�������ꂽ�u�Ԃ��`�F�b�N
BOOL Input::IsKeyTap(DWORD  keyCode)
{
	if (!(prevKeyState[keyCode] & 0x80) && keyState[keyCode] & 0x80)
	{
		return TRUE; //�������u��
	}
	return FALSE;      //���̑�
}

//�C�ӂ̃L�[�������ꂽ�u�Ԃ��`�F�b�N
BOOL Input::IsKeyRelease(DWORD keyCode)
{
	if ((prevKeyState[keyCode]&0x80)&&!(keyState[keyCode]&0x80))
	{
		return TRUE;	//�����Ă���
	}
	return FALSE;

}


//�C�ӂ̃R���g���[���[�̃{�^���������Ă��邩�`�F�b�N
BOOL Input::IsPadButtonPush(DWORD buttonCode, int ID)
{

	if (controllerState[ID].Gamepad.wButtons&buttonCode)
	{
		return TRUE; //�����Ă�
	}

	return FALSE;   //�����ĂȂ�

}

//�C�ӂ̃R���g���[���[�̃{�^�����������u�Ԃ��`�F�b�N
BOOL Input::IsPadButtonTap(DWORD buttonCode,int ID)
{

	if (!(prevControllerState[ID].Gamepad.wButtons&buttonCode) && controllerState[ID].Gamepad.wButtons&buttonCode)
	{
		return TRUE; //�����Ă�
	}

	return FALSE;   //�����ĂȂ�

}

//�R���g���[���[�̃{�^���𗣂����u�Ԃ�
BOOL  Input::IsPadButtonRelease(DWORD buttonCode,int ID)
{
	if ((prevControllerState[ID].Gamepad.wButtons&buttonCode) && !(controllerState[ID].Gamepad.wButtons&buttonCode))
	{
		return TRUE;	//�����Ă�
	}
	return FALSE;	//�����ĂȂ�

}

//�����X�e�B�b�N(���E)���ǂ炭�炢�X���Ă��邩
float Input::GetPadLStickX(int ID)
{

	float value = controllerState[ID].Gamepad.sThumbLX;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value/32767;

}

//�����X�e�B�b�N(�㉺)���ǂꂭ�炢�X���Ă��邩
float Input::GetPadLStickY(int ID)
{
	float value = controllerState[ID].Gamepad.sThumbLY;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;


}


//���E�X�e�B�b�N(���E)���ǂꂭ�炢�X���Ă��邩
float Input::GetPadRStickX(int ID)
{
	float value = controllerState[ID].Gamepad.sThumbRX;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;


}

//���E�X�e�B�b�N(�㉺)���ǂꂭ�炢�X���Ă��邩
float Input::GetPadRStickY(int ID)
{

	float value = controllerState[ID].Gamepad.sThumbRY;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;

}

//�����g���K�[���������܂�Ă��邩
float Input::GetPadLTrigger(int ID)
{

	float value = controllerState[ID].Gamepad.bLeftTrigger;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;
	}

	return value / 255;

}

float Input::GetPadRTrigger(int ID)                  //�E�g���K�[�̉�������
{

	float value = controllerState[ID].Gamepad.bRightTrigger;

	//�f�b�h�]�[��(�X��20%�����͓����Ȃ�)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;
	}

	return value / 255;

}

void Input::Vibration(float leftSpeed, float rightSpeed,int ID)                   //�U���G�t�F�N�g
{

	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftSpeed *65535; // �����[�^�[
	vibration.wRightMotorSpeed = rightSpeed *65535; // �E���[�^�[
	XInputSetState(0, &vibration);


}




