/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QDBusArgument>
#include <QDBusMetaType>
#include <QList>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QVariantMap>

//
// Type definitions for D-Bus marshalling
//

// For 'a(us(ss)(ss))' - Upgraded/Downgraded RPMs
// Represents a single package change with old and new versions.
struct RpmDiffEntry {
    uint epoch;
    QString name;
    QString arch;
    QString oldVersion;
    QString oldRelease;
    QString newVersion;
    QString newRelease;
};
Q_DECLARE_METATYPE(RpmDiffEntry)
Q_DECLARE_METATYPE(QList<RpmDiffEntry>)

// For 'a(usss)' - Added/Removed RPMs
// Represents a single added or removed package.
struct SimpleRpmEntry {
    uint epoch;
    QString name;
    QString version;
    QString arch;
};
Q_DECLARE_METATYPE(SimpleRpmEntry)
Q_DECLARE_METATYPE(QList<SimpleRpmEntry>)

// For 'a(sua{sv})' - Advisories or RpmDiff results
// Represents an item with a name, a uint, and a variant map.
struct NamedVariantMapEntry {
    QString name;
    uint value;
    QVariantMap details;
};
Q_DECLARE_METATYPE(NamedVariantMapEntry)
Q_DECLARE_METATYPE(QList<NamedVariantMapEntry>)

// For 'a(suuasa{sv})' - Detailed Advisories
// A more complex structure for security advisories.
struct AdvisoryEntry {
    QString name;
    uint type;
    uint severity;
    QStringList cves;
    QVariantMap details;
};
Q_DECLARE_METATYPE(AdvisoryEntry)
Q_DECLARE_METATYPE(QList<AdvisoryEntry>)

// For '(tt)' - Time data in DownloadProgress
// Represents start time and elapsed time.
struct TimeTuple {
    qint64 startTime;
    qint64 elapsedTime;
};
Q_DECLARE_METATYPE(TimeTuple)

// For '(uu)' - Outstanding data in DownloadProgress
// Represents outstanding fetches and writes.
struct OutstandingTuple {
    uint outstandingFetches;
    uint outstandingWrites;
};
Q_DECLARE_METATYPE(OutstandingTuple)

// For '(uuu)' - Metadata counts in DownloadProgress
// Represents scanned, fetched, and outstanding metadata.
struct MetadataTuple {
    uint scanned;
    uint fetched;
    uint outstanding;
};
Q_DECLARE_METATYPE(MetadataTuple)

// For '(uuut)' - Delta data in DownloadProgress
// Represents delta parts and sizes.
struct DeltaTuple {
    uint totalParts;
    uint fetchedParts;
    uint totalSuperblocks;
    qint64 totalSize;
};
Q_DECLARE_METATYPE(DeltaTuple)

// For '(tt)' - Transfer data in DownloadProgress
// Represents bytes transferred and transfer rate.
// Note: Reusing TimeTuple as the signature (tt) is identical.
using TransferTuple = TimeTuple;

//
// Marshalling operator definitions
//

// Marshalling for RpmDiffEntry: (us(ss)(ss))
inline QDBusArgument &operator<<(QDBusArgument &argument, const RpmDiffEntry &entry)
{
    argument.beginStructure();
    argument << entry.epoch << entry.name;
    argument.beginStructure();
    argument << entry.oldVersion << entry.oldRelease;
    argument.endStructure();
    argument.beginStructure();
    argument << entry.newVersion << entry.newRelease;
    argument.endStructure();
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, RpmDiffEntry &entry)
{
    argument.beginStructure();
    argument >> entry.epoch >> entry.name;
    argument.beginStructure();
    argument >> entry.oldVersion >> entry.oldRelease;
    argument.endStructure();
    argument.beginStructure();
    argument >> entry.newVersion >> entry.newRelease;
    argument.endStructure();
    argument.endStructure();
    return argument;
}

// Marshalling for SimpleRpmEntry: (usss)
inline QDBusArgument &operator<<(QDBusArgument &argument, const SimpleRpmEntry &entry)
{
    argument.beginStructure();
    argument << entry.epoch << entry.name << entry.version << entry.arch;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, SimpleRpmEntry &entry)
{
    argument.beginStructure();
    argument >> entry.epoch >> entry.name >> entry.version >> entry.arch;
    argument.endStructure();
    return argument;
}

