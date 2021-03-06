#include "math/matrix/mat.h"
Mat::Mat(int numRows, int numCols)
{
  if (numRows <= 0 && numCols <= 0)
  {
    throw "Invalid form";
  }

  this->rows = numRows;
  this->columns = numCols;

  values = new float[numRows*numCols];

  // Zero the matrix by default
  for(int counter = 0; counter < numRows*numCols; counter++)
  {
    values[counter] = 0.0f;
  }
}

// copy constructor
Mat::Mat(const Mat& matrix)
{
  this->rows = matrix.rows;
  this->columns = matrix.columns;
  this->values = new float[rows*columns];


  memcpy(this->values, matrix.values,(rows*columns)*sizeof(float));
}

int Mat::numberOfRows()
{
  return this->rows;
}

int Mat::numberOfColumns()
{
  return this->columns;
}

// insert value into the matrix
void Mat::insert(int row, int column, float value)
{
  if (row < 0 || column < 0 || row > this->rows || column > this->columns)
  {
    throw "invalid index";
  }

  values[(row*this->columns)+column] = value;
}

// destructor
Mat::~Mat()
{
  delete [] values;
}

// used to access value in matrix
float& Mat::operator()(const int row, const int column)
{
  if (row < 0 || column < 0 || row > this->rows || column > this->columns)
  {
    throw "invalid index";
  }

  return values[(row*this->columns)+column];
}


Mat Mat::operator+ (Mat& matrix)
{
  // matrices must be exactly equal for addition
  if (this->rows != matrix.numberOfRows() || this->columns != matrix.numberOfColumns())
  {
    throw "Matrix mismatch";
  }

  Mat result(this->rows, this->columns);
  float addedResult;
  // add the two matrices
  for(int row = 0; row < this->rows; row++)
  {
    for(int column = 0; column < this->columns; column++)
    {
      // is this even legal???
      addedResult = this->values[(row*this->columns)+column] + matrix(row,column);
      result.insert(row,column,addedResult);
    }
  }

  return result;
}

// Matrix scalar multiplication
Mat Mat::operator* (const float scalar)
{
  Mat result(this->rows, this->columns); // result matrix
  float scalarResult;

  // apply scalar matrix multiplication
  for(int row = 0; row < this->rows; row++)
  {
    for(int column = 0; column < this->columns; column++)
    {
      scalarResult = scalar*this->values[(row*this->columns)+column];
      result.insert(row,column,scalarResult);
    }
  }

  return result;
}
