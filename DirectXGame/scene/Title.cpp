#include "Title.h"
#include "TextureManager.h"
#include <cassert>

Title::Title() {}

Title::~Title() { delete sprite_; }

void Title::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	TextureHandle_ = TextureManager::Load("UI/Title.png");
	sprite_ = Sprite::Create(TextureHandle_, {0, 0});
}

void Title::Update() {
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			ChangeScene = true;
			NextScene = 1;
		}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
			ChangeScene = true;
			NextScene = 2;
		}
	}
}

void Title::Draw() {

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

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}