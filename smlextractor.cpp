#include "smlextractor.h"

SMLExtractor::SMLExtractor(QObject *parent) :
    QObject(parent)
{



    qDebug() << "Extracting sml";

    ByteArray data=QByteArray::fromHex("1B1B1B1B010101017607000B00B7ABF9620062007263010176010107000B006839530904039FC8DE59A2350101639A31007607000B00B7ABFA620062007263070177010904039FC8DE59A23501726201650068092A7777078181C78203FF0101010104454D480177070100000009FF010101010904039FC8DE59A2350177070100010800FF63028001621E52FF56fffffffdc80177070100010801FF0101621E52FF5600000000000177070100010802FF0101621E52FF560000172A4D01770701000F0700FF0101621B52FF55000002630177078181C78205FF010101018302C27E74A3346F0E50EE7BACA859927B7CF5577E18CD5BBCCA81F3026198D55EF51B8C7100366110C035C20A62A778774301010163CDF1007607000B00B7ABFD620062007263020171016326D5000000001B1B1B1B1A");
    //QByteArray data=QByteArray::fromHex("1B1B1B1B010101017607000B00B7ABF9620062007263010176010107000B006839530904039FC8DE59A2350101639A31007607000B00B7ABFA620062007263070177010904039FC8DE59A23501726201650068092A7777078181C78203FF0101010104454D480177070100000009FF010101010904039FC8DE59A2350177070100010800FF63028001621E52FF560000172A4D0177070100010801FF0101621E52FF5600000000000177070100010802FF0101621E52FF560000172A4D01770701000F0700FF0101621B52FF55000002630177078181C78205FF010101018302C27E74A3346F0E50EE7BACA859927B7CF5577E18CD5BBCCA81F3026198D55EF51B8C7100366110C035C20A62A778774301010163CDF1007607000B00B7ABFD620062007263020171016326D5000000001B1B1B1B1A");
    //QByteArray data=QByteArray::fromHex("1B1B1B1B010101017607001900D7797162006200726301017601010700190043D3260B06454D4801001D4062360101636CE5007607001900D77972620062007263070177010B06454D4801001D4062360172620165004390ED7777078181C78203FF0101010104454D480177070100000009FF010101010B06454D4801001D4062360177070100010800FF63018201621E52FF56000045C2C80177070100010801FF0101621E52FF560000459B6C0177070100010802FF0101621E52FF56000000275C01770701000F0700FF0101621B52FF5500000BA00177078181C78205FF010101018302E050C5ACEB0A6B4C5C862D77B2C2A2502434BD1C4A9EB250CA81EF93D26D7B7A52B7F265C9BACF6A370FCF162A213DAE010101638F34007607001900D77974620062007263020171016384A400001B1B1B1B1A");
    //QByteArray data=QByteArray::fromHex("1B1B1B1B010101017605001F3A4A620062007263010176010105000A68C40B0649534B01027A20E68A0101631E2E007605001F3A4B620062007263070177010B0649534B01027A20E68A070100620AFFFF726201650013C8807777078181C78203FF010101010449534B0177070100000009FF010101010B0649534B01027A20E68A0177070100010800FF650000018201621E52FF590000000000104E700177070100010801FF0101621E52FF5900000000000FFCAC0177070100010802FF0101621E52FF5900000000000051C401770701000F0700FF0101621B520065000001A00177078181C78205FF010101018302F3C5A800D40FAAF2FF7260E38891F1C92FB4274BB6E69143D36BE7C0A36BFE5CE06803DAC0E750D422352255544B32D2010101630BEE007605001F3A4C6200620072630201710163256E001B1B1B1B1A00C48D");

  


    qDebug() << "00.0.0:" << extrDatafromSML(data_string,"000000");
    qDebug() << "00.0.9:" << extrDatafromSML(data_string,"000009");
    qDebug() << "01.8.0:" << extrDatafromSML(data_string,"010800");
    qDebug() << "02.8.0:" << extrDatafromSML(data_string,"020800");
    qDebug() << "02.8.1:" << extrDatafromSML(data_string,"020801");
    qDebug() << "02.7.0:" << extrDatafromSML(data_string,"020700");
    qDebug() << "15.7.0:" << extrDatafromSML(data_string,"0f0700");
    qDebug() << "15.8.0:" << extrDatafromSML(data_string,"0f0800");


    return;



}

