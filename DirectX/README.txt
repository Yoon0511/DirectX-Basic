CGameFramework------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CreateDirect3DDevice()
-����-
����̽� COM��ü�� ����� ��ü ������ �Լ����� �̿��� �ϵ���� ����̽��� �׷��� ī�带
����Ʈ���� ����̽��� ǥ���ϰ� �ٷ� �� �ֵ��� ����̽��� �����ϴ� �Լ�

-����-
�켱 DirectX���� �������� DXGI�� �׷��� ī��, ����� ����, ������Ʈ ���� �����ϴµ�
���⼭ DXGI�� Factory�� �����ϸ� Factory �������̽� Ŭ������ �����ϴ� �Լ� �߿�
���ŵ� Adapter�� ������ ������ �� �ְ� ������ Adapter�� Adapter������ �ʿ��ϴٸ� �ش� Adapter�� ����� ���ŵ� Output�� ������ �� ����
�ᱹ Adapter�� ���� �츮�� ���� �ٷ� �� �ִ� Direct3D �Լ��� Device �������̽� ��ü�� ������ �� �ִ�.
�߿��� ���� Factory�� ���� �����ؾ� Factory���� �Լ��� ���� �ٸ� �������̽� Ŭ������ ������ �� �ִ�.

���� ���ŵ� Adapter�� ���ٸ� �����찡 �����ϴ� �׷��� ��� ���̺귯���� WRAP�� ���� ���� ��͸� ���� ���� �ִ�.

����̽� �������̽��� ����� ���ٸ� CheckFeatureSupport, CreateFence�� ���� ����̽��� �پ��� ����(���� ���ø�, ...)�� ���� �����ϰ� �潺�� �����Ͽ� CPU�� GPU�� ����ȭ�� �������ش�.

CreateCommandQueueAndList()
-����-
���� ť, ���� ����Ʈ�� ������ ���� ����Ʈ�� ���ɵ��� ����� ���� �Ҵ��ڸ� �����ϴ� �Լ�

-����-
�켱 ���� ť�� �����ϱ� ���ؼ��� � ���� ť ����(�켱����, Nodemask)�� ������ CommandQueueDesc�� ���� �̸� ���� ��
����̽� �������̽� ���� �Լ��� CreateCommandQueue�� ���� CommandQueue�� �����Ѵ�.

���� �Ҵ��ڴ� ������ ������ �� �ִ� �޸𸮸� �Ҵ�޴� ���̸� ����̽� �������̽� ���� �Լ��� CreateCommandAllocator�� ���� �ٷ� ���� �����ϴ�
���� �Ҵ��ڴ� �翬�� ���� �����ϸ� Reset()�Լ��� ���� �޸𸮸� ���� �� �� �ִ�. �ٸ� �������� ���� ����Ʈ�� ����� �Ѵ�.
���� �Ҵ��ڴ� �ϳ��� ���� ����Ʈ�� Open�� �� �ְ� Close�� �Ǿ�� ���� ���� ����Ʈ�� �� �� �ִ�. ��, �ѹ��� �ϳ��� ���� �����ϴ�.

���� ����Ʈ�� ����̽� �������̽� ���� �Լ��� CreateCommandList�� ���� ���� �����ϸ� �Լ� ���ڷ� � ���� �Ҵ��ڿ� �Ҵ����� CommandAllocator �����Ͱ� �ʿ��ϴ�(�ַ� �ϳ��� ���� ��.)
���� ����Ʈ�� �����ϰ� �Ǹ� Open(������ �߰��� �� �ִ�) ���°� �ȴ�.
���� ����Ʈ�� Close(������ �߰��� �� ����) ���°� �Ǹ� �� �̻� ������ �߰��� �� ����.

CreateSwapChain()
-����-
Ŭ���̾�Ʈ ȭ�� ������ ��Ÿ���� ��� â�� ������ DXGI�� ���� ��ȯ�ϴ� �Լ�

-����-
�켱 ȭ�� ��ȯ�� �ϱ����� ������ ���� DXGI_SWAP_CHAIN_DESC�� �ʿ��ϰ�
��� â�� ����/�ʺ� ��, ��� ����, ��ȯ ����, ���� ���ø� ���� �����Ͽ� ������ ���� DXGI�� Factory ���� �Լ�
CreateSwapChain()�� ���� SwapChain �������̽� ��ü�� ���������. ���ڷδ� CommandQueue�� DXGI_SWAP_CHAIN_DESC�� �ʿ��ѵ�
�̸� ���� ������� IDXGISwapChain�� FrameAdavance���� CPU�� GPU�� ����ȭ�� ���Ŀ� IDXGISwapChain->Present()�� �ϰԵǸ� �ĸ� ���۳����� ���� ���۷� �̵��ϰ� �ȴ�.

