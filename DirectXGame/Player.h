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

	//���V�M�~�b�N������
	void InitializeFloatingGimmick();

	void UpdateFloatingGimmick();

private:
	void Move();

private:
	Model* model_ = nullptr;

	//3d���f��
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	WorldTransform worldTransform_;
	uint32_t textureHandle_;
	Input* input_ = nullptr;

	//���V�M�~�b�N�̔}��ϐ�
	float floatingParameter_ = 0.0f;

};
