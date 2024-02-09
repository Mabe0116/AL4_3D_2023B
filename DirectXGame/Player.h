#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include <optional>

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

	void BehaviorRootUpdate();

	void BehaviorAttackUpdate();

	void BehaviorRootInitialize();

	void BehaviorAttackInitialize();

private:
	void Move();

private:

	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformHammer_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	enum class Behavior {
		kRoot,
		kAttack,
	};

	Behavior behavior_ = Behavior::kRoot;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	struct Attack {
		float time;
		const int kAnimMaxTime = 60;
		const int kAttakAllFrame = 80;
	};
	Attack attack_;
};
