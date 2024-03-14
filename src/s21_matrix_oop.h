#include <iostream>
#define OK 0
#define ERROR 1

using namespace std;
class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // Constructor with parameters
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  ~S21Matrix();                       // Destructor

  // Getter functions
  int rows() const { return rows_; }

  int cols() const { return cols_; }

  // Setter functions

  void set_cols(int cols);
  void set_rows(int rows);

  // Member functions
  // void sprint();
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix Minor(int row, int col);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Indexation by matrix elements (row, column)
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  // Addition of two matrices. Different matrix dimensions.
  S21Matrix operator+(const S21Matrix& other) const;

  // Subtraction of one matrix from another. Different matrix dimensions.
  S21Matrix operator-(const S21Matrix& other) const;

  // Matrix multiplication and matrix multiplication by a number. The number of
  // columns of the first matrix does not equal the number of rows of the second
  // matrix.
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;

  // Checks for matrices equality (EqMatrix).
  bool operator==(const S21Matrix& other) const;

  // Assignment of values from one matrix to another one.
  S21Matrix& operator=(const S21Matrix& other);

  // Addition assignment (SumMatrix) different matrix dimensions.
  S21Matrix& operator+=(const S21Matrix& other);

  // Difference assignment (SubMatrix) different matrix dimensions.
  S21Matrix& operator-=(const S21Matrix& other);

  // Multiplication assignment (MulMatrix/MulNumber). The number of columns of
  // the first matrix does not equal the number of rows of the second matrix.
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
};
