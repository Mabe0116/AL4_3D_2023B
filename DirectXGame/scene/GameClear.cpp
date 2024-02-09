#include "GameClear.h"
#include "TextureManager.h"
#include <cassert>

GameClear::GameClear() {}

GameClear::~GameClear() {}

void GameClear::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	TextureHandle_ = TextureManager::Load("UI/GameClear.png");
	sprite_ = Sprite::Create(TextureHandle_, {0, 0});

	// トランジション用のスプライト
	transitionSprite_.reset(Sprite::Create(0, {0.0f, 0.0f}));
	transitionSprite_->SetSize({1280.0f, 720.0f});
}

void GameClear::Update() {
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (!isFadeIn_ && !isFadeOut_) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

				isFadeIn_ = true;
			}
		}
	}

	// FadeInの処理
	if (isFadeIn_) {
		transitionSpriteColor_.w += 0.1f;
		if (transitionSpriteColor_.w > 1.0f) {
			transitionSpriteColor_.w = 1.0f;
			isFadeIn_ = false;
			ChangeScene = true;
		}
	}

	// FadeOutの処理
	if (isFadeOut_) {
		transitionSpriteColor_.w -= 0.1f;
		if (transitionSpriteColor_.w < 0.0f) {
			transitionSpriteColor_.w = 0.0f;
			isFadeOut_ = false;
		}
	}

	transitionSprite_->SetColor(transitionSpriteColor_);
}

void GameClear::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	sprite_->Draw();

	transitionSprite_->Draw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
