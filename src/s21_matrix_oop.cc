#include "s21_matrix_oop.h"
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = NULL;
}

// Constructor with parameters
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::runtime_error(
        "Error: The number of rows and columns must be greater than zero");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = NULL;
}

// Destructor
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

// Setter functions
void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument(
        "Error: The number of rows must be greater than zero");
  }
  rows_ = rows;
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument(
        "Error: The number of columns must be greater than zero");
  }
  cols_ = cols;
}

// Member functions
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; result == true && i < rows_; i++) {
    for (int j = 0; result == true && j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        result = false;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  int flag = OK;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    flag = ERROR;
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }
  for (int i = 0; flag == OK && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  int flag = OK;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    flag = ERROR;
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }
  for (int i = 0; flag == OK && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  int flag = OK;
  if (this->cols_ != other.rows_) {
    flag = ERROR;
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }
  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = S21Matrix(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  int flag = OK;
  S21Matrix result;
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::runtime_error("S21Matrix::Minor: Invalid matrix index");
  } else {
    S21Matrix result(rows_ - 1, cols_ - 1);
    for (int j = 1; j < rows_; j++) {
      for (int k = 0; k < cols_; k++) {
        if (k < col) {
          result.matrix_[j - 1][k] = matrix_[j][k];
        } else if (k > col) {
          result.matrix_[j - 1][k - 1] = matrix_[j][k];
        }
      }
    }
    // result.sprint();
    // std::cout<< result.matrix_[0][0]<<'1';
    return result;
  }
  return result;
}

// void S21Matrix::sprint(){
//   for (int i = 0; i < rows_;  i++){
//     for (int j = 0; j < cols_; j++){
//       std::cout<< matrix_[i][j] << ' ';
//     }
//     std::cout<< "\n";
//   }
//   std::cout<< "\n";
// }

double S21Matrix::Determinant() {
  int flag = OK;
  if (rows_ != cols_) {
    flag = ERROR;
    throw std::runtime_error("Error: The matrix must be square");
  }
  double result = 0.0;
  if (flag == OK && rows_ == 1) {
    result = matrix_[0][0];
  } else if (flag == OK && (rows_ == 2 || cols_ == 2)) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    // sprint();
    for (int i = 0; flag == OK && i < cols_; i++) {
      S21Matrix minor = Minor(0, i);
      int ed = (i % 2 == 0) ? 1 : -1;
      result += ed * matrix_[0][i] * minor.Determinant();
      // minor.sprint();
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::runtime_error("Error: The matrix must be square");
  } else if (rows_ == 2) {
    result.matrix_[0][0] = matrix_[1][1];
    result.matrix_[0][1] = -matrix_[1][0];
    result.matrix_[1][0] = -matrix_[0][1];
    result.matrix_[1][1] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix sub_matrix(result.Minor(i, j));
        result.matrix_[i][j] = sub_matrix.Determinant();
        // Calculate the sign of the complement
        if ((i + j) % 2 == 1) {
          result.matrix_[i][j] *= -1;
        }
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  int flag = OK;
  S21Matrix result(rows_, cols_);
  double det = Determinant();
  if (rows_ != cols_) {
    flag = ERROR;
    throw std::runtime_error("Error: The matrix must be square");
  } else if (det == 0) {
    flag = ERROR;
    throw std::runtime_error("Error: The matrix is not invertible");

  } else if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    result = CalcComplements();
    // result.sprint();
    result = result.Transpose();
    // result.sprint();
    result.MulNumber(1.0 / det);
    // result.sprint();
    return result;
  }
  if (flag = ERROR) result = S21Matrix();
  return result;
}

// Indexation by matrix elements (row, column)
double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::runtime_error("Error: Index is outside the matrix");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::runtime_error("Error: Index is outside the matrix");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  S21Matrix result(*this);
  return result.EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}