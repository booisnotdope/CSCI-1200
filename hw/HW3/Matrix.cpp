#include <iostream>
#include "Matrix.h"
//PURPOSE: Implements the declared functions in the Matrix.h
//CONSTRUCTORS
//Default Constructor
Matrix::Matrix(){
    temp = NULL;
    rows = 0;
    columns = 0;
    fill = 0;
}
//Constructor using a row, a column, and a fill double. If 0's are passed throught
//the rows and columns argument, point temp to null.
Matrix::Matrix(unsigned int arows, unsigned int acolumns, double afill){
    if (arows == 0 || acolumns == 0){
        temp = nullptr;
        rows = arows;
        columns = acolumns;
        fill = afill;
    } else{
        temp = new double *[arows];
        for (unsigned int i = 0; i < arows; i++){
            temp[i] = new double[acolumns];
            for (unsigned int j = 0; j < acolumns; j++){
                temp[i][j] = afill;
            }
        }
        rows = arows;
        columns = acolumns;
        fill = afill;
    }
}
//Copy Constructor. If the matrix already has 0 for their
//columns or rows, set temp to null.
Matrix::Matrix(const Matrix &m){
    if (m.num_rows() == 0 || m.num_cols() == 0){
        temp = nullptr;
        rows = m.num_rows();
        columns = m.num_cols();
        fill = 0;
    } else {
        rows = m.num_rows();
        columns = m.num_cols();
        fill = 0;
        temp = new double *[m.num_rows()];
        for (unsigned int i = 0; i < m.num_rows(); i++){
            temp[i] = m.get_row(i);
        }
    }
}
//Copy Constructor using operator If the matrix already has 0 for their
//columns or rows, set temp to null.
Matrix& Matrix::operator=(const Matrix& m){
    if (m.num_rows() == 0 || m.num_cols() == 0){
        temp = nullptr;
        rows = m.num_rows();
        columns = m.num_cols();
        fill = 0;
    } else {
        rows = m.num_rows();
        columns = m.num_cols();
        fill = 0;
        temp = new double *[m.num_rows()];
        for (unsigned int i = 0; i < m.num_rows(); i++){
            temp[i] = m.get_row(i);
        }
    }
    return *this;
}

//Destructor
Matrix::~Matrix(){
    clear();
}

//Basic FUnctionality
//return number of rows
unsigned int Matrix::num_rows() const{
    return rows;
}
//return number of columns
unsigned int Matrix::num_cols() const{
    return columns;
}
//clear all memory in heap
void Matrix::clear(){
    if (rows != 0 && columns != 0){
    for (unsigned int i = 0; i < rows; i++){
        delete[] temp[i];
    }
    delete[] temp;
    rows = 0;
    columns = 0;
    }
}
//takes in a row, column, and a referenced double. returns true if rows and columns are in bounds
//otherwise returns false. sets the referenced number to the index of the matrix
bool Matrix::get(unsigned int arows, unsigned int acolumns, double &anumber) const{
    if (rows == 0 || columns == 0){
        return false;
    }
    if (rows < arows && columns < acolumns){
        return false;
    }
    anumber = temp[arows][acolumns];
    return true;
}
//takes in a row, column, and a double. returns true if rows and columns are in bounds
//otherwise return false. set the index of the matrix to the double.
bool Matrix::set(unsigned int arows, unsigned int acolumns, double anumber){
    if (rows == 0 || columns == 0){
        return false;
    }
    if (rows < arows && columns < acolumns){
        return false;
    }
    temp[arows][acolumns] = anumber;
    return true;
}

//Simple Matrix Operations
//for each value in the matrix, multiple by the double.
void Matrix::multiply_by_coefficient(double num){
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            temp[i][j] *= num;
        }
    }
}
//if both parameters are in bounds, swap the pointers and return true.
//otherwise return false
bool Matrix::swap_row(unsigned int &row1, unsigned int &row2){
    if (row1 >= rows && row2 >= rows){
        return false;
    }
    double* old_row1 = temp[row1];
    temp[row1] = temp[row2];
    temp[row2] = old_row1;
    delete[] old_row1;
    return true;
}
//flip the matrix diagionally. creates a new matrix and sets the rows to the columns
//and the columns to the rows. set original matrix to the new one created. delete new matrix
void Matrix::transpose(){
    if (rows != 0 || columns != 0){
        Matrix new_m(columns, rows, 0);
        for (unsigned int i = 0; i < columns; i++){
            for (unsigned int j = 0; j < rows; j++){
                new_m.set_num(i, j, temp[j][i]);
            }
        }
        clear();
        *this = new_m;
    }
}

