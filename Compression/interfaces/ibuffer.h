#ifndef IBUFFER_H
#define IBUFFER_H

namespace Comp
{

class IBuffer
{
public:
    IBuffer(){}
    virtual ~IBuffer(){}

    virtual int size() const = 0;
    virtual const char* dataStart() const = 0;
};

}

#endif // IBUFFER_H
