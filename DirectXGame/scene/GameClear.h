#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
// #include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameClear {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameClear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClear();

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

	bool GetChangeScene() { return ChangeScene; };

	void Reset() {
		ChangeScene = false;
		isFadeIn_ = false;
		isFadeOut_ = true;
	};

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;
	uint32_t TextureHandle_ = 0;
	bool ChangeScene = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// トランジション用のスプライト
	std::unique_ptr<Sprite> transitionSprite_ = nullptr;
	Vector4 transitionSpriteColor_ = {0.0f, 0.0f, 0.0f, 1.0f};
	bool isFadeIn_ = false;
	bool isFadeOut_ = true;
};
