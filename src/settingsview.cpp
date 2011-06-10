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

    // Color Buttons.
    connect(m_ui->m_bgColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_gridColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_horColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));
    connect(m_ui->m_verColButton, SIGNAL(clicked()), m_colDialog, SLOT(exec()));

    // Grid.
    connect(m_ui->m_gridCheck, SIGNAL(clicked(bool)), m_ui->m_gridFrame, SLOT(setVisible(bool)));

    // Horizontal Axis.
    connect(m_ui->m_horGroup, SIGNAL(clicked(bool)), m_ui->m_horFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_horLabelGroup, SIGNAL(clicked(bool)), m_ui->m_horLabelFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_horTicsGroup, SIGNAL(clicked(bool)), m_ui->m_horTicsFrame, SLOT(setVisible(bool)));

    // Vertical Axis.
    connect(m_ui->m_verGroup, SIGNAL(clicked(bool)), m_ui->m_verFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_verLabelGroup, SIGNAL(clicked(bool)), m_ui->m_verLabelFrame, SLOT(setVisible(bool)));
    connect(m_ui->m_verTicsGroup, SIGNAL(clicked(bool)), m_ui->m_verTicsFrame, SLOT(setVisible(bool)));
}

SettingsView::~SettingsView(void)
{
    delete m_colDialog;
    delete m_ui;
}

void SettingsView::initSettings(QSettings *settings)
{
    settings->beginGroup("Settings");

    m_ui->m_settingsToolBox->setCurrentIndex(settings->value("CurrentPage", 0).toInt());

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
    m_ui->m_horColButton->setPalette(QPalette(settings->value("HorAxisColor", Qt::black).toString()));
    m_ui->m_horWidthSpin->setValue(settings->value("HorAxisWidth", 1).toInt());
    bool horLabelOn = settings->value("HorLabelOn", true).toBool();
    m_ui->m_horLabelGroup->setChecked(horLabelOn);
    m_ui->m_horLabelEdit->setText(settings->value("HorLabel", "X").toString());
    m_ui->m_horLabelFontCombo->setCurrentIndex(settings->value("HorLabelFont").toInt());
    m_ui->m_horLabelSizeSpin->setValue(settings->value("HorLabelSize", 10).toDouble());
    m_ui->m_horTicsGroup->setChecked(settings->value("HorTicsOn", true).toBool());
    m_ui->m_horTicsLengthSpin->setValue(settings->value("HOrTicsLength", 10).toInt());

    bool verAxisOn = settings->value("VerAxisOn", true).toBool();
    m_ui->m_verGroup->setChecked(verAxisOn);
    m_ui->m_verFrame->setVisible(verAxisOn);
    m_ui->m_verArrowCheck->setChecked(settings->value("VerArrowOn", true).toBool());
    m_ui->m_verWidthSpin->setValue(settings->value("VerAxisWidth", 1).toInt());
    m_ui->m_verColButton->setPalette(QPalette(settings->value("VerAxisColor", Qt::black).toString()));
    bool verLabelOn = settings->value("VerLabelOn", true).toBool();
    m_ui->m_verLabelGroup->setChecked(verLabelOn);
    m_ui->m_verLabelEdit->setText(settings->value("VerLabel", "Y").toString());
    m_ui->m_verLabelFontCombo->setCurrentIndex(settings->value("VerLabelFont").toInt());
    m_ui->m_verLabelSizeSpin->setValue(settings->value("VerLabelSize", 10).toDouble());
    m_ui->m_verTicsGroup->setChecked(settings->value("VerTicsOn", true).toBool());
    m_ui->m_verTicsLengthSpin->setValue(settings->value("VerTicsLength", 10).toInt());

    // Background.
    m_ui->m_bgColButton->setPalette(QPalette(settings->value("BGColor", Qt::white).toString()));

    // Coordinates.
    m_ui->m_coordMouseCheck->setChecked(settings->value("CoordinatesMouseOn", true).toBool());

    settings->endGroup();
}

QTabWidget* SettingsView::getAxesTab(void) const
{
    return m_ui->m_axesTabWidget;
}

QCheckBox* SettingsView::getAxisArrowCheck(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horArrowCheck;
    case Ver:      return m_ui->m_verArrowCheck;
    }
    return 0;
}

QPushButton* SettingsView::getAxisColButton(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horColButton;
    case Ver:      return m_ui->m_verColButton;
    }
    return 0;
}

QGroupBox* SettingsView::getAxisGroup(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horGroup;
    case Ver:      return m_ui->m_verGroup;
    }
    return 0;
}

QComboBox* SettingsView::getAxisStyleCombo(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horStyleCombo;
    case Ver:      return m_ui->m_verStyleCombo;
    }
    return 0;
}

QSpinBox* SettingsView::getAxisWidthSpin(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horWidthSpin;
    case Ver:      return m_ui->m_verWidthSpin;
    }
    return 0;
}

