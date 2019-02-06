#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Matrix.h"
#include "Model2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double L, double R, double B, double T, Matrix<> V, Matrix<int> E) : Camera2D(L, R, B, T)
	{
		model.SetVertices(V);
		model.SetEdges(E);
	}

	Model2D model;

	void Render(HDC dc) {
		Matrix<int> E = model.GetEdges();
		for (int i = 1; i <= model.GetColsEdges(); i++) {
			MoveTo(Tx(model.GetVerticesX(E(1, i)), 6), Ty(model.GetVerticesY(E(1, i)), 6));
			DrawLineTo(dc, Tx(model.GetVerticesX(E(2, i)), 6), Ty(model.GetVerticesY(E(2, i)), 6));
		}
	}

	void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);
		/*MoveTo(Tx(-5, 6), Ty(f(-5), 6));
		for (double i = -5; i < 5; i+=0.1)
		{
			DrawLineTo(dc, Tx(i, 6), Ty(f(i), 6));
			MoveTo(Tx(i, 6), Ty(f(i), 6));
		}*/
		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
};

#endif SCENE_2D_H
