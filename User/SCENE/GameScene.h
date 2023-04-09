#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <string>
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"

#include "Matrix4.h"
#include "Camera.h"

#include "ParticleManager.h"

#include"Player.h"
#include"EnemyManager.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �ÓI�����o�ϐ�
	//static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	void Reset();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void EffUpdate();
	void EffDraw();

	void CamMove();
	void CamRota();
	void CamUpdate();


	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	
private: // �����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


private:	//�����o�ϐ�
	const float PI = 3.141592;

	//�J����
	Camera* camera = nullptr;
	Transform camWtf;
	Transform targetWtf;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.1f;
	float camRotaSpeed = PI/180;

	//�v���C���[
	Player* player_ = nullptr;
	//�G�l�~�[
	EnemyManager* enemyManager_ = nullptr;

	//�w�i�⏰
	Object3d* floor = nullptr;
	Model* floorMD = nullptr;
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;

	//�p�[�e�B�N���N���X�̏����� 
	ParticleManager* bloodParticle = nullptr;
	//�����������̃G�t�F�N�g����
	int isEffFlag = 0;
	int EffTimer = 0;

	//UI
	Sprite* UI = nullptr;
	Sprite* buttomPng1 = nullptr;
	Sprite* buttomPng2 = nullptr;
	Sprite* hpGauge = nullptr;
	Vector2 hpPosition;
	Sprite* unionGauge = nullptr;
	Vector2 unionScale;
	Sprite* avoidUI = nullptr;
	Vector3 avoidScale;

	//�Q�[���t���[
	enum class Scene
	{
			Title,
			Select,
			Play,
			Clear,
			Gameover,
	};
	Scene scene;
	int stage;
	Sprite* titlePic;
	Sprite* selectPic;
	Sprite* clearPic;
	Sprite* gameoverPic;
	Sprite* sousaUi;
};