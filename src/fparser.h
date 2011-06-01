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

#ifndef FPARSER_H
#define FPARSER_H

#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

class FParser
{
public:
    FParser(const string &expr);

    const string& getExpression(void) const;
    double getResult(double val);
    void setExpression(const string &expr);

    enum Token { Tok_Err,  // Unknown token.
                 Tok_Num,  // Number.
                 Tok_Plu,  // Plus operator.
                 Tok_Min,  // Minus operator.
                 Tok_Mul,  // Multiplication operator.
                 Tok_Div,  // Division operator.
                 Tok_Pot,  // Exponentiation operator.
                 Tok_ParL, // Left parenthesis.
                 Tok_ParR  // Right parenthesis.
               };

private:
    double m_actNumber;
    unsigned short m_actToken;
    string m_expression;
    unsigned short m_index;
    double m_tmpvar;

    void eraseSpaces(void);
    unsigned short getToken(const char *str) const;
    bool isNumber(const string &str) const;
    double levelThree(void);
    double levelTwo(void);
    double levelOne(void);
    double levelZero(void);
    void scan(void);
};

#endif // FPARSER_H
