#include "Player.h"
#include <cassert>
#include "Mymath.h"
#include "ImGuiManager.h"

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

void Player::Initialize(const std::vector<Model*>& models) {
	
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	//基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldTransformHead_.translation_ = {0.0f, 1.4f, 0.0f};
	worldTransformL_arm_.translation_ = {-0.5f, 1.1f, 0.0f};
	worldTransformR_arm_.translation_ = {0.5f, 1.1f, 0.0f};

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	/*textureHandle_ = textureHandle;*/
	input_ = Input::GetInstance();
};

void Player::Update() {
	worldTransform_.TransferMatrix();
	//行列の更新
	worldTransform_.UpdateMatrix();

	//行列の更新
	BaseCharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	UpdateFloatingGimmick();

	Move();
};

void Player::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
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
	const uint16_t period = 60;

	//1フレームでのパラメータ加算地
	const float step = 2.0f * 3.14f / period;

	//パラメータを1ステップ分加算
	floatingParameter_ += step;

	//2πを超えたらΘに戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);

	//浮遊の振幅<m>
	const float floatingAmplitude = 0.125f;

	//浮遊を座標の反映
	worldTransformBody_.translation_.y =
	    std::sin(floatingParameter_) * floatingAmplitude;

	worldTransformL_arm_.translation_.z =
		std::sin(floatingParameter_) * floatingAmplitude;

	worldTransformR_arm_.translation_.z =
		std::sin(floatingParameter_) * -floatingAmplitude;

	ImGui::Begin("Player");
	ImGui::SliderFloat3("Body Translation", &worldTransformBody_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Head Translation", &worldTransformHead_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("ArmL Translation", &worldTransformL_arm_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("ArmR Translation", &worldTransformR_arm_.translation_.x, -10.0f, 10.0f);
	ImGui::End();


}
