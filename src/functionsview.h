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

#ifndef FUNCTIONSVIEW_H
#define FUNCTIONSVIEW_H

#include <QtGui>

#include "gfunction.h"

namespace Ui {
    class FunctionsView;
}

class FunctionsView : public QDockWidget
{
    Q_OBJECT
public:
    FunctionsView(QWidget *parent = 0);
    ~FunctionsView(void);

    void addFunc(GFunction *gfunc) const;
    QPushButton* getColButton(void) const;
    QColorDialog* getColDialog(void) const;
    QPushButton* getDelButton(void) const;
    QLineEdit* getFuncEdit(void) const;
    QListWidget* getFuncList(void) const;
    QCheckBox* getMaxCheck(void) const;
    QDoubleSpinBox* getMaxSpin(void) const;
    QCheckBox* getMinCheck(void) const;
    QDoubleSpinBox* getMinSpin(void) const;
    QCheckBox* getPrecCheck(void) const;
    QDoubleSpinBox* getPrecSpin(void) const;
    QCheckBox* getShowCheck(void) const;
    QComboBox* getStyleCombo(void) const;
    QDoubleSpinBox* getWidthSpin(void) const;
    void setFuncExpression(GFunction *gfunc) const;
    void setProperties(GFunction *gfunc);

private:
    QColorDialog *m_colDialog;
    Ui::FunctionsView *m_ui;
};

#endif // FUNCTIONSVIEW_H
