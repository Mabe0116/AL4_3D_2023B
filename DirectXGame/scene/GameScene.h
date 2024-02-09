#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Ground.h>
#include <Skydome.h>
#include <memory>


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
	std::unique_ptr<Enemy> enemy_ = nullptr;

	// 3dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	std::unique_ptr<Model> enemyModelBody_;
	std::unique_ptr<Model> enemyModelL_arm_;
	std::unique_ptr<Model> enemyModelR_arm_;

	std::unique_ptr<Model> modelHammer_;


	std::unique_ptr<FollowCamera> followcamera_ = nullptr;

	uint32_t textureHandle_;
};
