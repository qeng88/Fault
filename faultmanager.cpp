// faultmanager.cpp
#include "faultmanager.h"

FaultManager::FaultManager(QObject *parent)
    : QObject(parent)
{
    // 删除定时器相关代码
    // m_checkTimer = new QTimer(this);
    // connect(m_checkTimer, &QTimer::timeout, this, &FaultManager::checkFaultTimeout);
    // m_checkTimer->start(1000);
}

QStringList FaultManager::faultList() const
{
    return m_currentFaultList;
}

void FaultManager::updateFault(int faultId, bool isFault, const QString &faultDescription)
{
    auto it = m_faults.find(faultId);

    if (it == m_faults.end()) {
        // 新故障
        FaultInfo newFault;
        newFault.id = faultId;
        newFault.description = faultDescription;
        newFault.active = isFault;
        m_faults.insert(faultId, newFault);

        if (isFault) {
            m_activeFaults.insert(faultId);
            emit newFaultAdded(faultDescription);
        }
    } else {
        // 更新现有故障状态
        bool wasActive = it->active;
        it->active = isFault;
        it->description = faultDescription;

        if (wasActive && !isFault) {
            // 故障从活动变为非活动
            m_activeFaults.remove(faultId);
            emit faultRemoved(faultDescription);
        } else if (!wasActive && isFault) {
            // 故障从非活动变为活动
            m_activeFaults.insert(faultId);
            emit newFaultAdded(faultDescription);
        }
    }

    updateFaultList();
}

void FaultManager::removeFault(int faultId)
{
    auto it = m_faults.find(faultId);
    if (it != m_faults.end()) {
        if (it->active) {
            m_activeFaults.remove(faultId);
            emit faultRemoved(it->description);
        }
        m_faults.remove(faultId);
        updateFaultList();
    }
}

void FaultManager::clearAllFaults()
{
    // 发送故障移除信号
    for (const auto &fault : m_faults) {
        if (fault.active) {
            emit faultRemoved(fault.description);
        }
    }

    m_faults.clear();
    m_activeFaults.clear();
    updateFaultList();
}


void FaultManager::updateFaultList()
{
    QStringList newList;

    // 只添加活动的故障
    for (int faultId : m_activeFaults) {
        auto it = m_faults.find(faultId);
        if (it != m_faults.end() && it->active) {
            newList.append(QString("故障%1: %2").arg(faultId).arg(it->description));
        }
    }

    // 检查列表是否发生变化
    if (newList != m_currentFaultList) {
        m_currentFaultList = newList;
        emit faultListChanged();
    }
}
