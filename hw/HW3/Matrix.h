//PURPOSE: Header file of the matrix class. declares all the functions
class Matrix{
    public:
    Matrix();
    Matrix(unsigned int rows, unsigned int columns, double fill);
    Matrix(const Matrix &m);
    Matrix& operator=(const Matrix& m);

    //Destructor
    ~Matrix();

    //Basic Funtionality
    unsigned int num_rows() const;
    unsigned int num_cols() const;
    void clear();
    bool get(unsigned int rows, unsigned int columns, double &number) const;
    bool set(unsigned int rows, unsigned int columns, double number);

    //Simple Matrix Operations
    void multiply_by_coefficient(double num);
    bool swap_row(unsigned int &row1, unsigned int &row2);
    void transpose();

    //Binary Matrix Operations
    bool add(const Matrix& m2);
    bool subtract(const Matrix& m2);

    // Harder Matrix Operations
    double* get_row(unsigned int row)const;
    double* get_column(unsigned int col)const;
    Matrix* quarter();
    
    //Extra Credit
    void resize(unsigned int row, unsigned int col, double fill);

    //Own function
    double get_num(unsigned int row, unsigned int col)const;
    void set_num(unsigned int row, unsigned int col, double num);
    private:
    double **temp;
    unsigned int rows;
    unsigned int columns;
    double fill;
};

//Non-member functions
bool operator==(const Matrix& matrix1, const Matrix& matrix2);
bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
std::ostream& operator<< (std::ostream& out, const Matrix& m);
