#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <memory>
#include <Skydome.h>
#include <Ground.h>
#include "FollowCamera.h"


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
	
	std::unique_ptr<FollowCamera> followcamera_ = nullptr;

	uint32_t textureHandle_;
};
