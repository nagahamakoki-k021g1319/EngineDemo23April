#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <forward_list>

#include "Camera.h"

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"

/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class ParticleCommon
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		Vector4 color; // �F (RGBA)
	};

	// ���_�f�[�^�\����
	struct VertexPos
	{
		Vector3 pos; // xyz���W
		float scale;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Matrix4 mat;
		Matrix4 matBillboard;	// �r���{�[�h�s��
	};

	//�p�[�e�B�N���ꗱ
	struct Particle {

		//���W
		Vector3 position = {};
		//���x
		Vector3 velocity = {};
		//�����x
		Vector3 accel = {};
		//���݃t���[��
		int frame = 0;
		//�ߋ��t���[��
		int num_frame = 0;

		//�X�P�[��
		float scale = 1.0f;
		//�����l
		float s_scale = 1.0f;
		//�ŏI�l
		float e_scale = 0.0f;

		Vector4 color; // �F (RGBA)
	};

private: // �萔
	static const int division = 50;					// ������
	static const float radius;				// ��ʂ̔��a
	static const float prizmHeight;			// ���̍���
	static const int planeCount = division * 2 + division * 2;		// �ʂ̐�
	//static const int vertexCount = 30;//���_��
	static const int vertexCount = 1024;

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	ComPtr <ID3D12Device> device;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �R�}���h���X�g
	ComPtr <ID3D12GraphicsCommandList> cmdList;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// ���_�f�[�^�z��
	VertexPos vertices[vertexCount];
	//�r���{�[�h�s��
	Matrix4 matBillboard;
	//Y�����r���{�[�h�s��
	Matrix4 matBillboardY;
	//�p�[�e�B�N���z��
	std::forward_list<Particle>particles;

public: // �����o�֐�
	void LoadTexture(const std::string& fileName);

	void Initialize();

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	///	<param name="life">��������</param>
	///	<param name="position">�������W</param>
	///	<param name="velocity">���x</param>
	///	<param name="accel">�����x</param>
	void Add(int life, Vector3 position, Vector3 velociy, Vector3 accel, float start_scale, float end_scale);

	static void SetCamera(Camera* camera) { ParticleCommon::camera = camera; }


private:// �ÓI�����o�֐�
	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	void InitializeGraphicsPipeline();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel();

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	static Camera* camera;
	// ���[�J���X�P�[��
	Vector3 scale = { 1,1,1 };

	ConstBufferDataMaterial* constMapMaterial = nullptr;
};
