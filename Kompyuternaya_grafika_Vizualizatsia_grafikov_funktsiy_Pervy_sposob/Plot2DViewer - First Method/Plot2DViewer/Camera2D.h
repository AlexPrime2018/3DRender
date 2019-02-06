#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// ������� ���������� ������ ������� ������� ����
	int W, H;							// ���������� ������� ������� ����		
	inline int Tx(double X, int borderX) { return (1.0 / 2) * (X + borderX) * (W / borderX); }
	inline int Ty(double Y, int borderY) { return (-1.0 / 2) * (Y - borderY) * ( H / borderY); }
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return 0;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return 0;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return 0.0;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return 0.0;
	}
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
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
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void DrawLineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, posX, posY, NULL);
		LineTo(dc, X, Y);
		posX = X;
		posY = Y;
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{
		MoveTo(W, H / 2);
		DrawLineTo(dc, -W, H / 2);
		MoveTo(W / 2, H);
		DrawLineTo(dc, W / 2, -H);
		// ��������� ������������ ����
	}
};

#endif CAMERA_2D_H
