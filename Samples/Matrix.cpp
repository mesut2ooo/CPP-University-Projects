#include "Classes.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Matrix::Matrix(int _rows, int _coloumns)
{
    rows = _rows;
    coloumns = _coloumns;
    
    matrix = new Complex*[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new Complex[coloumns];
    }
}

Matrix::Matrix(const string& filename) 
{
    try
    {
        ifstream file(filename);

        // error for openning file
        if (!file.is_open()) 
            throw runtime_error("Error openning file " + filename);

        string line;
        getline(file, line);

        istringstream dimensionsStream(line);
        dimensionsStream >> rows >> coloumns;

        // Errors for rows and coloumns
        if (dimensionsStream.fail() || rows <= 0 || coloumns <= 0)
            throw runtime_error("Invalid matrix dimensions.");

        // Creating matrix
        matrix = new Complex*[rows];
        for (int i = 0; i < rows; ++i) 
        {
            matrix[i] = new Complex[coloumns];
        }

        // Reading
        for (int i = 0; i < rows; ++i) 
        {
            getline(file, line);
            istringstream rowStream(line);

            char openPar, comma, closePar;

            for (int j = 0; j < coloumns; ++j) 
            {
                double re, im;
                rowStream >> openPar >> re >> comma >> im >> closePar;
                
                // Errors for each element
                if (rowStream.fail() || comma != ',' || closePar != ')' || (j < coloumns - 1 && rowStream.get() != ',')) 
                    throw runtime_error("Invalid element format in line " + to_string(i+2) +".");

                matrix[i][j].setNu(re,im);
            }
        }

        if (file.fail() && !file.eof())
            throw runtime_error("Error reading from file.");

        file.close();
    }

    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return;
    }
}

int Matrix::getRows()
{
    return rows;
}

int Matrix::getcoloumns()
{
    return coloumns;
}

void Matrix::print()
{
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            cout << "(" << matrix[i][j].re() << " , " << matrix[i][j].im() << ")\t";
        }
        cout << endl;
    }
}

void Matrix::setNumbers()
{
    // taking the matrix input 
    cout << "Entering the elements\nFirst number is the real part and the second number is the imaginary part\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            cout << "Enter the element (" << i+1 << " , " << j+1 << ")  :  ";
            double re, im;
            cin >> re >> im;
            matrix[i][j].setNu(re,im);
        }
    }
}

Matrix Matrix::operator*(Matrix& other) const
{
    try
    {
        if (coloumns != other.getRows())
            throw runtime_error("CAN NOT BE MULTIPLIED");
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        return Matrix(1,1);
    }

    Matrix result(rows, other.getcoloumns());

    // calculating the multiply matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.getcoloumns(); j++)
        {
            result.matrix[i][j] = Complex();

            for (int k = 0; k < coloumns; k++)
            {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator+(Matrix& other) const
{
    try 
    {
        if (rows != other.getRows() || coloumns != other.getcoloumns())
        {
            throw runtime_error("CAN NOT BE ADDED");
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        return Matrix(1,1);
    }

    Matrix result(rows, coloumns);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            result.matrix[i][j] += matrix[i][j] + other.matrix[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator-(Matrix& other) const
{
    try 
    {
        if (rows != other.getRows() || coloumns != other.getcoloumns())
        {
            throw runtime_error("CAN NOT BE SUBSTRACTED");
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        return Matrix(1,1);
    }

    Matrix result(rows, coloumns);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            result.matrix[i][j] += matrix[i][j] - other.matrix[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator/(Matrix& other) const
{
    try 
    {
        if (rows != other.getRows() || coloumns != other.getcoloumns())
        {
            throw runtime_error("CAN NOT BE DIVIDED");
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        return Matrix(1,1);
    }

    Matrix result(rows, coloumns);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            result.matrix[i][j] += matrix[i][j] / other.matrix[i][j];
        }
    }

    return result;
}

Complex* Matrix::operator[](int row) 
{
    try
    {
        if (row < 0 || row >= rows) 
            throw out_of_range("Row index out of bounds");
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return matrix[row];
}

const Complex* Matrix::operator[](int row) const
{
    try
    {
        if (row < 0 || row >= rows) 
            throw out_of_range("Row index out of bounds");
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return matrix[row];
}

bool Matrix::isSymmetric()
{
    if (rows != coloumns)
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            if (!(matrix[i][j] == matrix[j][i]))
                return false;
        }
    }

    return true;
}

bool Matrix::isASymmetric()
{
    if (rows != coloumns)
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloumns; j++)
        {
            if (i == j)
                continue;
            if (matrix[i][j].re() != -matrix[j][i].re() || matrix[i][j].im() != -matrix[j][i].im())
            {
                return false;
            }
        }
    }

    return true;
}

int Matrix::isTriangle()
{
    bool isLowerT {true};
    bool isUpperT {true};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j].re() != 0 || matrix[i][j].im() != 0)
                isLowerT = false;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = i+1; j < coloumns; j++)
        {
            if (matrix[i][j].re() != 0 || matrix[i][j].im() != 0)
                isUpperT = false;
        }
    }

    if (isLowerT)
        return -1;
    else if (isUpperT)
        return 1;
    else    
        return 0;
}

ostream& operator<<(ostream& os, Matrix& m)
{
    for (int i = 0; i < m.getRows(); i++)
    {
        for (int j = 0; j < m.getcoloumns(); j++)
        {
            os << "(" << m.matrix[i][j].re() << " , " << m.matrix[i][j].im() << ")\t";
        }
        os << "\n";
    }

    return os;
}

void Matrix::saveToFile(const string& filename) const 
{
    ofstream outFile(filename, ios::binary);

    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write the number of rows and columns
    outFile.write(reinterpret_cast<const char*>(&rows), sizeof(int));
    outFile.write(reinterpret_cast<const char*>(&coloumns), sizeof(int));

    // Write the matrix data
    for (int i = 0; i < rows; ++i) {
        outFile.write(reinterpret_cast<const char*>(matrix[i]), sizeof(Complex) * coloumns);
    }

    outFile.close();
}


Matrix Matrix::readFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);

    if (!inFile.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        // Return an empty matrix or handle the error as needed
        return Matrix(0, 0);
    }

    // Read the number of rows and columns
    int readRows, readColumns;
    inFile.read(reinterpret_cast<char*>(&readRows), sizeof(int));
    inFile.read(reinterpret_cast<char*>(&readColumns), sizeof(int));

    // Create a new Matrix object
    Matrix result(readRows, readColumns);

    // Read the matrix data
    for (int i = 0; i < readRows; ++i) {
        inFile.read(reinterpret_cast<char*>(result.matrix[i]), sizeof(Complex) * readColumns);
    }

    inFile.close();

    return result;
}
