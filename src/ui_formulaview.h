/********************************************************************************
** Form generated from reading UI file 'formulaview.ui'
**
** Created: Fri Apr 29 11:03:53 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMULAVIEW_H
#define UI_FORMULAVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormulaView
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_formulaEdit;
    QPushButton *m_plotButton;

    void setupUi(QDockWidget *FormulaView)
    {
        if (FormulaView->objectName().isEmpty())
            FormulaView->setObjectName(QString::fromUtf8("FormulaView"));
        FormulaView->resize(418, 61);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_formulaEdit = new QLineEdit(dockWidgetContents);
        m_formulaEdit->setObjectName(QString::fromUtf8("m_formulaEdit"));

        horizontalLayout->addWidget(m_formulaEdit);

        m_plotButton = new QPushButton(dockWidgetContents);
        m_plotButton->setObjectName(QString::fromUtf8("m_plotButton"));

        horizontalLayout->addWidget(m_plotButton);

        FormulaView->setWidget(dockWidgetContents);

        retranslateUi(FormulaView);

        QMetaObject::connectSlotsByName(FormulaView);
    } // setupUi

    void retranslateUi(QDockWidget *FormulaView)
    {
        FormulaView->setWindowTitle(QApplication::translate("FormulaView", "DockWidget", 0, QApplication::UnicodeUTF8));
        m_plotButton->setText(QApplication::translate("FormulaView", "&Plot", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormulaView: public Ui_FormulaView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMULAVIEW_H
