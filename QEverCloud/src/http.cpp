#include <qevercloud/exceptions.h>
#include <qevercloud/globals.h>
#include "http.h"
#include <QEventLoop>
#include <QtNetwork>
#include <QSharedPointer>
#include <QUrl>

/** @cond HIDDEN_SYMBOLS  */

namespace qevercloud {

QNetworkAccessManager* evernoteNetworkAccessManager() {
    static QSharedPointer<QNetworkAccessManager> networkAccessManager_;
    static QMutex networkAccessManagerMutex;
    QMutexLocker mutexLocker(&networkAccessManagerMutex);
    if(networkAccessManager_.isNull()) {
        networkAccessManager_ = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager);
    }
    return networkAccessManager_.data();
}

ReplyFetcher::ReplyFetcher(): success_(false), httpStatusCode_(0)
{
    ticker_ = new QTimer(this);
    connect(ticker_, SIGNAL(timeout()), this, SLOT(checkForTimeout()));
}

void ReplyFetcher::start(QNetworkAccessManager *nam, QUrl url)
{
    QNetworkRequest request;
    request.setUrl(url);
    start(nam, request);
}

void ReplyFetcher::start(QNetworkAccessManager *nam, QNetworkRequest request, QByteArray postData)
{
    httpStatusCode_= 0;
    errorText_.clear();
    receivedData_.clear();
    success_ = true; // not in finished() signal handler, it might be not called according to the docs
                     // besides, I've added timeout feature
    lastNetworkTime_ = QDateTime::currentMSecsSinceEpoch();
    ticker_->start(1000);
    if(postData.isNull()) {
        reply = QSharedPointer<QNetworkReply>(nam->get(request), &QObject::deleteLater);
    } else {
        reply = QSharedPointer<QNetworkReply>(nam->post(request, postData), &QObject::deleteLater);
    }
    connect(reply.data(), SIGNAL(finished()), this, SLOT(onFinished()));
    connect(reply.data(), SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError()));
    connect(reply.data(), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));
    connect(reply.data(), SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
}

void ReplyFetcher::onDownloadProgress(qint64, qint64)
{
    lastNetworkTime_ = QDateTime::currentMSecsSinceEpoch();
}

void ReplyFetcher::checkForTimeout()
{
    const int connectionTimeout = 30*1000;
    if((lastNetworkTime_ - QDateTime::currentMSecsSinceEpoch()) > connectionTimeout) {
        setError(QStringLiteral("Connection timeout."));
    }
}


void ReplyFetcher::onFinished()
{
    ticker_->stop();
    if(!success_) return;
    receivedData_ = reply->readAll();
    httpStatusCode_ = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    disconnect(reply.data());
    emit replyFetched(this);
}

void ReplyFetcher::onError()
{
    setError(reply->errorString());
}

void ReplyFetcher::onSslErrors(QList<QSslError> l)
{
    QString errorText = QStringLiteral("SSL Errors:\n");
    foreach(QSslError e, l) {
        errorText += e.errorString().append('\n');
    }
    setError(errorText);
}

void ReplyFetcher::setError(QString errorText)
{
    success_ = false;
    ticker_->stop();
    errorText_ = errorText;
    disconnect(reply.data());
    emit replyFetched(this);

}

QByteArray simpleDownload(QNetworkAccessManager* nam, QNetworkRequest request,
                          QByteArray postData, int * httpStatusCode) {
    ReplyFetcher f;
    QEventLoop loop;
    QObject::connect(&f, SIGNAL(replyFetched(QObject*)), &loop, SLOT(quit()));
    f.start(nam, request, postData);
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    if(httpStatusCode) *httpStatusCode = f.httpStatusCode();
    if(f.isError()) {
        throw EverCloudException(f.errorText());
    }
    return f.receivedData();
}

QNetworkRequest createEvernoteRequest(QString url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-thrift"));

#if QT_VERSION < 0x050000
    request.setRawHeader("User-Agent", QString("QEverCloud %1.%2").arg(libraryVersion / 10000).arg(libraryVersion % 10000).toLatin1());
#else
    request.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("QEverCloud %1.%2").arg(libraryVersion / 10000).arg(libraryVersion % 10000));
#endif

    request.setRawHeader("Accept", "application/x-thrift");
    return request;
}

QByteArray askEvernote(QString url, QByteArray postData) {
    int httpStatusCode = 0;
    QByteArray reply = simpleDownload(evernoteNetworkAccessManager(), createEvernoteRequest(url), postData, &httpStatusCode);
    if(httpStatusCode != 200) {
        throw EverCloudException(QStringLiteral("HTTP Status Code = %1").arg(httpStatusCode));
    }
    return reply;
}





}

/** @endcond */
