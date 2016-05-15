#include "Matrix.h"


void Matrix::resize(int rows, int cols) {
	resizeRows(rows);
	resizeCols(cols);
}
void Matrix::resizeRows(int rows){
	if(rows==0)
		free();
	else if(this->rows >= rows){
		for(int row=rows; row<this->rows; ++row)
			delete[] mat[row];
		this->rows = rows;
		return;
	}
	else{
		int** newMat = new int*[rows];
		for(int row=0; row<this->rows; ++row)
			newMat[row] = mat[row];
		for(int row=this->rows; row<rows; ++row)
			newMat[row] = new int[colsCap];
		mat = newMat;
		this->rows = rows;
	}
}
void Matrix::resizeCols(int cols){
	if(rows<=0 || this->cols>=cols) return;
	if(colsCap >= cols){
		for(int row=0; row<rows; ++row){
			for(int col=this->cols; col<cols; ++col){
				mat[row][col] = initVal;
			}
		}
		this->cols = cols;
	}
	else {
		colsCap = cols*3/2==1? 2 : cols*3/2;
		for(int row=0; row<rows; ++row){
			int* newRow = new int[colsCap];
			for(int col=0; col<this->cols; ++col)
				newRow[col] = mat[row][col];
			for(int col=this->cols; col<cols; ++col)
				newRow[col] = initVal;
			delete[] mat[row];
			mat[row] = newRow;
		}
		this->cols = cols;
	}
}
void Matrix::free() {
	if (rows <= 0) return;
	for (int row=0; rows<rows; ++rows)
		delete[] mat[row];
	delete[] mat;
	rows = 0;
	cols = 0;
	colsCap = 0;
	mat = 0;
}
int Matrix::getRows(){
	return rows;
}
int Matrix::getCols(){
	return cols;
}
void Matrix::setInitValue(int val){
	initVal = val;
}
int Matrix::getInitValue(){
	return initVal;
}
Matrix& Matrix::operator=(const Matrix& other) {
	this->resize(other.rows, other.cols);
	for (int row = 0; row<other.rows; ++row) {
		for (int col = 0; col<other.cols; ++col) {
			mat[row][col] = other.mat[row][col];
		}
	}
	return *this;
}
int* Matrix::operator[](int n){
	return mat[n];
}
Matrix Matrix::operator*(const Matrix& other) { // sumproduct
	Matrix ret(other.rows, other.cols);
	for (int row = 0; row<rows; ++row) {
		for (int col = 0; col<cols; ++col) {
			ret[row][col] = mat[row][col] * other.mat[row][col];
		}
	}
	return ret;
}
Matrix Matrix::operator+(const Matrix& other) {
	Matrix ret(other.rows, other.cols);
	for (int row = 0; row<rows; ++row) {
		for (int col = 0; col<cols; ++col) {
			ret[row][col] = mat[row][col] + other.mat[row][col];
		}
	}
	return ret;
}
Matrix Matrix::operator-(const Matrix& other) {
	Matrix ret(other.rows, other.cols);
	for (int row = 0; row<rows; ++row) {
		for (int col = 0; col<cols; ++col) {
			ret[row][col] = mat[row][col] - other.mat[row][col];
		}
	}
	return ret;
}
Matrix Matrix::operator/(const Matrix& other) {
	Matrix ret(other.rows, other.cols);
	for (int row = 0; row<rows; ++row) {
		for (int col = 0; col<cols; ++col) {
			ret[row][col] = mat[row][col] / other.mat[row][col];
		}
	}
	return ret;
}

std::pair<int, int> Matrix::getMinRowCol()
{
	if(rows<=0 || cols<=0) return std::make_pair(-1, -1);
	std::pair<int, int> ret(0, 0);
	int minVal = mat[0][0];
	for(int row=0; row<rows; ++row){
		for(int col=0; col<cols; ++col){
			if(minVal > mat[row][col]){
				minVal = mat[row][col];
				ret.first = row;
				ret.second = col;
			}
		}
	}
	return ret;
}
bool Matrix::isIn(int row, int col)
{
	return row>=0 && row<rows && col>=0 && col<cols;
}
