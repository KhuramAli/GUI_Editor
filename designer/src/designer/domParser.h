#ifndef DOMPARSER_H
#define DOMPARSER_H


#include <QDomDocument>
#include <QXmlStreamWriter>
#include <QFile>
#include <QVector>
#include <QHash>
#include <QDir>
#include <QStringList>
#include <QWidget>

class domParser
{
public:

    void writeWddx(QFile *, QString);

private:
    QXmlStreamWriter uiWriter;
    QDomDocument doc;

    struct widgetStruct
    {
        QString widgetName;
        QString id;
        QString name;
        QString type;
        QString title;
        QString layout;
        QString help;
        QString action;
        QString geometry;
        QString editable;
        QString value;
        QString minimumLength;
        QHash <QString, QString> dynamicProperty;
    };

    QDir dir;
    QString formTitle;
    QHash <QString, QString>runAction;
    QVector <widgetStruct*> list;
    QStringList flexProList;
    QHash<QString,QString>::const_iterator i;
    QWidgetList * widgetList;

    void parseElement(QDomElement root, QString tag);
    void widget(QDomElement parentElement, QString att, widgetStruct * flexWidget);
    void actions(QDomElement parentElement);
    void parseFlexProperties(QString name);

    void titleDefault ();
    void closingDefault();

    void writeFile (widgetStruct * newWidget);
    void writeFile ();
    QByteArray writeFlexview (QDomDocument doc);

};

#endif // DOMPARSER_H

