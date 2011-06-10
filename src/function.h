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
    void setExpression(const string &expr);

    double getMaxNum(void) const;
    void setMaxNum(double max);

    double getMinNum(void) const;
    void setMinNum(double min);

    const string& getName(void) const;
    void setName(const string &name);

    double getPrecision(void) const;
    void setPrecision(double prec);

    double getValue(double x) const;

private:
    double m_maxNum;
    double m_minNum;
    string m_name;
    FParser *m_parser;
    double m_prec;
};

#endif // FUNCTION_H
