#ifndef TEST_H
#define TEST_H
#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

signals:
	void sendSignal();
	void sendSignal2();

};
#endif
