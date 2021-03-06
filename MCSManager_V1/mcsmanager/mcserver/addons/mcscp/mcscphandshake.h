#ifndef MCSCPHANDSHAKE_H
#define MCSCPHANDSHAKE_H

#include "mcscpglobal.h"

#include <QString>
#include <QRegularExpression>

namespace Mcscp { class McscpHandshake; }

class Mcscp::McscpHandshake
{
public:
    McscpHandshake();

    /**
     * @brief processData Processes data received from the server
     * until the handshake is complete or the connection is terminated
     * @param data The data from the server
     * @return True if the connections should be continued, false otherwise
     */
    bool processData(const QString &data);

    /**
     * @brief getNextMessage Returns the next message that the client
     * should send to the server to advance the handshake
     * @return The next message
     */
    QString getNextMessage();

    /**
     * @brief isComplete Checks if the handshake is completed
     * @return True if complete, otherwise false
     */
    bool isComplete();

    /**
     * @brief reset Resets the handshake process
     * so that it may be used with a new client
     */
    void reset();

private:
    enum State {
        Idle, SendProtocol, SendReady,
        Complete, Failed
    };

    State mState = Idle;

    static const QRegularExpression PROTOCOL_MATCHER;

    static const QString PROTOCOL;
};

#endif // MCSCPHANDSHAKE_H
