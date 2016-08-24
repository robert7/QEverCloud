/**
 * Copyright (c) 2016 Dmitry Ivanov
 *
 * This file is a part of QEverCloud project and is distributed under the terms of MIT license:
 * https://opensource.org/licenses/MIT
 */

#ifndef QEVERCLOD_INK_NOTE_IMAGE_DOWNLOADER_H
#define QEVERCLOD_INK_NOTE_IMAGE_DOWNLOADER_H

#include "export.h"
#include "AsyncResult.h"
#include "generated/types.h"
#include <QByteArray>
#include <QString>
#include <QNetworkAccessManager>

namespace qevercloud {

/** @cond HIDDEN_SYMBOLS  */
class InkNoteImageDownloaderPrivate;
/** @endcond */

/**
 * @brief the class is for downloading the images of ink notes which can be created
 * with the official Evernote client on Windows (only with it, at least at the time
 * of this writing).
 *
 * On all other platforms the most one can get instead of the actual ink note
 * is its non-editable image. This class retrieves just these.
 */
class QEVERCLOUD_EXPORT InkNoteImageDownloader
{
public:
    /**
     * Specifies image type of the returned thumbnail.
     *
     * Can be PNG, JPEG, GIF or BMP.
     */
    struct ImageType {
        enum type {PNG, JPEG, GIF, BMP};
    };

    /**
     * @brief Default constructor.
     *
     * host, shardId, authenticationToken have to be specified before calling
     * @link download @endlink or @link createPostRequest @endlink
     */
    InkNoteImageDownloader();

    /**
     * @brief Constructs InkNoteImageDownloader.
     * @param host
     * www.evernote.com or sandbox.evernote.com
     * @param shardId
     * You can get the value from UserStore service or as a result of an authentication.
     * @param authenticationToken
     * For working private ink notes you must supply a valid authentication token.
     * For public resources the value specified is not used.
     * @param imageType
     * Ink note image type. See ImageType. By default PNG is used.
     */
    InkNoteImageDownloader(QString host, QString shardId, QString authenticationToken,
                           ImageType::type imageType = ImageType::PNG);

    virtual ~InkNoteImageDownloader();

    /**
     * @param host
     * www.evernote.com or sandbox.evernote.com
     */
    InkNoteImageDownloader & setHost(QString host);

    /**
     * @param shardId
     * You can get the value from UserStore service or as a result of an authentication.
     */
    InkNoteImageDownloader & setShardId(QString shardId);

    /**
     * @param authenticationToken
     * For working private ink notes you must supply a valid authentication token.
     * For public resources the value specified is not used.
     */
    InkNoteImageDownloader & setAuthenticationToken(QString authenticationToken);

    /**
     * @param imageType
     * InkNoteImageDownloader image type. See ImageType. By default PNG is used.
     */
    InkNoteImageDownloader & setImageType(ImageType::type imageType);

    /**
     * @brief Downloads the image for the ink note.
     * @param guid
     * The ink note's resource guid
     * @param isPublic
     * Specify true for public ink notes. In this case authentication token is not sent to
     * with the request as it shoud be according to the docs.
     * @return downloaded data.
     *
     */
    QByteArray download(Guid guid, bool isPublic = false);

    /** Asynchronous version of @link download @endlink function*/
    AsyncResult * downloadAsync(Guid guid, bool isPublic = false);

    /**
     * @brief Prepares a POST request for the ink note's image download.
     * @param guid
     * The ink note's resource guid
     * @param isPublic
     * Specify true for public ink notes. In this case authentication token is not sent to
     * with the request as it shoud be according to the docs.
     * @return a pair of QNetworkRequest for the POST request and data that must be posted with the request.
     */
    QPair<QNetworkRequest, QByteArray> createPostRequest(qevercloud::Guid guid,
                                                         bool isPublic = false);
};

} // namespace qevercloud

#endif // QEVERCLOD_INK_NOTE_IMAGE_DOWNLOADER_H
