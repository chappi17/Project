#include "framework.h"
#include "Project.h"

// WIN_API
// 그리는 작업을 CPU에서 해줌

// DX11 (Direct Access)
// -> 목표 : 2D 게임엔진을 만든다.
// 업데이트는 CPU, Render는 GPU가 해준다.
// -> WINAPI : 1980 x 1080 = pixel들의 개수 -> 빨강혹은 초록... 
// 
// CPU : 어려운 계산을 직렬처리한다.
// GPU : 쉬운계산을 병렬처리하는데 특화되어있다.
// => ALU가 많기 때문에 픽셀 병렬 계산에 매우 효율적이다.

// DX 그래픽스
// 영화 촬영 = 게임 제작
// 카메라 / 카메라
// 감독 / 프로그래머
// 사운드 / 사운드매니저
// 조명 / Light
// 촬영장 / World
// 영화사 / 엔진

// 렌더링 파이프라인

// 외주를 맡기고 실질적인 공사 대표 뽑기
// 컴퓨터의 하드웨어 기능 점검, 리소스 할당
// -> 인력사무소장
Microsoft::WRL::ComPtr<ID3D11Device>               device;
// 세트장을 실질적으로 꾸며주는 연출가
// 렌더링 대상 결정
// -> 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 명령 지시
Microsoft::WRL::ComPtr<ID3D11DeviceContext>      deviceContext;
// DX의 인터페이스로써 1개 이상의 표면을 포함할 수 있다.
// 각각의 표면(버퍼, 텍스쳐)를 출력하기 전에 데이터를 보관한다.
Microsoft::WRL::ComPtr<IDXGISwapChain>           swapChain;
// 후면 버퍼를 가리키는 포인터
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

// 렌더링파이프라인 단계
Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer; // 정점들을 담아놓는 버퍼
Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayOut;

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView; // 판박이를 만들어서 가리키는 포인터
Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState; // 판박이를 붙여주는 사람


HWND hWnd;

struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
    XMFLOAT2 uv;
};

void InitDevice();
void Render();

// -> 내부를 들여다보지 말라
// => 하다보면 경험,통계 -> 이걸로 이해하라

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));

    MSG msg = {};

    // 생성
    InitDevice();

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 메인 루프
            Render();
        }
    }

    // 삭제

    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_PROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void InitDevice()
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // Numeartor / Denominator = 화면 프레임 갱신 속도
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true; // 창모드

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        nullptr,
        deviceContext.GetAddressOf()
    );

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {
            "POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,
            D3D11_INPUT_PER_VERTEX_DATA,0
        },

        {
            "COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,
            D3D11_INPUT_PER_VERTEX_DATA,0
        },   

        {
            "UV",0, DXGI_FORMAT_R32G32_FLOAT,0,28,
            D3D11_INPUT_PER_VERTEX_DATA,0
        }
    };

    UINT layoutSize = ARRAYSIZE(layout);

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob; // vertexShader를 만들 때 필요한 얘
    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr,
        "VS", "vs_5_0", flags, 0, vertexBlob.GetAddressOf(), nullptr);

    // Shader 정보 전달
    device->CreateInputLayout(layout, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), inputLayOut.GetAddressOf());

    device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr,
        vertexShader.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr,
        "PS", "ps_5_0", flags, 0, pixelBlob.GetAddressOf(), nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr,
        pixelShader.GetAddressOf());

    vector<Vertex> vertices;

    Vertex v;
    v.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    v.color = { 0.0f, 1.0f,0.0f,1.0f }; // 초록
    v.uv = { 0.0f, 0.0f };
    vertices.push_back(v);

    v.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    v.color = { 0.0f, 0.0f, 1.0f,1.0f }; // 파랑
    v.uv = { 1.0f, 1.0f };
    vertices.push_back(v);

    v.pos = { -0.5f, -0.5f, 0.0f }; // 왼쪽 아래
    v.color = { 1.0f, 0.0f,0.0f,1.0f }; // 빨강
    v.uv = { 0.0f, 1.0f };
    vertices.push_back(v);

    v.pos = { 0.5f, 0.5f, 0.0f }; // 오른쪽 위
    v.color = { 1.0f, 0.0f,0.0f,1.0f }; // 빨강
    v.uv = { 1.0f, 0.0f };
    vertices.push_back(v);

    v.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    v.color = { 0.0f, 0.0f, 1.0f,1.0f }; // 파랑
    v.uv = { 1.0f, 1.0f };
    vertices.push_back(v);

    v.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    v.color = { 0.0f, 1.0f,0.0f,1.0f }; // 초록
    v.uv = { 0.0f, 0.0f };
    vertices.push_back(v);


    // Vertex 버퍼 : Vertex
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * 6;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();

    device->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());

    ScratchImage image;
    LoadFromWICFile(L"Resource/Brotato/BackGround/Bro_Background.png", WIC_FLAGS_NONE, nullptr, image);

    CreateShaderResourceView(device.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        shaderResourceView.GetAddressOf());

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
}



void Render()
{
    FLOAT myColorR = 120.0f / 255.0f;
    FLOAT myColorG = 120.0f / 255.0f;
    FLOAT myColorB = 120.0f / 255.0f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    deviceContext->IASetInputLayout(inputLayOut.Get());

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());

    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

    deviceContext->Draw(6, 0);

    swapChain->Present(0, 0);
}