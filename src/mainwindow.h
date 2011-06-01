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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <qwt_plot.h>
#include <vector>

#include "aboutdialog.h"
#include "funcview.h"
#include "functionsview.h"
#include "formulaview.h"
#include "gfunction.h"
#include "manualdialog.h"
#include "settingsview.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow(void);

public slots:
    void plot(void);
    void removeFunc(void);
    void replot(void);
    void showFormulaView(bool on) const;
    void showFunctionsView(bool on) const;
    void showSettingsView(bool on) const;

private:
    QAction *m_aboutAction;
    QAction *m_formAction;
    QAction *m_funcAction;
    QAction *m_manAction;
    QAction *m_quitAction;
    QAction *m_settingsAction;

    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QMenu *m_viewMenu;

    AboutDialog *m_aboutDialog;
    ManualDialog *m_manDialog;

    FuncView *m_funcview;
    FunctionsView *m_functionsview;
    FormulaView *m_formview;
    SettingsView *m_settingsview;

    vector<GFunction*> m_gfunc;
};

#endif // MAINWINDOW_H
