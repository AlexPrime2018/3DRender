#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include <fstream>
#include "Matrix.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<> CumulativeAT;
	Matrix<> InitialVertices;
	double I[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
public:
	Model2D() : Vertices(), Edges(), CumulativeAT(), InitialVertices() {}
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
		Vertices(Vertices), Edges(Edges), InitialVertices(Vertices), CumulativeAT(3, 3, I) {}

	double GetVerticesX(int n) { if (n <= Vertices.GetCols()) return Vertices(1, n); }
	double GetVerticesY(int n) { if (n <= Vertices.GetCols()) return Vertices(2, n); }

	void SetVertices(Matrix<> V) { Vertices = V; }

	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }

	void Apply(Matrix<> AT) {
		CumulativeAT = Vertices;
		Vertices = AT * Vertices;
	}
};

#endif // ! MODEL2D_H