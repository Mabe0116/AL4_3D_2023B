#include "GameScene.h"
#include "Mymath.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_.reset(Model::Create());
	viewprojection_.Initialize();
	viewprojection_.farZ = 1400.0f;
	viewprojection_.translation_.y = 5.0f;
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	player_ = std::make_unique<Player>();
	player_->Initialize(model_.get(), textureHandle_);
	//Skydome
	modelskydome_ = Model::CreateFromOBJ("skydome",true);
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelskydome_);

	//Ground
	modelground_ = Model::CreateFromOBJ("ground", true);
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelground_);
}

void GameScene::Update() {
	player_->Update();
	skydome_->Update();
	ground_->Update();
	viewprojection_.UpdateMatrix();
}

void GameScene::Draw() {

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
	player_->Draw(viewprojection_);

	skydome_->Draw(viewprojection_);

	ground_->Draw(viewprojection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
