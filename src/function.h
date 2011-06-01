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

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "fparser.h"

using namespace std;

class Function
{
public:
    Function(const string name, const string &expr);
    ~Function(void);

    const string& getExpression(void) const;
    const string& getName(void) const;
    double getPrecision(void) const;
    double getValue(double x) const;
    double getXMax(void) const;
    double getXMin(void) const;
    void setPrecision(double prec);
    void setStr(const string &str) const;
    void setXMax(double xmax);
    void setXMin(double xmin);

private:
    string m_expr;
    string m_name;
    FParser *m_parser;
    double m_prec;
    double m_xmax;
    double m_xmin;
};

#endif // FUNCTION_H
