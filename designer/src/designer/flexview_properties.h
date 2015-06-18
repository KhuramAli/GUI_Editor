#ifndef FLEXVIEW_PROPERTIES_H
#define FLEXVIEW_PROPERTIES_H

#include <QDialog>
#include <QHash>
#include <QPair>

class QCheckBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QStringList;
class QComboBox;
class QVBoxLayout;
class QScrollArea;
class QFile;
class domParser;
class QStackedWidget;

class flexview_properties : public QDialog
{
    Q_OBJECT

   friend class domParser;
   friend class QDesignerActions;

public:
    flexview_properties(QWidget *parent = 0);
    ~flexview_properties();
    static QString getClassName();
    void clear();
    void setWidgetName(QWidget *current);
    void addProperty(QString propertyName, QString propertyType, QStringList comboList);
    void showProperty();
    void removeProperties(QString propertyName);
    void saveSettings (QHash<QPair <QString, QString>,QString> newProperties);
    QStringList* getPropertyList();
    QHash<QPair <QString, QString>, QString> saveProperties();

private slots:
    void showDialog();
    void showRemove();
    void updateList();

private:
    void loadSettings ();
    void loadFormSettings();
    void loadDialogSettings();
    void loadMainWindowSettings();
    void loadButtonSettings();
    void loadCheckboxSettings();
    void loadTextboxSettings();
    void loadMtextEditSettings();
    void loadComboboxSettings();
    void loadLabelSettings();
    void loadCalanderSettings();
    void loadTableSettings();
    void loadLayoutSettings();
    void updatePropertyList(QWidget* stackedWidget);

    static QWidget *formProperties;
    static QWidget *mainwindowProperties;
    static QWidget *dialogProperties;
    static QWidget *buttonProperties;
    static QWidget *checkboxProperties;
    static QWidget *textboxProperties;
    static QWidget *mtexteditProperties;
    static QWidget *comboboxProperties;
    static QWidget *labelProperties;
    static QWidget *calanderProperties;
    static QWidget *tableProperties;
    static QWidget *layoutProperties;
    static QWidget *tempwidget;
    static QString className;

    QLabel          *widgetname;
    QPushButton     *newProperty;
    QPushButton     *removeProperty;

    QVBoxLayout     *mainLayout;
    QVBoxLayout     *newmainwindowlayout;
    QVBoxLayout     *newformlayout;
    QVBoxLayout     *newdialoglayout;
    QVBoxLayout     *newbuttonboxlayout;
    QVBoxLayout     *newcheckboxlayout;
    QVBoxLayout     *newtextboxlayout;
    QVBoxLayout     *newmtexteditlayout;
    QVBoxLayout     *newcomboboxlayout;
    QVBoxLayout     *newlabellayout;
    QVBoxLayout     *newcalanderlayout;
    QVBoxLayout     *newtablelayout;
    QVBoxLayout     *newlayoutlayout;
    QScrollArea     *scrollArea;
    QStackedWidget  *stackArea;
    QWidget         *currentWidget = NULL;

    typedef QPair <QString, QString> widget_key;
    QHash<widget_key, QString> newProperties;
    QHash<QString, QHash<QString,QString>> widgetList;
    QStringList stringList;
    QFile * settingFile;
};

#endif // FLEXVIEW_PROPERTIES_H
