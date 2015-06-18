#include "domParser.h"
#include "flexview_properties.h"
#include "qdesigner_toolwindow.h"


#include <iostream>
#include <qDebug>
#include <QFileInfo>


#define     _widget        "widget"
#define     _action        "action"
#define     _tagclass      "class"
#define     _name          "name"
#define     _property      "property"
#define     _text          "text"
#define     _toolTip       "toolTip"
#define     _maintag       "QDialog"
#define     _windowTitle   "windowTitle"
#define     _QWidget       "QWidget"
#define     _QRbutton      "QRadioButton"
#define     _QCbox         "QCheckBox"
#define     _QTview        "QTableView"
#define     _QCombo        "QComboBox"
#define     _QPtext        "QPlainTextEdit"
#define     _QLedit        "QLineEdit"
#define     _QCalender     "QCalendarWidget"
#define     _QLable        "QLabel"
#define     _QPbutton      "QPushButton"
#define     _Geometry      "geometry"
#define     _layoutDir     "layoutDirection"
#define     _VBox          "verticalLayoutWidget"
#define     _HBox          "horizontalLayoutWidget"
#define     DIALOG          "Dialog"
#define     FORM            "Form"
#define     MAINWINDOW      "MainWindow"

void domParser::writeWddx(QFile *file, QString savefile)
{
    QFileInfo fileDir(savefile);
    QDomDocument doc;
    if(!doc.setContent(file))
        {
            qDebug() <<  "File error!";
        }

    dir.cd (fileDir.path());
    dir.mkdir("FlexView");
    dir.cd("FlexView");

    QDomElement root = doc.documentElement();

    parseElement(root,_widget);
    file->close();
    file->open(QFile::WriteOnly);
   file->write(writeFlexview(doc));
    file->close();
}//parser function


void domParser::parseElement(QDomElement root, QString tag)
{
    QDomNodeList nodes = root.elementsByTagName(tag);
    QDomElement parentElement;

    for (int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);

        if(elm.isElement())
        {
            parentElement = elm.toElement();

        }
            //identfying pushbutton.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QPbutton)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QPbutton;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "Button";
                widget(parentElement, _widget, flexWidget);
                parseFlexProperties(_QPbutton);
        }

        //identifying vertical layouts.
        if (parentElement.tagName() == _widget && parentElement.attribute(_name) == _VBox)
        {
             widgetStruct * flexWidget = new widgetStruct;
             flexWidget->widgetName = _QWidget;
             flexWidget->id = parentElement.attribute(_name);
             flexWidget->name = "VBox";
             widget(parentElement, _widget, flexWidget);
        }

        //identifying horizantal layouts.
        if (parentElement.tagName() == _widget && parentElement.attribute(_name) == _HBox)
        {
             widgetStruct * flexWidget = new widgetStruct;
             flexWidget->widgetName = _QWidget;
             flexWidget->id = parentElement.attribute(_name);
             flexWidget->name = "HBox";
             widget(parentElement, _widget, flexWidget);
        }
            //identfying radiobutton.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QRbutton)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QRbutton;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "RadioButton";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying checkbox.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QCbox)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QCbox;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "CheckBox";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying tableview.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QTview)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QTview;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "Table";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying combobox.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QCombo)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QCombo;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "ComboBox";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying plainTextEdit.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QPtext)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QPtext;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "PlainTextEdit";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying LineEdit.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QLedit)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QLedit;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "LineEdit";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying calander widget.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QCalender)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QCalender;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "Calander";
                widget(parentElement, _widget, flexWidget);
        }

            //identfying lable.
        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _QLable)
        {
                widgetStruct * flexWidget = new widgetStruct;
                flexWidget->widgetName = _QLable;
                flexWidget->id = parentElement.attribute(_name);
                flexWidget->name = "Lable";
                widget(parentElement, _widget, flexWidget);
        }

        if (parentElement.tagName() == _widget && parentElement.attribute(_tagclass) == _maintag)
        {
                actions(parentElement);
        }

    }//primary for loop

}//parseElement Function


void domParser::widget(QDomElement parentElement, QString att, widgetStruct * flexWidget)
{
    QDomNodeList nodes = parentElement.childNodes();
    QDomNode childNode;

                for (int j = 0; j < nodes.count(); j++)
                {
                    childNode = nodes.at(j);

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == _Geometry)
                    {
                        flexWidget->geometry = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == _layoutDir)
                    {
                        flexWidget->layout = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == _toolTip)
                    {
                        flexWidget->help = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute("stdset") == "0")
                    {
                        flexWidget->dynamicProperty.insert(childNode.toElement().attribute(_name), childNode.toElement().text());
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == "editable")
                    {
                        flexWidget->editable = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == "minimumContentsLength")
                    {
                        flexWidget->minimumLength = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == "currentText")
                    {
                        flexWidget->value = childNode.toElement().text();
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == _text)
                    {
                        flexWidget->title = childNode.toElement().text();

                        if (runAction.contains(flexWidget->title))
                        {
                            flexWidget->action = runAction.value(flexWidget->title);
                        }
                    }

                    if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == "checked")
                    {
                        flexWidget->type = childNode.toElement().text();

                        if (runAction.contains(flexWidget->title))
                        {
                            flexWidget->action = runAction.value(flexWidget->title);
                        }
                    }

           }//for loop
                list.append(flexWidget);
                writeFile(flexWidget);

}//widget Function


