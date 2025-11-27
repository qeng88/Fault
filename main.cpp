// main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "faultmanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 创建故障管理器
    FaultManager faultManager;

    QQmlApplicationEngine engine;

    // 将故障管理器暴露给QML
    engine.rootContext()->setContextProperty("faultManager", &faultManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // 模拟接收总线故障信号（在实际应用中，这里应该连接真实的信号）
    QTimer simulationTimer;
    QObject::connect(&simulationTimer, &QTimer::timeout, [&faultManager]() {
        static int counter = 0;
        counter++;

        // 模拟故障1：随机出现和消失
        if (counter == 1) {
            faultManager.updateFault(1, true, "电机过载");
        } else if (counter == 20) {
            faultManager.updateFault(1, false, "电机过载");
        }

        // 模拟故障2：随机出现和消失
        if (counter == 5) {
            faultManager.updateFault(2, true, "温度过高");
        } else if (counter == 25) {
            faultManager.updateFault(2, false, "温度过高");
        }

        // 模拟故障2：随机出现和消失
        if (counter == 10) {
            faultManager.updateFault(3, true, "温度过低");
        } else if (counter == 30) {
            faultManager.updateFault(3, false, "温度过低");
        }

        if(counter > 40) counter = 0;

        qDebug()<< "counter" << counter;
    });
    simulationTimer.start(1000);

    return app.exec();
}
