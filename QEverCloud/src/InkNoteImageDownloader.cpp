#include "InkNoteImageDownloader.h"

namespace qevercloud {

InkNoteImageDownloader::InkNoteImageDownloader()
{
    // TODO: implement
}

InkNoteImageDownloader::InkNoteImageDownloader(QString host, QString shardId, QString authenticationToken, InkNoteImageDownloader::ImageType::type imageType)
{
    // TODO: implement
}

InkNoteImageDownloader::~InkNoteImageDownloader()
{}

InkNoteImageDownloader & InkNoteImageDownloader::setHost(QString host)
{
    // TODO: implement
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setShardId(QString shardId)
{
    // TODO: implement
    return *this;
}

InkNoteImageDownloader &InkNoteImageDownloader::setAuthenticationToken(QString authenticationToken)
{
    // TODO: implement
    return *this;
}

InkNoteImageDownloader & InkNoteImageDownloader::setImageType(InkNoteImageDownloader::ImageType::type imageType)
{
    // TODO: implement
    return *this;
}

QByteArray InkNoteImageDownloader::download(Guid guid, bool isPublic)
{
    // TODO: implement
    return QByteArray();
}

AsyncResult * InkNoteImageDownloader::downloadAsync(Guid guid, bool isPublic)
{
    // TODO: implement
    return NULL;
}

QPair<QNetworkRequest, QByteArray> InkNoteImageDownloader::createPostRequest(Guid guid, bool isPublic)
{
    return QPair<QNetworkRequest, QByteArray>();
}

} // namespace qevercloud
