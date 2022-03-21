#include "GameEngineWindow.h"

//static 변수니까 전역
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();
LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // 윈도우를 종료하고 모든 
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
    //내가 만들어준게 아니라면 다 지워줘야한다.

}
void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    // 윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;//어떻게 스타일로 만들어질지
    wcex.lpfnWndProc = MessageProcess;//함수포인터 이걸 넣어주면 Os가 알아서 호출
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;//우리 프로세스의 핸들
    wcex.hIcon = nullptr;//아이콘
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//커서
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);//배경색
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";//윈도우 클래스이름
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);//윈도우클래스 등록
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
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
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다 화면에 출력할수 없습니다.");
    }
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}
