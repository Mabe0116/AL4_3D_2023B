#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"

class Player : public BaseCharacter {
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;
	const WorldTransform& GetWorldTransform() { 
		return worldTransform_;
	}

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

private:
	void Move();

private:

	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};
