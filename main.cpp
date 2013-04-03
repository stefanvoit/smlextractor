#include <QCoreApplication>
#include "smlextractor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SMLExtractor *sm=new SMLExtractor();

    return 1;
    return a.exec();
}
