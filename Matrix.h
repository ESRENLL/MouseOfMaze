#pragma once

// 행렬을 표현하는 클래스
// 연산자 오버로딩과 크기재조정 기능

class Matrix
{
private:
	int** mat;
	int rows;
	int cols;
	int colsCap;
	int initVal;
public:
	Matrix(int rows=0, int cols=0, int** arr=0) : mat(0), rows(0), cols(0), colsCap(0), initVal(0) {
		resize(rows, cols);
		if(arr!=0){
			for(int row=0; row<rows; ++row){
				for(int col=0; col<cols; ++col)
					mat[row][col] = arr[row][col];
			}
		}
	}
	~Matrix() {
		free();
	}
	void resize(int rows, int cols);
	void resizeRows(int rows);
	void resizeCols(int cols);
	void free();
	int getRows();
	int getCols();
	void setInitValue(int val);
	int getInitValue();
	Matrix& operator=(const Matrix& other);
	int* operator[](int n);
	Matrix operator*(const Matrix& other); // sumproduct
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator/(const Matrix& other);
};