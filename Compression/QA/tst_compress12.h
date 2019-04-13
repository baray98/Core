#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>

#include "compress12.h"
#include "ibuffermock.h"

using namespace testing;

class Compress12Test : public ::testing::Test{
protected:
    Compress12Test(){

    }
    ~Compress12Test() override{

    }

    void SetUp() override{

    }
    void TearDown() override{

    }

    void deltaTest(Comp::Compress12& compress,int rawSize,Comp::PakType12 targetType,int delta)
    {
        int16_t raw[rawSize];
        int16_t res[rawSize];

        raw[0] = 1;
        raw[1] = raw[0] + delta;

        Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res);
        EXPECT_EQ(type,targetType);
        EXPECT_EQ(res[0],0x0);
        for (int i = 1 ; i < rawSize ; ++i)
        {
            EXPECT_EQ(res[1],delta) << "error on index " << i <<"expected delta = " << delta;
        }

        raw[0] = 1;
        raw[1] = raw[0] - delta;

        type = compress.getPakTypeAndResiduals(raw,rawSize,res);
        EXPECT_EQ(type,targetType) << "expected target type = " << targetType;
        EXPECT_EQ(res[0],0x0);
        for (int i = 1 ; i < rawSize ; ++i)
        {
            EXPECT_EQ(res[1],-delta) << "error on index " << "expected (-)delta = " << delta;;
        }
    }
};

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;


TEST_F(Compress12Test,GetPakTypeMeanTest){

    Comp::Compress12 compress;

    //    EXPECT_CALL(buff,size())
    //            .Times(1)
    //            .WillOnce(Return(100));

    int rawSize = 64;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    memset(raw,0xff,sizeof (raw));

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res);
    EXPECT_EQ(type,Comp::PakMean);
    EXPECT_EQ(res[0],0);
    for (int i = 1 ; i < rawSize ; ++i)
    {
        EXPECT_EQ(res[i],0) << "error on index " << i;
    }

}



TEST_F(Compress12Test,GetPakType1Delta1Test){

    Comp::Compress12 compress;

    int rawSize = 2;
    int delta = 1;
    deltaTest(compress,rawSize,Comp::Pak_1,delta);
}

TEST_F(Compress12Test,GetPakType2Delta2Test)
{

    Comp::Compress12 compress;

    int rawSize = 2;
    int delta = 2;
    deltaTest(compress,rawSize,Comp::Pak_2,delta);
}

TEST_F(Compress12Test,GetPakType4Test){

    Comp::Compress12 compress;

    int rawSize = 2;
    for (int delta = 3 ; delta < 0x9 ; delta++)
    {
        deltaTest(compress,rawSize,Comp::Pak_4,delta);
    }

}

TEST_F(Compress12Test,GetPakType8Test){

    Comp::Compress12 compress;

    int rawSize = 2;
    for (int delta = 9 ; delta < 0x81 ; delta++)
    {
        deltaTest(compress,rawSize,Comp::Pak_8,delta);
    }

}


TEST_F(Compress12Test,BenchMarkTest){

    Comp::Compress12 compress;

    int rawSize = 64;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    memset(raw,0xff,sizeof (raw));

    for (int i = 0; i < 0xFFFF; ++i)
    {
        Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res);
        EXPECT_EQ(type,Comp::PakMean);
        for (int i = 1 ; i < rawSize ; ++i)
        {
            EXPECT_EQ(res[i],0) << "error on index " << i;
        }
    }

}

TEST_F(Compress12Test,GetPakType12Test){

    Comp::Compress12 compress;

    //    EXPECT_CALL(buff,size())
    //            .Times(1)
    //            .WillOnce(Return(100));

    int rawSize = 2;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    raw[0] = 1;
    raw[1] = raw[0] + 0x081;

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res);
    EXPECT_EQ(type,Comp::Pak_12);
    EXPECT_EQ(res[0],0x0);
    for (int i = 1 ; i < rawSize ; ++i)
    {
        EXPECT_EQ(res[i],0x7FFF) << "error on index " << i;
    }

}

TEST_F(Compress12Test,GetPakType8_12Test){

    Comp::Compress12 compress;

    int rawSize = 3;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    raw[0] = 1;
    raw[1] = raw[0] + 0x081;
    raw[2] = raw[1] + 0x09;

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res,0);
    EXPECT_EQ(type,Comp::Pak_8_12);
    EXPECT_EQ(res[0],0x0);
    EXPECT_EQ(res[1],0x7FFF);
    EXPECT_EQ(res[2],0x09);
}

TEST_F(Compress12Test,GetPakType4_8Test){

    Comp::Compress12 compress;

    int rawSize = 3;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    raw[0] = 1;
    raw[1] = raw[0] + 0x09;
    raw[2] = raw[1] + 0x03;

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res,0);
    EXPECT_EQ(type,Comp::Pak_4_8);
    EXPECT_EQ(res[0],0x0);
    EXPECT_EQ(res[1],0x9);
    EXPECT_EQ(res[2],0x03);
}

TEST_F(Compress12Test,GetPakType2_8Test){

    Comp::Compress12 compress;

    int rawSize = 3;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    raw[0] = 1;
    raw[1] = raw[0] + 0x09;
    raw[2] = raw[1] + 0x02;

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res,0);
    EXPECT_EQ(type,Comp::Pak_2_8);
    EXPECT_EQ(res[0],0x0);
    EXPECT_EQ(res[1],0x9);
    EXPECT_EQ(res[2],0x02);
}

TEST_F(Compress12Test,GetPakType1_8Test){

    Comp::Compress12 compress;

    int rawSize = 3;
    int16_t raw[rawSize];
    int16_t res[rawSize];

    raw[0] = 1;
    raw[1] = raw[0] + 0x09;
    raw[2] = raw[1] + 0x01;

    Comp::PakType12 type = compress.getPakTypeAndResiduals(raw,rawSize,res,0);
    EXPECT_EQ(type,Comp::Pak_1_8);
    EXPECT_EQ(res[0],0x0);
    EXPECT_EQ(res[1],0x9);
    EXPECT_EQ(res[2],0x01);
}
