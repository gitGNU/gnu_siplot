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

#include "cparser.h"

CParser::CParser(const string &str, vector<GFunction*> gfunc) :
    m_expr(string()),
    m_gfunc(gfunc),
    m_name(string()),
    m_str(str),
    m_type(Err)
{
    m_keywords.push_back("func");
    eraseSpaces();
    parse();
}

CParser::~CParser(void)
{
    /*size_t size = m_gfunc.size();
    for (unsigned short i = 0; i < size; ++i)
        delete m_gfunc[i];
    m_gfunc.clear();*/
}

void CParser::eraseSpaces(void)
{
    unsigned short length = m_str.length();

    for (unsigned short i = 0; i < length; ++i)
        while (isspace(m_str[i]) != 0) {
            m_str.erase(i, 1);
            length = m_str.length();
        }
}

const string& CParser::getExpression(void) const
{
    return m_expr;
}

const string& CParser::getName(void) const
{
    return m_name;
}

unsigned short CParser::getType(void) const
{
    return m_type;
}

bool CParser::isAlphabetic(const string &str) const
{
    unsigned short length = str.length();
    for (unsigned short i = 0; i < length; ++i)
        if (!isalpha(str[i]))
            return false;

    return true;
}

bool CParser::isFuncName(const string &str) const
{
    unsigned short length = m_gfunc.size();
    for (unsigned short i = 0; i < length; ++i)
        if (str == m_gfunc[i]->getFuncName())
            return true;

    return false;
}

bool CParser::isKeyword(const string &str) const
{
    unsigned short length = m_keywords.size();
    for (unsigned short i = 0; i < length; ++i)
        if (str.compare(m_keywords[i]) == 0)
            return true;

    return false;
}

void CParser::parse(void)
{
    if (m_str.substr(0, 4) == "func") {
        if (m_str.length() == 4)
            m_type = Err;
        else {
            m_type = Func;
            unsigned short i = 4;
            unsigned short length = m_str.length();
            string arg;
            bool name = true;

            for (; i < length; ++i) {
                if (m_str.substr(i, 1) == "(")
                    name = false;
                else if (name)
                    m_name += m_str.substr(i, 1);
                else if (m_str.substr(i, 2) == ")=")
                    break;
                else if (!name)
                    arg += m_str.substr(i, 1);
            }
            if (isKeyword(m_name) || !isAlphabetic(m_name) || isFuncName(m_name) || m_name.empty() || arg != "x")
                m_type = Err;
            else
                m_expr = m_str.substr(i + 2, length); // + 2 : Skip ")="
        }
    }
}
