#include "Exceptions.h"

Exceptions::Exceptions(std::string error) : m_error(error) {}

void Exceptions::getError() const {
    std::cerr << m_error << std::endl;
}