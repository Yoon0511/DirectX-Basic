CGameFramework------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CreateDirect3DDevice()
-정의-
디바이스 COM객체를 만들어 객체 내부의 함수들을 이용해 하드웨어 디바이스인 그래픽 카드를
소프트웨어 디바이스로 표현하고 다룰 수 있도록 디바이스를 생성하는 함수

-내용-
우선 DirectX보다 저수준인 DXGI가 그래픽 카드, 모니터 열거, 프리젠트 등을 관리하는데
여기서 DXGI의 Factory를 생성하면 Factory 인터페이스 클래스가 제공하는 함수 중에
열거된 Adapter의 정보를 가져올 수 있고 가져온 Adapter로 Adapter정보와 필요하다면 해당 Adapter와 연결된 열거된 Output도 가져올 수 있음
결국 Adapter를 통해 우리가 직접 다룰 수 있는 Direct3D 함수인 Device 인터페이스 객체를 생성할 수 있다.
중요한 것은 Factory를 먼저 생성해야 Factory내부 함수를 통해 다른 인터페이스 클래스를 가져올 수 있다.

만약 열거된 Adapter가 없다면 윈도우가 지원하는 그래픽 출력 라이브러리인 WRAP를 통해 가상 어뎁터를 만들 수도 있다.

디바이스 인터페이스가 만들어 졌다면 CheckFeatureSupport, CreateFence를 통해 디바이스의 다양한 지원(다중 샘플링, ...)을 설정 가능하고 펜스를 생성하여 CPU와 GPU의 동기화를 지원해준다.

CreateCommandQueueAndList()
-정의-
명령 큐, 명령 리스트의 생성과 명령 리스트의 명령들이 저장될 명령 할당자를 생성하는 함수

-내용-
우선 명령 큐를 생성하기 위해서는 어떤 명령 큐 구조(우선순위, Nodemask)를 만들지 CommandQueueDesc을 통해 미리 설정 후
디바이스 인터페이스 내부 함수인 CreateCommandQueue를 통해 CommandQueue를 생성한다.

명령 할당자는 명령을 저장할 수 있는 메모리를 할당받는 것이며 디바이스 인터페이스 내부 함수인 CreateCommandAllocator를 통해 바로 생성 가능하다
명령 할당자는 당연히 재사용 가능하며 Reset()함수를 통해 메모리를 재사용 할 수 있다. 다만 실행중인 명령 리스트가 없어야 한다.
명령 할당자는 하나의 명령 리스트를 Open할 수 있고 Close가 되어야 다음 명령 리스트를 쓸 수 있다. 즉, 한번에 하나씩 접근 가능하다.

명령 리스트도 디바이스 인터페이스 내부 함수인 CreateCommandList를 통해 생성 가능하며 함수 인자로 어떤 명령 할당자에 할당할지 CommandAllocator 포인터가 필요하다(주로 하나를 재사용 함.)
명령 리스트를 생성하게 되면 Open(명령을 추가할 수 있는) 상태가 된다.
명령 리스트가 Close(명령을 추가할 수 없는) 상태가 되면 더 이상 명령을 추가할 수 없다.

CreateSwapChain()
-정의-
클라이언트 화면 영역에 나타나는 출력 창의 내용을 DXGI를 통해 전환하는 함수

-내용-
우선 화면 전환을 하기위한 정보를 가진 DXGI_SWAP_CHAIN_DESC이 필요하고
출력 창의 높이/너비 값, 출력 형식, 전환 형식, 다중 샘플링 등을 설정하여 이전에 만든 DXGI의 Factory 내부 함수
CreateSwapChain()를 통해 SwapChain 인터페이스 객체가 만들어진다. 인자로는 CommandQueue와 DXGI_SWAP_CHAIN_DESC이 필요한데
이를 통해 만들어진 IDXGISwapChain은 FrameAdavance에서 CPU와 GPU가 동기화된 이후에 IDXGISwapChain->Present()를 하게되면 후면 버퍼내용이 전면 버퍼로 이동하게 된다.

