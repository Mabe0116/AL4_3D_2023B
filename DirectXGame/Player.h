#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"

class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	const WorldTransform& GetWorldTransform() { 
		return worldTransform_;
	}

private:
	void Move();

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;
};