��ü/â��带 �����Ϸ��� DXGI_SWAP_CHAIN_FULLSCREEN_DESC�� �߰��� �ʿ��ϰ� DXGI�� Factory ���� �Լ��� CreateSwapChainForHwnd()�� ����ϰ� �ȴ�.
�� ���� �Լ��� MakeWindowAssociation�� ���� DXGI_MWA_NO_ALT_ENTER�� Alt+EnterŰ�� ���� �� ��ü/â����� ��ȯ�� ���� �� �ִ�.

CreateRtvAndDsvDescriptorHeap()
-����-
���� Ÿ�ٰ� ����-���ٽ��� ������ ���� �����ϴ� �Լ�

-����-
�⺻������ ���ҽ����� ���������ο� ����Ǳ� ���ؼ��� View�� �ʿ��ϴ�. ���ʿ� ���� ���ҽ��� ���� �� ������ ���̴� �Լ��� ���ҽ��� �����Ϸ��� View�� ���� Set�ϴ� �Լ��ۿ� ������
���̴��� ���ҽ��� ���� �������� �����Ϸ��� �ᱹ �߰����� ������ Root Signature�� �ʿ��ϴ�. �̴� ���̴� �Լ��� �ٱ��� �ִ� View�� �����͸� �����ϱ� ���� �����̴�.
���� Constant Buffer, Shader Resource, Unordered Access, Sampler, Render Target, Depth Stencil�� ���� ���ҽ����� View�� ����� ���� �ݵ�� �����Ͽ� DescriptorHeap�� ������ �Ѵ�.

D3D12_DESCRIPTOR_HEAP_DESC�� ���� NumDescriptors-�ʿ��� ������ ����, Type, Flags, NodeMask�� ���� ������ ���� Desc�� �����
�̸� �̿��� RtvDescriptorHeap�� DsvDescriptorHeap�� �����.
�� Desc�� Type�� ���ҽ��� �������� �ܶ��̱� ������ �ݵ�� ���ҽ��� �°� ��������� �Ѵ�.(TYPE_CBV_SRV_UAV / TYPE_SAMPLER / TYPE_RTV / TYPE_DSV)
���� Ÿ��. ��, �������� �ĸ� ���۸� ���� RtvDescriptorHeap�� NumDescriptors�� �ĸ� ������ ������ �Ǿ�� �ϰ� Type�� D3D12_DESCRIPTOR_HEAP_TYPE_RTV�� �ȴ�.
����-���ٽ��� �ϳ��� ������ �Ǳ� ������ NumDescriptors�� 1���� �ǰ� Type�� D3D12_DESCRIPTOR_HEAP_TYPE_DSV�� �Ǿ�� �Ѵ�.

GetDescriptorHandleIncrementSize()�Լ��� ���� ������ ���� ���� ũ�⸦ �˾Ƴ� �� ������ �̸� ���� �ش� Decriptor�� �ּҿ� Descriptor�� ũ�⸦ �ȴٸ� �� ���ҿ� ������ �����ϰ� �ȴ�.(���ڿ��� ���������� type�� ��)

CreateRenderTargetViews()
-����-
�ĸ� ������ ���� ���ҽ� View�� ����� �Լ�

-����-
Device�� Command List�� ������ �Լ��� �� CPU �ڵ� �Ǵ� GPU �ڵ��� �Ѱ��־�� �ϴ� �Լ��� ������
Device�� CreateRenderTargetView�Լ��� CPU�ڵ��� �Ѱ��־�� �ϹǷ�
CPUDescriptorHandle�� �ʿ��ϰ� �̴� �̹� ���� RtvDescriptorHeap�� ������ġ�� �˷��ִ� GetCPUDescriptorHandleForHeapStart()�Լ��� ���� ���� �ּҸ� �Ѱܹ޴´�.

CreateSwapChain()�Լ����� ������ �ĸ� ������ ������ŭ ������ ���� dxgiSwapChain()�Լ��� GetBuffer�� ���� �ش� �ĸ� ������ ������ ���ҽ� �����Ϳ��� �Ѱ��ش�. (��, ���ҽ� ����)
Device�� CreateRenderTargetView()�Լ����� �ش� ���ҽ��� CPUDescriptorHandle�� ���� �ش��ϴ� ������ ���� ��ġ�� ���ҽ��� �����ϰ� �ȴ�.
���� CPUDescriptorHandle��ġ�� ������ RtvDescriptorIncrementSize��ŭ �Ѱ��ָ鼭 ������ �ݺ��Ѵ�.

