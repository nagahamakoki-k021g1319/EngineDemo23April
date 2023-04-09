#include"EnemyManager.h"
#include"player.h"

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::Initialize() {
	origin = new Transform();
	origin->Initialize();
	
}

void EnemyManager::creatEnemy(int round) {
	//”O‚Ì‚½‚ßƒŠƒXƒg‚Ì‘|œ
	enemys_.clear();

	//“G‚Ì“Ç‚İ‚İ
	if (round == 0) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ 0,0,7 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}else if (round == 1) {
		{
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ -3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		} {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize({ 3,0,5 });
			newEnemy->SetPlayer(player_);
			enemys_.push_back(std::move(newEnemy));
		}
	}
}


void EnemyManager::Update() {
	//“G‚ª‚¢‚È‚¢‚Æ‚«Œ´“_‚ÉUŒ‚
	player_->SetEnemyPos(origin);


	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		float damage = 0;
		//“G‚ÆƒvƒŒƒCƒ„[UŒ‚Õ“Ë
		if (player_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
			enemy->OnColision(damage);	
		}
		//“G‚ÆƒoƒfƒB‚ÌÕ“Ë
		if (player_->wolf_->CheckAttack2Enemy(enemy->GetWorldPosition(), damage)) {
			enemy->OnColision(damage);
		}

		enemy->Update();
	}

}

void EnemyManager::Draw() {
	for (std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw();
	}

}


bool EnemyManager::IsAllEnemyDead() {
	bool result = false;

	if (enemys_.size() == 0) {
		result = true;
	}

	return result;
}