전체/창모드를 지원하려면 DXGI_SWAP_CHAIN_FULLSCREEN_DESC이 추가로 필요하고 DXGI의 Factory 내부 함수로 CreateSwapChainForHwnd()를 사용하게 된다.
또 내부 함수인 MakeWindowAssociation을 통해 DXGI_MWA_NO_ALT_ENTER로 Alt+Enter키를 누를 시 전체/창모드의 전환을 막을 수 있다.

CreateRtvAndDsvDescriptorHeap()
-정의-
렌더 타겟과 깊이-스텐실의 서술자 힙을 생성하는 함수

-내용-
기본적으로 리소스들이 파이프라인에 연결되기 위해서는 View가 필요하다. 에초에 직접 리소스를 만들 수 있지만 쉐이더 함수와 리소스를 연결하려면 View를 통해 Set하는 함수밖에 없으며
쉐이더가 리소스에 대한 정보들을 이해하려면 결국 추가적인 정보인 Root Signature가 필요하다. 이는 쉐이더 함수가 바깥에 있는 View의 데이터를 설명하기 위한 정보이다.
따라서 Constant Buffer, Shader Resource, Unordered Access, Sampler, Render Target, Depth Stencil와 같은 리소스들은 View를 만들기 위해 반드시 선행하여 DescriptorHeap을 만들어야 한다.

D3D12_DESCRIPTOR_HEAP_DESC를 통해 NumDescriptors-필요한 서술자 개수, Type, Flags, NodeMask에 대한 정보를 갖는 Desc을 만들고
이를 이용해 RtvDescriptorHeap과 DsvDescriptorHeap을 만든다.
위 Desc의 Type은 리소스를 구분짓는 단락이기 때문에 반드시 리소스에 맞게 구분지어야 한다.(TYPE_CBV_SRV_UAV / TYPE_SAMPLER / TYPE_RTV / TYPE_DSV)
렌더 타겟. 즉, 여러개의 후면 버퍼를 갖는 RtvDescriptorHeap은 NumDescriptors가 후면 버퍼의 개수가 되어야 하고 Type은 D3D12_DESCRIPTOR_HEAP_TYPE_RTV가 된다.
깊이-스텐실은 하나만 가지면 되기 때문에 NumDescriptors는 1개가 되고 Type은 D3D12_DESCRIPTOR_HEAP_TYPE_DSV가 되어야 한다.

GetDescriptorHandleIncrementSize()함수를 통해 서술자 힙의 원소 크기를 알아낼 수 있으며 이를 통해 해당 Decriptor의 주소와 Descriptor의 크기를 안다면 각 원소에 접근이 가능하게 된다.(인자에는 서술자힙의 type이 들어감)

CreateRenderTargetViews()
-정의-
후면 버퍼의 관한 리소스 View를 만드는 함수

-내용-
Device와 Command List의 각각의 함수들 중 CPU 핸들 또는 GPU 핸들을 넘겨주어야 하는 함수가 존재함
Device의 CreateRenderTargetView함수는 CPU핸들을 넘겨주어야 하므로
CPUDescriptorHandle이 필요하고 이는 이미 만든 RtvDescriptorHeap의 시작위치를 알려주는 GetCPUDescriptorHandleForHeapStart()함수를 통해 시작 주소를 넘겨받는다.

CreateSwapChain()함수에서 생성한 후면 버퍼의 개수만큼 루프를 돌고 dxgiSwapChain()함수의 GetBuffer를 통해 해당 후면 버퍼의 정보를 리소스 포인터에게 넘겨준다. (즉, 리소스 생성)
Device의 CreateRenderTargetView()함수에서 해당 리소스와 CPUDescriptorHandle을 통해 해당하는 서술자 힙의 위치에 리소스를 저장하게 된다.
이후 CPUDescriptorHandle위치를 저장한 RtvDescriptorIncrementSize만큼 넘겨주면서 루프를 반복한다.

