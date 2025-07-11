/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "Transaction.h"
#include "RpmOstreeInterface.h"

Transaction::Transaction(QString connectionAddress, QObject *parent)
    : QObject(parent)
    , m_peerConnection(QDBusConnection::connectToPeer(connectionAddress, u"hephaestus_transaction"_s))
    , m_rpmOstreeInterface(sharedRpmOstreeInterface())
    , m_transactionInterface(m_rpmOstreeInterface->transaction(m_peerConnection))
{
    connect(m_transactionInterface, &OrgProjectatomicRpmostree1TransactionInterface::Finished, this, &Transaction::setFinished);

    Q_EMIT finishedChanged();
}

Transaction::~Transaction()
{
    m_peerConnection.disconnectFromPeer(u"hephaestus_transaction"_s);
    delete m_transactionInterface;
}

QString Transaction::title() const
{
    return m_transactionInterface->title();
}

bool Transaction::isFinished()
{
    return m_finished;
}

// FIXME: This doesn't seem to ever get called?
// It seems like the peer connection is holding the transaction open until a timeout.
void Transaction::setFinished(bool success, const QString &errorMessage)
{
    Q_UNUSED(success);
    Q_UNUSED(errorMessage);
    m_finished = true;
    Q_EMIT finishedChanged();
}
