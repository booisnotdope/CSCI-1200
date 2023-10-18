#include "Matrix.h"
#include <ostream>

Matrix::Matrix(unsigned int rows,unsigned int cols, double fill) : rows_(rows), colz_(cols) {
    matrix_array = new double*[rows];
    for(unsigned int i = 0 ; i < rows ; i++){
    	matrix_array[i]=new double[colz_];
    	for(unsigned int j = 0; j < cols; j++){
    		matrix_array[i][j]=fill;
    	}
    }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), colz_(other.colz_){
    matrix_array = new double*[rows_ ];

    for(unsigned int i = 0 ; i < rows_ ; i++){
    	matrix_array[i]=new double[colz_];
    	for(unsigned int j = 0; j < colz_; j++){
    		matrix_array[i][j] = other.matrix_array[i][j];
    	}
    }
}

Matrix::~Matrix(){
	clear();
}

//get and set that return true if given row and col are within range
bool Matrix::get(unsigned int row, unsigned int col, double& value){
	if( row < rows_ && col < colz_){
		value = matrix_array[row][col];
		return true;
	}
	return false;
	
}

bool Matrix::set(unsigned int row, unsigned int col, double value){
	if( row<rows_ && col<colz_){
		matrix_array[row][col] = value;
		return true;
	}
	return false;
}

//multiply all matrix values by coefficient
void Matrix::multiply_by_coefficient(double coefficient){
	for(unsigned int i = 0 ; i < rows_ ; i++){
    	for(unsigned int j = 0; j < colz_; j++){
    		matrix_array[i][j]*=coefficient;
    	}
    }
}

void Matrix::clear(){
	 if (rows_!=0 && colz_!=0) {
        for (unsigned int i = 0; i < rows_; ++i){
        	delete [] matrix_array[i];
		}
        delete [] matrix_array;
		rows_ = 0;
		colz_ = 0;
    }
}

//swaps two rows
void Matrix::swap_row(unsigned int row1, unsigned int row2){
	if(row1 < rows_ && row2 < rows_){
		double* temp = matrix_array[row1];
		matrix_array[row1] = matrix_array[row2];
		matrix_array[row2] = temp;
		delete[] temp; 
	}
	
}

//transpose the matrix(flipping on its side)
void Matrix::transpose(){
	Matrix newmat(colz_ ,rows_ ,0);
	for(unsigned int i = 0; i < rows_; i++){
		for(unsigned int j = 0; j < colz_; j++){
			newmat.matrix_array[j][i] = matrix_array[i][j];
		}
	}	
	
	*this=newmat;
}

bool Matrix::add(const Matrix& other){
 	if (rows_ != other.rows_ || colz_ != other.colz_) {
   		return false;
  	}
  	for(unsigned int i = 0; i < rows_; i++){
  		for(unsigned int j = 0; j<colz_; j++)
  			matrix_array[i][j]+=other.matrix_array[i][j];
  	}
  	return true;
}

bool Matrix::subtract(const Matrix& other){
 	if (rows_ != other.rows_ || colz_ != other.colz_) {
   		return false;
  	}
  	for(unsigned int i = 0; i < rows_; i++){
  		for(unsigned int j = 0; j<colz_; j++)
  			matrix_array[i][j]-=other.matrix_array[i][j];
  	}
  	return true;
}


//overloaded << output operator  outs a formatted matrix
std::ostream& operator<< (std::ostream& out, Matrix& m){
  out << std::endl << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
  if (m.num_rows() == 0 || m.num_cols() == 0) {
    out << "[ ]";
    return out;
  }
  out << "[";
  for (unsigned int i = 0; i < m.num_rows(); ++i) {
  	out<<" ";
    if (i != 0) {
      out << " ";
    }
    for (unsigned int j = 0; j < m.num_cols(); ++j) {
      if (j != 0) {out << " ";}
      double temp;
      m.get(i, j, temp);
      out <<temp;
    }
    if (i != m.num_rows() - 1) {
      out << std::endl;
    }
  }
  out << " ]" << std::endl;
  return out;
}

bool Matrix::operator==(const Matrix& other) const{
  	if (rows_ != other.rows_ || colz_ != other.colz_){
    	return false;
  	}
  	else{
  		for(unsigned int i = 0; i < rows_; i++){
  			for(unsigned int j = 0 ; j < colz_; j++){
  				if(matrix_array[i][j]!=other.matrix_array[i][j]){
  					return false;
  				}
  			}
  		}
	}	
	return true;
}

bool Matrix::operator!=(const Matrix& other) const{
  	if (rows_ != other.rows_ || colz_ != other.colz_){
    	return true;
  	}
  	else{
  		for(unsigned int i = 0; i < rows_; i++){
  			for(unsigned int j = 0 ; j < colz_; j++){
  				if(matrix_array[i][j]!=other.matrix_array[i][j]){
  					return true;
  				}
  			}
  		}
  	}
	return false;
}

double* Matrix::get_row(unsigned int row){
	if (row > rows_){
		return nullptr;
	}
	return matrix_array[row];
}

double* Matrix::get_col(unsigned int col){
	if (col >= colz_) {
    return nullptr;
  }
  double* ptr=new double[rows_];
  for(unsigned int i = 0; i < rows_;i++){
  	*ptr=matrix_array[i][col];
  }
  return ptr;
}

Matrix* Matrix::quarter(){
	Matrix* quad = new Matrix[4];
	unsigned int half_row=rows_/2;
  unsigned int half_col=colz_/2;
  if(rows_ % 2 > 0){
  	half_row+=1;
  }

  if(colz_ % 2 > 0){
  	half_col+=1;
  }
		
  Matrix temp(half_row, half_col, 0);
  Matrix temp1(half_row, half_col, 0);
  Matrix temp2(half_row, half_col, 0);
  Matrix temp3(half_row, half_col, 0);
  

  quad[0]=temp;
  quad[1]=temp1;
  quad[2]=temp2;
  quad[3]=temp3;
  for (unsigned int i = 0; i < half_row; i++)
    {
        for (unsigned int j = 0; j < half_col; j++)
        {	
        	quad[0].matrix_array[i][j]=matrix_array[i][j];
        	quad[1].matrix_array[i][j]=matrix_array[i][j+half_col-colz_%2];
        	quad[2].matrix_array[i][j]=matrix_array[i+half_row-rows_%2][j];
        	quad[3].matrix_array[i][j]=matrix_array[i+half_row-rows_%2][j+half_col-colz_%2];
        }
    }
	return quad;    
}



