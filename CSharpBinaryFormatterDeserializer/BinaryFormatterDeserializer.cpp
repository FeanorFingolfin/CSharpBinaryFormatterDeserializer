/**
 * @file          BinaryFormatterDeserializer.h
 * @brief         c# BinaryFormatter 的反序列化工具类定义
 * @author        Narsil
 * @version       0.1
 * @date          2018.09.02
 */
#include <QFile>
#include "BinaryFormatterDeserializer.h"

bool BinaryFormatterDeserializer::deserialize(const QString& fileName, DataItemList& itemList)
{
    // 解析规则:
    // GrayScaleInfoBase[] 大小: GrayScaleInfo.GrayScaleInfoBase[] 后 11
    // GrayBitInfo[] 大小: GrayScaleInfo.GrayBitInfo[] 后 11(偏移量 18)
    // GrayScaleInfoBase 的值: value__ + 6(18)
    // GrayBitInfo 的值: _grayBit\r_oeWidthValue + 8(9)
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        file.close();
        return false;
    }
    QByteArray data = file.readAll();

    // 获取 GrayScaleInfoBase[] 大小
    const char* c_grayScaleInfoBaseCntIndicator = "GrayScaleInfo.GrayScaleInfoBase[]";
    const int c_grayScaleInfoBaseCntOffset = 11;
    int grayScaleCntOffset = data.indexOf(c_grayScaleInfoBaseCntIndicator) + qstrlen(c_grayScaleInfoBaseCntIndicator) + c_grayScaleInfoBaseCntOffset;
    int grayScaleCnt = *(int*)(data.data() + grayScaleCntOffset);

    // 获取每个 GrayScaleInfoBase 内 grayBitInfoList 的元素个数
    const char* c_grayBitInfoCntIndicator = "GrayScaleInfo.GrayBitInfo[]";
    const int c_grayBitInfoCntInitOffset = c_grayScaleInfoBaseCntOffset;
    const int c_grayBitInfoCntOffset = 18;
    QList<int> grayBitVecCntList;
    grayBitVecCntList.reserve(grayScaleCnt);
    int grayBitCntOffset = data.indexOf(c_grayBitInfoCntIndicator) + qstrlen(c_grayBitInfoCntIndicator) + c_grayBitInfoCntInitOffset;
    for (int i = 0; i < grayScaleCnt; ++i)
    {
        int cnt = *(int*)(data.data() + grayBitCntOffset);
        grayBitVecCntList.append(cnt);
        grayBitCntOffset += sizeof(int);
        grayBitCntOffset += c_grayBitInfoCntOffset;
    }

    // 获取 GrayScaleInfoBase[] 数据
    itemList.clear();
    itemList.reserve(grayScaleCnt);
    const char* c_grayScaleInfoBaseDataIndicator = "value__";
    const char* c_grayBitDataIndicator = "_grayBit\r_oeWidthValue";
    const int c_grayScaleDataInitOffset = 6;
    const int c_grayBitDataInitOffset = 8;
    const int c_grayScaleDataOffset = 18;
    const int c_grayBitDataOffset = 9;
    int grayScaleDataOffset = data.indexOf(c_grayScaleInfoBaseDataIndicator) + qstrlen(c_grayScaleInfoBaseDataIndicator) + c_grayScaleDataInitOffset;
    int grayBitDataOffset = data.indexOf(c_grayBitDataIndicator) + qstrlen(c_grayBitDataIndicator) + c_grayBitDataInitOffset;
    for (int i = 0; i < grayScaleCnt; ++i)
    {
        DataItemFileMap* grayScaleFileMap = (DataItemFileMap*)(data.data() + grayScaleDataOffset);
        DataItem grayScale(grayScaleFileMap);

        int grayBitCnt = grayBitVecCntList[i]; // 获取当前 grayBitInfoList 的元素个数
        for (int j = 0; j < grayBitCnt; ++j)
        {
            SubItemFileMap* grayBit = (SubItemFileMap*)(data.data() + grayBitDataOffset);
            grayScale.subItemList.append(*grayBit);
            grayBitDataOffset += sizeof(SubItemFileMap);
            grayBitDataOffset += c_grayBitDataOffset;
        }
        itemList.append(grayScale);
        grayScaleDataOffset += sizeof(DataItemFileMap);
        grayScaleDataOffset += c_grayScaleDataOffset;
    }
    return true;
}
