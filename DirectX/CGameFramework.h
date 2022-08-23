#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Timer.h"

class CGameFramework {
private:
	CGameTimer m_GameTimer;
	_TCHAR m_pszFrameRate[50];

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;		//DXGI ���丮 �������̽��� ���� �������̴�.
	IDXGISwapChain3* m_pdxgiSwapChain;	//���� ü�� �������̽��� ���� �������̴�. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ��ϴ�.
	ID3D12Device* m_pd3dDevice;			//Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�.

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;	//MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�.

	static const UINT m_nSwapChainBuffers = 2;	//���� ü���� �ĸ� ������ �����̴�
	UINT m_nSwapChainBufferIndex;				//���� ���� ü���� �ĸ� ���� �ε����̴�.

	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];	//���� Ÿ�� ����
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;						//������ �� �������̽� ������
	UINT m_nRtvDescriptorIncrementSize;									//���� Ÿ�� ������ ������ ũ���̴�.

	ID3D12Resource* m_pd3dDepthStencilBuffer;		//����-���ٽ� ����
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;	//������ �� �������̽� ������
	UINT m_nDsvDescriptorIncrementSize;				//����-���ٽ� ������ ������ ũ���̴�.

	ID3D12CommandQueue* m_pd3dCommandQueue;			//��� ť
	ID3D12CommandAllocator* m_pd3dCommandAllocator;	//��� �Ҵ���
	ID3D12GraphicsCommandList* m_pd3dCommandList;	//��� ����Ʈ �������̽� �������̴�.

	ID3D12PipelineState* m_pd3dPipelineState;	//�׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� �������̴�.

	ID3D12Fence* m_pd3dFence;	//�潺 �������̽� ������
	UINT64 m_nFenceValues[m_nSwapChainBuffers];		//�潺�� ��
	HANDLE m_hFenceEvent;		//�̺�Ʈ �ڵ��̴�.

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);	//�����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ��̴�(�� �����찡 �����Ǹ� ȣ��ȴ�).
	void OnDestroy();

	void ChangeSwapChainState();

	void CreateSwapChain();					//���� ü���� �����ϴ� �Լ��̴�.
	void CreateRtvAndDsvDescriptorHeaps();	//����̽��� �����ϴ� �Լ��̴�.
	void CreateDirect3DDevice();			//������ ���� �����ϴ� �Լ��̴�.
	void CreateCommandQueueAndList();		//��� ť/�Ҵ���/����Ʈ�� �����ϴ� �Լ��̴�.

	void CreateRenderTargetViews();	//���� Ÿ�� �並 �����ϴ� �Լ��̴�. 
	void CreateDepthstencilView();	//����-���ٽ� �並 �����ϴ� �Լ��̴�. 

	void BuildObjects();		//�������� �޽��� ���� ��ü�� �����ϴ� �Լ��̴�. 
	void ReleaseObjects();	//�������� �޽��� ���� ��ü�� �Ҹ��ϴ� �Լ��̴�. 

	void ProcessInput();		//�����ӿ�ũ�� �ٽ� �� ����� �Է��� �����ϴ� �Լ��̴�.
	void AnimateObjects();		//�����ӿ�ũ�� �ٽ� �� �ִϸ��̼��� �����ϴ� �Լ��̴�.
	void SetPipelineAndRendering();
	void FrameAdvance();		//�����ӿ�ũ�� �ٽ� �� �������� �����ϴ� �Լ��̴�.
	void WaitForGpuComplete();	//CPU�� GPU�� ����ȭ�ϴ� �Լ��̴�. 

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�.

public:
	void MoveToNextFrame();

	CScene* m_pScene;

	CCamera* m_pCamera = NULL;
};