//Binary Matrix Operations
//takes in a matrix. if the rows and columns are the same, return true. otherwise return false
//for each value in both matrixes add the values and set the new value to the original matrix
bool Matrix::add(const Matrix& m2){
    if(rows != m2.num_rows() || columns != m2.num_cols()){
        return false;
    }
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            temp[i][j] += m2.get_num(i, j);
        }
    }
    return true;
}
//similar to add function except you subtract
bool Matrix::subtract(const Matrix& m2){
    if(rows != m2.num_rows() || columns != m2.num_cols()){
        return false;
    }
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            temp[i][j] -= m2.get_num(i, j);
        }
    }
    return true;    
}

//Harder Matrix Operations
//if arow is out of bounds, return a NULL pointer. otherwise loop through the desired row
//and return the row.
double* Matrix::get_row(unsigned int arow) const{
    if (rows < arow){
        return NULL;
    }
    double* row;
    row = new double[columns];
    for (unsigned int i = 0; i < columns; i++){
        row[i] = temp[arow][i];
    }
    return row;
}
//similar to get_row function. return the desired column
double* Matrix::get_column(unsigned int col) const{
    if (columns < col){
        return NULL;
    }
    double* cols = new double[rows];
    for (unsigned int i = 0; i < rows; i++){
        cols[rows] = temp[rows][col];
    }
    return cols;
}
//returns a matrix pointer. points to an array of matrixes. each quarter is equal size. 
//quarter[0] is upper left, quarter[1] is upper right, quarter[2] is lower left, quarter[3] is lower right
Matrix* Matrix::quarter(){
    unsigned int new_row = (rows/2 + rows%2) , new_col = (columns/2 + columns%2), 
                row_math = (rows/2 - rows%2) + 1, col_math = (columns/2 - columns%2);
    Matrix* quarters = new Matrix[4];
    for (int i = 0; i < 4; i++){
        quarters[i] = Matrix(new_row, new_col, 0); 
    }
    if (rows == 0 || columns == 0){
        return quarters;
    }
    for (unsigned int i = 0; i < new_row; i++){
        for (unsigned int j = 0; j < new_col; j++){
            quarters[0].temp[i][j] = temp[i][j];
            quarters[1].temp[i][j] = temp[i][j + col_math];
            quarters[2].temp[i][j] = temp[i + row_math][j];
            quarters[3].temp[i][j] = temp[i + row_math][j + col_math];
        }
    }    
    return quarters;
}

//Extra Credit
/*given a row, col, and a double, fill a matrix with those values. Then 
if the index of that matrix matches with the original matrix, set that value
of the new matrix to the original values.*/
void Matrix::resize(unsigned int row, unsigned int col, double afill){
    Matrix resized(row, col, afill);
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            if (i < row && j < col){
                resized.set_num(i, j, temp[i][j]);
            }
        }
    }
    clear();
    *this = resized;
}

//Own function
//This function isn't one of the required functions but is used to make life easier
double Matrix::get_num(unsigned int row, unsigned int col)const {
    
    return temp[row][col];
}

void Matrix::set_num(unsigned int row, unsigned int col, double num){
    temp[row][col] = num;
    
}

//Operators
//return true if the rows and columns are the same size as well as each value
//in the matrix is the same. else, return false
bool operator==(const Matrix& matrix1, const Matrix& matrix2){
    unsigned int row1 = matrix1.num_rows(), row2 = matrix2.num_rows(),
        col1 = matrix1.num_cols(), col2 = matrix2.num_cols();
    if (row1 != row2 || col1 != col2){
        return false;
    }
    for (unsigned int i = 0; i < row1; i++){
        for (unsigned int j = 0; j < col1; j++){
            if (matrix1.get_num(i, j) != matrix2.get_num(i, j)){
                return false;
            }
        }
    }
    return true;
}
//use the == operator and return the not.
bool operator!=(const Matrix& matrix1, const Matrix& matrix2){
    return !(matrix1 == matrix2);
}
//use ostream and output desired format of the matrix
std::ostream& operator<< (std::ostream& out, const Matrix& m){
    out << ' ' << m.num_cols() << " x " << m.num_rows() 
        << " matrix: " << std::endl << "[ ";
    for (unsigned int i = 0; i < m.num_rows(); i++){
        if (i != 0){
            out << std::endl << "  ";
        }
        for (unsigned int j = 0; j < m.num_cols(); j++){
            out << m.get_num(i, j) << ' ';
        }      
    }
    out << ']' << std::endl;
    return out;
}

