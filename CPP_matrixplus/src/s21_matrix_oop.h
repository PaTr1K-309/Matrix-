#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21_matrix_oop {
class S21Matrix {
 private:
  /******** Переменные класса ********/
  int rows_, cols_;
  double** matrix_;

  /******** Приватные методы ********/
  void AllocateMemory();
  void InitializeMatrix();
  void CopyValues(const S21Matrix& other);
  bool IsMatrixSameDimension(S21Matrix matrix) const;
  bool IsMatrixSquare();
  void swap(S21Matrix& first, S21Matrix& second) noexcept;
  S21Matrix Minor(int ex_row, int ex_col);
  void DeleteMemory();

 public:
  /******** Конструкторы ********/
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  /******** Деструкторы ********/
  ~S21Matrix();
  /******** Публичные методы ********/
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  /******** Дополнительные публичные методы ********/
  void SetMatrix(const std::vector<std::vector<double>>& values);
  void PrintMatrix();
  int getRows();
  int getCols();
  void setRows(int new_rows);
  void setCols(int new_cols);

  /******** Перегрузка операторов ********/
  double& operator()(int row, int col);
  double operator()(int row, int col) const;
  bool operator==(const S21Matrix& other) const;
  bool operator!=(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num) const;
};
}  // namespace s21_matrix_oop
#endif  // S21_MATRIX_OOP_H_