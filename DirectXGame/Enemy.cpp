#include "Enemy.h"
#include "Mymath.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models); 

	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	
	worldTransformL_arm_.translation_ = {-0.5f, 1.1f, 0.0f};
	worldTransformR_arm_.translation_ = {0.5f, 1.1f, 0.0f};

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;
}

void Enemy::Update() { 
	BaseCharacter::Update(); 

	// 回転
	const float rotSpeed = 0.08f;
	worldTransform_.rotation_.y += rotSpeed;
	// 回転方向に移動
	Vector3 velocity{0.0f, 0.0f, 0.2f};
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	// 移動処理
	Move(worldTransform_.translation_, velocity);


	// 行列の更新
	BaseCharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformBody_,viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);

}
