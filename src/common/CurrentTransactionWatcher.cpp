/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "CurrentTransactionWatcher.h"
#include "RpmOstreeInterface.h"

CurrentTransactionWatcher::CurrentTransactionWatcher(QObject *parent)
    : QObject(parent)
    , m_rpmOstreeInterface(sharedRpmOstreeInterface())
    , m_transaction(nullptr)
{
    m_serviceWatcher = new QDBusServiceWatcher(RPM_OSTREE_SERVICE_NAME,
                                               QDBusConnection::systemBus(),
                                               QDBusServiceWatcher::WatchForRegistration | QDBusServiceWatcher::WatchForUnregistration,
                                               this);

    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceRegistered, this, &CurrentTransactionWatcher::onServiceRegistered);
    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered, this, &CurrentTransactionWatcher::onServiceUnregistered);

    if (QDBusConnection::systemBus().interface()->isServiceRegistered(RPM_OSTREE_SERVICE_NAME)) {
        // When the service is registered we need to connect to the PropertiesChanged signal.
        onServiceRegistered();
        setTransaction();
    }
}

void CurrentTransactionWatcher::onServiceRegistered()
{
    QDBusConnection::systemBus().connect(RPM_OSTREE_SERVICE_NAME,
                                         u"/org/projectatomic/rpmostree1/Sysroot"_s,
                                         u"org.freedesktop.DBus.Properties"_s,
                                         u"PropertiesChanged"_s,
                                         this,
                                         SLOT(onPropertyChanged(QString, QVariantMap, QStringList)));
}

void CurrentTransactionWatcher::onServiceUnregistered()
{
    QDBusConnection::systemBus().disconnect(RPM_OSTREE_SERVICE_NAME,
                                            m_rpmOstreeInterface->sysroot()->path(),
                                            u"org.freedesktop.DBus.Properties"_s,
                                            u"PropertiesChanged"_s,
                                            this,
                                            SLOT(onPropertyChanged(QString, QVariantMap, QStringList)));
    if (m_transaction) {
        delete m_transaction;
        m_transaction = nullptr;
        Q_EMIT transactionChanged();
    }
}

void CurrentTransactionWatcher::onPropertyChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties);

    if (interfaceName != RPM_OSTREE_SERVICE_NAME + u".Sysroot"_s) {
        return;
    }

    if (changedProperties.contains(u"ActiveTransactionPath"_s)) {
        setTransaction();
    }
}

void CurrentTransactionWatcher::setTransaction()
{
    QString transactionPath = m_rpmOstreeInterface->sysroot()->activeTransactionPath();

    if (m_transaction) {
        delete m_transaction;
        m_transaction = nullptr;
    }

    if (!transactionPath.isEmpty()) {
        m_transaction = new Transaction(transactionPath);
    }

    Q_EMIT transactionChanged();
}