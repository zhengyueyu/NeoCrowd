#ifndef NETWORKREID_H
#define NETWORKREID_H

#include <QObject>
#include <QImage>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QTextCodec>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QBuffer>
#include <QJsonArray>
#include <QJsonObject>

class NetworkReid : public QObject
{
    Q_OBJECT

public:
    NetworkReid(QObject *parent = nullptr);
    void SendQImage2ReidModel(unsigned stamp, QImage* img_src);

private slots:
    void requestFinished(QNetworkReply* reply);

signals:
    void ID_SIGNAL(int stamp, int id);

private:
    QByteArray Base64Img2Json(unsigned stamp, QString* img_base64_str);
    QString QImage2Base64(QImage* img_src);
    void PostImage(QByteArray json);

    QNetworkRequest request;
    QNetworkAccessManager* naManager;
    QNetworkReply* reply;
};


NetworkReid* CreateReid();


#endif // NETWORKREID_H
