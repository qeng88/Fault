// faultmanager.h
#ifndef FAULTMANAGER_H
#define FAULTMANAGER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QSet>
#include <QDebug>

class FaultManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList faultList READ faultList NOTIFY faultListChanged)

public:
    explicit FaultManager(QObject *parent = nullptr);

    QStringList faultList() const;

public slots:
    // 接收总线上的bool故障信号
    void updateFault(int faultId, bool isFault, const QString &faultDescription);
    void clearAllFaults();
    void removeFault(int faultId); // 新增：手动移除特定故障

// 删除 checkFaultTimeout 槽函数声明
// private slots:
//     void checkFaultTimeout();

signals:
    void faultListChanged();
    void newFaultAdded(const QString &fault);
    void faultRemoved(const QString &fault);

private:
    struct FaultInfo {
        int id;
        QString description;
        bool active;
        // 删除 lastUpdateTime 成员
        // qint64 lastUpdateTime;
    };

    QHash<int, FaultInfo> m_faults;
    QStringList m_currentFaultList;
    // 删除定时器
    // QTimer *m_checkTimer;
    QSet<int> m_activeFaults;

    void updateFaultList();
};

#endif // FAULTMANAGER_H