CreateDepthStencilView()
-����-
����-���ٽ� ���� ���ҽ� View�� ����� �Լ�

-����-
�켱 View�� �����ϱ� ���� ���ҽ��� ������ �ϱ� ������
Device�� CreateCommittedResource()�Լ��� �̿��� ���ҽ��� �����.

CreateCommittedResource�� ���ڷ� HeapProperties(���� ����, ���� ���� CPU-������ �Ӽ�, ���� ���� �޸� Ǯ ��), Heap_Flag,
ResouceDesc(���ҽ� ���� - Alignment, ����/���� ũ��, ���� �Ǵ� �迭�� ũ��, �Ӹ� ����, ���ҽ� ����, ���� ���ø� ��),
Resource_States(���ҽ� ��� �뵵), ClearValue(���ҽ��� ������ ������� �ʱ�ȭ�� �� -> �ʱ�ȭ ���� �������� ������ ��Ÿ���� ������ �� �ִ�) ������ �����ȴ�.

�� ������ ���������� ���� �Ǹ� ���� Ÿ�ٰ� ���������� Device�� CreateDepthStencilView()�Լ�����
CPU �ڵ��� �Ѱ��־�� �ϱ� ������ DsvCPUDescriptorHandle�� �ʿ��ϰ� �̴� DsvDescriptorHeap�� ������ġ�� GetCPUDescriptorHandleForHeapStart()�Լ��� ���� ���� �ּҸ� �Ѱ� �޴´�.

WaitForGpuComplete()
-����-
Fence�� ���� Cpu�� Gpu�� ����ȭ�ϴ� �Լ�

-����-
�� �Լ��� �� ������ nFenceValue���� ������Ű�� pd3dFence�� nFenceValue�� ������ �����ϴµ� CommandQueue�� Signal�Լ��� ����Ѵ�.
�̴� CommandQueue�� ������ ��� ����Ǹ� Signal�� ������ ������ �ȴ�.
��, ��� ������ ����ǰ� GPU�� �� ���� ������ �� pd3dFence�� ���� nFenceValue������ �����ǰ�
SetEventOnCompletion�Լ��� Windows Api���� �����ϴ� ����ȭ ��ü�� ���ؼ� �ü���� �˾Ƽ� ��ٸ��� �ϰ� CPU�� �ٸ� �۾��� �� �� �ֵ��� �ϴ� �Լ��� ���� Signal������ ����Ǹ� �̺�Ʈ�� �߻��Ͽ� CPU�� GPU�� ����ȭ�� �ϰ� �Ѵ�.

FrameAdvance()
-����-
������ ������ ���� �Լ�

-����-
���μ��� �Է�, �ִϸ��̼�, ���ҽ� ����, �������� ����

	ProcessInput()
	-����-
	�Է¿� ���� ó���� �ϴ� �Լ�

	-����-
	pass

	AnimateObjects()
	-����-
	�ִϸ��̼� ǥ���� ���� �Լ�
	
	-����-
	pass

	SetPipelineAndRendering()
	-����-
	���������� ������ �������� ���� �Լ�

	-����-
	���� �Ҵ��ڸ� �����ϱ� ���� CommandAllocator�� Reset�� �Ŀ� CommandList�� Reset�� �Ѵ�.
	�⺻������ �����庮�� �̿��ϹǷ� �������¿� ���Ļ��¸� �����ؾ� �Ѵ�.
	���������ΰ� ���ҽ��� ������ ���� ���ҽ� �庮�� ����ϱ� ���� D3D12_RESOURCE_BARRIER�� �����Ѵ�. (����/��ħ/������ �庮, ���ҽ� ���� ��)
	���ҽ� �庮�� ������ �Ϸ��ߴٸ�(Ư�� ���ҽ� ���¸� ������ �����ߴٸ�) CommandList�� ���� ���������� ������ �����ϴ�.
	�⺻������ ���������� ������ Rtv�� Dsv�� Clear������ �׸��� ���� ������������ OM(��º���)�� RederTargets�� �����ؾ��Ѵ�.
	CommandList�� ���ɵ��� ��� �߰��Ͽ��ٸ� ���ҽ� �庮�� ����/���Ļ��¸� �ٽ� �˸°� �������ְ� ���������� Close�� ���ؼ� CommandList�� CommandQueue�� �߰����ش�.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------