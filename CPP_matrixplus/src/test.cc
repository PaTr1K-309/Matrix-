#include <gtest/gtest.h>

/*#include <cstdio>
#include <fstream>
#include <iostream>*/

#include "s21_matrix_oop.h"

using namespace s21_matrix_oop;

/* ПРОВЕРКА РАБОТЫ КОНСТРУКТОРОВ */
TEST(CreateMatrix1, StandartConstructor) {
  S21Matrix matrix;
  matrix.setRows(2);
  matrix.setCols(2);
  ASSERT_TRUE(matrix.getRows() == 2);
  ASSERT_TRUE(matrix.getCols() == 2);
  matrix.setRows(3);
  matrix.setCols(4);
  ASSERT_TRUE(matrix.getRows() == 3);
  ASSERT_TRUE(matrix.getCols() == 4);
  EXPECT_THROW(matrix.setRows(0), std::length_error);
  EXPECT_THROW(matrix.setCols(0), std::length_error);
}

TEST(CreateMatrix2, ParameterConstructor) {
  ASSERT_NO_THROW(S21Matrix matrix(2, 2));
  EXPECT_THROW(S21Matrix matrix1(0, 0), std::invalid_argument);
}

TEST(CreateMatrix3, ConstructorWrongSize) {
  EXPECT_THROW(S21Matrix matrix(-1, 2), std::invalid_argument);
}

TEST(CreateMatrix4, MoveConstructor) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b = std::move(matrix_a));
}

TEST(CreateMatrix5, CopyConstructor) {
  S21Matrix matrix_a(2, 2);
  ASSERT_NO_THROW(S21Matrix matrix_b(matrix_a));
}

TEST(OperatorAssignment1, AssignOperatorWrongIndexes) {
  S21Matrix matrix_a(2, 2);
  EXPECT_THROW(matrix_a(3, 0) = 1, std::out_of_range);
  EXPECT_THROW(matrix_a.SetMatrix({{1, 2}, {4, 5}, {7, 8}}),
               std::invalid_argument);
}

TEST(OperatorAssignment2, AssignOperatorWrongIndexes) {
  S21Matrix matrix_a(2, 2);
  EXPECT_THROW(matrix_a.SetMatrix({{1, 2, 3}, {4, 5, 6}}),
               std::invalid_argument);
}

TEST(EqualMatrix, NonEqualMatrix) {
  S21Matrix matrix_a(1, 3);
  matrix_a.SetMatrix({{1, 2, 3}});
  matrix_a.PrintMatrix();
  S21Matrix matrix_b(2, 2);
  matrix_b.SetMatrix({{1, 2}, {3, 4}});
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(SumMatrix, SumNonEqualMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{1, 2}});
  matrix_b.SetMatrix({{1, 2}, {3, 4}});
  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::range_error);
}

TEST(SubMatrix, SubNonEqualMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{3, 2}});
  matrix_b.SetMatrix({{-7, 0}, {-3, 2}});
  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::range_error);
}

TEST(MulMatrix, MulNonEqualMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{3}, {-6.6}});
  matrix_b.SetMatrix({{-7, 0}, {-3.5, 2}});
  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::range_error);
}

TEST(OperatorSumMatrix, OperatorSumWithNonEqualSizesMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{1, 2}});
  matrix_b.SetMatrix({{1, 2}, {3, 4}});
  EXPECT_THROW(matrix_a += matrix_b, std::range_error);
}

TEST(OperatorSubMatrix, OperatorSubWithNonEqualSizesMatrix) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{3, 2}});
  matrix_b.SetMatrix({{-7, 0}, {-3, 2}});
  EXPECT_THROW(matrix_a -= matrix_b, std::range_error);
}

TEST(OperatorMulMatrix, OperatorMulWithNonEqualSizesMatrix) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);
  matrix_a.SetMatrix({{3}, {-6.6}});
  matrix_b.SetMatrix({{-7, 0}, {-3.5, 2}});
  EXPECT_THROW(matrix_a *= matrix_b, std::range_error);
}

TEST(OperatorEqual, Equality) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b;
  EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(InvalidRanges, OperatorsAndMethods) {
  S21Matrix matrix_a(3, 1);
  S21Matrix matrix_b(3, 2);
  matrix_a.SetMatrix({{3}, {-6.6}, {1.0}});
  matrix_b.SetMatrix({{1, 2}, {3, 4}, {5, 6}});
  EXPECT_THROW(matrix_b *= matrix_a, std::range_error);
  ASSERT_FALSE(matrix_b.EqMatrix(matrix_a));
  EXPECT_THROW(matrix_b.InverseMatrix(), std::range_error);
  EXPECT_THROW(matrix_b.Determinant(), std::range_error);
  EXPECT_THROW(matrix_b.CalcComplements(), std::range_error);
  EXPECT_NO_THROW(matrix_b *= 2);
  EXPECT_THROW(matrix_b += matrix_a, std::range_error);
  EXPECT_THROW(matrix_b -= matrix_a, std::range_error);
}

