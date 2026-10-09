#pragma once
template <typename T>
class Matrix{
private:
	T** array = nullptr;
	int rows, cols;

private:
	void create(int rows, int cols);
	void del();

public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	~Matrix();

	void show();
	void fill();
	void fill(int data);

	void resize(int rows, int cols);

	int get_rows() const;
	int get_cols() const;

	bool is_one_size(const Matrix& matrix) const;
	bool can_mult(const Matrix& matrix) const;
	bool is_null() const;
	bool is_square() const;
	bool is_diagonal() const;
	bool is_singular() const;
	bool is_symmetric() const;

	bool operator== (const Matrix& other) const;
	bool operator!= (const Matrix& other) const;

	Matrix<T> operator+(const Matrix& other) const;
	Matrix<T> operator-(const Matrix& other) const;
	Matrix<T> operator*(const int data) const;
	Matrix<T> operator*(const Matrix& other) const;
	Matrix<T>& operator=(const Matrix& other);

	T& at(int rows, int cols);
	T get(int rows, int cols);

	Matrix& transposition();

};

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
	create(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other): rows(rows), cols(cols), array(nullptr) {
	create(other.rows, other.cols);
	for (int i = 0; i < other.rows; i++){
		for (int j = 0; j < other.cols; ++j) {
			this->array[i][j] = other.array[i][j];
		}
	}
}

template <typename T>
Matrix<T>::~Matrix() {
	del();
}

template <typename T>
void Matrix<T>::create(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
	array = new T* [rows];
	for (int i = 0; i < rows; i++)
	{
		array[i] = new T[cols];
	}
}

template <typename T>
void Matrix<T>::del(){
	if (array == nullptr) return;
	for (int i = 0; i < rows; i++)
	{
		delete[](array[i]);
	}
	delete[](array);
	array = nullptr;
}

template <typename T>
int Matrix<T>::get_rows() const { return rows; }

template <typename T>
int Matrix<T>::get_cols() const  { return cols; }

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
void Matrix<T>::resize(int rows, int cols) {
	del();
	create(rows, cols);
}

template <typename T>
bool Matrix<T>::is_one_size(const Matrix& other) const {
	return this->rows == other.rows &&
		this->cols == other.cols;
}

template <typename T>
bool Matrix<T>::can_mult(const Matrix& other) const {
	return this->cols == other.rows;
}

template <typename T>
bool Matrix<T>::is_null() const {
	bool flag = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; ++j) {
			if (array[i][j] != (T)NULL) return false;
		}
	}
	return true;
}

template <typename T>
bool Matrix<T>::is_square() const {
	return rows == cols;
}

template<typename T>
bool Matrix<T>::is_diagonal() const {
	if (rows != cols) return false;

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (i == j) continue;
			if (array[i][j] != NULL) return false;
		}
	}
	return true;
}

template <typename T>
bool Matrix<T>::is_singular() const {
	if (rows != cols) return false;

	for (int i = 0; i < rows; i++) {
		if (array[i][i] != 1) return false;
	}
	return true;
}

template <typename T>
bool Matrix<T>::is_symmetric() const {
	if (rows != cols) return false;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) continue;
			if (array[i][j] != array[j][i]) return false;
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

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
	if (!can_mult(other)) { throw std::invalid_argument("cannot mult"); }
	Matrix matrix(this->rows, other.cols);
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < other.cols; ++j) {
			matrix.array[i][j] = 0;
			for (int k = 0; k < cols; k++)
			{
				matrix.array[i][j] += this->array[i][k] * other.array[k][j];
			}
		}
	}
	return matrix;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other){
	if (this == &other) { return *this; }

	Matrix temp(other);

	std::swap(this->rows, temp.rows);
	std::swap(this->cols, temp.cols);
	std::swap(this->array, temp.array);

	return *this;
}

template <typename T>
T& Matrix<T>::at(int rows, int cols) {
	if (this->rows > rows && this->cols > cols) return array[rows][cols];
	else throw std::invalid_argument("out of the range");
}

template <typename T>
T Matrix<T>::get(int rows, int cols) {
	if (this->rows > rows && this->cols > cols) return array[rows][cols];
	else throw std::invalid_argument("out of the range");
}

template <typename T>
Matrix<T>& Matrix<T>::transposition() {
	Matrix temp(cols, rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.array[j][i] = this->array[i][j];
		}
	}

	std::swap(this->rows, temp.rows);
	std::swap(this->cols, temp.cols);
	std::swap(this->array, temp.array);

	return *this;
}