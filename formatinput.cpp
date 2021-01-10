#include "FormatInput.h"

FormatInput::FormatInput(QObject *parent) :
QObject(parent)
{
}

/* This function formats the data input while the user is typing
   example ---> ( AB CD 45 73 )    */

QString FormatInput::formatData(QString arg_text)
{
    if(arg_text.length() > 23){
        arg_text.chop(1);
        return arg_text;
    }
    if( (arg_text.length() % 2) == 0 && (arg_text.length() == 2) )
    {
        arg_text += ' ';
    }

    else if( (arg_text.length() % 3) == 2)
    {
        arg_text += ' ';
    }

    return arg_text;
}

QString FormatInput::formatId(QString arg_text)
{
    if(arg_text.length() > 7){
        arg_text.chop(1);
        return arg_text;
    }
    return arg_text;
}


QString FormatInput::deleteLastChar(QString arg_text)
{
    arg_text.chop(1);
    return arg_text;
}
