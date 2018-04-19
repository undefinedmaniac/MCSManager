#include "mcscphandshake.h"

const QRegularExpression McscpHandshake::PROTOCOL_MATCHER(QStringLiteral("\\[HANDSHAKE]:\\[PROTOCOL:(.*)]"));

const QString McscpHandshake::PROTOCOL = QStringLiteral("MCSCPV1.0.0");

McscpHandshake::McscpHandshake()
{
}

bool McscpHandshake::processData(const QString &data)
{
    switch(mState) {
    case Idle: {
        QRegularExpressionMatch match = PROTOCOL_MATCHER.match(data);
        if (match.hasMatch()) {
            const QString serverProtocol = match.captured(1);
            if (serverProtocol.toUpper() == PROTOCOL) {
                mState = SendProtocol;
                return true;
            }
        }
        break;
    }
    case SendProtocol: {
        if (data.toUpper() == QStringLiteral("[HANDSHAKE]:[READY]")) {
            mState = SendReady;
            return true;
        }
        break;
    }
    case SendReady: {
        if (data.toUpper() == QStringLiteral("[HANDSHAKE]:[COMPLETE]")) {
            mState = Complete;
            return true;
        }
        break;
    }
    default:
        break;
    }
    mState = Failed;
    return false;
}

QString McscpHandshake::getNextMessage()
{
    switch(mState) {
    case SendProtocol:
        return QStringLiteral("[HANDSHAKE]:[PROTOCOL:") + PROTOCOL +
                QStringLiteral("]");
    case SendReady:
        return QStringLiteral("[HANDSHAKE]:[READY]");
    default:
        return QStringLiteral("");
    }
}

bool McscpHandshake::isComplete()
{
    return mState == Complete;
}
