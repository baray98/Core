#ifndef IBUFFERMOCK_H
#define IBUFFERMOCK_H

#include "ibuffer.h"

#include <gmock/gmock.h>
namespace Comp {

class IBufferMock : public IBuffer
{
public:
     MOCK_CONST_METHOD0 (size     ,int         () );
     MOCK_CONST_METHOD0 (dataStart,const char* () );
};

}

#endif // IBUFFERMOCK_H
