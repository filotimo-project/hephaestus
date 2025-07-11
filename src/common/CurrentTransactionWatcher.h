/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "RpmOstreeInterface.h"
#include "Transaction.h"
#include <QDBusServiceWatcher>
#include <QObject>

class CurrentTransactionWatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Transaction *transaction READ transaction NOTIFY transactionChanged)

public:
    explicit CurrentTransactionWatcher(QObject *parent = nullptr);

    Transaction *transaction() const
    {
        return m_transaction;
    }

    Q_SIGNAL void transactionChanged();

private:
    Q_SLOT void onPropertyChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);
    Q_SLOT void onServiceRegistered();
    Q_SLOT void onServiceUnregistered();
    void setTransaction();

    RpmOstreeInterface *m_rpmOstreeInterface;
    Transaction *m_transaction;
    QDBusServiceWatcher *m_serviceWatcher;
};
