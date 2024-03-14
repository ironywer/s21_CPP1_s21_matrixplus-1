#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.rows(), 0);
  EXPECT_EQ(matrix.cols(), 0);
}

TEST(Constructor, ConstructorWithSize) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.rows(), 3);
  EXPECT_EQ(matrix.cols(), 4);
}

TEST(Constructor, CopyConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 1.0;
  S21Matrix copy(original);
  EXPECT_EQ(copy.rows(), original.rows());
  EXPECT_EQ(copy.cols(), original.cols());
  EXPECT_EQ(copy(0, 0), original(0, 0));
}

TEST(Constructor, MoveConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 1.0;
  S21Matrix moved(std::move(original));
  EXPECT_EQ(moved.rows(), 2);
  EXPECT_EQ(moved.cols(), 3);
  EXPECT_EQ(moved(0, 0), 1.0);
  EXPECT_EQ(original.rows(), 0);
}

TEST(Constructor, Destructor) {
  S21Matrix* matrix = new S21Matrix(2, 2);
  delete matrix;
}

TEST(Mutators, Mutator) {
  S21Matrix matrix(2, 2);
  matrix.set_cols(3);
  matrix.set_rows(3);
  EXPECT_EQ(matrix.rows(), 3);
  EXPECT_EQ(matrix.cols(), 3);
  matrix.set_cols(2);
  matrix.set_rows(2);
  EXPECT_EQ(matrix.rows(), 2);
  EXPECT_EQ(matrix.cols(), 2);
  matrix.set_cols(2);
  matrix.set_rows(2);
  EXPECT_EQ(matrix.rows(), 2);
  EXPECT_EQ(matrix.cols(), 2);

  EXPECT_THROW({ matrix.set_cols(-1); }, std::invalid_argument);
  EXPECT_THROW({ matrix.set_rows(-1); }, std::invalid_argument);
}

TEST(Mutators, Rows) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.rows(), 0);
  EXPECT_EQ(matrix.cols(), 0);
}

TEST(Arithmetic, SumMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 9.0);
}

TEST(Arithmetic, EqMatrixEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      matrix1(i, j) = 1.0;
      matrix2(i, j) = 1.0;
    }
  }

  bool result = matrix1.EqMatrix(matrix2);

  EXPECT_TRUE(result);
}

TEST(Arithmetic, EqMatrixNotEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      matrix1(i, j) = 1.0;
      matrix2(i, j) = 2.0;
    }
  }

  bool result = matrix1.EqMatrix(matrix2);

  EXPECT_FALSE(result);
}

TEST(Arithmetic, Exceptions) {
  S21Matrix matrix1(6, 7);
  S21Matrix matrix2(8, 9);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::runtime_error);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::runtime_error);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::runtime_error);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Arithmetic, SubMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -1.0);
}

TEST(Arithmetic, MulNumber) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(Arithmetic, MulMatrix) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 6.0;
  matrix2(2, 1) = 7.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 28.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 34.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 64.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 79.0);
}

TEST(LinearAlgebra, InverseMatrixCorrect) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix inverse = matrix.InverseMatrix();
  // inverse.sprint();
  EXPECT_DOUBLE_EQ(inverse(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(inverse(1, 1), -0.5);
}

TEST(LinearAlgebra, Determinant) {
  S21Matrix matrix1(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 8;

  EXPECT_DOUBLE_EQ(matrix1.Determinant(), 3.0);
}

TEST(LinearAlgebra, Exceptions) {
  S21Matrix matrix1(6, 7);

  EXPECT_THROW(matrix1.Determinant(), std::runtime_error);
  EXPECT_THROW(matrix1.CalcComplements(), std::runtime_error);
  EXPECT_THROW(matrix1.InverseMatrix(), std::runtime_error);
}

TEST(LinearAlgebra, InverseMatrixNonSquare) {
  S21Matrix matrix(2, 3);

  EXPECT_THROW(matrix.InverseMatrix(), std::runtime_error);
}

TEST(Operators, Plus) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 9.0);
}

TEST(Operators, OperatorMinus) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 4.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -3.0);
}

TEST(Operators, OperatorMultiply) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 6.0;
  matrix2(2, 1) = 7.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.rows(), 2);
  EXPECT_EQ(result.cols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 28.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 34.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 79.0);
}

TEST(Operators, OperatorMultiplyScalar) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix * 2;

  EXPECT_EQ(result.rows(), 2);
  EXPECT_EQ(result.cols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST(Operators, OperatorMultiplyByZero) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix * 0;

  EXPECT_EQ(result.rows(), 2);
  EXPECT_EQ(result.cols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

TEST(Operators, OperatorEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(Operators, OperatorEqual2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix3(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix3(0, 0) = 1.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 3.0;
  matrix3(1, 1) = 5.0;

  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(Operators, OperatorAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2;
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.rows(), matrix1.rows());
  EXPECT_EQ(matrix2.cols(), matrix1.cols());
  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      EXPECT_DOUBLE_EQ(matrix2(i, j), matrix1(i, j));
    }
  }
}

TEST(Operators, OperatorSelfAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 = matrix1;

  EXPECT_EQ(matrix1.rows(), matrix1.rows());
  EXPECT_EQ(matrix1.cols(), matrix1.cols());
  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), matrix1(i, j));
    }
  }
}

TEST(Operators, OperatorPlusEqual) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  matrix1 += matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 9.0);
}

TEST(Operators, OperatorMinusEquals) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  matrix1 -= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -1.0);
}

TEST(Operators, OperatorMultiplyAssignment) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(2, 0) = 6.0;
  matrix2(2, 1) = 7.0;

  matrix1 *= matrix2;

  S21Matrix expectedResult(2, 2);

  expectedResult(0, 0) = 28.0;
  expectedResult(0, 1) = 34.0;
  expectedResult(1, 0) = 64.0;
  expectedResult(1, 1) = 79.0;

  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), expectedResult(i, j));
    }
  }
}

TEST(Operators, OperatorParenthesisValidIndex) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
}

TEST(Operators, OperatorParenthesisInvalidIndex) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix(2, 1), std::runtime_error);
  EXPECT_THROW(matrix(1, 2), std::runtime_error);
  EXPECT_THROW(matrix(-1, 1), std::runtime_error);
  EXPECT_THROW(matrix(1, -1), std::runtime_error);
}

TEST(Operators, Exceptions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 2);
  EXPECT_THROW({ S21Matrix result = matrix1 + matrix2; }, std::runtime_error);
  EXPECT_THROW({ S21Matrix result = matrix1 - matrix2; }, std::runtime_error);
  EXPECT_THROW({ S21Matrix result = matrix1 * matrix2; }, std::runtime_error);
  EXPECT_THROW({ matrix1 *= matrix2; }, std::runtime_error);
  EXPECT_THROW({ matrix1 -= matrix2; }, std::runtime_error);
  EXPECT_THROW({ matrix1 += matrix2; }, std::runtime_error);
  EXPECT_THROW(matrix1(-1, -1), std::runtime_error);
  EXPECT_FALSE(matrix1 == matrix2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}