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
    QPushButton* getBGColButton(void) const;
    QColorDialog* getColDialog(void) const;
    QCheckBox* getCoordMouseCheck(void) const;
    QCheckBox* getGridCheck(void) const;
    QPushButton* getGridColButton(void) const;
    QComboBox* getGridStyleCombo(void) const;
    QSpinBox* getGridWidthSpin(void) const;
    QCheckBox* getHorArrowCheck(void) const;
    QGroupBox* getHorGroup(void) const;
    QCheckBox* getHorLabelCheck(void) const;
    QLineEdit* getHorLabelEdit(void) const;
    QToolBox* getToolBox(void) const;
    QCheckBox* getVerArrowCheck(void) const;
    QGroupBox* getVerGroup(void) const;
    QCheckBox* getVerLabelCheck(void) const;
    QLineEdit* getVerLabelEdit(void) const;
    void saveSettings(QSettings *settings);

private:
    QColorDialog *m_colDialog;
    Ui::SettingsView *m_ui;
};

#endif // SETTINGSVIEW_H
