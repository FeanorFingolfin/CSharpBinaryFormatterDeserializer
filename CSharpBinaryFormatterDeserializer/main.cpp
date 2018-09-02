#include <QCoreApplication>
#include "BinaryFormatterDeserializer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString appPath = QCoreApplication::applicationDirPath();
    QString fileName = appPath + "/" + "test.bin";

    DataItemList itemList;
    bool isOK = BinaryFormatterDeserializer::deserialize(fileName, itemList);
    if (!isOK)
    {
        return -1;
    }
    return a.exec();
}
