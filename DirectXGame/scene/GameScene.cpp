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
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body"));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head"));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm"));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm"));

	enemyModelBody_.reset(Model::CreateFromOBJ("needle_Body"));
	enemyModelL_arm_.reset(Model::CreateFromOBJ("needle_L_arm"));
	enemyModelR_arm_.reset(Model::CreateFromOBJ("needle_R_arm"));

    modelHammer_.reset(Model::CreateFromOBJ("hammer"));

	viewprojection_.Initialize();
	viewprojection_.farZ = 1400.0f;
	viewprojection_.translation_.y = 5.0f;
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	//自機
	player_ = std::make_unique<Player>();
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(),modelHammer_.get()};
	player_->Initialize(playerModels);

	//敵
	enemy_ = std::make_unique<Enemy>();
	std::vector<Model*> enemyModels = {
	    enemyModelBody_.get(), enemyModelL_arm_.get(), enemyModelR_arm_.get()};
	enemy_->Initialize(enemyModels);


	// Skydome
	modelskydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelskydome_);

	// Ground
	modelground_ = Model::CreateFromOBJ("ground", true);
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelground_);

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	followcamera_->SetTarget(&player_->GetWorldTransform());
}

void GameScene::Update() {
	player_->Update();
	enemy_->Update();
	skydome_->Update();
	ground_->Update();
	followcamera_->Update();
	viewprojection_.matView = followcamera_->GetViewProjection().matView;

	viewprojection_.matProjection = followcamera_->GetViewProjection().matProjection;
	viewprojection_.TransferMatrix();
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

	enemy_->Draw(viewprojection_);

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