void domParser::actions(QDomElement parentElement)
{
    QDomNodeList nodes = parentElement.childNodes();
    QDomNode childNode;

    for (int j = 0; j < nodes.count(); j++)
    {
        childNode = nodes.at(j);

        if (childNode.toElement().tagName() == _action)
        {
            runAction.insert(childNode.toElement().attribute(_name), childNode.toElement().text());
        }

        if (childNode.toElement().tagName() == _property && childNode.toElement().attribute(_name) == _windowTitle)
        {
            formTitle = childNode.toElement().text();
        }

    }
}

void domParser::writeFile(widgetStruct *newWidget)
{
    QList<QString> list = DockedMainWindow::flex->widgetList.keys();
    QList <QString> proList;
    QString pre = "##";
    QString buttontitle ;
    QString action = "MainAction/";

    QString fileName = formTitle;
    fileName.append(newWidget->title);
    fileName.append(newWidget->name);
    fileName.append(".xml-dev");
    fileName.prepend("/");

    QString Description = formTitle;
    Description.append(newWidget->title);
    Description.append(newWidget->name);

    //Making custom directories based on widget type.

    if (newWidget->widgetName != _QWidget)
    {
        dir.mkdir("Widget");
        dir.cd("Widget");
        dir.mkdir("Control");
        dir.cd("Control");
        dir.mkdir(newWidget->name);
        dir.cd(newWidget->name);
    }else{
        dir.mkdir("views");
        dir.cd("views");
    }

    fileName.prepend(dir.absolutePath());

    QFile file (fileName);
    file.open(QIODevice::WriteOnly);

     if (newWidget->widgetName != _QWidget)
     {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }else{
         dir.cdUp();
     }
    uiWriter.setAutoFormatting(true);
    uiWriter.setDevice(&file);

    uiWriter.writeStartDocument();

    uiWriter.writeStartElement("wddxPacket");
    uiWriter.writeStartElement("header/");
    uiWriter.writeStartElement("data");
    uiWriter.writeStartElement("struct");

    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name","description");
    uiWriter.writeTextElement("string", Description);
    uiWriter.writeEndElement();

    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "name");
    uiWriter.writeTextElement("string", newWidget->name);
    uiWriter.writeEndElement();

// incase of Checkbox.
    if (newWidget->widgetName == _QCbox)
    {
        if (newWidget->type == "true")
        {
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","checked");
            uiWriter.writeTextElement("string", "true");
            uiWriter.writeEndElement();

        }else{
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","checked");
            uiWriter.writeTextElement("string", "false");
            uiWriter.writeEndElement();
             }
    }


//incase of Push Button.
    if (newWidget->widgetName == _QPbutton)
    {
        buttontitle = newWidget->title;
        buttontitle.prepend(pre);
        buttontitle.append(pre);

            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","title");
            uiWriter.writeTextElement("string", buttontitle);
            uiWriter.writeEndElement();

            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","buttontype");
            uiWriter.writeTextElement("string", "noicon");
            uiWriter.writeEndElement();

            //adding help (tool tip)
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","help");
            uiWriter.writeTextElement("string", newWidget->help);
            uiWriter.writeEndElement();

    }else{
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","title");
        uiWriter.writeTextElement("string", newWidget->title);
        uiWriter.writeEndElement();

        //adding help (tool tip)
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","help");
        uiWriter.writeTextElement("string", newWidget->help);
        uiWriter.writeEndElement();
    }//if condition for checking push button.

    //incase of combobox.
    if (newWidget->widgetName == _QCombo)
    {
        if (newWidget->editable == "true")
        {
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","allowManual");
            uiWriter.writeTextElement("string", "1");
            uiWriter.writeEndElement();
         }else{
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","allowManual");
            uiWriter.writeTextElement("string", "0");
            uiWriter.writeEndElement();
        }

        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","value");
        uiWriter.writeTextElement("string", newWidget->value);
        uiWriter.writeEndElement();

        if (newWidget->minimumLength == "0")
        {
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","addEmpty");
            uiWriter.writeTextElement("string", "1");
            uiWriter.writeEndElement();
        }

        if (newWidget->minimumLength == "1")
        {
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name","addEmpty");
            uiWriter.writeTextElement("string", "0");
            uiWriter.writeEndElement();
        }

    }
    //incase of layout
    if (newWidget->widgetName == _QWidget)
    {

    }//if condition for checking layouts

    if (newWidget->layout == "Qt::RightToLeft")
    {
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","layout");
        uiWriter.writeTextElement("string", "RL");
        uiWriter.writeEndElement();
    }else{
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","layout");
        uiWriter.writeTextElement("string", "LR");
        uiWriter.writeEndElement();
    }

    if (runAction.contains(newWidget->title))
    {
        action.append(runAction.value(newWidget->title));

        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name","runAction");
        uiWriter.writeTextElement("string", action);
        uiWriter.writeEndElement();
    }
