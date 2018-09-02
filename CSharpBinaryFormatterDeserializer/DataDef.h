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

struct SubItemFileMap
{
    int a  = 0;
    int b  = 0;

    SubItemFileMap(int a_ = 0, int b_ = 0)
        : a(a_),
          b(b_)
    {
    }
};
typedef SubItemFileMap SubItem;
typedef QList<SubItem> SubItemList;

struct DataItemFileMap
{
    int  c          = 0;
    int  d          = 0;
    char reserve[5] = {0};
    int  e          = 0;
    int  f          = 0;
    int  g          = 0;
};

#pragma pack(pop)

// 业务数据(与 c# 对应)
struct DataItem : public SubItem
{
    int c  = 0;
    int d  = 0;
    int e  = 0;
    SubItemList subItemList;

    DataItem(const DataItemFileMap* data)
        : SubItem(data->f, data->g),
          c(data->c),
          d(data->d),
          e(data->e)
    {
        subItemList.clear();
    }
};
typedef QList<DataItem> DataItemList;

#endif // DATADEF_H
