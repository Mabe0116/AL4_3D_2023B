#include "GameScene.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete ModelPlayerBullet_;

	for (Balloon* it : balloon_) {
		delete it;
	}
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_.reset(Model::Create());
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body"));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head"));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm"));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm"));
	ModelPlayerBullet_ = Model::CreateFromOBJ("PlayerBullet", true);
	balloon = Model::CreateFromOBJ("Balloon", true);

	viewprojection_.Initialize();
	viewprojection_.farZ = 1400.0f;
	viewprojection_.translation_.y = 5.0f;
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	player_ = std::make_unique<Player>();
	player_->Initialize(
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), ModelPlayerBullet_);

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

	std::random_device seedGenerator;
	randomEngine = std::mt19937(seedGenerator());

	for (int i = 0; i < kStartBalloonCount; ++i) {
		AddBalloon();
	}
}

void GameScene::Update() {
	player_->Update();
	skydome_->Update();
	ground_->Update();
	followcamera_->Update();

	// デスフラグの立った弾を削除
	balloon_.remove_if([](Balloon* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	if (++balloonSpawnTimer_ > kBalloonSpawnTime) {
		balloonSpawnTimer_ = 0;
		AddBalloon();
	}

	// 風船
	for (Balloon* it : balloon_) {
		it->Update();
	}

	CheckAllCollision();

	viewprojection_.matView = followcamera_->GetViewProjection().matView;

	viewprojection_.matProjection = followcamera_->GetViewProjection().matProjection;
	viewprojection_.TransferMatrix();

	if (hitCount_ >= kClearBalloonCount) {
		ChangeScene = true;
	}

	// ImGui::Begin("GameScene");
	// ImGui::Text("HitCount : %d", hitCount_);
	// ImGui::End();
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

	// 風船
	for (Balloon* it : balloon_) {
		it->Draw(viewprojection_);
	}

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

void GameScene::CheckAllCollision() {

	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	for (Balloon* it : balloon_) {

		// 敵キャラの座標
		posA = it->GetWorldPosition();

		// 敵キャラと自弾全ての当たり判定
		for (PlayerBullet* bullet : playerBullets) {
			// 自弾の座標
			posB = bullet->GetWorldPosition();

			// 球と球の交差判定
			float Distance = Length(Subtract(posA, posB));
			if (Distance < 3.0f + 1.0f) {
				// 敵キャラの衝突時コールバックを呼び出す
				it->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				bullet->OnCollision();

				hitCount_++;
			}
		}
	}
}

void GameScene::Reset() {
	ChangeScene = false;
	hitCount_ = 0;

	for (Balloon* it : balloon_) {
		delete it;
	}

	balloon_.clear();
	player_->Reset();

	for (int i = 0; i < kStartBalloonCount; ++i) {
		AddBalloon();
	}
}

void GameScene::AddBalloon() {
	Balloon* newBalloon = new Balloon();
	Vector3 position = {GetRandomFloat(minX, maxX), 0.0f, GetRandomFloat(minZ, maxZ)};
	newBalloon->Initialize(balloon, 0, position);
	balloon_.push_back(newBalloon);
}

float GameScene::GetRandomFloat(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomEngine);
}