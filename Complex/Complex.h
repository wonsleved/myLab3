#ifndef MYLAB3_COMPLEX_H
#define MYLAB3_COMPLEX_H

#include <iostream>

class Complex
{
private:
    int m_real;
    int m_image;
public:
    Complex();
    Complex(int real, int image);
    int getReal();
    Complex& setReal(int real);
    int getImage();
    Complex& setImage(int image);
    void cin(int real, int image);
    void cout();
    bool operator < (Complex another);
    bool operator > (Complex another);
    bool operator >= (Complex another);
    bool operator <= (Complex another);
    bool operator == (Complex another);
    Complex operator +(Complex another);
    Complex &operator ++();

};

#endif
