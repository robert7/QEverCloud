#include <qevercloud/EventLoopFinisher.h>

namespace qevercloud {

class EventLoopFinisherPrivate
{
public:
    EventLoopFinisherPrivate(QEventLoop * loop, int exitCode) :
        m_loop(loop),
        m_exitCode(exitCode)
    {}

    QEventLoop *    m_loop;
    int             m_exitCode;
};

qevercloud::EventLoopFinisher::EventLoopFinisher(QEventLoop * loop, int exitCode, QObject * parent) :
    QObject(parent),
    d_ptr(new EventLoopFinisherPrivate(loop, exitCode))
{}

EventLoopFinisher::~EventLoopFinisher()
{
    delete d_ptr;
}

void qevercloud::EventLoopFinisher::stopEventLoop()
{
    Q_D(EventLoopFinisher);
    d->m_loop->exit(d->m_exitCode);
}

} // namespace qevercloud
