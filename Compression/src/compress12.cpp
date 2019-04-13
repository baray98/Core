#include "compress12.h"
#include "ibuffer.h"

namespace Comp
{


Compress12::Compress12()

{

}

PakType12 Compress12::getPakTypeAndResiduals(const int16_t raw[], int16_t rawSize, int16_t residuals[],int mixedCount)
{
    PakType12 type = Comp::PakMean;
    uint16_t histPak1 = 0,histPak2 = 0,histPak4 = 0,histPak8 = 0,histPak12 = 0;
    uint16_t absDelta = 0;
    int16_t delta = 0;
    residuals[0] = 0x0; // always zero
    for (int i = 1 ; i < rawSize ; ++i)
    {
        delta = raw[i] - raw[i-1];
        if (delta < 0)
            absDelta = (uint16_t)(-delta);
        else {
            absDelta = delta;
        }

        residuals[i] = delta;

        if (absDelta > 0x80 )
        {
            histPak12++;
            residuals[i] = 0x7FFF;
        }
        else
        {
            if (absDelta > 0x8 )
            {
                histPak8++;
            }
            else if(absDelta != 0)
            {
                if (absDelta == 1)
                    histPak1++;
                else if (absDelta == 2)
                    histPak2++;
                else {
                    histPak4++;
                }
            }
        }

    }
    //figure out compression type
    uint16_t subCount = 0;
    if (histPak12)
    {
        type = Comp::Pak_12;
        subCount = histPak8 + histPak4 + histPak2 + histPak1;
        if (subCount > mixedCount)
            type = Comp::Pak_8_12;
    }
    else
    {
        if (histPak8)
        {
            if (histPak4)
            {
                type=Comp::Pak_8;
                subCount = histPak4 + histPak2 + histPak1;
                if (subCount > mixedCount)
                    type = Comp::Pak_4_8;
            }
            else if (histPak2)
            {
                type=Comp::Pak_8;
                subCount = histPak2 + histPak1;
                if (subCount > mixedCount)
                    type = Comp::Pak_2_8;
            }
            else {
                type=Comp::Pak_8;
                if (histPak1 > mixedCount)
                    type = Comp::Pak_1_8;
            }
        }
        else if (histPak4)
            type = Comp::Pak_4;
        else if (histPak2)
            type = Comp::Pak_2;
        else if (histPak1)
            type = Comp::Pak_1;
        else {
            type = Comp::PakMean;
        }
    }

    return type;
}



}
