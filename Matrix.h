#pragma once
template <typename T>
class Matrix{
private:
	T** array;
	int rows, cols;

private:
	void create(int rows, int cols);

public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	~Matrix();

	void show();
	void fill();
	void fill(int data);

	int get_rows();
	int get_cols();

	bool is_one_size(const Matrix& matrix) const;
	bool is_null();

	bool operator== (const Matrix& other) const;
	bool operator!= (const Matrix& other) const;

	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const int data) const;

};

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
	create(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) {
	create(other.rows, other.cols);
}

template <typename T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < rows; i++)
	{
		delete[](array[i]);
	}
	delete[](array);
}

template <typename T>
int Matrix<T>::get_rows() { return rows; }

template <typename T>
int Matrix<T>::get_cols() { return cols; }

template <typename T>
void Matrix<T>::create(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	array = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		array[i] = new int[cols];
	}
}

template <typename T>
void Matrix<T>::show() {
	std::cout << "rows: " << rows << "\tcols: " << cols << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			std::cout << array[i][j] << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

template <typename T>
void Matrix<T>::fill() {
	srand(time(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			array[i][j] = rand() % 10;
		}
	}
}

template <typename T>
void Matrix<T>::fill(int data) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			array[i][j] = data;
		}
	}
}

template <typename T>
bool Matrix<T>::is_one_size(const Matrix& other) const {
	return this->rows == other.rows &&
		this->cols == other.cols;
}

template <typename T>
bool Matrix<T>::is_null() {
	bool flag = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			if (array[i][j] != NULL) return false;
		}
	}
	return true;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
	if (!is_one_size(other)) return false;
	bool flag = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			if (array[i][j] != other.array[i][j]) return false;
		}
	}
	return true;
}

template <typename T>
bool Matrix<T>::operator!= (const Matrix& other) const {
	if (!is_one_size(other)) return true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			if (array[i][j] != other.array[i][j]) return true;
		}
	}
	return false;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
	Matrix matrix(rows, cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			matrix.array[i][j] = this->array[i][j] + other.array[i][j];
		}
	}
	return matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
	Matrix matrix(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			matrix.array[i][j] = this->array[i][j] - other.array[i][j];
		}
	}
	return matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const int data) const {
	Matrix matrix(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			matrix.array[i][j] = this->array[i][j] * data;
		}
	}
	return matrix;
}