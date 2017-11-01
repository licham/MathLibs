#pragma once

#include <vector>

namespace ml {

	template<typename T>
	class Matrix {

	public:
		Matrix();
		Matrix(const Matrix &other);
		Matrix(const std::vector<T> &vector);
		Matrix(const size_t &rows, const size_t &cols);
		Matrix(const std::pair<size_t, size_t> &size);
		Matrix(const std::vector<std::vector<T>> &matrix);
		Matrix(const size_t &rows, const size_t &cols, const T &value);

		void						setRow(const size_t &row, const std::vector<T> &vector);
		void						setCol(const size_t &col, const std::vector<T> &vector);

		std::pair<size_t, size_t>	getSize();
		std::vector<T>				getRow(const size_t &row);
		std::vector<T>				getCol(const size_t &col);
		Matrix<T>					getMinor(const size_t &row, const size_t &col);
		Matrix<T>					getInverse();
		Matrix<T>					getTranspose();
		T							getDeterminant();

		std::vector<T>				eraseRow(const size_t &row);
		std::vector<T>				eraseCol(const size_t &col);

		std::vector<T>&				operator[](const size_t &row);
		Matrix<T>					operator*(const T &value);
		Matrix<T>					operator*(const Matrix<T> &other);
		Matrix<T>					operator*(const std::vector<T> &vector);
		Matrix<T>					operator*(const std::vector<std::vector<T>> &matrix);
		Matrix<T>					operator/(const T &value);
		Matrix<T>					operator/(const Matrix<T> &other);
		Matrix<T>					operator/(const std::vector<std::vector<T>> &matrix);
		Matrix<T>					operator+(const T &value);
		Matrix<T>					operator+(const Matrix<T> &other);
		Matrix<T>					operator+(const std::vector<std::vector<T>> &matrix);
		Matrix<T>					operator-(const T &value);
		Matrix<T>					operator-(const Matrix<T> &other);
		Matrix<T>					operator-(const std::vector<std::vector<T>> &matrix);
		bool						operator==(const Matrix<T> &other);

	private:
		std::vector<std::vector<T>> matrix;
		std::pair<size_t, size_t>	size;
		T							det;
		bool						det_calc;
	};

	template<typename T>
	inline Matrix<T>::Matrix() {
		det_calc = false;
	}

	template<typename T>
	inline Matrix<T>::Matrix(const size_t & rows, const size_t & cols) : Matrix<T>(std::make_pair(rows, cols)) {
	}

	template<typename T>
	inline Matrix<T>::Matrix(const size_t & rows, const size_t & cols, const T & value) : Matrix<T>(std::make_pair(rows, cols)) {
		for (auto &vec : matrix) {
			for (auto &val : vec) {
				val = value;
			}
		}
	}

	template<typename T>
	inline Matrix<T>::Matrix(const std::pair<size_t, size_t>& size) : Matrix<T>() {
		this->size = size;
		matrix.resize(size.first);
		for (auto &vec : matrix) {
			vec.resize(size.second);
		}
	}

