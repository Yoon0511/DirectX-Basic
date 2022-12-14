#pragma once
#include "Mesh.h"

class CShader;
class CCamera;

class CGameObject {
public:
	CGameObject(int nMeshes = 1);
	virtual ~CGameObject();

private:
	int m_nReferences = 0;
	
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	XMFLOAT4X4 m_xmf4x4World;

	bool IsVisible(UINT nIndex, CCamera* pCamera = NULL);

protected:
	CMesh** m_ppMeshes = NULL;
	int m_nMeshes = 0;

	CShader* m_pShader = NULL;

public:
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	void ReleaseUploadBuffers();
	virtual void SetMesh(int nIndex, CMesh* pMesh);
	virtual void SetShader(CShader* pShader);

	virtual void Animate(float fTimeElapsed);
	void Rotate(XMFLOAT3* pxmfAxis, float fAngle);

	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera *pCamera);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	void GenerateRayForPicking(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, XMFLOAT3* pxmf3PickRayOrigin, XMFLOAT3* pxmf3PickRayDirection);
	int PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float* pfHitDistance);
};

class CRotatingObject : public CGameObject {
public:
	CRotatingObject(int nMeshes = 1);
	virtual ~CRotatingObject();

private:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;

public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) { m_xmf3RotationAxis = xmf3RotationAxis; }
	virtual void Animate(float fTimeElapsed);
};

class CHeightMapTerrain : public CGameObject {
public:
	CHeightMapTerrain(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, LPCTSTR pFileName, int nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4 xmf4Color);
	virtual ~CHeightMapTerrain();

private:
	CHeightMapImage* m_pHeightMapImage;

	int m_nWidth;
	int m_nLength;

	XMFLOAT3 m_xmf3Scale;

public:
	float GetHeight(float x, float z) { return m_pHeightMapImage->GetHeight(x / m_xmf3Scale.x, z / m_xmf3Scale.z) * m_xmf3Scale.y; }
	XMFLOAT3 GetNormal(float x, float z) { return m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z / m_xmf3Scale.z)); }

	int GetHeightMapWidth() { return m_pHeightMapImage->GetHeightMapWidth(); }
	int GetHeightMapLength() { return m_pHeightMapImage->GetHeightMapLength(); }

	XMFLOAT3 GetScale() { return m_xmf3Scale; }

	float GetWidth() { return m_nWidth * m_xmf3Scale.x; }
	float GetLength() { return m_nLength * m_xmf3Scale.z; }
};