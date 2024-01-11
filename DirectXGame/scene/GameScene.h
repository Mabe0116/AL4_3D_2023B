#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Balloon.h"
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

	void AddEnemy(Vector3 pos);

	void CheckAllCollision();

	bool GetChangeScene() { return ChangeScene; };

	void Reset();

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

	uint32_t hitCount_ = 0;

	std::mt19937 randomEngine;
};