CreateDepthStencilView()
-정의-
깊이-스텐실 관한 리소스 View를 만드는 함수

-내용-
우선 View를 생성하기 전에 리소스를 만들어야 하기 때문에
Device의 CreateCommittedResource()함수를 이용해 리소스를 만든다.

CreateCommittedResource의 인자로 HeapProperties(힙의 유형, 힙에 대한 CPU-페이지 속성, 힙에 대한 메모리 풀 등), Heap_Flag,
ResouceDesc(리소스 정보 - Alignment, 가로/세로 크기, 깊이 또는 배열의 크기, 밉맵 레벨, 리소스 형식, 다중 샘플링 등),
Resource_States(리소스 사용 용도), ClearValue(리소스를 최적의 방법으로 초기화할 값 -> 초기화 값을 설정하지 않으면 런타임이 느려질 수 있다) 순으로 나열된다.

위 내용의 설정값들이 들어가게 되며 렌더 타겟과 마찬가지로 Device의 CreateDepthStencilView()함수에게
CPU 핸들을 넘겨주어야 하기 때문에 DsvCPUDescriptorHandle이 필요하고 이는 DsvDescriptorHeap의 시작위치인 GetCPUDescriptorHandleForHeapStart()함수를 통해 시작 주소를 넘겨 받는다.

WaitForGpuComplete()
-정의-
Fence를 통해 Cpu와 Gpu를 동기화하는 함수

-내용-
이 함수에 들어갈 때마다 nFenceValue값을 증가시키고 pd3dFence를 nFenceValue의 값으로 설정하는데 CommandQueue의 Signal함수를 사용한다.
이는 CommandQueue에 명령이 모두 실행되면 Signal의 명령이 실행이 된다.
즉, 모든 명령이 실행되고 GPU의 할 일이 끝났을 때 pd3dFence의 값이 nFenceValue값으로 설정되고
SetEventOnCompletion함수는 Windows Api에서 제공하는 동기화 객체를 통해서 운영체제가 알아서 기다리게 하고 CPU가 다른 작업을 할 수 있도록 하는 함수라 이후 Signal명령이 실행되면 이벤트가 발생하여 CPU와 GPU의 동기화를 하게 한다.

FrameAdvance()
-정의-
프레임 진행을 위한 함수

-내용-
프로세스 입력, 애니메이션, 리소스 상태, 랜더링을 관리

	ProcessInput()
	-정의-
	입력에 대한 처리를 하는 함수

	-내용-
	pass

	AnimateObjects()
	-정의-
	애니메이션 표현을 위한 함수
	
	-내용-
	pass

	SetPipelineAndRendering()
	-정의-
	파이프라인 설정과 랜더링에 관한 함수

	-내용-
	명령 할당자를 재사용하기 위해 CommandAllocator를 Reset한 후에 CommandList도 Reset을 한다.
	기본적으로 전이장벽을 이용하므로 이전상태와 이후상태를 설정해야 한다.
	파이프라인과 리소스의 연결을 위해 리소스 장벽을 사용하기 위해 D3D12_RESOURCE_BARRIER를 설정한다. (전이/겹침/무순서 장벽, 리소스 상태 등)
	리소스 장벽을 설정을 완료했다면(특히 리소스 상태를 적절히 적용했다면) CommandList를 통해 파이프라인 설정이 가능하다.
	기본적으로 파이프라인 설정은 Rtv와 Dsv의 Clear서술자 그리고 고정 파이프라인인 OM(출력병합)에 RederTargets을 연결해야한다.
	CommandList에 명령들을 모두 추가하였다면 리소스 장벽의 이전/이후상태를 다시 알맞게 변경해주고 마지막으로 Close를 통해서 CommandList를 CommandQueue에 추가해준다.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------