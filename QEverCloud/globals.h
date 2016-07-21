#ifndef QEVERCLOUD_GLOBALS_H
#define QEVERCLOUD_GLOBALS_H

#include "export.h"
#include <QNetworkAccessManager>

/**
 * All the library lives in this namespace.
 */
namespace qevercloud {

/**
 * All network request made by QEverCloud - including OAuth - are
 * served by this NetworkAccessManager.
 *
 * Use this function to handle proxy authentication requests etc.
 */
QEVERCLOUD_EXPORT QNetworkAccessManager * evernoteNetworkAccessManager();

/**
 * qevercloud library version.
 */
QEVERCLOUD_EXPORT const int libraryVersion = 2*10000 + 3*100 + 0;

} // namespace qevercloud

#endif // QEVERCLOUD_GLOBALS_H
