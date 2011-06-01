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

#include "function.h"

Function::Function(const string name, const string &expr) :
    m_name(name),
    m_parser(new FParser(expr)),
    m_prec(0),
    m_xmax(0),
    m_xmin(0)
{
}

Function::~Function(void)
{
    delete m_parser;
}

const string& Function::getExpression(void) const
{
    return m_parser->getExpression();
}

const string& Function::getName(void) const
{
    return m_name;
}

double Function::getPrecision(void) const
{
    return m_prec;
}

double Function::getValue(double x) const
{
    return m_parser->getResult(x);
}

double Function::getXMax(void) const
{
    return m_xmax;
}

double Function::getXMin(void) const
{
    return m_xmin;
}

void Function::setExpression(const string &expr)
{
    m_parser->setExpression(expr);
}

void Function::setName(const string &name)
{
    m_name = name;
}

void Function::setPrecision(double prec)
{
    m_prec = prec;
}

void Function::setXMax(double xmax)
{
    m_xmax = xmax;
}

void Function::setXMin(double xmin)
{
    m_xmin = xmin;
}
