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

void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	/*textureHandle_ = textureHandle;*/
	input_ = Input::GetInstance();
};

void Player::Update() {
	worldTransform_.TransferMatrix();
	//行列の更新
	worldTransform_.UpdateMatrix();

	Move();
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
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		
		// 移動量
		move.x = (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y = 0.0f;
		move.z = (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;


		//移動
		Add(worldTransform_.translation_, move);

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

void Player::InitializeFloatingGimmick(){ 
	floatingParameter_ = 0.0f;
}

void Player::UpdateFloatingGimmick() {
	//浮遊移動のサイクル＜frame＞
	const uint16_t;

	//1フレームでのパラメータ加算地
	const float;

	//パラメータを1ステップ分加算
	floatingParameter_ += ;

	//2πを超えたらΘに戻す
	floatingParameter_ = syd::fmod(floatingParameter_, 2.0f *);

	//浮遊の振幅<m>
	const float = ;

	//浮遊を座標の反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_)*;

}
