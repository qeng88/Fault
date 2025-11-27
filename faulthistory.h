#ifndef FAULTHISTORY_H
#define FAULTHISTORY_H

#include <QObject>

class FaultHistory : public QObject
{
    Q_OBJECT
public:
    explicit FaultHistory(QObject *parent = nullptr);

signals:

};

#endif // FAULTHISTORY_H