QString SMLExtractor::extrDatafromSML(QString reply, QString OBISstr)
{

    QStringList message=reply.split("72630701");
    if(message.size()<2) return "";

    if(OBISstr=="000000") {
        int position=1;
        qDebug() << message[1].mid(0,40);

        QString clientID=extractObisValue(message[1],&position);
        qDebug() << "clientID:" << clientID << "Next pos:" << position;

        QString serverID=extractObisValue(message[1],&position);
        qDebug() << "serverID:" << serverID << "Next pos:" << position;



        QByteArray sn_ba=QByteArray::fromHex(serverID.toUtf8());
        QString Ascii_sn(sn_ba);
        qDebug() << "SerialNumber:" << serverID << Ascii_sn;
        return serverID;

    }


    QStringList obis=message[1].split("77",QString::SkipEmptyParts);


    foreach(QString o,obis) {
        if(!o.endsWith("01"))continue;
        if(o.size()<=10) continue;
        QString content=o;
        QString obis_content=content.mid(1,13);
        if(obis_content.contains(OBISstr)) {
            return extractContentBasedOnObis(content);
        }
        else continue;
    }


    return "";


}

QString SMLExtractor::extractContentBasedOnObis(QString content)
{
    QString obis_content=content.mid(1,13);
    QByteArray b_content=QByteArray::fromHex(content.toUtf8());

    qDebug() << "Handling ObisCode:" << obis_content << "Content:" << b_content.toHex();
    qDebug() << "----------------Extracting----------------";

    int position=0;
    QString obiscode=extractObisValue(content,&position);
    qDebug() << "obiscode:" << obiscode << "Next pos:" << position;

    QString status=extractObisValue(content,&position);
    qDebug() << "Status:" << status.toLong() << "Next pos:" << position;
    QString valTime=extractObisValue(content,&position);
    qDebug() << "valTime:" << valTime.toLong() << "Next pos:" << position;

    QString unit=extractObisValue(content,&position);
    qDebug() << "unit:" << unit.toLong() << "Next pos:" << position;

    QString scaler=extractObisValue(content,&position);
    qDebug() << "scaler:" << scaler.toLong() << "Next pos:" << position;

    QString value=extractObisValue(content,&position);
    qDebug() << "value:" << value.toLong() << "Next pos:" << position;

    double scalerval=pow10(scaler.toInt());

    if(scaler.toInt()==0||scaler.toInt()==1)scalerval=1;

    double dval=value.toDouble();
    dval=dval*(double)scalerval;
    qDebug() << "Value final:" << dval << "Scaler:" << scalerval;


    QString StringUnit=translateUnit(unit.toInt());
    qDebug() << "StringUnit:" << StringUnit;


    if(scalerval==1)return value;
    return QString::number(dval,'f');


}


QString SMLExtractor::extractObisValue(QString content, int *position)
{
    bool ok;
    int cur_pos=*position;
    char TL=content.mid(cur_pos*2,2).toInt(&ok,16);
    int lengh=getDataLengh(TL);
    QString unit=getDataType(TL);
    qDebug() << "Lengh:" << lengh << "DType:" << unit;
    if(lengh<=0) {
        int newpos=cur_pos+1;
        *position=newpos;
        return "0";
    }
    QString data=content.mid(cur_pos*2+2,lengh*2);


    int newpos=cur_pos+lengh+1;
    *position=newpos;

    qDebug() << data;

    if(unit=="octetstring")return data;
    if(unit=="int") {
        qDebug() << "Data:" << data.toLongLong(0, 16);
        QString final=QString::number(qint64(data.toLongLong(0, 16)));
        if(lengh<=4)final=QString::number(qint32(data.toLongLong(0, 16)));
        if(lengh<=2)final=QString::number(qint16(data.toLongLong(0, 16)));
        if(lengh<=1)final=QString::number(qint8(data.toLongLong(0, 16)));
        qDebug() << "Final:" << final;
        return final;
    }

    else return QString::number(data.toLongLong(0, 16));



}

QString SMLExtractor::translateUnit(int value)
{
    if(value==27)return "W";
    if(value==28)return "VA";
    if(value==29)return "var";
    if(value==30)return "Wh";
    return "";
}



QString SMLExtractor::getDataType(char vlaue)
{
    qDebug() << "DType Value:" << QByteArray::fromRawData(&vlaue,1).toHex();
    if(vlaue==0x01) return "unset";
    char val=vlaue&0xf0;
    if(val==0x20)return "bool";
    if(val==0x50||val==0xd0)return "int";
    if(val==0x60||val==0xe0)return "uint";
    if(val==0x00)return "octetstring";
    if(val==0x70)return "list";


    return "";
}

int SMLExtractor::getDataLengh(char value)
{
    char val=value&0x0f;
    return val-1;
}