	template<typename T>
	inline Matrix<T>::Matrix(const Matrix & other) : Matrix<T>(other.getSize()) {
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				matrix[i][j] = other[i][j];
			}
		}
		det = other.getDeterminant();
		det_calc = true;
	}

	template<typename T>
	inline Matrix<T>::Matrix(const std::vector<T>& vector) : Matrix<T>(vector.size(), 1) {
		for (size_t i = 0; i < size.first; ++i) {
			matrix[i][0] = vector[i];
		}
	}

	template<typename T>
	inline Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrix) : Matrix<T>() {
		size = std::make_pair(matrix.size(), matrix[0].size());
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				this->matrix[i][j] = matrix[i][j];
			}
		}
	}

	template<typename T>
	inline void Matrix<T>::setRow(const size_t & row, const std::vector<T> &vector) {
		for (size_t i = 0; i < size.second; ++i) {
			matrix[row][i] = vector[i];
		}
		det_calc = false;
	}

	template<typename T>
	inline void Matrix<T>::setCol(const size_t & col, const std::vector<T> &vector) {
		for (size_t i = 0; i < size.first; ++i) {
			matrix[i][col] = vector[i];
		}
		det_calc = false;
	}

	template<typename T>
	inline std::pair<size_t, size_t> Matrix<T>::getSize() {
		return size;
	}

	template<typename T>
	inline std::vector<T> Matrix<T>::getRow(const size_t & row) {
		return matrix[row];
	}

	template<typename T>
	inline std::vector<T> Matrix<T>::getCol(const size_t & col) {
		std::vector<T> temp(size.first);
		for (size_t i = 0; i < size.first; ++i) {
			temp[i] = matrix[i][col];
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::getMinor(const size_t & row, const size_t & col) const {
		Matrix<T> matrix(*this);
		matrix.eraseRow(row);
		matrix.eraseCol(col);
		return matrix;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::getInverse() const {
		Matrix<T> temp(size);
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				temp[i][j] = getMinor(j, i).getDeterminant() / det * ((i + j) % 2 == 0 ? 1 : -1);
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::getTranspose() const {
		Matrix<T> temp(size.second, size.first);
		for (size_t i = 0; i < size.second; ++i) {
			for (size_t j = 0; j < size.first; ++j) {
				temp[i][j] = matrix[j][i];
			}
		}
		return temp;
	}

	template<typename T>
	inline T Matrix<T>::getDeterminant() {
		if (det_calc) {
			return determinant;
		}
		if (size.first == 1) return matrix[0][0];
		double res = 0;
		for (size_t i = 0; i < size.first; ++i) {
			res += matrix[i][0] * getMinor(i, 0).getDeterminant() * (i % 2 == 0 ? 1 : -1);
		}
		determinant = res;
		det_calc = true;
		return res;
	}

	template<typename T>
	inline std::vector<T> Matrix<T>::eraseRow(const size_t & row) {
		std::vector<T> temp = matrix[row];
		matrix.erase(matrix.begin() + row);
		det_calc = false;
		--size.second;
		return temp;
	}

	template<typename T>
	inline std::vector<T> Matrix<T>::eraseCol(const size_t & col) {
		std::vector<T> temp(size.first);
		for (size_t i = 0; i < size.first; ++i) {
			temp[i] = matrix[i][col];
			matrix[i].erase(matrix[i].begin() + col);
		}
		det_calc = false;
		--size.first;
		return temp;
	}

	template<typename T>
	inline std::vector<T>& Matrix<T>::operator[](const size_t & row) {
		return &matrix[row];
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator*(const T & value) const {
		Matrix<T> temp(*this);
		for (auto &vec : temp) {
			for (auto &val : vec) {
				val *= value;
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
		Matrix<T> temp(size.first, other.getSize().second);
		for (size_t i = 0; i < temp.getSize().first; i++) {
			for (size_t j = 0; j < temp.getSize().second; j++) {
				for (size_t k = 0; k < size.second; k++) {
					temp[i][j] += matrix[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator*(const std::vector<T>& vector) const {
		return *this * Matrix<T>::Matrix(vector);
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator*(const std::vector<std::vector<T>>& matrix) const {
		return *this * Matrix<T>::Matrix(matrix);
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator/(const T & value) const {
		Matrix<T> temp(*this);
		for (auto &vec : temp) {
			for (auto &val : vec) {
				val /= value;
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator/(const Matrix<T>& other) const {
		return *this * other.getInverse();
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator/(const std::vector<std::vector<T>>& matrix) const {
		return *this / Matrix<T>::Matrix(matrix);
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator+(const T & value) const {
		Matrix<T> temp(*this);
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				temp[i][j] += value;
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
		Matrix<T> temp(size);
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				temp[i][j] = matrix[i][j] + other[i][j];
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator+(const std::vector<std::vector<T>>& matrix) const {
		return *this + Matrix<T>::Matrix(matrix);
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator-(const T & value) const {
		Matrix<T> temp(*this);
		for (auto &vec : temp) {
			for (auto &val : vec) {
				val -= value;
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
		Matrix<T> temp(size);
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				temp[i][j] = matrix[i][j] - other[i][j];
			}
		}
		return temp;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::operator-(const std::vector<std::vector<T>>& matrix) const {
		return *this - Matrix<T>::Matrix(matrix);
	}

	template<typename T>
	inline bool	Matrix<T>::operator==(const Matrix<T> &other) const {
		if (other.getSize() != size) {
			return false;
		}
		for (size_t i = 0; i < size.first; ++i) {
			for (size_t j = 0; j < size.second; ++j) {
				if (matrix[i][j] != other[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

}


