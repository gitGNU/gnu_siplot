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
#include <QPen>
#include <QString>
#include <qwt_plot_curve.h>

#include "function.h"

class GFunction
{
public:
    GFunction(const string &name, const string &expr);
    ~GFunction(void);

    QwtPlotCurve* getCurve(void) const;
    const string& getExpression(void) const;
    bool getMaxOn(void) const;
    bool getMinOn(void) const;
    const string& getName(void) const;
    QPen* getPen(void) const;
    bool getPrecUser(void) const;
    bool getShow(void) const;
    void setColor(const QColor col) const;
    bool setData(void);
    void setExpression(const string& expr) const;
    void setMax(bool on);
    void setMin(bool on);
    void setName(const string& str) const;
    void setPrecOn(bool on);
    void setPrecision(double prec) const;
    void setShow(bool on);
    void setStyle(Qt::PenStyle i) const;
    void setWidth(int width) const;
    void setXMax(double xmax) const;
    void setXMin(double xmin) const;

private:
    QwtPlotCurve *m_curve;
    Function *m_func;
    bool m_maxOn;
    bool m_minOn;
    QPen *m_pen;
    bool m_precUser;
    bool m_show;
};

#endif // GFUNCTION_H
