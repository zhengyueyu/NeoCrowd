#include "NetworkReid.h"

NetworkReid::NetworkReid(QObject *parent) : QObject(parent)
{

}


QString NetworkReid::QImage2Base64(QImage* img_src)
{
    QByteArray qByteArray;
    QBuffer buf(&qByteArray);
    img_src->save(&buf, "PNG", 50);
    QByteArray img_base64 = qByteArray.toBase64();
    buf.close();
    return QString(img_base64);
}

QByteArray NetworkReid::Base64Img2Json(unsigned stamp, QString* img_base64_str)
{
    QJsonObject qJsonObject;
    QString q_stamp = QString::number(stamp);
    qJsonObject.insert("stamp", q_stamp);
    qJsonObject.insert("image", *img_base64_str);
    QJsonDocument document;
    document.setObject(qJsonObject);
    return document.toJson(QJsonDocument::Compact);
}

void NetworkReid::PostImage(QByteArray json)
{
    naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);
    request.setUrl(QUrl("http://192.168.48.1:8080"));
    reply = naManager->post(request, json.data());
}

void NetworkReid::SendQImage2ReidModel(unsigned stamp, QImage* img_src)
{
    QString base64 = QImage2Base64(img_src);
    QByteArray json = Base64Img2Json(stamp, &base64);
    PostImage(json);
}

void NetworkReid::requestFinished(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QByteArray allData = reply->readAll();
        QString all = codec->toUnicode(allData);
        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson(allData, &jsonError);
        if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
        {  // 解析未发生错误
            QJsonObject qJsonObject = document.object();
            QJsonObject::iterator iter = qJsonObject.find("stamp");
            if(iter == qJsonObject.end())
            {
                qDebug() << "request finish fail: Can\'t get stamp.";
                return;
            }
            unsigned stamp = iter.value().toInt();
            iter = qJsonObject.find("id");
            if(iter == qJsonObject.end())
            {
                qDebug() << "request finish fail: Stamp has been gotten. Can\'t get id.";
                return;
            }
            int m_id = iter.value().toInt();
            emit ID_SIGNAL(stamp, m_id);
        }
        reply->deleteLater();
    }
}


NetworkReid* CreateReid()
{
    NetworkReid* reid = new NetworkReid();
    return reid;
}
