#include "Complex.h"

Complex::Complex() : m_real(0), m_image(0) {}

Complex::Complex(int real, int image = 0) : m_real(real), m_image(image) {}

void Complex::cin(int real, int image) {
    m_real = real;
    m_image = image;
}

Complex& Complex::setReal(int real) {
    m_real = real;
    return *this;
}

int Complex::getReal() {
    return m_real;
}

Complex& Complex::setImage(int real) {
    m_image = real;
    return *this;
}

int Complex::getImage() {
    return m_image;
}

void Complex::cout() {
    std::cout << m_real;
    if (m_image > 0) std::cout << "+";
    std::cout << m_image << "i" << std::endl;
}

bool Complex::operator< (const Complex another) {
    return m_real < another.m_real;
}

bool Complex::operator<= (const Complex another) {
    return m_real <= another.m_real;
}

bool Complex::operator== (const Complex another) {
    return m_real == another.m_real && m_image == another.m_image;
}

Complex Complex::operator+ (const Complex another) {
    Complex tmp;
    tmp.m_image = m_image + another.m_image;
    tmp.m_real = m_real + another.m_real;
    return tmp;
}

Complex & Complex::operator++ () {
    m_real += 1;
    return *this;
}

bool Complex::operator> (const Complex another) {
    return m_real > another.m_real;
}

bool Complex::operator>= (const Complex another) {
    return m_real >= another.m_real;
}

std::ostream& operator<< (std::ostream& out, Complex& complex) {
    out << complex.getReal();
    if (complex.getImage() > 0) std::cout << "+";
    std::cout << complex.getImage() << "i" << std::endl;
    return out;
}