#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <iostream>
#include <fstream>

class Complex 
{
    private:
        double real;
        double imag;
    public:
        Complex(double r, double i);
        Complex(double r);
        Complex();
        void setNu(double re, double im);
        void print() const;

        Complex add(const Complex& c) const;
        void inc(const Complex& c);

        double re() const { return real; }
        double im() const { return imag; }

        //  + overloading (default)
        Complex operator+(const Complex& c) const;
        //  += overloading (default)
        Complex& operator+=(const Complex& c);

        //  - overloading 
        Complex operator-(const Complex& c) const;
        //  -= oveloading
        Complex& operator-=(const Complex& c);

        //  == overloading
        bool operator==(const Complex& c);

        //  * overloading 
        Complex operator*(const Complex& c) const;


        //  ~ overloading
        Complex operator~();

        //  / overloading
        Complex operator/(Complex c) const;

        // ++c
        Complex& operator++();  
        // c++  
        Complex operator++(int);


};


class Matrix
{
    private:
        int rows;
        int coloumns;
        Complex** matrix;
    public:
        Matrix(int _rows, int _coloumns);
        Matrix(const std::string& filename);

        int getRows();
        int getcoloumns();
        void print();
        void setNumbers();

        // overloadings
        Matrix operator*(Matrix& other) const;
        Matrix operator+(Matrix& other) const;
        Matrix operator-(Matrix& other) const;
        Matrix operator/(Matrix& other) const;
        Complex* operator[](int row);
        const Complex* operator[](int row) const;
        friend std::ostream& operator<<(std::ostream& os, Matrix& m);

        bool isSymmetric();
        bool isASymmetric();
        int isTriangle();

        void saveToFile(const std::string& filename) const;
        static Matrix readFromFile(const std::string& filename);

};


#endif