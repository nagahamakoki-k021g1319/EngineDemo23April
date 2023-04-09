#include"Enemy.h"
#include"player.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete enemyObj_;
	delete enemyModel_;
	delete daggerBulletModel_;
	daggerBullets_.clear();
	delete enemyCBModel_;
	crystalBullets_.clear();
}

void Enemy::Initialize(Vector3 pos) {
	enemyModel_ = Model::LoadFromOBJ("as");
	enemyObj_ = Object3d::Create();
	enemyObj_->SetModel(enemyModel_);
	enemyObj_->wtf.position = pos;

	isInvincible = false;

	// ダガーファンネル
	daggerBulletModel_ = Model::LoadFromOBJ("boll");
	//順番に弾が飛んでくる攻撃
	enemyCBModel_ = Model::LoadFromOBJ("boll");
	
}

void Enemy::Update() {
	//無敵時間更新
	if (invincibleTimer > 0) {
		invincibleTimer--;
	}
	else if (invincibleTimer <= 0) {
		isInvincible = false;
	}

	{//仮でプレイヤーとのやり取り
		player_->SetEnemyPos(&enemyObj_->wtf);
	}

	enemyObj_->Update();

	//各種球更新
	//ダガーバレット
	daggerBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Update();
		if (bullet->isPop) {
			//仮でプレイヤーとのやり取り
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetPos(), 1.0f, 1.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	//クリスタルバレット
	crystalBullets_.remove_if([](std::unique_ptr<EnemyCrystalBullet>& bullet) { return bullet->IsDead(); });
	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Update();
		{//仮でプレイヤーとのやり取り
			if (coll.CircleCollision(player_->GetWorldPosition(), bullet->GetWorldPosition(), 2.0f, 2.0f)) {
				player_->OnCollision();
				bullet->OnCollision();
			}
		}
	}

	switch (phase_) {
	case Phase::Approach:
		enemyResetTimer = 0;
		enemyAttackTimer++;

		//フェーズ移行
		if (enemyAttackTimer >= 450) {
			phase_ = Phase::Leave;
		}

		//攻撃するまで移動
		if (enemyAttackTimer >= 0 && enemyAttackTimer <=9) {
			enemyObj_->wtf.position.z += 0.1f;
		}
		//攻撃するまで移動
		if (enemyAttackTimer >= 150 && enemyAttackTimer <= 190) {
			enemyObj_->wtf.position.z += 0.05f;
			enemyObj_->wtf.position.x += 0.1f;
		}

		//ダガーファンネルを秒数で攻撃させる
		if (enemyAttackTimer == 10|| enemyAttackTimer == 200|| enemyAttackTimer == 250) {
			CreatDaggerBullet(5);
		}


		break;
	case Phase::Leave:
		
		enemyAttackTimer2++;
		if (enemyAttackTimer2 >= 300) {
			phase_ = Phase::ReLeave;
		}
		
		//攻撃するまで移動
		if (enemyAttackTimer2 >= 0 && enemyAttackTimer2 <= 9) {
			enemyObj_->wtf.position.z -= 0.05f;
			enemyObj_->wtf.position.x -= 0.1f;
		}
		//順番に攻撃する弾を秒数で攻撃させる
		if (enemyAttackTimer2 == 10) {
			CreatCrystalBullet();
		}

		break;
	case Phase::ReLeave:
		enemyResetTimer++;
		if (enemyResetTimer >= 50) {
			phase_ = Phase::Approach;
		}
		enemyAttackTimer = 0;
		enemyAttackTimer2 = 0;
	
		break;
	}
	

}

void Enemy::CreatDaggerBullet(int bulletNum) {
	for (int i = 0; i < bulletNum; i++) {
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(20 + 20 * i, daggerBulletModel_);
		newBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f + 2.0f * i,enemyObj_->wtf.position.y,enemyObj_->wtf.position.z + 8.0f });
		newBullet->SetScale({ 0.5f,0.5f, 0.5f });
		daggerBullets_.push_back(std::move(newBullet));
	}
}

void Enemy::CreatCrystalBullet() {
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
		newCrystalBullet->Initialize(i, enemyCBModel_);
		newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 2.0f + 4.0f * i,enemyObj_->wtf.position.y - 3.0f,enemyObj_->wtf.position.z + 15.0f });
		newCrystalBullet->Vec(player_->GetWorldPosition());
		crystalBullets_.push_back(std::move(newCrystalBullet));
	}
	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet->Initialize(2, enemyCBModel_);
	newCrystalBullet->SetPos({ enemyObj_->wtf.position.x - 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet2 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet2->Initialize(3, enemyCBModel_);
	newCrystalBullet2->SetPos({ enemyObj_->wtf.position.x + 4.0f,enemyObj_->wtf.position.y + 1.0f, enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet2->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet2));

	std::unique_ptr<EnemyCrystalBullet> newCrystalBullet3 = std::make_unique<EnemyCrystalBullet>();
	newCrystalBullet3->Initialize(4, enemyCBModel_);
	newCrystalBullet3->SetPos({ enemyObj_->wtf.position.x,enemyObj_->wtf.position.y + 4.0f,enemyObj_->wtf.position.z + 15.0f });
	newCrystalBullet3->Vec(player_->GetWorldPosition());
	crystalBullets_.push_back(std::move(newCrystalBullet3));
}

void Enemy::Draw() {
	enemyObj_->Draw();
	
	for (std::unique_ptr<EnemyBullet>& bullet : daggerBullets_) {
		bullet->Draw();
	}

	for (std::unique_ptr<EnemyCrystalBullet>& bullet : crystalBullets_) {
		bullet->Draw();
	}
	
	switch (phase_) {
	case Phase::Approach:

		break;
	case Phase::Leave:
		
		break;

	case Phase::ReLeave:
		break;
	}


}

Vector3 Enemy::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = enemyObj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyObj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyObj_->wtf.matWorld.m[3][2];


	return worldPos;
}

void Enemy::OnColision(int damage) {
	if (isInvincible == false) {
		hp -= damage;
		if (hp <= 0) {
			isLive = false;
		}
		isInvincible = true;
		invincibleTimer = invincibleLimit;
	}
}