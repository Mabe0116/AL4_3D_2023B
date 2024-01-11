#include "Balloon.h"
#include <cassert>
#include "Mymath.h"
#include "Player.h"

Balloon::~Balloon(){ }

void Balloon::Initialize(Model* model, uint32_t textureHandle, Vector3 pos) { 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = pos;

}

void Balloon::Update() {
	//switch (phase_) {
	//case Phase::Approach:
	//default:
	//	Balloon::Approach();
	//	break;
	//case Phase::Leave:
	//	Balloon::Leave();
	//	break;
	//}
	UpdateFloatingGimmick();

	worldTransform_.UpdateMatrix();

}

void Balloon::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection); 
}

void Balloon::Approach() {

	// 敵の移動ベクトル
	Vector3 move = {0, 0, -0.2f};

	// 移動
	Move(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();

	// 既定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Balloon::Leave() {

	// 敵の移動ベクトル
	Vector3 move = {0, 0.1f, -0.2f};

	// 移動
	Move(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();
}

void Balloon::OnCollision() { 
	isDead_ = true; 
}

Vector3 Balloon::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


void Balloon::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル＜frame＞
	const uint16_t period = 60;

	// 1フレームでのパラメータ加算地
	const float step = 2.0f * 3.14f / period;

	// パラメータを1ステップ分加算
	floatingParameter_ += step;

	// 2πを超えたらΘに戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * 3.14f);

	// 浮遊の振幅<m>
	const float floatingAmplitude = 0.125f;

	// 浮遊を座標の反映
	worldTransform_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;
}