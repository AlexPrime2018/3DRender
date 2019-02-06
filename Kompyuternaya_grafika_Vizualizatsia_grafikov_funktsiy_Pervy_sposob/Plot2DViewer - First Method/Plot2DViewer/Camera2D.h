#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// Мировые координаты границ рабочей области окна
	int W, H;							// Разрешение рабочей области окна		
	inline int Tx(double X, int borderX) { return (1.0 / 2) * (X + borderX) * (W / borderX); }
	inline int Ty(double Y, int borderY) { return (-1.0 / 2) * (Y - borderY) * ( H / borderY); }
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return 0;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return 0;
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return 0.0;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return 0.0;
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		InvalidateRect(NULL, NULL, TRUE);
	}
	void SetResolution(HWND hWnd)
	{
		RECT Rect;
		GetWindowRect(hWnd, &Rect);
		L = Rect.left;
		T = Rect.top;
		B = Rect.bottom;
		R = Rect.right;
		H = B - T;
		W = R - L;
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void DrawLineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, posX, posY, NULL);
		LineTo(dc, X, Y);
		posX = X;
		posY = Y;
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{
		MoveTo(W, H / 2);
		DrawLineTo(dc, -W, H / 2);
		MoveTo(W / 2, H);
		DrawLineTo(dc, W / 2, -H);
		// Отрисовка координатных осей
	}
};

#endif CAMERA_2D_H