TEST(InverseMatrix, TestInversion) {
  S21Matrix matrix_a(4, 3);
  matrix_a.SetMatrix({{1, 2, 3}, {5, 6, 7}, {9, 10, 11}, {4, 8, 12}});
  EXPECT_THROW(matrix_a.InverseMatrix(), std::range_error);
}

TEST(PublicMethods, TestAllMethods) {
  S21Matrix matrix_a(3, 3), matrix_b(3, 3), result_matrix(3, 3),
      template_matrix(3, 3);
  matrix_a.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  matrix_b.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  // Сложение
  result_matrix = matrix_a;
  result_matrix.SumMatrix(matrix_b);
  template_matrix.SetMatrix({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Вычитание
  result_matrix = matrix_a;
  result_matrix.SubMatrix(matrix_b);
  template_matrix.SetMatrix({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Умножение
  result_matrix = matrix_a;
  result_matrix.MulMatrix(matrix_b);
  template_matrix.SetMatrix({{30, 36, 42}, {66, 81, 96}, {102, 126, 150}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Умножение число
  result_matrix = matrix_a;
  result_matrix = matrix_a * 2;
  template_matrix.SetMatrix({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  ASSERT_TRUE(result_matrix == template_matrix);
}

TEST(SimpleOperators, TestSimpleOperators) {
  S21Matrix matrix_a(3, 3), matrix_b(3, 3), result_matrix(3, 3),
      template_matrix(3, 3);
  matrix_a.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  matrix_b.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  // Сложение
  result_matrix = matrix_a + matrix_b;
  template_matrix.SetMatrix({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Вычитание
  result_matrix = matrix_a - matrix_b;
  template_matrix.SetMatrix({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Умножение
  result_matrix = matrix_a * matrix_b;
  template_matrix.SetMatrix({{30, 36, 42}, {66, 81, 96}, {102, 126, 150}});
  ASSERT_TRUE(result_matrix == template_matrix);
  // Умножение число
  result_matrix = matrix_a * 2;
  template_matrix.SetMatrix({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  ASSERT_TRUE(result_matrix == template_matrix);
}

TEST(Determinant, TestDeterminant) {
  S21Matrix matrix(3, 3);
  matrix.SetMatrix({{1, 0, 2}, {-1, 3, 4}, {-2, 1, 5}});
  ASSERT_EQ(matrix.Determinant(), 21);
  S21Matrix matrix_1(1, 1);
  matrix_1.SetMatrix({{1}});
  ASSERT_EQ(matrix_1.Determinant(), 1);
}

TEST(CalcComplements, TestCalc) {
  S21Matrix matrix(3, 3);
  S21Matrix template_matrix(3, 3);
  matrix.SetMatrix({{1, 0, 2}, {-1, 3, 4}, {-2, 1, 5}});
  template_matrix.SetMatrix({{11, -3, 5}, {2, 9, -1}, {-6, -6, 3}});
  ASSERT_TRUE(matrix.CalcComplements() == template_matrix);

  S21Matrix matrix_1(1, 1);
  matrix_1.SetMatrix({{1}});
  S21Matrix matrix_2 = matrix_1.CalcComplements();
  ASSERT_TRUE(matrix_1 == matrix_2);
}

TEST(Transpose, TestTranspose) {
  S21Matrix matrix(3, 3);
  S21Matrix template_matrix(3, 3);
  matrix.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  template_matrix.SetMatrix({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
  ASSERT_TRUE(matrix.Transpose() == template_matrix);
}

TEST(Inverse, TestInverse) {
  S21Matrix matrix(3, 3);
  S21Matrix template_matrix(3, 3);
  matrix.SetMatrix({{1, 0, 2}, {-1, 3, 4}, {-2, 1, 5}});
  matrix = matrix.InverseMatrix();
  template_matrix.SetMatrix({{0.52381, 0.0952381, -0.285714},
                             {-0.142857, 0.428571, -0.285714},
                             {0.238095, -0.047619, 0.142857}});
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ASSERT_NEAR(matrix(i, j), template_matrix(i, j), 0.001);

  matrix.SetMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  EXPECT_THROW(matrix.InverseMatrix(), std::range_error);

  S21Matrix matrix_1(1, 1), matrix_2(1, 1);
  matrix_1.SetMatrix({{2}});
  matrix_2.SetMatrix({{0.5}});
  ASSERT_TRUE(matrix_1.InverseMatrix() == matrix_2);
}

TEST(NotEqualOperator, TestNotEqual) {
  S21Matrix matrix(3, 3);
  S21Matrix template_matrix(3, 3);
  matrix.SetMatrix({{1, 0, 2}, {-1, 3, 4}, {-2, 1, 5}});
  template_matrix = matrix;
  matrix(0, 0) = 2;
  ASSERT_TRUE(matrix != template_matrix);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}