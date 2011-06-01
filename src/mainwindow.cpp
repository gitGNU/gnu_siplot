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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :     
    QMainWindow(parent),
    m_aboutAction(new QAction(tr("A&bout"), this)),
    m_formAction(new QAction(tr("Show &Input"), this)),
    m_funcAction(new QAction(tr("Show &Functions"), this)),
    m_manAction(new QAction(tr("&Manual"), this)),
    m_quitAction(new QAction(tr("&Quit"), this)),
    m_settingsAction(new QAction(tr("Show &Settings"), this)),
    m_fileMenu(new QMenu(tr("&File"), this)),
    m_helpMenu(new QMenu(tr("&Help"), this)),
    m_viewMenu(new QMenu(tr("&View"), this)),
    m_aboutDialog(new AboutDialog()),
    m_manDialog(new ManualDialog()),
    m_funcview(new FuncView()),
    m_functionsview(new FunctionsView()),
    m_formview(new FormulaView()),
    m_settingsview(new SettingsView())
{
    resize(460, 500);
    setCentralWidget(m_funcview);

    addDockWidget(Qt::BottomDockWidgetArea, m_formview);
    addDockWidget(Qt::RightDockWidgetArea, m_functionsview);
    addDockWidget(Qt::RightDockWidgetArea, m_settingsview);
    m_functionsview->hide();
    m_settingsview->hide();

    m_aboutAction->setShortcut(tr("Ctrl+B"));
    m_formAction->setShortcut(tr("Ctrl+I"));
    m_funcAction->setShortcut(tr("Ctrl+F"));
    m_manAction->setShortcut(tr("Ctrl+M"));
    m_quitAction->setShortcut(tr("Ctrl+Q"));
    m_settingsAction->setShortcut(tr("Ctrl+S"));

    m_formAction->setCheckable(true);
    m_formAction->setChecked(true);
    m_funcAction->setCheckable(true);
    m_funcAction->setChecked(false);
    m_settingsAction->setCheckable(true);
    m_settingsAction->setChecked(false);

    menuBar()->addMenu(m_fileMenu);
    m_fileMenu->addAction(m_quitAction);
    menuBar()->addMenu(m_viewMenu);
    m_viewMenu->addAction(m_formAction);
    m_viewMenu->addAction(m_funcAction);
    m_viewMenu->addAction(m_settingsAction);
    menuBar()->addMenu(m_helpMenu);
    m_helpMenu->addAction(m_manAction);
    m_helpMenu->addAction(m_aboutAction);

    // FormulaView.
    connect(m_formview->getPlotButton(), SIGNAL(clicked()), this, SLOT(plot()));
    connect(m_formview->getFormEdit(), SIGNAL(returnPressed()), this, SLOT(plot()));

    // FunctionsView.
    connect(m_functionsview->getDelButton(), SIGNAL(clicked()), this, SLOT(removeFunc()));

    // FuncView.
    connect(m_funcview, SIGNAL(resized()), this, SLOT(replot()));
    connect(m_funcview->getMagnifier(), SIGNAL(rescaleEvent()), this, SLOT(replot()));
    connect(m_funcview->getPanner(), SIGNAL(panned(int, int)), this, SLOT(replot()));

    // SettingsView.
    connect(m_settingsview->getCoordCheck(), SIGNAL(stateChanged(int)), m_funcview, SLOT(changeCoordinates(int)));
    connect(m_settingsview->getGridCheck(), SIGNAL(stateChanged(int)), m_funcview, SLOT(changeGrid(int)));

    // Actions.
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_aboutAction, SIGNAL(triggered()), m_aboutDialog, SLOT(exec()));
    connect(m_formAction, SIGNAL(toggled(bool)), this, SLOT(showFormulaView(bool)));
    connect(m_funcAction, SIGNAL(toggled(bool)), this, SLOT(showFunctionsView(bool)));
    connect(m_manAction, SIGNAL(triggered()), m_manDialog, SLOT(exec()));
    connect(m_settingsAction, SIGNAL(toggled(bool)), this, SLOT(showSettingsView(bool)));
}

MainWindow::~MainWindow(void)
{
    size_t size = m_gfunc.size();
    for (unsigned short i = 0; i < size; ++i)
        delete m_gfunc[i];
    m_gfunc.clear();

    delete m_aboutAction;
    delete m_formAction;
    delete m_funcAction;
    delete m_manAction;
    delete m_quitAction;
    delete m_settingsAction;
    delete m_fileMenu;
    delete m_helpMenu;
    delete m_viewMenu;
    delete m_aboutDialog;
    delete m_manDialog;
    delete m_funcview;
    delete m_formview;
    delete m_settingsview;
}

void MainWindow::plot(void)
{
    // Adds function to vector.
    if (m_formview->addFunc(m_gfunc)) {
        unsigned short index = m_gfunc.size() - 1;
        // Plots function.
        if (m_funcview->plot(m_gfunc[index])) {
            // Adds function to dock widget.
            m_functionsview->addFunc(m_gfunc[index]);
            m_formview->getFormEdit()->clear();
        } else {
            delete m_gfunc[++index];
            m_gfunc.erase(m_gfunc.begin() + index);
        }
    } else {
        QMessageBox msgBox(QMessageBox::Warning, tr("Error"), tr("Input incorrect."));
        msgBox.exec();
    }
}

void MainWindow::removeFunc(void)
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        unsigned short i = list->currentRow();
        list->takeItem(i);
        delete m_gfunc[i];
        m_gfunc.erase(m_gfunc.begin() + i);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::replot(void)
{
    unsigned short size = m_gfunc.size();
    for (unsigned short i = 0; i < size; ++i)
        m_funcview->plot(m_gfunc[i]);
}

void MainWindow::showFormulaView(bool on) const
{
    if (on)
        m_formview->show();
    else
        m_formview->hide();
}

void MainWindow::showFunctionsView(bool on) const
{
    if (on)
        m_functionsview->show();
    else
        m_functionsview->hide();
}

void MainWindow::showSettingsView(bool on) const
{
    if (on)
        m_settingsview->show();
    else
        m_settingsview->hide();
}
