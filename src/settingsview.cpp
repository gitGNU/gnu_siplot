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
    m_colDialog(new QColorDialog()),
    m_ui(new Ui::SettingsView)
{
    m_ui->setupUi(this);
    setWindowTitle(tr("Settings"));

    m_ui->m_gridStyleCombo->setCurrentIndex(1);

    m_ui->m_gridColButton->setPalette(QPalette(Qt::gray));
    m_ui->m_bgColButton->setPalette(QPalette(Qt::white));

    connect(m_ui->m_bgColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_gridCheck, SIGNAL(clicked(bool)), m_ui->m_gridFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_gridColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_horGroup, SIGNAL(clicked(bool)), m_ui->m_horFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_horLabelCheck, SIGNAL(clicked(bool)), m_ui->m_horLabelEdit, SLOT(setEnabled(bool)));
    connect(m_ui->m_verGroup, SIGNAL(clicked(bool)), m_ui->m_verFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_verLabelCheck, SIGNAL(clicked(bool)), m_ui->m_verLabelEdit, SLOT(setEnabled(bool)));
}

SettingsView::~SettingsView(void)
{
    delete m_colDialog;
    delete m_ui;
}

QPushButton* SettingsView::getBGColButton(void) const
{
    return m_ui->m_bgColButton;
}

QColorDialog* SettingsView::getColDialog(void) const
{
    return m_colDialog;
}

QCheckBox* SettingsView::getCoordMouseCheck(void) const
{
    return m_ui->m_coordMouseCheck;
}

QCheckBox* SettingsView::getGridCheck(void) const
{
    return m_ui->m_gridCheck;
}

QPushButton* SettingsView::getGridColButton(void) const
{
    return m_ui->m_gridColButton;
}

QComboBox* SettingsView::getGridStyleCombo(void) const
{
    return m_ui->m_gridStyleCombo;
}

QSpinBox* SettingsView::getGridWidthSpin(void) const
{
    return m_ui->m_gridWidthSpin;
}

QCheckBox* SettingsView::getHorArrowCheck(void) const
{
    return m_ui->m_horArrowCheck;
}

QGroupBox* SettingsView::getHorGroup(void) const
{
    return m_ui->m_horGroup;
}

QCheckBox* SettingsView::getHorLabelCheck(void) const
{
    return m_ui->m_horLabelCheck;
}

QLineEdit* SettingsView::getHorLabelEdit(void) const
{
    return m_ui->m_horLabelEdit;
}

QToolBox* SettingsView::getToolBox(void) const
{
    return m_ui->m_toolBox;
}

QCheckBox* SettingsView::getVerArrowCheck(void) const
{
    return m_ui->m_verArrowCheck;
}

QGroupBox* SettingsView::getVerGroup(void) const
{
    return m_ui->m_verGroup;
}

QCheckBox* SettingsView::getVerLabelCheck(void) const
{
    return m_ui->m_verLabelCheck;
}

QLineEdit* SettingsView::getVerLabelEdit(void) const
{
    return m_ui->m_verLabelEdit;
}
