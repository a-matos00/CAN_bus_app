#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlComponent>
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QList>
#include <QQmlContext>
#include <QCanBusFrame>

#include "SendData.h"   //sends data to all CAN nodes
#include "FormatInput.h"    //input field formatting
#include "comboboxmodel.h"  //model for storing the available nodes list to a combobox
#include "recieveFrames.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<SendData>("SendData", 1, 0, "SendData");    //register SendData class as qml component
    qmlRegisterType<FormatInput>("FormatInput", 1, 0, "FormatInput");

    //create the main window
    QQmlEngine engine;
    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));

    //Check if the socketCAN plugin is avaliable(for debugging)
    /*
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
        qInfo() <<"socketCAN plugin avaliable";
     }
     */

    QList<QCanBusDeviceInfo>device_list;   //will contain available CAN devices
    device_list = QCanBus::instance()->availableDevices("socketcan");   //update node list

    //model for the comboBox which contains names of connected devices
    ComboBoxModel connectedNodesComboBox;

    QStringList nodeNameList;
    //fill the list
    for(const QCanBusDeviceInfo &info : qAsConst(device_list))
        nodeNameList << info.name();

    connectedNodesComboBox.setComboList(nodeNameList);  //assign list to model

    //make the comboModel available to the qml file
    QQmlContext *classContext = engine.rootContext();
    classContext->setContextProperty("comboModel", &connectedNodesComboBox);

    recieveFrames recieveFramesObj;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("recieveFramesObj", &recieveFramesObj);
    QObject *mainWindowObj = component.create();    //display the main window


    return app.exec();
}
