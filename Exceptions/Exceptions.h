#ifndef MYLAB3_EXCEPTIONS_H
#define MYLAB3_EXCEPTIONS_H

#include "iostream"

namespace ExceptionConsts {
    const std::string ITEM_EXISTS = "Item is already exist!";
}

class Exceptions
{
protected:
    std::string m_error;
public:
    explicit Exceptions(std::string error);
    virtual void getError() const;
};


#endif
