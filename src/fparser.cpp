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

#include "fparser.h"

FParser::FParser(const string &expr)
{
    setExpression(expr);
}

void FParser::eraseSpaces(void)
{
    unsigned short length = m_expression.length();

    for (unsigned short i = 0; i < length; ++i)
        while (isspace(m_expression[i]) != 0) {
            m_expression.erase(i, 1);
            length = m_expression.length(); // Update length.
        }
}

double FParser::getResult(double val)
{
    m_actNumber = 0;
    m_actToken = Tok_Err;
    m_index = 0;
    m_tmpvar = val;

    scan();
    return levelZero();
}

unsigned short FParser::getToken(const char *str) const
{
    switch (*str) {
    case '+':   return Tok_Plu;
    case '-':   return Tok_Min;
    case '*':   return Tok_Mul;
    case '/':   return Tok_Div;
    case '^':   return Tok_Pot;
    case '(':   return Tok_ParL;
    case ')':   return Tok_ParR;
    }
    return Tok_Err;
}

bool FParser::isNumber(const string &str) const
{
    unsigned short length = str.length();
    unsigned short points = 0;

    for (unsigned short i = 0; i < length; ++i) {
        if (str ==  ".") {
            if (++points > 1) // Don't allow more than one "." in a number.
                return false;
        } else if (!isdigit(str[i]))
            return false;

    }
    return true;
}

double FParser::levelThree(void)
{
    if (m_actToken == Tok_ParL) {
        scan();
        double res = levelZero();
        // Missing right parenthesis.
        /*if (m_actToken != Tok_ParR) {
            m_error = getError(Error::Err_MisRP);
        }
        if (!m_error.empty()) {
            return 0;
        }*/
        scan();
        return res;
    } else if (m_actToken == Tok_Num) {
        scan();
        return m_actNumber;
    }
    return 0;
}

double FParser::levelTwo(void)
{
    double res = levelThree();

    while (m_actToken == Tok_Pot)
        if (m_actToken == Tok_Pot) {
            scan();
            res = pow(res, levelThree());
        }
    return res;
}

double FParser::levelOne(void)
{
    double res = levelTwo();

    while (m_actToken == Tok_Mul || m_actToken == Tok_Div)
        if (m_actToken == Tok_Mul) {
            scan();
            res *= levelTwo();
        } else if (m_actToken == Tok_Div) {
            scan();
            double tmp = levelTwo();            
            if (tmp == 0) // Divison by zero!
                throw string("Division by zero.");
            res /= tmp;
        }
    return res;
}

double FParser::levelZero(void)
{
    double res = levelOne();

    while (m_actToken == Tok_Plu || m_actToken == Tok_Min)
        if (m_actToken == Tok_Plu) {
            scan();
            res += levelOne();
        } else if (m_actToken == Tok_Min) {
            scan();
            res -= levelOne();
        }
    return res;
}

void FParser::scan(void)
{
    unsigned short length = m_expression.length();
    if (m_index < length) {
        string str = m_expression.substr(m_index, 1);

        if (isNumber(str)) { // "str" is a number.
            unsigned short j = 0;
            while (m_index + j < length && isNumber(m_expression.substr(m_index + j, 1))) {
                str = m_expression.substr(m_index, j + 1);
                ++j;
            }
            m_index += j ;
            m_actToken = Tok_Num;
            m_actNumber = atof(str.data());
            return;
        } else if (str == "x") { // "str" is 'x'.
            ++m_index;
            m_actToken = Tok_Num;
            m_actNumber = m_tmpvar;
            return;
        }

        if ((m_actToken = getToken(str.c_str())) == Tok_Err)
            throw string("Unknown token.");

        ++m_index;
    }
}

void FParser::setExpression(const string &expr)
{
    m_actNumber = 0;
    m_actToken = Tok_Err;
    m_expression = expr;
    m_index = 0;
    m_tmpvar = 0;
}
