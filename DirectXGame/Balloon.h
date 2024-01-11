#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <list>

// 行動フェーズ
enum class Phase {
	Approach,
	Leave,
};

class Balloon {
public:
	void Initialize(Model* model,uint32_t textureHandle,Vector3 pos);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void Approach();
	void Leave();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	bool IsDead() const { return isDead_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	void UpdateFloatingGimmick();

	~Balloon();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	// フェーズ
	Phase phase_ = Phase ::Approach;
	// デスフラグ
	bool isDead_ = false;

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};
