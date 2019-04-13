#ifndef COMPRESS12_H
#define COMPRESS12_H

#include "compression.h"
#include <stdint.h>

namespace Comp {

class IBuffer;

class Compress12
{
public:
    Compress12();

    PakType12 getPakTypeAndResiduals(const int16_t raw[], int16_t rawSize, int16_t residuals[],int mixedCount = 3 );
private:



};
}

#endif // COMPRESS12_H
