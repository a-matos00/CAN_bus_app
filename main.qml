import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import SendData 1.0
import FormatInput 1.0

Window {
    objectName: "mainWindow"
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("CAN message sender")
    color: "grey"

    //custom QML component transfered from c++ files
    SendData {
        id: sendData
    }

    FormatInput {
        id: formatInput
    }

    //GPIO-------------------------------------------------------------------------------------------------------
    Connections {
                target: GPIOHandler;
                function onSignalPinValChange(pin, value){
                  pinTesting.text = "Change on input pin " + pin +" to value " + value;
                }
     }

    Text {
        id: pinTesting
        x: 20
        y: 214
        text: qsTr("PIN TESTING")
        font.pixelSize: 16
    }

    //~GPIO-------------------------------------------------------------------------------------------------------

    Rectangle{
        id:transmitContainer
        x: 0
        y: 71
        width: 800
        height: 137
        color:"#d2d2d2"

Rectangle {
    id: idInputContainer
    x: 117
    y: 81
    width: 179
    height: 23
    color: "#ffffff"

        TextInput {
            id: idInput
            objectName: "idInput"
            x: 0
            y: 2
            width: 142
            height: 20
            font.pixelSize: 16
            font.family: "Monospace";
            validator: RegExpValidator { regExp: /[0-9A-F]+/ }

            onTextEdited: {
              idInput.text = formatInput.formatId(idInput.text);
            }       
        }
        Button {
            id: deleteIdButton
            x: 148
            y: 0
            width: 32
            height: 24

            Image {
                x: 6
                y: 6
                width: 23
                height: 14
                source: "/delete.png"
            }

            onClicked:{
               idInput.text = formatInput.deleteLastChar(idInput.text);
               idInput.forceActiveFocus();
            }
        }
}

  Text {
      id: idLabel
      x: 117
      y: 55
      width: 52
      height: 20
      text: qsTr("ID")
      font.pixelSize: 18
      font.family:"Monospace"
  }

  Button {
      id: confirmButton
      x: 607
      y: 73
      font.pixelSize: 16
      text: qsTr("Send")
      font.family:"Monospace"

      onClicked: {
          sendData.sendMessage(idInput.text, dataInput.text);
          dataInput.text = "";
          idInput.text = "";
      }
  }

  Rectangle {
      id: dataInputContainer
      x: 334
      y: 81
      width: 233
      height: 23
      color: "#ffffff"

      TextInput{
          validator: RegExpValidator { regExp: /[0-9A-F" "]+/ }
          id: dataInput
          objectName: "dataInput"
          x: 0
          y: 4
          width: 203
          height: 15
          font.pixelSize: 14
          font.family: "Monospace";

          onTextEdited: {
            dataInput.text = formatInput.formatData(dataInput.text);
          }
      }
      Button {
          id: deleteDataButton
          x: 204
          y: 0
          width: 29
          height: 23
          Image {
              x: 2
              y: 3
              width: 26
              height: 16
              source: "/delete.png"
          }

          onClicked:{
             dataInput.text = formatInput.deleteLastChar(dataInput.text);
             dataInput.forceActiveFocus();
          }
  }

  }
  Text {
      id: dataLabel
      x: 334
      y: 55
      width: 85
      height: 21
      text: qsTr("Data")
      font.pixelSize: 18
      font.family:"Monospace"
  }

  Text {
      id: text4
      x: 8
      y: 8
      width: 178
      height: 25
      text: qsTr("Transmit message")
      font.pixelSize: 20
      font.family:"Monospace"
  }


    }

ToolBar {
    id: toolBar
    x: 0
    y: 0
    width: 800
    height: 40

    ComboBox {
        id: nodesComboBox
        x: 168
        y: 0
        width: 169
        height: 40
        objectName: "comboBox"
        model: comboModel.comboList
        background: Rectangle {
               color:"white"
           }
    }

    Text {
        id: text1
        x: 9
        y: 13
        width: 172
        height: 27
        text: qsTr("Connected nodes:")
        font.pixelSize: 16
        font.family: "Monospace";
    }
}


    Connections {
                target: recieveFramesObj
                function onSignalFrame(frame){
                   messageModel.append({"frame":frame})
                   messageList.positionViewAtEnd()
                }
    }

    ListModel {
        id: messageModel
    }

    Rectangle{
        x: 0
        y: 238
        width:800
        height:362
        color:"#d2d2d2"

        Text {
            id: text2
            x: 8
            y: 20
            width: 223
            height: 31
            text: qsTr("Recieved messages")
            font.pixelSize: 20
            font.family: "Monospace"
            minimumPixelSize: 12
        }

        Text {
            id: text3
            x: 185
            y: 71
            text: qsTr("ID")
            font.pixelSize: 14

        }

        Text {
            id: text5
            x: 232
            y: 71
            text: qsTr("Size")
            font.pixelSize: 14
        }

        Text {
            id: text6
            x: 281
            y: 71
            text: qsTr("Data")
            font.pixelSize: 14
        }


    Rectangle{
        x: 133
        y: 96
        width:534
        height:237
        color:"white"

        ListView {
            id:messageList
            x: 0
            y: 26
            width: 534
            height: 172
            model: messageModel
            ScrollIndicator.vertical: ScrollIndicator{}

            delegate: ItemDelegate {
                text: frame
                font.pixelSize: 14
                font.family: "Monospace";
            }


        }
    }
    }

    Text {
        id: rpmDisplay
        x: 471
        y: 209
        text: qsTr("RPM")
        font.pixelSize: 20

        Connections {
                    target: recieveFramesObj
                    function onSignalRPM(data){
                       rpmDisplay.text = "RPM: " + data;
                    }
        }
    }

    Text {
        id: kphDisplay
        x: 621
        y: 209
        text: qsTr("KPH")
        font.pixelSize: 20

        Connections {
                    target: recieveFramesObj
                    function onSignalKPH(data){
                        kphDisplay.text = "KPH: " + data;
                    }
        }
    }


}   //main window






/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
