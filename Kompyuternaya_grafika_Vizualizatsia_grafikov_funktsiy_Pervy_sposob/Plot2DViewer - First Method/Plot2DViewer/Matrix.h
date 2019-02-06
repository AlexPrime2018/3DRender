#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int rows, cols;
	Cell **cells;
	void AllocateCells(int, int);
	void FreeCells();
public:
	Matrix() : rows(0), cols(0), cells(nullptr) {}	// ����������� �� ���������
	Matrix(const Matrix&);					// ����������� �����������
	Matrix(int, int);							// ����������� ������� �������
	Matrix(int, int, Cell*);						// ����������� ������� �� ������
	~Matrix();								// ����������

	int GetCols() { return cols; }

	Cell &operator()(int i, int j) { return cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// ���������� ��������� ������������
	Matrix  operator + (const Matrix&);		// �������� ������
	Matrix  operator - (const Matrix&);		// ��������� ������
	Matrix  operator * (const Matrix&);		// ��������� ������

	friend istream& operator >> <> (istream&, Matrix&);			// ���������� ��������� >> ��� ����� �������
	friend ostream& operator << <> (ostream&, const Matrix&);	// ���������� ��������� << ��� ������ �������
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows, M.cols);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int row, int col)
{
	AllocateCells(row, col);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int row, int col, Cell* list)
{
	int k = 0;
	AllocateCells(row, col);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			cells[i][j] = list[k];
			k++;
		}
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (rows != M.rows && cols != M.cols)
	{
		FreeCells();
		AllocateCells(M.rows, M.cols);
	}
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i<rows; i++)
			for (int j = 0; j<cols; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i<rows; i++)
			for (int j = 0; j<cols; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	Matrix<Cell> res(*this);
	Matrix<Cell> result(res.rows, M.cols);
	for (int i = 0; i < res.rows; i++)
		for (int j = 0; j < M.cols; j++)
			for (int k = 0; k < res.cols; k++)
				result.cells[i][j] += res.cells[i][k] * M.cells[k][j];
	return result;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int row, int col)
{
	cells = new Cell*[row];
	for (int i = 0; i<row; i++)
		cells[i] = new Cell[col];
	rows = row;
	cols = col;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i<rows; i++)
		delete[] cells[i];
	delete[] cells;
	cells = NULL;
	rows = 0;
	cols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i<M.size; i++)
		for (int j = 0; j<M.size; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i<M.rows; i++)
	{
		fo << "  ";
		for (int j = 0; j<M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H