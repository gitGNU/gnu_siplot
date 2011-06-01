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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
    m_ui->m_aboutLabel->setOpenExternalLinks(true);
    m_ui->m_titleLabel->setText(QString(tr("<b>About %1 Version %2</b>")).arg(QCoreApplication::applicationName())
                                                                         .arg(QCoreApplication::applicationVersion()));

    setWindowTitle(tr("About"));

    connect(m_ui->m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

AboutDialog::~AboutDialog(void)
{
    delete m_ui;
}