QLineEdit* SettingsView::getAxisLabelEdit(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horLabelEdit;
    case Ver:      return m_ui->m_verLabelEdit;
    }
    return 0;
}

QGroupBox* SettingsView::getAxisLabelGroup(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horLabelGroup;
    case Ver:      return m_ui->m_verLabelGroup;
    }
    return 0;
}

QDoubleSpinBox* SettingsView::getAxisLabelSizeSpin(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horLabelSizeSpin;
    case Ver:      return m_ui->m_verLabelSizeSpin;
    }
    return 0;
}

QFontComboBox* SettingsView::getAxisLabelFontCombo(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horLabelFontCombo;
    case Ver:      return m_ui->m_verLabelFontCombo;
    }
    return 0;
}

QGroupBox* SettingsView::getAxisTicsGroup(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsGroup;
    case Ver:      return m_ui->m_verTicsGroup;
    }
    return 0;
}

QSpinBox* SettingsView::getAxisTicsLengthSpin(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsLengthSpin;
    case Ver:      return m_ui->m_verTicsLengthSpin;
    }
    return 0;
}

/* Not implemented yet.

QPushButton* SettingsView::getAxisTicsColButton(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsColButton;
    case Ver:      return m_ui->m_verTicsColButton;
    }
    return 0;
}

QSpinBox* SettingsView::getAxisTicsWidthSpin(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsWidthSpin;
    case Ver:      return m_ui->m_verTicsWidthSpin;
    }
    return 0;
}

QFontComboBox* SettingsView::getAxisTicsFontCombo(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsFontCombo;
    case Ver:      return m_ui->m_verTicsFontCombo;
    }
    return 0;
}

QDoubleSpinBox* SettingsView::getAxisTicsSizeSpin(unsigned short axis) const
{
    switch (axis) {
    case Hor:    return m_ui->m_horTicsSizeSpin;
    case Ver:      return m_ui->m_verTicsSizeSpin;
    }
    return 0;
}
*/

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

QToolBox* SettingsView::getToolBox(void) const
{
    return m_ui->m_settingsToolBox;
}


void SettingsView::saveSettings(QSettings *settings)
{
    settings->beginGroup("Settings");

    settings->setValue("IsOn", isVisible());
    settings->setValue("CurrentPage", m_ui->m_settingsToolBox->currentIndex());

    // Grid.
    settings->setValue("GridOn", m_ui->m_gridCheck->isChecked());
    settings->setValue("GridStyle", m_ui->m_gridStyleCombo->currentIndex());
    settings->setValue("GridColor", m_ui->m_gridColButton->palette().color(QPalette::Background).name());
    settings->setValue("GridWidth", m_ui->m_gridWidthSpin->value());

    // Axes.
    settings->setValue("HorAxisOn", m_ui->m_horGroup->isChecked());
    settings->setValue("HorArrowOn", m_ui->m_horArrowCheck->isChecked());
    settings->setValue("HorAxisColor", m_ui->m_horColButton->palette().color(QPalette::Background).name());
    settings->setValue("HorAxisWidth", m_ui->m_horWidthSpin->value());
    settings->setValue("HorLabelOn", m_ui->m_horLabelGroup->isChecked());
    settings->setValue("HorLabel", m_ui->m_horLabelEdit->text());
    settings->setValue("HorLabelFont", m_ui->m_horLabelFontCombo->currentIndex());
    settings->setValue("HorLabelSize", m_ui->m_horLabelSizeSpin->value());
    settings->setValue("HorTicsOn", m_ui->m_horTicsGroup->isChecked());
    settings->setValue("HorTicsLength", m_ui->m_horTicsLengthSpin->value());

    settings->setValue("VerAxisOn", m_ui->m_verGroup->isChecked());
    settings->setValue("VerArrowOn", m_ui->m_verArrowCheck->isChecked());
    settings->setValue("VerAxisColor", m_ui->m_verColButton->palette().color(QPalette::Background).name());
    settings->setValue("VerAxisWidth", m_ui->m_verWidthSpin->value());
    settings->setValue("VerLabelOn", m_ui->m_verLabelGroup->isChecked());
    settings->setValue("VerLabel", m_ui->m_verLabelEdit->text());
    settings->setValue("VerLabelFont", m_ui->m_verLabelFontCombo->currentIndex());
    settings->setValue("VerLabelSize", m_ui->m_verLabelSizeSpin->value());
    settings->setValue("VerTicsOn", m_ui->m_verTicsGroup->isChecked());
    settings->setValue("VerTicsLength", m_ui->m_verTicsLengthSpin->value());

    // Background.
    settings->setValue("BGColor", m_ui->m_bgColButton->palette().color(QPalette::Background).name());

    // Coordinates.
    settings->setValue("CoordinatesMouseOn", m_ui->m_coordMouseCheck->isChecked());

    settings->endGroup();
}
