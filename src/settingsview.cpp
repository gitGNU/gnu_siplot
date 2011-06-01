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

#include "settingsview.h"
#include "ui_settingsview.h"

SettingsView::SettingsView(QWidget *parent) :
    QDockWidget(parent),
    m_ui(new Ui::SettingsView)
{
    m_ui->setupUi(this);
    setWindowTitle(tr("Settings"));
}

SettingsView::~SettingsView(void)
{
    delete m_ui;
}

QCheckBox* SettingsView::getCoordCheck(void) const
{
    return m_ui->m_coordCheck;
}

QCheckBox* SettingsView::getGridCheck(void) const
{
    return m_ui->m_gridCheck;
}
