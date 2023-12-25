#include "Player.h"
#include <cassert>
#include "Mymath.h"

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	textureHandle_ = textureHandle;
	input_ = Input::GetInstance();
};

void Player::Update() {
	worldTransform_.TransferMatrix();
	//行列の更新
	worldTransform_.UpdateMatrix();
};

void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move(){
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	// ジョイスティック状態取得
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 速さ
		const float speed = 0.3f;

		// 自機移動処理
		// Move(worldTransform_.translation_, move);
		
		// 移動量
		move.x = (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y = (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;

		//移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		//// 押した方向で移動ベクトルを変更(左右)
		// if (input_->PushKey(DIK_LEFT)) {
		//	move.x -= kCharacterSpeed;
		// } else if (input_->PushKey(DIK_RIGHT)) {
		//	move.x += kCharacterSpeed;
		// }

		//// 押した方向で移動ベクトルを変更(上下)
		// if (input_->PushKey(DIK_UP)) {
		//	move.y += kCharacterSpeed;
		// }

		// if (input_->PushKey(DIK_DOWN)) {
		//	move.y -= kCharacterSpeed;
		// }
	}
};
