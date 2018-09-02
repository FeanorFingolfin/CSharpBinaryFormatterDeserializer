/**
 * @file          DataDef.h
 * @brief         数据结构声明
 * @author        Narsil
 * @version       0.1
 * @date          2018.09.02
 */
#ifndef DATADEF_H
#define DATADEF_H

#include <QList>

// 以下是与二进制文件内容对应的数据结构,必须以 1B 对齐
#pragma pack(push)
#pragma pack(1)

struct GrayBitInfoFileMap
{
    int grayBit       = 0;
    int oeWidthValue  = 0;

    GrayBitInfoFileMap(int grayBit_ = 0, int oeWidthValue_ = 0)
        : grayBit(grayBit_),
          oeWidthValue(oeWidthValue_)
    {
    }
};
typedef GrayBitInfoFileMap GrayBitInfo;
typedef QList<GrayBitInfo> GrayBitInfoList;

struct GrayScaleInfoBaseFileMap
{
    int  configChipType = 0;
    int  partNumPerRef  = 0;
    char reserve[5]     = {0};
    int  seleteGrayBit  = 0;
    int  grayBit        = 0;
    int  oeWidthValue   = 0;
};

#pragma pack(pop)

// 业务数据(与 c# 对应)
struct GrayScaleInfoBase : public GrayBitInfo
{
    int configChipType = 0;
    int partNumPerRef  = 0;
    int seleteGrayBit  = 0;
    GrayBitInfoList grayBitInfoList;

    GrayScaleInfoBase(const GrayScaleInfoBaseFileMap* data)
        : GrayBitInfo(data->grayBit, data->oeWidthValue),
          configChipType(data->configChipType),
          partNumPerRef(data->partNumPerRef),
          seleteGrayBit(data->seleteGrayBit)
    {
        grayBitInfoList.clear();
    }
};
typedef QList<GrayScaleInfoBase> GrayScaleInfoBaseList;

#endif // DATADEF_H
