#include "Classes.h"
#include <iostream>

using namespace std;

Complex::Complex(double r, double i) : real(r), imag(i) {}
Complex::Complex(double r) : real(r), imag(0) {}
Complex::Complex(): real(0), imag(0) {}
void Complex::setNu(double re, double im)
{
    real = re;
    imag = im;
}


Complex Complex::add(const Complex& c) const {
    return Complex(real + c.real, imag + c.imag);
}

void Complex::inc(const Complex& c) {
    real += c.real;
    imag += c.imag;
}

void Complex::print() const {
    cout << real;
    if (imag > 0)
        cout << '+' << imag << 'i';
    else if (imag < 0)
        cout << imag << 'i';
}

//  + overloading (default)
Complex Complex::operator+(const Complex& c) const
{
    return Complex(real + c.real, imag + c.imag);
}

//  += overloading (default)
Complex& Complex::operator+=(const Complex& c)
{
    real += c.real;
    imag += c.imag;
    return *this;
}

//  - overloading
Complex Complex::operator-(const Complex& c) const
{
    return Complex(real - c.real, imag - c.imag);
}

//  -= overloading
Complex& Complex::operator-=(const Complex& c)
{
    real -= c.real;
    imag -= c.imag;
    return *this;
}

//  == overloading
bool Complex::operator==(const Complex& c)
{
    if (real == c.real && imag == c.imag)
        return true;
    else
        return false;
}

//  * overloading
Complex Complex::operator*(const Complex& c) const
{
    return Complex(real*c.real - imag*c.imag, real*c.imag + imag*c.real);
}

//  ~ overloading
Complex Complex::operator~()
{
    Complex result = *this;
    result.imag = -imag;
    return result;
    
}

//  / overloading
Complex Complex::operator/(Complex c) const
{
    double realPart = ((*this * ~c).re()) / (c * ~c).re();
    double imagPart = ((*this * ~c).im()) / (c * ~c).re();
    Complex result(realPart, imagPart);
    return result;
}

Complex& Complex::operator++()
{
    ++real;
    ++imag;
    return *this;
}

Complex Complex::operator++(int) 
{
    Complex temp = *this;
    ++real;
    ++imag;
    return temp;
}

