#pragma once
#include "WorldTransform.h"
#include "Model.h"

class BaseCharacter {
public:
	virtual void Initialize(const std::vector<Model*>& models);

	virtual void Update();

	virtual void Draw(const ViewProjection& viewProjection);

	const WorldTransform& GetworldTransform() { return worldTransform_; }

protected:
	//モデルデータ配列
	std::vector<Model*> models_;

	//ワールド変換データ
	WorldTransform worldTransform_;

};
