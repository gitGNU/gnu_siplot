/********************************************************************************
** Form generated from reading UI file 'settingsview.ui'
**
** Created: Fri Apr 29 11:47:25 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSVIEW_H
#define UI_SETTINGSVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsView
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *m_coordCheck;
    QCheckBox *m_gridCheck;

    void setupUi(QDockWidget *SettingsView)
    {
        if (SettingsView->objectName().isEmpty())
            SettingsView->setObjectName(QString::fromUtf8("SettingsView"));
        SettingsView->resize(108, 70);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_coordCheck = new QCheckBox(dockWidgetContents);
        m_coordCheck->setObjectName(QString::fromUtf8("m_coordCheck"));
        m_coordCheck->setChecked(true);

        verticalLayout_2->addWidget(m_coordCheck);

        m_gridCheck = new QCheckBox(dockWidgetContents);
        m_gridCheck->setObjectName(QString::fromUtf8("m_gridCheck"));
        m_gridCheck->setChecked(true);

        verticalLayout_2->addWidget(m_gridCheck);

        SettingsView->setWidget(dockWidgetContents);

        retranslateUi(SettingsView);

        QMetaObject::connectSlotsByName(SettingsView);
    } // setupUi

    void retranslateUi(QDockWidget *SettingsView)
    {
        SettingsView->setWindowTitle(QApplication::translate("SettingsView", "DockWidget", 0, QApplication::UnicodeUTF8));
        m_coordCheck->setText(QApplication::translate("SettingsView", "&Coordinates", 0, QApplication::UnicodeUTF8));
        m_gridCheck->setText(QApplication::translate("SettingsView", "Show &Grid", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsView: public Ui_SettingsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSVIEW_H
