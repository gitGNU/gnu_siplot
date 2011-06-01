/********************************************************************************
** Form generated from reading UI file 'functionsview.ui'
**
** Created: Fri Apr 29 11:47:25 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONSVIEW_H
#define UI_FUNCTIONSVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FunctionsView
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QListWidget *m_funcList;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_delButton;

    void setupUi(QDockWidget *FunctionsView)
    {
        if (FunctionsView->objectName().isEmpty())
            FunctionsView->setObjectName(QString::fromUtf8("FunctionsView"));
        FunctionsView->resize(166, 226);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_funcList = new QListWidget(dockWidgetContents);
        m_funcList->setObjectName(QString::fromUtf8("m_funcList"));
        m_funcList->setLineWidth(0);
        m_funcList->setViewMode(QListView::ListMode);
        m_funcList->setWordWrap(false);
        m_funcList->setSelectionRectVisible(false);
        m_funcList->setSortingEnabled(false);

        verticalLayout->addWidget(m_funcList);

        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_delButton = new QPushButton(frame);
        m_delButton->setObjectName(QString::fromUtf8("m_delButton"));

        horizontalLayout->addWidget(m_delButton);


        verticalLayout->addWidget(frame);

        FunctionsView->setWidget(dockWidgetContents);

        retranslateUi(FunctionsView);

        QMetaObject::connectSlotsByName(FunctionsView);
    } // setupUi

    void retranslateUi(QDockWidget *FunctionsView)
    {
        FunctionsView->setWindowTitle(QApplication::translate("FunctionsView", "DockWidget", 0, QApplication::UnicodeUTF8));
        m_delButton->setText(QApplication::translate("FunctionsView", "&Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FunctionsView: public Ui_FunctionsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONSVIEW_H