// Marshalling for NamedVariantMapEntry: (sua{sv})
inline QDBusArgument &operator<<(QDBusArgument &argument, const NamedVariantMapEntry &entry)
{
    argument.beginStructure();
    argument << entry.name << entry.value << entry.details;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, NamedVariantMapEntry &entry)
{
    argument.beginStructure();
    argument >> entry.name >> entry.value >> entry.details;
    argument.endStructure();
    return argument;
}

// Marshalling for AdvisoryEntry: (suuasa{sv})
inline QDBusArgument &operator<<(QDBusArgument &argument, const AdvisoryEntry &entry)
{
    argument.beginStructure();
    argument << entry.name << entry.type << entry.severity << entry.cves << entry.details;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, AdvisoryEntry &entry)
{
    argument.beginStructure();
    argument >> entry.name >> entry.type >> entry.severity >> entry.cves >> entry.details;
    argument.endStructure();
    return argument;
}

// Marshalling for TimeTuple: (tt)
inline QDBusArgument &operator<<(QDBusArgument &argument, const TimeTuple &t)
{
    argument.beginStructure();
    argument << t.startTime << t.elapsedTime;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, TimeTuple &t)
{
    argument.beginStructure();
    argument >> t.startTime >> t.elapsedTime;
    argument.endStructure();
    return argument;
}

// Marshalling for OutstandingTuple: (uu)
inline QDBusArgument &operator<<(QDBusArgument &argument, const OutstandingTuple &t)
{
    argument.beginStructure();
    argument << t.outstandingFetches << t.outstandingWrites;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, OutstandingTuple &t)
{
    argument.beginStructure();
    argument >> t.outstandingFetches >> t.outstandingWrites;
    argument.endStructure();
    return argument;
}

// Marshalling for MetadataTuple: (uuu)
inline QDBusArgument &operator<<(QDBusArgument &argument, const MetadataTuple &t)
{
    argument.beginStructure();
    argument << t.scanned << t.fetched << t.outstanding;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, MetadataTuple &t)
{
    argument.beginStructure();
    argument >> t.scanned >> t.fetched >> t.outstanding;
    argument.endStructure();
    return argument;
}

// Marshalling for DeltaTuple: (uuut)
inline QDBusArgument &operator<<(QDBusArgument &argument, const DeltaTuple &t)
{
    argument.beginStructure();
    argument << t.totalParts << t.fetchedParts << t.totalSuperblocks << t.totalSize;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, DeltaTuple &t)
{
    argument.beginStructure();
    argument >> t.totalParts >> t.fetchedParts >> t.totalSuperblocks >> t.totalSize;
    argument.endStructure();
    return argument;
}

//
// Registration function for D-Bus types
//

// This is called at instantiation of RpmOstreeInterface to register the types with D-Bus
inline void registerDbusTypes()
{
    // Register the struct types
    qRegisterMetaType<RpmDiffEntry>();
    qRegisterMetaType<SimpleRpmEntry>();
    qRegisterMetaType<NamedVariantMapEntry>();
    qRegisterMetaType<AdvisoryEntry>();
    qRegisterMetaType<TimeTuple>();
    qRegisterMetaType<OutstandingTuple>();
    qRegisterMetaType<MetadataTuple>();
    qRegisterMetaType<DeltaTuple>();
    qRegisterMetaType<TransferTuple>();

    // Register lists of those structs
    qRegisterMetaType<QList<RpmDiffEntry>>();
    qRegisterMetaType<QList<SimpleRpmEntry>>();
    qRegisterMetaType<QList<NamedVariantMapEntry>>();
    qRegisterMetaType<QList<AdvisoryEntry>>();

    // Register the D-Bus marshalling operators for the structs
    qDBusRegisterMetaType<RpmDiffEntry>();
    qDBusRegisterMetaType<SimpleRpmEntry>();
    qDBusRegisterMetaType<NamedVariantMapEntry>();
    qDBusRegisterMetaType<AdvisoryEntry>();
    qDBusRegisterMetaType<TimeTuple>();
    qDBusRegisterMetaType<OutstandingTuple>();
    qDBusRegisterMetaType<MetadataTuple>();
    qDBusRegisterMetaType<DeltaTuple>();
    qDBusRegisterMetaType<TransferTuple>();

    // Register the D-Bus marshalling for lists of those structs
    qDBusRegisterMetaType<QList<RpmDiffEntry>>();
    qDBusRegisterMetaType<QList<SimpleRpmEntry>>();
    qDBusRegisterMetaType<QList<NamedVariantMapEntry>>();
    qDBusRegisterMetaType<QList<AdvisoryEntry>>();
}
