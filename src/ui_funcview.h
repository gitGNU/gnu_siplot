/********************************************************************************
** Form generated from reading UI file 'funcview.ui'
**
** Created: Fri Apr 29 11:03:53 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCVIEW_H
#define UI_FUNCVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_FuncView
{
public:
    QVBoxLayout *verticalLayout;
    QwtPlot *m_qwtPlot;

    void setupUi(QWidget *FuncView)
    {
        if (FuncView->objectName().isEmpty())
            FuncView->setObjectName(QString::fromUtf8("FuncView"));
        FuncView->resize(440, 374);
        verticalLayout = new QVBoxLayout(FuncView);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_qwtPlot = new QwtPlot(FuncView);
        m_qwtPlot->setObjectName(QString::fromUtf8("m_qwtPlot"));
        m_qwtPlot->setLineWidth(0);

        verticalLayout->addWidget(m_qwtPlot);


        retranslateUi(FuncView);

        QMetaObject::connectSlotsByName(FuncView);
    } // setupUi

    void retranslateUi(QWidget *FuncView)
    {
        FuncView->setWindowTitle(QApplication::translate("FuncView", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FuncView: public Ui_FuncView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCVIEW_H
