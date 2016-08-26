/**
 * Copyright (c) 2016 Dmitry Ivanov
 *
 * This file is a part of QEverCloud project and is distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#include <InkNoteImageDownloader.h>
#include <qt4helpers.h>
#include "http.h"
#include <QSize>
#include <QImage>
#include <QPainter>
#include <QBuffer>

namespace qevercloud {

class InkNoteImageDownloaderPrivate
{
public:
    QList<QPair<QNetworkRequest, QByteArray> > createPostRequests(qevercloud::Guid guid,
                                                                  bool isPublic = false);

    QString m_host;
    QString m_shardId;
    QString m_authenticationToken;
    int m_width;
    int m_height;
};

InkNoteImageDownloader::InkNoteImageDownloader() :
    d_ptr(new InkNoteImageDownloaderPrivate)
{}

InkNoteImageDownloader::InkNoteImageDownloader(QString host, QString shardId, QString authenticationToken,
                                               int width, int height) :
    d_ptr(new InkNoteImageDownloaderPrivate)
{
    d_ptr->m_host = host;
    d_ptr->m_shardId = shardId;
    d_ptr->m_authenticationToken = authenticationToken;
    d_ptr->m_width = width;
    d_ptr->m_height = height;
}

InkNoteImageDownloader::~InkNoteImageDownloader()
{
    delete d_ptr;
}

InkNoteImageDownloader & InkNoteImageDownloader::setHost(QString host)
{
    d_ptr->m_host = host;
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setShardId(QString shardId)
{
    d_ptr->m_shardId = shardId;
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setAuthenticationToken(QString authenticationToken)
{
    d_ptr->m_authenticationToken = authenticationToken;
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setWidth(int width)
{
    d_ptr->m_width = width;
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setHeight(int height)
{
    d_ptr->m_height = height;
    return *this;
}

QByteArray InkNoteImageDownloader::download(Guid guid, bool isPublic)
{
    Q_D(InkNoteImageDownloader);

    QList<QPair<QNetworkRequest, QByteArray> > postRequests = d->createPostRequests(guid, isPublic);
    int numPostRequests = postRequests.size();

    QSize inkNoteImageSize(d_ptr->m_width, d_ptr->m_height);
    QScopedPointer<QImage> pAssembledInkNoteImage;

    int painterPosition = 0;
    for(int i = 0; i < numPostRequests; ++i)
    {
        int httpStatusCode = 0;
        QPair<QNetworkRequest, QByteArray> & postRequest = postRequests[i];

        QByteArray reply = simpleDownload(evernoteNetworkAccessManager(), postRequest.first,
                                          postRequest.second, &httpStatusCode);
        if (httpStatusCode != 200) {
            throw EverCloudException(QStringLiteral("HTTP Status Code = %1").arg(httpStatusCode));
        }

        QImage replyImagePart;
        Q_UNUSED(replyImagePart.loadFromData(reply, "PNG"))
        if (replyImagePart.isNull())
        {
            if (Q_UNLIKELY(pAssembledInkNoteImage.isNull())) {
                throw EverCloudException(QStringLiteral("Ink note's image part is null before even starting to assemble"));
            }

            break;
        }

        if (pAssembledInkNoteImage.isNull()) {
            pAssembledInkNoteImage.reset(new QImage(inkNoteImageSize, replyImagePart.format()));
        }

        QRect painterCurrentRect(0, painterPosition, replyImagePart.width(), replyImagePart.height());
        painterPosition += replyImagePart.height();

        QPainter painter(pAssembledInkNoteImage.data());
        painter.setRenderHints(QPainter::Antialiasing);
        painter.drawImage(painterCurrentRect, replyImagePart);

        if (painterPosition >= inkNoteImageSize.height()) {
            break;
        }
    }

    if (pAssembledInkNoteImage.isNull()) {
        return QByteArray();
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    Q_UNUSED(buffer.open(QIODevice::WriteOnly))
    pAssembledInkNoteImage->save(&buffer, "PNG");
    return imageData;
}

QList<QPair<QNetworkRequest, QByteArray> > InkNoteImageDownloaderPrivate::createPostRequests(qevercloud::Guid guid,
                                                                                             bool isPublic)
{
    QString urlPattern("https://%1/shard/%2/res/%3.ink?slice=");
    QString url = urlPattern.arg(m_host, m_shardId, guid);

    int numSlices = (m_height - 1) / 480 + 1;

    QList<QPair<QNetworkRequest, QByteArray> > result;
    result.reserve(numSlices);

    for(int i = 1; i <= numSlices; ++i)
    {
        QNetworkRequest request;
        request.setUrl(QUrl(url + QString::number(i)));
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

        QByteArray postData = ""; // not QByteArray()! or else ReplyFetcher will not work.
        if (!isPublic) {
            postData = QByteArray("auth=")+ QUrl::toPercentEncoding(m_authenticationToken);
        }

        result << qMakePair(request, postData);
    }

    return result;
}

} // namespace qevercloud
