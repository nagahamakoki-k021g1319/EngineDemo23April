#include "EnemyCrystalBullet.h"
#include "Player.h"

EnemyCrystalBullet::~EnemyCrystalBullet() {
	delete crystalObj_;
}

void EnemyCrystalBullet::Initialize(int num, Model* crystalModel_) {
	// ダガーファンネル
	crystalObj_ = Object3d::Create();
	crystalObj_->SetModel(crystalModel_);

	isLive = true;
	bulletNum = num;
	shotTimer = 300 - num * 50;
}


//移動ベクトル計算
void EnemyCrystalBullet::Vec(Vector3 pos) {
	//プレイヤーのワールド座標の取得
	Vector3 playerPosition;
	playerPosition = pos;
	//敵のワールド座標を取得
	Vector3 BulletPosition;
	BulletPosition = GetWorldPosition();
	//差分ベクトルを求める
	Vector3 A_BVec = Vector3(
		playerPosition.x - BulletPosition.x,
		playerPosition.y - BulletPosition.y,
		playerPosition.z - BulletPosition.z
	);

	//ベクトル正規化
	float length = sqrt(A_BVec.x * A_BVec.x + A_BVec.y * A_BVec.y + A_BVec.z * A_BVec.z);
	A_BVecNolm = Vector3(A_BVec.x / length, A_BVec.y / length, A_BVec.z / length);

	A_BVecNolm *= speed;
}

void EnemyCrystalBullet::CrystalBAttack() {
	shotTimer--;

	if (isLive) {
		if (shotTimer <= 100) {
			crystalObj_->wtf.position += A_BVecNolm;
		}
	}

	if (crystalObj_->wtf.position.z <= -30) {
		isLive = false;
	}
}

void EnemyCrystalBullet::Update(){
	CrystalBAttack();
	crystalObj_->Update();

}

void EnemyCrystalBullet::Draw(){
	crystalObj_->Draw();

}

Vector3 EnemyCrystalBullet::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = crystalObj_->wtf.position.x;
	worldPos.y = crystalObj_->wtf.position.y;
	worldPos.z = crystalObj_->wtf.position.z;

	return worldPos;
}


void EnemyCrystalBullet::OnCollision() {
	isLive = false;

}