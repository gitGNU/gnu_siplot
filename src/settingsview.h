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

#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QtGui>

namespace Ui {
    class SettingsView;
}

class SettingsView : public QDockWidget
{
    Q_OBJECT
public:
    SettingsView(QWidget *parent = 0);
    ~SettingsView(void);

    void initSettings(QSettings *settings);
    void saveSettings(QSettings *settings);

    QTabWidget* getAxesTab(void) const;

    // Axes.
    QCheckBox* getAxisArrowCheck(unsigned short axis) const;
    QPushButton* getAxisColButton(unsigned short axis) const;
    QGroupBox* getAxisGroup(unsigned short axis) const;
    QComboBox* getAxisStyleCombo(unsigned short axis) const;
    QSpinBox* getAxisWidthSpin(unsigned short axis) const;

    // Axes Label.
    QGroupBox* getAxisLabelGroup(unsigned short axis) const;
    QLineEdit* getAxisLabelEdit(unsigned short axis) const;
    QFontComboBox* getAxisLabelFontCombo(unsigned short axis) const;
    QDoubleSpinBox* getAxisLabelSizeSpin(unsigned short axis) const;

    // Axes Tics.
    QGroupBox* getAxisTicsGroup(unsigned short axis) const;
    QSpinBox* getAxisTicsLengthSpin(unsigned short axis) const;

    /* Not implemented yet.
     * QPushButton* getAxisTicsColButton(unsigned short axis) const;
     * QSpinBox* getAxisTicsWidthSpin(unsigned short axis) const;
     * QFontComboBox* getAxisTicsFontCombo(unsigned short axis) const;
     * QDoubleSpinBox* getAxisTicsSizeSpin(unsigned short axis) const;
     */

    QPushButton* getBGColButton(void) const;

    // Grid.
    QColorDialog* getColDialog(void) const;
    QCheckBox* getCoordMouseCheck(void) const;
    QCheckBox* getGridCheck(void) const;
    QPushButton* getGridColButton(void) const;
    QComboBox* getGridStyleCombo(void) const;
    QSpinBox* getGridWidthSpin(void) const;

    QToolBox* getToolBox(void) const;

    enum AxisType {
        Hor,
        Ver
    };

private:
    QColorDialog *m_colDialog;
    Ui::SettingsView *m_ui;
};

#endif // SETTINGSVIEW_H
