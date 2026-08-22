#ifndef SPARSEEXCEPTIONS_H
#define SPARSEEXCEPTIONS_H


#include <string>
#include <exception>


namespace ptn
{

class SparseException : public std::exception
{

public:

    explicit SparseException(const std::string & message) : exception(), message(message)
    {}


    virtual ~SparseException(void) throw ()
    {}


    inline std::string getMessage(void) const
    {
        return this->message;
    }


protected:

    std::string message;

};


class InvalidDimensionsException : public SparseException
{

public:

    InvalidDimensionsException(const std::string & message) : SparseException(message)
    {}

};


class InvalidCoordinatesException : public SparseException
{

public:

    InvalidCoordinatesException(const std::string & message) : SparseException(message)
    {}

};

}

#endif // SPARSEEXCEPTIONS_H
