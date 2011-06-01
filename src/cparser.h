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

#ifndef CPARSER_H
#define CPARSER_H

#include <string>
#include <vector>

#include "gfunction.h"

using namespace std;

class CParser
{
public:
    CParser(const string &str, vector<GFunction*> gfunc, bool same = false);
    ~CParser(void);

    const string& getExpression(void) const;
    const string& getName(void) const;
    unsigned short getType(void) const;

    enum Type { Func, // Add function.
                Var,  // Add variable.
                Calc, // Do a calculation.
                Err   // Error.
              };

private:
    string m_expr; // Function expression.
    // vector<string> m_keywords;
    vector<GFunction*> m_gfunc;
    string m_name; // Name of function or variable.
    bool m_same;
    string m_str;  // Complete input string.
    Type m_type; // Type of command.
    // double m_val;  // Value of variable.

    void eraseSpaces(void);
    bool isAlphabetic(const string &str) const;
    bool isFuncName(const string &str) const;
    // bool isKeyword(const string &str) const;
    void parse(void);
};

#endif // CPARSER_H
