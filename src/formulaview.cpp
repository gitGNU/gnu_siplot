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

#include "formulaview.h"
#include "ui_formulaview.h"

FormulaView::FormulaView(QWidget *parent) :
    QDockWidget(parent),
    m_ui(new Ui::FormulaView)
{
    m_ui->setupUi(this);
    setWindowTitle(tr("Input"));
    QTimer::singleShot(0, m_ui->m_formulaEdit, SLOT(setFocus()));
}

FormulaView::~FormulaView(void)
{
    delete m_ui;
}

bool FormulaView::addFunc(vector<GFunction*> &gfunc) const
{
    CParser *cpar = new CParser(m_ui->m_formulaEdit->text().toStdString(), gfunc);
    if (cpar->getType() == CParser::Func) {
        gfunc.push_back(new GFunction(cpar->getName(), cpar->getExpression()));
        delete cpar;
        return true;
    }
    delete cpar;
    return false;
}

QLineEdit* FormulaView::getFormEdit(void) const
{
    return m_ui->m_formulaEdit;
}

QPushButton* FormulaView::getPlotButton(void) const
{
    return m_ui->m_plotButton;
}
