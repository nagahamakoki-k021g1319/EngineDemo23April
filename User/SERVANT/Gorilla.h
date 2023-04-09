#pragma once
#include"Object3d.h"
#include "Input.h"

class Gorilla {


public:
	Gorilla();
	~Gorilla();

	void Initialize();

	void Move();
	void Update();

	//í èÌçUåÇ
	void ShortRange();
	void ChargeShortRange();
	void LongRange();
	void ChargeLongRange();


	void Draw();

	void SetPlayerWtf(Transform* worldTransform) { playerWtf = worldTransform; };

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

private:
	const float PI = 3.141592;

	Model* bodyModel_ = nullptr;
	Object3d* bodyObj_ = nullptr;

	bool isAttack;
	Transform* playerWtf = nullptr;

	Vector3 defaultPos = { 3,2,0 };

public:
};