//dynamic properties.
for (i = newWidget->dynamicProperty.begin(); i != newWidget->dynamicProperty.end(); ++i)
{
    if (i.value() =="true")
    {
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name",i.key());
        uiWriter.writeTextElement("string", "1");
        uiWriter.writeEndElement();
    }

    if (i.value() =="false")
    {
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name",i.key());
        uiWriter.writeTextElement("string", "0");
        uiWriter.writeEndElement();
    }else{
        uiWriter.writeStartElement("var");
        uiWriter.writeAttribute("name",i.key());
        uiWriter.writeTextElement("string", i.value());
        uiWriter.writeEndElement();
    }
}

//for Flexview property editor properties.
for(int i = 0; i < list.size(); i++){
    if(list.value(i)!= NULL){
       if(list.value(i)== newWidget->id){
           proList = DockedMainWindow::flex->widgetList.value(list.value(i)).keys();
    }
}
    for (int j = 0; j < proList.size(); j++){
        if(proList.value(j)!= NULL){
            if(list.value(i) == newWidget->id){
            uiWriter.writeStartElement("var");
            uiWriter.writeAttribute("name",proList.value(j));
            uiWriter.writeTextElement("string",(DockedMainWindow::flex->widgetList.value(list.value(i)).value(proList.value(j))) );
            uiWriter.writeEndElement();
            }
        }
    }
    proList.clear();
}
    closingDefault();
    uiWriter.writeEndDocument();
newWidget = {0};
file.close();
}// wirte file funtion over loaded for widget struct.


void domParser::closingDefault()
{
    QList<QString> list = DockedMainWindow::flex->widgetList.keys();
    QList <QString> proList;

    //for Flexview property editor properties.
    for(int i = 0; i < list.size(); i++){
        if(list.value(i)!= NULL){
           if(list.value(i)== DIALOG || list.value(i)== FORM || list.value(i)== MAINWINDOW){
               proList = DockedMainWindow::flex->widgetList.value(list.value(i)).keys();
        }
    }
        for (int j = 0; j < proList.size(); j++){
            if(proList.value(j)!= NULL){
                if(list.value(i)== DIALOG || list.value(i)== FORM || list.value(i)== MAINWINDOW){
                uiWriter.writeStartElement("var");
                uiWriter.writeAttribute("name",proList.value(j));
                uiWriter.writeTextElement("string",(DockedMainWindow::flex->widgetList.value(list.value(i)).value(proList.value(j))) );
                uiWriter.writeEndElement();
                }
            }
        }
        proList.clear();
    }

    //adding parametersConfig
    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "parametersConfig");
    uiWriter.writeTextElement("struct/","");
    uiWriter.writeEndElement();

    //adding parameters with default value '0'
    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "parameters");
    uiWriter.writeStartElement("array");
    uiWriter.writeAttribute("length", "0");
    uiWriter.writeEndElement();
    uiWriter.writeEndElement();

    //adding open openDialog with default value
    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "openDialog");
    uiWriter.writeTextElement("string","Array");
    uiWriter.writeEndElement();

    //adding form_validation with default value '1'
    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "form_validation");

    //adding current version with default value
    uiWriter.writeStartElement("var");
    uiWriter.writeAttribute("name", "current version");
    uiWriter.writeTextElement("number","0");
    uiWriter.writeEndElement();

}//closingDefault funtion

QByteArray domParser::writeFlexview(QDomDocument doc)
{
QList<QString> list = DockedMainWindow::flex->widgetList.keys();
QList <QString> proList;

for(int i = 0; i < list.size(); i++){
    QDomElement pro = doc.createElement("Properties");
    if(list.value(i)!= NULL){
        pro.setAttribute("name", list.value(i));
        doc.appendChild(pro);
        proList = DockedMainWindow::flex->widgetList.value(list.value(i)).keys();
    }

    for (int j = 0; j < proList.size(); j++){
        if(proList.value(j)!= NULL){
            QDomElement elem = doc.createElement(proList.value(j));
            pro.appendChild(elem);
            QDomText t = doc.createTextNode(DockedMainWindow::flex->widgetList.value(list.value(i)).value(proList.value(j)));
            elem.appendChild(t);
        }
    }
proList.clear();
}

    return doc.toByteArray();
}

void domParser::parseFlexProperties(QString name)
{
    //qDebug () << name;
    //QList<QString> list = DockedMainWindow::flex->widgetList.keys();

}
