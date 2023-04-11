// InterestingProjects.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "InterestingProjects.h"
#include <cmath>
#include <stdlib.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Swapping(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculator(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_INTERESTINGPROJECTS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTERESTINGPROJECTS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INTERESTINGPROJECTS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_INTERESTINGPROJECTS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_TOOLS_CALCULATOR:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CALC), hWnd, Calculator);
                break;
            case ID_TOOLS_SWAP:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SWAP), hWnd, Swapping);
                break;
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
INT_PTR CALLBACK Swapping(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{   
    char secondText[100];
    char firstText[100];
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
        else if (LOWORD(wParam) == IDC_BUTTON1) {
            GetDlgItemText(hDlg, IDC_EDIT2, firstText, 100);
            GetDlgItemText(hDlg, IDC_EDIT4, secondText, 100);
            SetDlgItemText(hDlg, IDC_EDIT4, firstText);
            SetDlgItemText(hDlg, IDC_EDIT2, secondText);
        }
        else if (LOWORD(wParam) == IDC_BUTTON2) {
            int firstInt = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
            int secondInt = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, TRUE);
            SetDlgItemInt(hDlg, IDC_EDIT3, firstInt, TRUE);
            SetDlgItemInt(hDlg, IDC_EDIT1, secondInt, TRUE);
        }
        break;
    }
    return (INT_PTR)FALSE;
}
class ValuesClass {
private:
    int firstIntt, secondIntt,temp_result;
public:
    void setResult(int result) {
        temp_result = result;
    }
    int getResult() {
        return temp_result;
    }
    void setFirst(int integer) {
        firstIntt = integer;

    }
    int getFirst() {
        
        return firstIntt;
    }
    void setSecond(int integer) {
        secondIntt = integer;
    }
    int getSecond() {
        
        return secondIntt;
    }
};


INT_PTR CALLBACK Calculator(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{   
    ValuesClass val;

    
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
        
        else if (LOWORD(wParam) == IDC_BUTTON_ADDITION){
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            val.setSecond(GetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE));
            val.setResult(val.getFirst()+val.getSecond());
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_SUBSTRACTION){
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            val.setSecond(GetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE));
            val.setResult(val.getFirst() - val.getSecond());
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_MULTIPLICATION) {
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            val.setSecond(GetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE));
            val.setResult(val.getFirst() * val.getSecond());
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_DEVIDE) {
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            val.setSecond(GetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE));
            val.setResult(val.getFirst() / val.getSecond());
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_SQUARE) {
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            
            val.setResult(sqrt(val.getFirst()));
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_PROC) {
            val.setFirst(GetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE));
            val.setSecond(GetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE));
            val.setResult(val.getFirst() % val.getSecond());
            SetDlgItemInt(hDlg, IDC_EDIT_RESULT, val.getResult(), TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_CLEAR) {
            SetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, NULL, TRUE);
            SetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, NULL, TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_RANDOM) {
            
            SetDlgItemInt(hDlg, IDC_EDIT_FIRSTINPUT, rand() % 100 + 1, TRUE);
            SetDlgItemInt(hDlg, IDC_EDIT_SECONDINPUT, rand() % 100 + 1, TRUE);
        }
        break;
    }
    return (INT_PTR)FALSE;
}