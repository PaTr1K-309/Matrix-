#include "s21_matrix_oop.h"

using namespace s21_matrix_oop;
using std::swap;

// Конструкторы S21Matrix
S21Matrix::S21Matrix() : S21Matrix(2, 2) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "Ошибка создания матрицы! Количество строк и столбцов должно быть не "
        "менее 1!");
  }
  AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_{other.rows_}, cols_{other.cols_} {
  AllocateMemory();
  CopyValues(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { DeleteMemory(); }

// Основные публичные методы S21Matrix
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!IsMatrixSameDimension(other))
    throw std::range_error(
        "S21Matrix Class => Ошибка метода SumMatrix(const S21Matrix& other): "
        "Матрицы разных размеров!");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!IsMatrixSameDimension(other))
    throw std::range_error(
        "S21Matrix Class => Ошибка метода SubMatrix(const S21Matrix& other): "
        "Матрицы разных размеров!");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::range_error("Матрицы не совместимы для умножения");
  }
  S21Matrix result_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result_matrix(i, j) = 0;
      for (int k = 0; k < cols_; ++k) {
        result_matrix(i, j) += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result_matrix;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result_matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result_matrix.matrix_[j][i] = matrix_[i][j];
  return result_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!IsMatrixSquare())
    throw std::range_error(
        "S21Matrix Class => Ошибка метода CalcComplements(): Ожидается "
        "квадратная матрица!");
  S21Matrix result_matrix(rows_, cols_);
  if (rows_ == 1)
    result_matrix(0, 0) = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = this->Minor(i, j);
        result_matrix(i, j) = pow(-1, i + j) * minor.Determinant();
      }
    }
  }
  return result_matrix;
}

double S21Matrix::Determinant() {
  if (!IsMatrixSquare())
    throw std::range_error(
        "S21Matrix Class => Ошибка метода Determinant(): Ожидается квадратная "
        "матрица!");
  double result = 0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  else {
    for (int i = 0; i < cols_; i++) {
      S21Matrix minored_matrix(Minor(0, i));
      result += pow((-1), i) * matrix_[0][i] * minored_matrix.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determ = Determinant();
  if (!Determinant() || !IsMatrixSquare())
    throw std::range_error(
        "S21Matrix Class => Ошибка метода InverseMatrix(): Определитель "
        "матрицы не найден либо неверный размер исходной матрицы для "
        "вычисления обратной матрицы!");
  S21Matrix result_matrix(rows_, cols_);
  if (rows_ == 1)
    result_matrix.matrix_[0][0] = 1.0 / matrix_[0][0];
  else {
    result_matrix = CalcComplements().Transpose();
    result_matrix.MulNumber(1 / determ);
  }
  return result_matrix;
}

// Операторы S21Matrix
double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range(
        "Ошибка! Значение индекса за пределами размера матрицы!");
  }
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix temp(other);
    swap(*this, temp);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) swap(*this, other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result_matrix(*this);
  result_matrix.SumMatrix(other);
  return result_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result_matrix(*this);
  result_matrix.SubMatrix(other);
  return result_matrix;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result_matrix(*this);
  result_matrix.MulNumber(num);
  return result_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result_matrix(*this);
  result_matrix.MulMatrix(other);
  return result_matrix;
}

// Дополнительные общедоступные методы S21Matrix
// Установка значений матрицы
void S21Matrix::SetMatrix(const std::vector<std::vector<double>> &values) {
  if ((int)values.size() != rows_)
    throw std::invalid_argument("Ошибка: Несоответствие количества строк!");
  for (const auto &row : values)
    if ((int)row.size() != cols_)
      throw std::invalid_argument(
          "Ошибка: Несоответствие количества столбцов!");
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = values[i][j];
}

// Вывод матрицы в консоль
void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) std::cout << matrix_[i][j] << "\t";
    std::cout << std::endl;
  }
}

// Методы get & set для получения и установки значений приватных полей
int S21Matrix::getRows() { return rows_; }
int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(int new_rows) {
  if (new_rows < 1) {
    throw std::length_error("Количество строк должно быть > 0");
  }
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    int min = std::min(rows_, new_rows);
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::setCols(int new_cols) {
  if (new_cols < 1) {
    throw std::length_error("Количество столбцов должно быть > 0");
  }
  S21Matrix tmp(rows_, new_cols);
  int min = std::min(cols_, new_cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < min; ++j) {
      tmp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(tmp);
}

// Дополнительные методы S21Matrix
void S21Matrix::AllocateMemory() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::CopyValues(const S21Matrix &other) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}

void S21Matrix::swap(S21Matrix &obj1, S21Matrix &obj2) noexcept {
  using std::swap;
  swap(obj1.rows_, obj2.rows_);
  swap(obj1.cols_, obj2.cols_);
  swap(obj1.matrix_, obj2.matrix_);
}

bool S21Matrix::IsMatrixSameDimension(S21Matrix matrix) const {
  return (rows_ == matrix.rows_ && cols_ == matrix.cols_);
}

bool S21Matrix::IsMatrixSquare() { return (cols_ == rows_); }

S21Matrix S21Matrix::Minor(int delete_row, int delete_col) {
  S21Matrix minored_matrix(rows_ - 1, cols_ - 1);
  for (int i = 0, minor_row = 0; i < rows_; i++)
    if (i != delete_row) {
      for (int j = 0, minor_col = 0; j < cols_; j++)
        if (j != delete_col) {
          minored_matrix.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      minor_row++;
    }
  return minored_matrix;
}

void S21Matrix::DeleteMemory() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}
