/**
 * @file          BinaryFormatterDeserializer.h
 * @brief         c# BinaryFormatter 的反序列化工具类声明
 * @author        Narsil
 * @version       0.1
 * @date          2018.09.02
 */
#ifndef BINARYFORMATTERDESERIALIZER_H
#define BINARYFORMATTERDESERIALIZER_H

#include <QString>
#include "DataDef.h"

class BinaryFormatterDeserializer
{
public:
    /**
     * @brief   反序列化
     * @param   fileName 文件完整路径名
     * @param   itemList(out) 数据项列表
     * @return  bool 是否成功
     */
    static bool deserialize(const QString& fileName, DataItemList& itemList);
};

#endif // BINARYFORMATTERDESERIALIZER_H
