/* siplot -- simple graph plotter and math tool.
   Copyright (C) 2010 - 2011 David Jenni <dave.j@gmx.ch>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "functionsview.h"
#include "ui_functionsview.h"

FunctionsView::FunctionsView(QWidget *parent) :
    QDockWidget(parent),
    m_colDialog(new QColorDialog()),
    m_ui(new Ui::FunctionsView)
{
    m_ui->setupUi(this);
    setWindowTitle("Functions");

    m_ui->m_delButton->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/icons/edit-delete.png"));
    m_ui->m_toolBox->setCurrentIndex(0);
    m_ui->m_toolBox->hide();

    m_ui->m_colButton->setPalette(QPalette(Qt::blue));

    m_ui->m_precSpin->setEnabled(false);
    m_ui->m_maxSpin->setEnabled(false);
    m_ui->m_minSpin->setEnabled(false);

    connect(m_ui->m_colButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_maxCheck, SIGNAL(clicked(bool)), m_ui->m_maxSpin, SLOT(setEnabled(bool)));
    connect(m_ui->m_minCheck, SIGNAL(clicked(bool)), m_ui->m_minSpin, SLOT(setEnabled(bool)));
    connect(m_ui->m_precCheck, SIGNAL(clicked(bool)), m_ui->m_precSpin, SLOT(setEnabled(bool)));
}

FunctionsView::~FunctionsView()
{
    delete m_colDialog;
    delete m_ui;
}

void FunctionsView::addFunc(GFunction *gfunc) const
{
    QString str = gfunc->getName().c_str();
    str += "(x) = ";
    str += gfunc->getExpression().c_str();
    m_ui->m_funcList->addItem(str);

    m_ui->m_funcList->setCurrentRow(m_ui->m_funcList->count() - 1);
    m_ui->m_funcList->item(m_ui->m_funcList->count() - 1)->setSelected(true);
}

QPushButton* FunctionsView::getColButton(void) const
{
    return m_ui->m_colButton;
}

QColorDialog* FunctionsView::getColDialog(void) const
{
    return m_colDialog;
}

QPushButton* FunctionsView::getDelButton(void) const
{
    return m_ui->m_delButton;
}

QLineEdit* FunctionsView::getFuncEdit(void) const
{
    return m_ui->m_funcEdit;
}

QListWidget* FunctionsView::getFuncList(void) const
{
    return m_ui->m_funcList;
}

QCheckBox* FunctionsView::getMaxCheck(void) const
{
    return m_ui->m_maxCheck;
}

QDoubleSpinBox* FunctionsView::getMaxSpin(void) const
{
    return m_ui->m_maxSpin;
}

QCheckBox* FunctionsView::getMinCheck(void) const
{
    return m_ui->m_minCheck;
}

QDoubleSpinBox* FunctionsView::getMinSpin(void) const
{
    return m_ui->m_minSpin;
}

QCheckBox* FunctionsView::getPrecCheck(void) const
{
    return m_ui->m_precCheck;
}

QDoubleSpinBox* FunctionsView::getPrecSpin(void) const
{
    return m_ui->m_precSpin;
}

QCheckBox* FunctionsView::getShowCheck(void) const
{
    return m_ui->m_showCheck;
}

QComboBox* FunctionsView::getStyleCombo(void) const
{
    return m_ui->m_styleCombo;
}

QSpinBox* FunctionsView::getWidthSpin(void) const
{
    return m_ui->m_widthSpin;
}

void FunctionsView::setFuncExpression(GFunction *gfunc) const
{
    QString str = gfunc->getName().c_str();
    str += "(x) = ";
    str += gfunc->getExpression().c_str();
    m_ui->m_funcList->item(m_ui->m_funcList->currentRow())->setText(str);
}

void FunctionsView::setProperties(GFunction *gfunc)
{
    if (m_ui->m_funcList->count() == 1)
        this->show();

    if (gfunc != 0) {
        m_ui->m_toolBox->show();

        m_ui->m_colButton->setPalette(QPalette(gfunc->getPen()->color()));
        m_ui->m_showCheck->setChecked(gfunc->getShow());
        m_ui->m_funcEdit->setText(QString::fromStdString(gfunc->getName() + "(x) = " + gfunc->getExpression()));
        m_ui->m_precCheck->setChecked(gfunc->getPrecUser());
        m_ui->m_precSpin->setEnabled(gfunc->getPrecUser());
        m_ui->m_maxCheck->setChecked(gfunc->getMaxOn());
        m_ui->m_maxSpin->setEnabled(gfunc->getMaxOn());
        m_ui->m_minCheck->setChecked(gfunc->getMinOn());
        m_ui->m_minSpin->setEnabled(gfunc->getMinOn());
        m_ui->m_widthSpin->setValue(gfunc->getPen()->width());
    } else {
        m_ui->m_toolBox->show();
        this->hide();
    }
}
