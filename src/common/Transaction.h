/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

// TODO make this useful

#pragma once

#include "RpmOstreeInterface.h"
#include <QObject>
#include <qdbusconnection.h>

class Transaction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(bool finished READ isFinished NOTIFY finishedChanged)

public:
    explicit Transaction(QString connectionPath, QObject *parent = nullptr);
    ~Transaction() override;

    QString title() const;

    bool isFinished();
    Q_SIGNAL void finishedChanged();

private:
    Q_SLOT void setFinished(bool success, const QString &errorMessage);
    QDBusConnection m_peerConnection;
    RpmOstreeInterface *m_rpmOstreeInterface;
    OrgProjectatomicRpmostree1TransactionInterface *m_transactionInterface;
    bool m_finished = false;
};
