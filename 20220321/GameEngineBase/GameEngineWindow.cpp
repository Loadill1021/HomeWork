#include "GameEngineWindow.h"

//static �����ϱ� ����
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();
LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // �����츦 �����ϰ� ��� 
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
GameEngineWindow::GameEngineWindow() 
    :hInst_(nullptr)
{
}
void GameEngineWindow::Off()
{
    WindowOn_ = false;
}
GameEngineWindow::~GameEngineWindow() 
{
    //���� ������ذ� �ƴ϶�� �� ��������Ѵ�.

}
void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // ������ Ŭ���� ���
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;//��� ��Ÿ�Ϸ� ���������
    wcex.lpfnWndProc = MessageProcess;//�Լ������� �̰� �־��ָ� Os�� �˾Ƽ� ȣ��
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;//�츮 ���μ����� �ڵ�
    wcex.hIcon = nullptr;//������
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//Ŀ��
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);//����
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";//������ Ŭ�����̸�
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);//������Ŭ���� ���
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    
    if (nullptr != hInst_)
    {
        MsgBoxAssert("�����츦 2�� ������ �߽��ϴ�.");
        return;
    }
    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    HDC_ = GetDC(hWnd_);
    
}
void GameEngineWindow::ShowGameEngineWindow()
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ� ȭ�鿡 ����Ҽ� �����ϴ�.");
    }
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}
