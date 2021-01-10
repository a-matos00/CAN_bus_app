#ifndef FORMATINPUT_H
#define FORMATINPUT_H

#include <QObject>
#include <QQmlComponent>

/* This function formats the data input while the user is typing
   example ---> ( AB CD 45 73 )    */
class FormatInput : public QObject
{
    Q_OBJECT
    public:
    explicit FormatInput(QObject *parent = 0);
    Q_INVOKABLE QString formatData(QString arg_text);   //data input field formatting
    Q_INVOKABLE QString formatId(QString arg_text); //id input field formatting
    Q_INVOKABLE QString deleteLastChar(QString arg_text);   //delete button function

    signals:

    public slots:

};

#endif // FORMATINPUT_H
