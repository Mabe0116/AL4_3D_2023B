#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	void Initialize(Model* modelBody,Model* modelHead,Model* modelL_arm,Model* modelR_arm);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	const WorldTransform& GetWorldTransform() { 
		return worldTransform_;
	}

	//浮遊ギミック初期化
	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

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
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};
