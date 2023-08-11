﻿// Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }

    XMFLOAT3 pos;
};

struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct WVP
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};

WVP wvp;

vector<VertexColor> vertices;
vector<UINT>    indices;

ID3D11Device*        device;         // 무언가를 만들 때 사용, CPU를 다루는 객체 
ID3D11DeviceContext* deviceContext;  // 무언가를 그릴 때 사용, GPU를 다루는 객체(RENDER, HDC)

IDXGISwapChain*         swapChain;         // 더블버퍼링을 구현하는 객체
ID3D11RenderTargetView* renderTargetView;  // 백버퍼를 관리하는 객체

//////////////////////////////////////////////////////////////////////////

ID3D11VertexShader* vertexShader;
ID3D11PixelShader*   pixelShader;

ID3D11InputLayout* inputLayout;

ID3D11Buffer* vertexBuffer;
ID3D11Buffer*  indexBuffer;

ID3D11Buffer*  constBuffer;

UINT stride = 0;
UINT offset = 0;

void Initialize();
void Render();
void Release();



HWND hWnd;

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

    Initialize();

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // TODO : Update. Render
            Render();
        }
    };

    Release();

    return (int)msg.wParam;
}



void Initialize()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1; // 백버퍼가 몇개 있나
    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // RGBA 8비트 * 4개 = 32비트, UNORM = Unsigned Normal = 0~1

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    swapChainDesc.OutputWindow = hWnd;

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.Windowed = true;

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG, // 속성
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );

    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr); // 랜더링 파이프라인의 Output Merge 단계

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width    = WIN_WIDTH;
    viewPort.Height   = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    deviceContext->RSSetViewports(1, &viewPort);


    //VertexShader
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


    ID3DBlob* vertexBlob; // blob : 파일정보를 불러와서 저장해놓은 객체
    D3DCompileFromFile
    (
        L"_Shader/VertexTutorial.hlsl",
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &vertexBlob,
        nullptr
    );

    device->CreateVertexShader
    (
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        nullptr,
        &vertexShader
    );

    D3D11_INPUT_ELEMENT_DESC layoutDesc[2] = {};

   layoutDesc[0].SemanticName         = "POSITION";
   layoutDesc[0].SemanticIndex        = 0;
   layoutDesc[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
   layoutDesc[0].InputSlot            = 0;
   layoutDesc[0].AlignedByteOffset    = 0;
   layoutDesc[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
   layoutDesc[0].InstanceDataStepRate = 0;

   layoutDesc[1].SemanticName         = "COLOR";
   layoutDesc[1].SemanticIndex        = 0;
   layoutDesc[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
   layoutDesc[1].InputSlot            = 0;
   layoutDesc[1].AlignedByteOffset    = 12;
   layoutDesc[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
   layoutDesc[1].InstanceDataStepRate = 0;



   device->CreateInputLayout
   (
       layoutDesc,
       ARRAYSIZE(layoutDesc),
       vertexBlob->GetBufferPointer(),
       vertexBlob->GetBufferSize(),
       &inputLayout
   );

   vertexBlob->Release();


   //PixelShader
   ID3DBlob* pixelBlob; 
   D3DCompileFromFile
   (
       L"_Shader/PixelTutorial.hlsl",
       nullptr,
       nullptr,
       "main",
       "ps_5_0",
       flags,
       0,
       &pixelBlob,
       nullptr
   );

   device->CreatePixelShader
   (
       pixelBlob->GetBufferPointer(),
       pixelBlob->GetBufferSize(),
       nullptr,
       &pixelShader
   );

   pixelBlob->Release();

   //Vertex
   // Vertex vertex(0.0f, 0.0f, 0.0f);
   
   vertices =
   {
       VertexColor({ -1.0f, +1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }),
       VertexColor({ +1.0f, +1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }),
       VertexColor({ -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }),
       VertexColor({ +1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }),

       VertexColor({ -1.0f, +1.0f, +1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }),
       VertexColor({ +1.0f, +1.0f, +1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }),
       VertexColor({ -1.0f, -1.0f, +1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }),
       VertexColor({ +1.0f, -1.0f, +1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }),
   };

   //VertexBuffer
   {
       D3D11_BUFFER_DESC bufferDesc = {};

       bufferDesc.ByteWidth           = sizeof(VertexColor) * vertices.size();
       bufferDesc.Usage               = D3D11_USAGE_DEFAULT; // 버퍼의 용도를 물어보는 것
       bufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
       bufferDesc.CPUAccessFlags      = 0;
       bufferDesc.MiscFlags           = 0;
       bufferDesc.StructureByteStride = 0;

       D3D11_SUBRESOURCE_DATA data;

       data.pSysMem = vertices.data(); // vector의 data함수는 주소값을 반환하는 함수

       device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
   }

   // IndexBuffer
   indices =
   {
       //Front
       0, 1, 2,
       2, 1, 3,

       //Right
       1, 5, 3,
       3, 5, 7,

       //Top
       0, 4, 1,
       1, 4, 5,

       //Left
       4, 0, 6,
       6, 0, 2,

       //Back
       5, 4, 7,
       7, 4, 6,

       //Bottom
       2, 3, 6,
       6, 3, 7
   };

   {
       D3D11_BUFFER_DESC bufferDesc = {};

       bufferDesc.ByteWidth           = sizeof(UINT) * indices.size();
       bufferDesc.Usage               = D3D11_USAGE_DEFAULT; // 버퍼의 용도를 물어보는 것
       bufferDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
       bufferDesc.CPUAccessFlags      = 0;
       bufferDesc.MiscFlags           = 0;
       bufferDesc.StructureByteStride = 0;

       D3D11_SUBRESOURCE_DATA data;

       data.pSysMem = indices.data(); // vector의 data함수는 주소값을 반환하는 함수

       device->CreateBuffer(&bufferDesc, &data, &indexBuffer);
   }

   //WVP

   wvp.world = XMMatrixIdentity();

   XMVECTOR eyePos   = XMVectorSet(+3.0f, +3.0f, -3.0f, +1.0f);
   XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +0.0f);
   XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

   wvp.view = XMMatrixLookAtLH(eyePos, focusPos, upVector);


   wvp.projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

     {
       D3D11_BUFFER_DESC bufferDesc = {};

       bufferDesc.ByteWidth           = sizeof(WVP);
       bufferDesc.Usage               = D3D11_USAGE_DEFAULT; // 버퍼의 용도를 물어보는 것
       bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
       bufferDesc.CPUAccessFlags      = 0;
       bufferDesc.MiscFlags           = 0;
       bufferDesc.StructureByteStride = 0;

       device->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
   }
}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

    //TODO : Render
    stride = sizeof(VertexColor);
    offset = 0;

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // vertex들의 연결 방식

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);


    deviceContext->DrawIndexed(indices.size(), 0, 0); // Rendering pipeLine 시작하는 지점 , 따라서 이 이후부터는 Rendering pipeLine의 순서에 맞춰 코드를 적어야함

    // WVP
    WVP data;

    data.world      = XMMatrixTranspose(wvp.world);
    data.view       = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0); //cbuffer로 실시간으로 정보를 보내주는 함수
    deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);


    static float angle = 0.0f;

    angle += 0.0001f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f); // Roll : 앞을 기준으로 회전 / Yaw : 세로를 기준으로 회전 / Pitch : 가로를 기준으로 회전
                                                                  // DX 기준 z축                DX 기준 y축                 DX 기준 x축
    ////////////////////

    swapChain->Present(0, 0);
}

void Release()
{
    device->Release();
    deviceContext->Release();
    swapChain->Release();
    renderTargetView->Release();
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
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

    RECT rect = { 0,0,WIN_WIDTH, WIN_HEIGHT };

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

  hWnd = CreateWindowW
    (
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, hInstance, nullptr
    );

    SetMenu(hWnd, nullptr);

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
