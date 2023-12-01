#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 地面
/// </summary>

class Ground {

public:
	void Initialize(Model* model);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
};
