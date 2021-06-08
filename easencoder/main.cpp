#include "../Encoder/Encoder.h"
#include <windows.h>
#include <windowsx.h>
#include <new>
#include <string>
#include <future>
#define ID_BUTTON1 0x8801
#define ID_BUTTON2 0x8802

struct AppStateInfo
{

};

struct globals
{

};

DWORD WINAPI playback()
{
    return PlaySound(L"pcm.wav", NULL, SND_SYNC | SND_NODEFAULT);
}

inline AppStateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    AppStateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}

void OnResize(HWND hwnd)
{
    SetWindowPos(hwnd, NULL, NULL, NULL, 600, 300, SWP_NOMOVE | SWP_NOOWNERZORDER);
}

void OnCommand(HWND hwnd, int cmdID, HWND hwndCtl, UINT codeNotify)
{
    switch(cmdID)
    {
        case ID_BUTTON1:
        {
            DWORD threadID;
            HANDLE thread = CreateThread(nullptr, 0, playback, nullptr, 0, &threadID);
        }

        case ID_BUTTON2:
        {
            std::string alert = "ZCZC-WXR-TOR-0234-2342-3423-56675-74554-4234467+0015-1231212-12345678";
            Encoder encoder;
            encoder.encode(alert, 1, 7, 0, 2, 0, 1);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmID = LOWORD(wParam);
    AppStateInfo* AppState;

    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_COMMAND,    OnCommand);

        case WM_CREATE:
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam)
            AppState = reinterpret_cast<AppStateInfo*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)AppState);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
        {
            OnResize(hwnd);
            break;
        }

        default:
            GetAppState(hwnd);

    }
    else
    {
        AppState = GetAppState(hwnd);
    }
    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    if (uMsg == WM_PAINT)
    {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);

        return 0;
    }
    if (uMsg == WM_SIZE)
    {
        OnResize(hwnd);
    }
    if (uMsg == WM_COMMAND)
    {
        WORD wmid = LOWORD(wParam);
        WORD wmEvent = HIWORD(wParam);

        if (wmEvent == BN_CLICKED)
        {
            if (wmid == ID_BUTTON1)
            {
                HANDLE myhandle;
                DWORD mythreadid;
                myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)playback, 0, 0, &mythreadid);
            }
            if (wmid == ID_BUTTON2)
            {
                std::string alert = "ZCZC-WXR-TOR-0234-2342-3423-56675-74554-4234467+0015-1231212-12345678";
                Encoder e;
                e.encode(alert, 1, 7, 0, 2, 0, 1);
            }
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void CreateButtons(HWND hwnd)
{
    CreateWindowW(L"BUTTON", L"Encode", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 220, 100, 30, hwnd, (HMENU)ID_BUTTON2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
     CreateWindowW(L"BUTTON", L"Play Alert", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120, 220, 100, 30, hwnd, (HMENU)ID_BUTTON1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"easencoder";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    AppStateInfo* CurrentAppState;
    CurrentAppState = new (std::nothrow) AppStateInfo;

    HWND hwnd = CreateWindowEx( 0, CLASS_NAME, L"pendec Interface",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZE | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 300, nullptr, nullptr, hInstance, pState);
    CreateButtons(hwnd);

    if (hwnd == nullptr || pState == nullptr)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
