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

#ifndef FORMULAVIEW_H
#define FORMULAVIEW_H

#include <QtGui>
#include <string>

#include "cparser.h"
#include "gfunction.h"

using namespace std;

namespace Ui {
    class FormulaView;
}

class FormulaView : public QDockWidget
{
    Q_OBJECT
public:
    FormulaView(QWidget *parent = 0);
    ~FormulaView(void);

    bool addFunc(vector<GFunction*> &gfunc) const;
    QPushButton* getPlotButton(void) const;
    QLineEdit* getFormEdit(void) const;

private:
    Ui::FormulaView *m_ui;
};

#endif // FORMULAVIEW_H
