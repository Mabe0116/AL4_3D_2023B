#pragma once

#include "Audio.h"
#include "Balloon.h"
#include "DirectXCommon.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Ground.h>
#include <Skydome.h>
#include <memory>
#include <random>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void AddBalloon();

	void CheckAllCollision();

	bool GetChangeScene() { return ChangeScene; };

	void Reset();

	float GetRandomFloat(float min, float max);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;

	std::unique_ptr<Skydome> skydome_ = nullptr;
	Model* modelskydome_ = nullptr;

	std::unique_ptr<Ground> ground_ = nullptr;
	Model* modelground_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	ViewProjection viewprojection_;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;

	// 3dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	Model* ModelPlayer_ = nullptr;
	Model* ModelPlayerBullet_ = nullptr;

	Model* balloon = nullptr;

	std::list<Balloon*> balloon_;

	std::unique_ptr<FollowCamera> followcamera_ = nullptr;

	bool ChangeScene = false;
	int32_t NextScene = 0;

	uint32_t textureHandle_;

	std::mt19937 randomEngine;

	const int kStartBalloonCount = 3;
	const int kClearBalloonCount = 20;
	int hitCount_ = 0;

	const int kBalloonSpawnTime = 60 * 2;
	int balloonSpawnTimer_ = 0;

	float minX = -50.0f;
	float maxX = 50.0f;
	float minZ = 0.0f;
	float maxZ = 50.0f;

	// トランジション用のスプライト
	std::unique_ptr<Sprite> transitionSprite_ = nullptr;
	Vector4 transitionSpriteColor_ = {0.0f, 0.0f, 0.0f, 1.0f};
	bool isFadeIn_ = false;
	bool isFadeOut_ = true;
};
