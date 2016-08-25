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
 * is its non-editable image. This class retrieves just these, exclusively in PNG format.
 */
class QEVERCLOUD_EXPORT InkNoteImageDownloader
{
public:
    /**
     * @brief Default constructor.
     *
     * host, shardId, authenticationToken, width, height have to be specified before calling
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
     * @param width
     * Width of the ink note's resource
     * @param height
     * Height of the ink note's resource
     */
    InkNoteImageDownloader(QString host, QString shardId, QString authenticationToken, int width, int height);

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
     * @param width
     * Width of the ink note's resource
     */
    InkNoteImageDownloader & setWidth(int width);

    /**
     * @param height
     * Height of the ink note's resource
     */
    InkNoteImageDownloader & setHeight(int height);

    /**
     * @brief Downloads the image for the ink note.
     * @param guid
     * The guid of the ink note's resource
     * @param isPublic
     * Specify true for public ink notes. In this case authentication token is not sent to
     * with the request as it shoud be according to the docs.
     * @return downloaded data.
     *
     */
    QByteArray download(Guid guid, bool isPublic = false);

    /**
     * @brief Asynchronous version of @link download @endlink function.
     *
     * As downloading the ink note's resource image takes multiple http requests,
     * this method returns not a single AsyncResult but a multitude of them.
     *
     * Note that each AsyncResult would only receive a part of the image
     * and it would be a client's responsibility to assemble them in a full image.
     *
     * Also note that the number of AsyncResults may be larger than really required,
     * in that case some of AsyncResults would receive null images in reply.
     */
    QList<AsyncResult*> downloadAsync(Guid guid, bool isPublic = false);

    /**
     * @brief Prepares a series of POST requests for an ink note image's downloading.
     * @param guid
     * The guid of ink note's resource
     * @param isPublic
     * Specify true for public ink notes. In this case authentication token is not sent to
     * with the request as it shoud be according to the docs.
     * @return a pair of QNetworkRequest for the POST request and data that must be posted with the request.
     */
    QList<QPair<QNetworkRequest, QByteArray> > createPostRequests(qevercloud::Guid guid,
                                                                  bool isPublic = false);
private:
    InkNoteImageDownloaderPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(InkNoteImageDownloader)
};

} // namespace qevercloud

#endif // QEVERCLOD_INK_NOTE_IMAGE_DOWNLOADER_H
