/*=======================================================================================================
概　略：入力処理
作成日：2015年/6月/15日
更新日：
制作者：佐々木　郁哉
=======================================================================================================*/

#include "Input.h"


Input::Input()
{
	ZeroMemory(keyState, sizeof(keyState));
}


Input::~Input()
{
	//キーボードのアクセス権を解放
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}

	//DirectInput解放
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(pDinput);

}



HRESULT Input::Init(HWND hWnd)
{
	//DirectInputオブジェクトの作成 
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return E_FAIL;
	}
	// 「DirectInputデバイス」オブジェクトの作成
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;
	}
	// デバイスをキーボードに設定
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))

	{
		return E_FAIL;
	}
	// 協調レベルの設定
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))

	{
		return E_FAIL;
	}

	return S_OK;

}

HRESULT  Input::Update()
{
	//前回のコントローラーの状態を確保
	for (int i = 0; i < 4; i++)
	{
		memcpy(&prevControllerState[i], &controllerState[i], sizeof(controllerState[i]));
	}


	//コントローラーの状態を取得
	//引数:コントローラーの番号
	//引数:コントローラーの状態
	for (int i = 0; i < 4; i++)
	{
		XInputGetState(i, &controllerState[i]);
	}



	// デバイスのアクセス権を取得する
	HRESULT hr = pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		

		//prevKeystateに前回のキー情報を入れる
		memcpy(prevKeyState, keyState, sizeof(keyState));

		//全てのキーの状態を取得
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		return S_OK;
	}
	return E_FAIL;
}

BOOL Input::IsKeyPush(DWORD keyCode)

{
	if (keyState[keyCode] & 0x80)
	{
		return TRUE; //押している
	}
	return FALSE;      //押してない
}

//キーが押された瞬間かチェック
BOOL Input::IsKeyTap(DWORD  keyCode)
{
	if (!(prevKeyState[keyCode] & 0x80) && keyState[keyCode] & 0x80)
	{
		return TRUE; //押した瞬間
	}
	return FALSE;      //その他
}

//任意のキーが離された瞬間かチェック
BOOL Input::IsKeyRelease(DWORD keyCode)
{
	if ((prevKeyState[keyCode]&0x80)&&!(keyState[keyCode]&0x80))
	{
		return TRUE;	//押している
	}
	return FALSE;

}


//任意のコントローラーのボタンを押しているかチェック
BOOL Input::IsPadButtonPush(DWORD buttonCode, int ID)
{

	if (controllerState[ID].Gamepad.wButtons&buttonCode)
	{
		return TRUE; //押してる
	}

	return FALSE;   //押してない

}

//任意のコントローラーのボタンを押した瞬間かチェック
BOOL Input::IsPadButtonTap(DWORD buttonCode,int ID)
{

	if (!(prevControllerState[ID].Gamepad.wButtons&buttonCode) && controllerState[ID].Gamepad.wButtons&buttonCode)
	{
		return TRUE; //押してる
	}

	return FALSE;   //押してない

}

//コントローラーのボタンを離した瞬間か
BOOL  Input::IsPadButtonRelease(DWORD buttonCode,int ID)
{
	if ((prevControllerState[ID].Gamepad.wButtons&buttonCode) && !(controllerState[ID].Gamepad.wButtons&buttonCode))
	{
		return TRUE;	//押してる
	}
	return FALSE;	//押してない

}

//今左スティック(左右)がどらくらい傾いているか
float Input::GetPadLStickX(int ID)
{

	float value = controllerState[ID].Gamepad.sThumbLX;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value/32767;

}

//今左スティック(上下)がどれくらい傾いているか
float Input::GetPadLStickY(int ID)
{
	float value = controllerState[ID].Gamepad.sThumbLY;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;


}


//今右スティック(左右)がどれくらい傾いているか
float Input::GetPadRStickX(int ID)
{
	float value = controllerState[ID].Gamepad.sThumbRX;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;


}

//今右スティック(上下)がどれくらい傾いているか
float Input::GetPadRStickY(int ID)
{

	float value = controllerState[ID].Gamepad.sThumbRY;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;
	}

	return value / 32767;

}

//今左トリガーが押し込まれているか
float Input::GetPadLTrigger(int ID)
{

	float value = controllerState[ID].Gamepad.bLeftTrigger;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;
	}

	return value / 255;

}

float Input::GetPadRTrigger(int ID)                  //右トリガーの押し込み
{

	float value = controllerState[ID].Gamepad.bRightTrigger;

	//デッドゾーン(傾き20%未満は動かない)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;
	}

	return value / 255;

}

void Input::Vibration(float leftSpeed, float rightSpeed,int ID)                   //振動エフェクト
{

	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftSpeed *65535; // 左モーター
	vibration.wRightMotorSpeed = rightSpeed *65535; // 右モーター
	XInputSetState(0, &vibration);


}




