// Project3.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "Project3.h"
#include "Model3D.h"
#include <windowsx.h>
#include <glew.h>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE	hInst;								// Instancia actual
TCHAR		szTitle[MAX_LOADSTRING];			// Texto de la barra de título
TCHAR		szWindowClass[MAX_LOADSTRING];		// Nombre de clase de la ventana principal
Model3D*	model;								// Model 3D a renderizar


// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM				MyRegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void 				SetDCPixelFormat(HDC hDC);
void	 			EnableOpenGL(HWND hWnd);
void 				DisableOpenGL(HWND hWnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: colocar código aquí.
	MSG msg;
	HACCEL hAccelTable;
	HWND hWnd;

	model = new Model3D();

	// Inicializar cadenas globales
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PROJECT3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Realizar la inicialización de la aplicación:
	hWnd = InitInstance(hInstance, nCmdShow);
	if (hWnd == NULL)
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT3));

	EnableOpenGL(hWnd);

	// Bucle principal de mensajes:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	DisableOpenGL(hWnd);
	delete model;

	return (int)msg.wParam;
}


//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: registrar la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT3));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
//
//	HWND WINAPI CreateWindow(
//		_In_opt_ LPCTSTR   lpClassName,
//		_In_opt_ LPCTSTR   lpWindowName,
//		_In_     DWORD     dwStyle,
//		_In_     int       x,
//		_In_     int       y,
//		_In_     int       nWidth,
//		_In_     int       nHeight,
//		_In_opt_ HWND      hWndParent,
//		_In_opt_ HMENU     hMenu,
//		_In_opt_ HINSTANCE hInstance,
//		_In_opt_ LPVOID    lpParam
//		);
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Almacenar identificador de instancia en una variable global

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return NULL;
	}

	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

//
//  FUNCIÓN: SetDCPixelFormat(HDC hDC)
//
//  PROPÓSITO:  configurar el contexto gráfico.
//
void SetDCPixelFormat(HDC hDC)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		16,
		0,
		0,
		0,
		0,
		0, 0, 0
	};

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

//
//  FUNCIÓN: EnableOpenGL(HWND hWnd)
//
//  PROPÓSITO:  activar OpenGL.
//
void EnableOpenGL(HWND hWnd)
{
	RECT rect;
	HDC hDC;
	HGLRC hRC;

	hDC = GetDC(hWnd);
	SetDCPixelFormat(hDC);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	glewInit();
	SetTimer(hWnd, 101, 20, NULL);
	GetClientRect(hWnd, &rect);
	model->Initialize(rect.right, rect.bottom);
}

//
//  FUNCIÓN: DisableOpenGL(HWND hWnd)
//
//  PROPÓSITO:  desactivar OpenGL.
//
void DisableOpenGL(HWND hWnd)
{
	model->Finalize();
	KillTimer(hWnd, 101);
	HDC hDC = GetDC(hWnd);
	HGLRC hRC = wglGetCurrentContext();
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  procesar mensajes de la ventana principal.
//
//  WM_COMMAND	: procesar el menú de aplicación
//  WM_PAINT	: pintar la ventana principal
//  WM_DESTROY	: enviar un mensaje de finalización y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC = NULL;
	int xPos, yPos, button;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		break;
	case WM_KEYDOWN:
		//  if (wParam == VK_ESCAPE) PostQuitMessage(0);
		model->KeyboardAction(wParam);
		break;
	case WM_TIMER:
		model->TimerAction();
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		button = GET_XBUTTON_WPARAM(wParam);
		model->MouseAction(button, wParam, xPos, yPos);
		break;
	case WM_PAINT:
		model->RenderScene();
		SwapBuffers(hDC);
		ValidateRect(hWnd, NULL);
		break;
	case WM_SIZE:
		model->ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

