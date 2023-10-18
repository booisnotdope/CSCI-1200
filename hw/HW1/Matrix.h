#ifndef _matrix_h_
#define _matrix_h_
//definition of a simple matrix class.
#include <algorithm>
#include <ostream>

class Matrix{
public:
	//constructor takes 3 values
	Matrix(unsigned int rows,unsigned int cols, double fill);
    
    //default constructor
    Matrix():rows_(0), colz_(0){matrix_array=new double*[0];}

    //copy constructor
    Matrix(const Matrix& other);

  	~Matrix();

    unsigned int num_rows() const{return rows_;}
    unsigned int num_cols() const{return colz_;} 
    void clear();
    void multiply_by_coefficient(double coefficient);
    void swap_row(unsigned int row1, unsigned int row2);
    void transpose();

    bool add(const Matrix& other);
    bool subtract(const Matrix& other);
    bool get(unsigned int row, unsigned int col, double& value);
    bool set(unsigned int row, unsigned int col, double value);
	  bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    double* get_row(unsigned int row);
  	double* get_col(unsigned int col);
  	Matrix* quarter();
  private:
	double** matrix_array;
  unsigned int rows_, colz_;

};         

std::ostream& operator<< (std::ostream& out, Matrix& m);

#endif
