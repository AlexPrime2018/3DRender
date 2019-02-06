#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double L, double R, double B, double T) : Camera2D(L, R, B, T)
	{
	}
	void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);
		MoveTo(Tx(-5, 6), Ty(f(-5), 6));
		for (double i = -5; i < 5; i+=0.1)
		{
			DrawLineTo(dc, Tx(i, 6), Ty(f(i), 6));
			MoveTo(Tx(i, 6), Ty(f(i), 6));
		}
		// ���������� ������� ������� f
		// ����� ������������ � �������� ��������� ������� f ���������� ��� ������� �������:
		// f(x);
	}
};

#endif SCENE_2D_H
