#pragma once
#include"Enemy.h"

class Player;

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();

	void Initialize();

	void Update();
	
	void Draw();

	void creatEnemy(int round);

	void SetPlayer(Player* player) { player_ = player; };

	bool IsAllEnemyDead();

private:
	Transform* origin = nullptr;

	Player* player_ = nullptr;

	std::list<std::unique_ptr<Enemy>> enemys_;

};