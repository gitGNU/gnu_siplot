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

void SettingsView::initSettings(QSettings *settings)
{
    settings->beginGroup("Settings");

    m_ui->m_toolBox->setCurrentIndex(settings->value("CurrentPage", 0).toInt());

    // Grid.
    bool gridOn = settings->value("GridOn", true).toBool();
    m_ui->m_gridCheck->setChecked(gridOn);
    m_ui->m_gridFrame->setVisible(gridOn);
    m_ui->m_gridStyleCombo->setCurrentIndex(settings->value("GridStyle", 1).toInt());
    m_ui->m_gridWidthSpin->setValue(settings->value("GridWidth", 1).toDouble());
    m_ui->m_gridColButton->setPalette(QPalette((settings->value("GridColor", Qt::gray).toString())));


    // Axes
    bool horAxisOn = settings->value("HorAxisOn", true).toBool();
    m_ui->m_horGroup->setChecked(horAxisOn);
    m_ui->m_horFrame->setVisible(horAxisOn);
    m_ui->m_horArrowCheck->setChecked(settings->value("HorArrowOn", true).toBool());
    bool horLabelOn = settings->value("HorLabelOn", true).toBool();
    m_ui->m_horLabelCheck->setChecked(horLabelOn);
    m_ui->m_horLabelEdit->setEnabled(horLabelOn);
    m_ui->m_horLabelEdit->setText(settings->value("HorLabel", "X").toString());

    bool verAxisOn = settings->value("VerAxisOn", true).toBool();
    m_ui->m_verGroup->setChecked(verAxisOn);
    m_ui->m_verFrame->setVisible(verAxisOn);
    m_ui->m_verArrowCheck->setChecked(settings->value("VerArrowOn", true).toBool());
    bool verLabelOn = settings->value("VerLabelOn", true).toBool();
    m_ui->m_verLabelCheck->setChecked(verLabelOn);
    m_ui->m_verLabelEdit->setEnabled(verLabelOn);
    m_ui->m_verLabelEdit->setText(settings->value("VerLabel", "Y").toString());

    // Background.
    m_ui->m_bgColButton->setPalette(QPalette((settings->value("BGColor", Qt::white).toString())));

    // Coordinates.
    m_ui->m_coordMouseCheck->setChecked(settings->value("CoordinatesMouseOn", true).toBool());

    settings->endGroup();
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

void SettingsView::saveSettings(QSettings *settings)
{
    settings->beginGroup("Settings");

    settings->setValue("IsOn", isVisible());
    settings->setValue("CurrentPage", m_ui->m_toolBox->currentIndex());

    // Grid.
    settings->setValue("GridOn", m_ui->m_gridCheck->isChecked());
    settings->setValue("GridStyle", m_ui->m_gridStyleCombo->currentIndex());
    settings->setValue("GridColor", m_ui->m_gridColButton->palette().color(QPalette::Background).name());
    settings->setValue("GridWidth", m_ui->m_gridWidthSpin->value());

    // Axes.
    settings->setValue("HorAxisOn", m_ui->m_horGroup->isChecked());
    settings->setValue("HorArrowOn", m_ui->m_horArrowCheck->isChecked());
    settings->setValue("HorLabelOn", m_ui->m_horLabelCheck->isChecked());
    settings->setValue("HorLabel", m_ui->m_horLabelEdit->text());

    settings->setValue("VerAxisOn", m_ui->m_verGroup->isChecked());
    settings->setValue("VerArrowOn", m_ui->m_verArrowCheck->isChecked());
    settings->setValue("VerLabelOn", m_ui->m_verLabelCheck->isChecked());
    settings->setValue("VerLabel", m_ui->m_verLabelEdit->text());

    // Background.
    settings->setValue("BGColor", m_ui->m_bgColButton->palette().color(QPalette::Background).name());

    // Coordinates.
    settings->setValue("CoordinatesMouseOn", m_ui->m_coordMouseCheck->isChecked());

    settings->endGroup();
}
