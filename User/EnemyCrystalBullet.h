#pragma once
#include "Object3d.h"
#include <memory>
#include <list>
class Player;

class EnemyCrystalBullet {
public:
	~EnemyCrystalBullet();

	///< summary>
	///初期化
	///</summary>
	void Initialize(int num, Model* crystalModel_);
	///< summary>
	///更新
	///</summary>
	void CrystalBAttack();

	///< summary>
	///更新
	///</summary>
	void Update();

	///< summary>
	///描画
	///</summary>
	void Draw();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { crystalObj_->wtf.position = pos; };

	/// <summary>
	/// 大きさ
	/// </summary>
	/// <param name="pos"></param>
	void SetScale(Vector3 scale) { crystalObj_->wtf.scale = scale; };

	void Vec(Vector3 pos);

	bool IsDead() const { if (isLive) { return false; } else { return true; } };

	void OnCollision();

	////ワールド座標を取得
	Vector3 GetWorldPosition();

private:

	////-----------///
	Object3d* crystalObj_ = nullptr;
	//召喚して飛ばすまでの時間とフラグ
	int crystalTimer;
	bool isLive = false;
	int shotTimer;
	//////////////////////////////

	int bulletNum;

	Vector3 A_BVecNolm;
	const float speed = 0.5f;
};

