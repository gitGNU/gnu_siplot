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

#ifndef GFUNCTION_H
#define GFUNCTION_H

#include <QMessageBox>
#include <QString>
#include <qwt_plot_curve.h>

#include "function.h"

class GFunction
{
public:
    GFunction(const string &name, const string &expr);
    ~GFunction(void);

    QwtPlotCurve* getCurve(void) const;
    const string& getFuncExpression(void) const;
    const string& getFuncName(void) const;
    bool setData(void);
    void setPrecision(double prec) const;
    void setXMax(double xmax) const;
    void setXMin(double xmin) const;

private:
    QwtPlotCurve *m_curve;
    Function *m_func;
};

#endif // GFUNCTION_H
