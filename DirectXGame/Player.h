#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"

class Player {
public:
	void Initialize(Model* modelBody,Model* modelHead,Model* modelL_arm,Model* modelR_arm,Model* PlayerBullet);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	const WorldTransform& GetWorldTransform() { 
		return worldTransform_;
	}
	void Attack();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();
	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

	void Reset();

	~Player();

private:
	void Move();

private:
	Model* model_ = nullptr;

	//3dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;

	// 弾
	std::list<PlayerBullet*> bullets_;

	int32_t BulletTimer = 0;

	Model* ModelPlayerBullet_ = nullptr;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};
