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

    //register SendData class as qml component
    qmlRegisterType<SendData>("SendData", 1, 0, "SendData");

    qmlRegisterType<FormatInput>("FormatInput", 1, 0, "FormatInput");

    //create the main window
    QQmlEngine engine;
    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));

    //model for the comboBox which contains names of connected devices
    ComboBoxModel connectedNodesComboBox;
    QStringList nodeNameList;

    QList<QCanBusDeviceInfo>device_list;   //the list will contain available CAN devices
    device_list = QCanBus::instance()->availableDevices("socketcan"); //update device list

    if( !device_list.isEmpty() )    //if there are available devices
    {
        //fill the list
        for(const QCanBusDeviceInfo &info : qAsConst(device_list))
            nodeNameList << info.name();

        connectedNodesComboBox.setComboList(nodeNameList);  //assign list to model

        //make the comboModel available to the qml file
        QQmlContext *classContext = engine.rootContext();
        classContext->setContextProperty("comboModel", &connectedNodesComboBox);
    }

    else    //if no devices are available
    {
        nodeNameList << "No device detected!";
        connectedNodesComboBox.setComboList(nodeNameList);  //assign list to model

        //make the comboModel available to the qml file
        QQmlContext *classContext = engine.rootContext();
        classContext->setContextProperty("comboModel", &connectedNodesComboBox);
    }

    //create object which reacts to recieved CAN messages
    recieveFrames recieveFramesObj;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("recieveFramesObj", &recieveFramesObj);

    QObject *mainWindowObj = component.create();    //display the main window

    return app.exec();
}
