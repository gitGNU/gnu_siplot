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

#include "gfunction.h"

GFunction::GFunction(const string &name, const string &expr) :
    m_curve(new QwtPlotCurve()),
    m_func(new Function(name, expr)),
    m_maxOn(false),
    m_minOn(false),
    m_pen(new QPen(Qt::blue)),
    m_precUser(false),
    m_show(true)
{
    m_curve->setPen(*m_pen);
}

GFunction::~GFunction(void)
{
    m_curve->detach();
    delete m_curve;
    delete m_func;
    delete m_pen;
}

QwtPlotCurve* GFunction::getCurve(void) const
{
    return m_curve;
}

const string& GFunction::getExpression(void) const
{
    return m_func->getExpression();
}

bool GFunction::getMaxOn(void) const
{
    return m_maxOn;
}

bool GFunction::getMinOn(void) const
{
    return m_minOn;
}

const string& GFunction::getName(void) const
{
    return m_func->getName();
}

QPen* GFunction::getPen(void) const
{
    return m_pen;
}

bool GFunction::getPrecUser(void) const
{
    return m_precUser;
}

bool GFunction::getShow(void) const
{
    return m_show;
}

void GFunction::setColor(const QColor col) const
{
    m_pen->setColor(col);
    m_curve->setPen(*m_pen);
}

void GFunction::setExpression(const string &expr) const
{
    m_func->setExpression(expr);
}

bool GFunction::setData(void)
{
    m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    QVector<double> xvector, yvector;
    QString errorStr = QString();

    double prec = m_func->getPrecision();
    double max = m_func->getXMax();

    for (double x = m_func->getXMin(); x <= max; x += prec) {
        try {
            double val = m_func->getValue(x);
            if (val == val) { // Otherwise it's "nan".
                yvector.push_back(val);
                xvector.push_back(x);
            }
        } catch (const string &str) {
            if (errorStr.toStdString() != str) {
                /*errorStr = str.c_str();
                QMessageBox msgBox(QMessageBox::Warning, tr("Error"), errorStr);
                msgBox.exec();*/
                return false;
            }
        }
    }

    m_curve->setData(xvector, yvector);
    return true;
}

void GFunction::setPrecOn(bool on)
{
    m_precUser = on;
}

void GFunction::setPrecision(double prec) const
{
    m_func->setPrecision(prec);
}

void GFunction::setMax(bool on)
{
    m_maxOn = on;
}

void GFunction::setMin(bool on)
{
    m_minOn = on;
}

void GFunction::setName(const string &name) const
{
    m_func->setName(name);
}

void GFunction::setShow(bool on)
{
    m_show = on;
}

void GFunction::setStyle(Qt::PenStyle i) const
{
    m_pen->setStyle(i);
    m_curve->setPen(*m_pen);
}

void GFunction::setWidth(int width) const
{
    m_pen->setWidth(width);
    m_curve->setPen(*m_pen);
}

void GFunction::setXMax(double xmax) const
{
    m_func->setXMax(xmax);
}

void GFunction::setXMin(double xmin) const
{
    m_func->setXMin(xmin);
}
