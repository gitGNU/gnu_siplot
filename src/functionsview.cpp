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
    m_ui(new Ui::FunctionsView)
{
    m_ui->setupUi(this);
    setWindowTitle("Functions");
}

FunctionsView::~FunctionsView()
{
    delete m_ui;
}

void FunctionsView::addFunc(GFunction *gfunc) const
{
    QString str = gfunc->getFuncName().c_str();
    str += "(x) = ";
    str += gfunc->getFuncExpression().c_str();
    m_ui->m_funcList->addItem(str);
}

QPushButton* FunctionsView::getDelButton(void) const
{
    return m_ui->m_delButton;
}

QListWidget* FunctionsView::getFuncList(void) const
{
    return m_ui->m_funcList;
}
