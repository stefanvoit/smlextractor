#ifndef SMLEXTRACTOR_H
#define SMLEXTRACTOR_H

#include <QObject>
#include <QtCore>

class SMLExtractor : public QObject
{
    Q_OBJECT
public:
    explicit SMLExtractor(QObject *parent = 0);

private:
    QString extrDatafromSML(QString reply, QString OBISstr);
    QString extractContentBasedOnObis(QString content);
    QString getDataType(char vlaue);
    int getDataLengh(char value);
    QString extractObisValue(QString content,int *position);
    QString translateUnit(int value);
    
signals:
    
public slots:
    
};

#endif // SMLEXTRACTOR_H
