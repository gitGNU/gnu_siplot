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

MainWindow::MainWindow(QWidget *parent, QString *initFunc) :
    QMainWindow(parent),
    m_aboutAction(new QAction(tr("About"), this)),
    m_formAction(new QAction(tr("Show Input"), this)),
    m_fullscreenAction(new QAction(tr("Full Screen Mode"), this)),
    m_funcAction(new QAction(tr("Show Functions"), this)),
    m_manAction(new QAction(tr("Manual"), this)),
    m_quitAction(new QAction(tr("Quit"), this)),
    m_settingsAction(new QAction(tr("Show Settings"), this)),
    m_fileMenu(new QMenu(tr("File"), this)),
    m_helpMenu(new QMenu(tr("Help"), this)),
    m_viewMenu(new QMenu(tr("View"), this)),
    m_settings(new QSettings("David Jenni", QCoreApplication::applicationName())),
    m_aboutDialog(new AboutDialog()),
    m_manDialog(new ManualDialog()),
    m_funcview(new FuncView()),
    m_functionsview(new FunctionsView()),
    m_formview(new FormulaView()),
    m_settingsview(new SettingsView())
{
    setCentralWidget(m_funcview);
    setWindowIcon(QIcon(QString(QCoreApplication::applicationDirPath() + "/icons/siplot.png")));

    addDockWidget(Qt::BottomDockWidgetArea, m_formview);
    addDockWidget(Qt::RightDockWidgetArea, m_functionsview);
    addDockWidget(Qt::LeftDockWidgetArea, m_settingsview);
    m_settingsview->hide();
    m_functionsview->hide();
    m_formview->hide();

    initActions();
    initMenus();
    initConnects();

    if (initFunc) {
        m_formview->getFormEdit()->setText(*initFunc);
        plot();
    }

    initSettings();
}

MainWindow::~MainWindow(void)
{
    size_t size = m_gfunc.size();
    for (unsigned short i = 0; i < size; ++i)
        delete m_gfunc[i];
    m_gfunc.clear();

    delete m_aboutAction;
    delete m_formAction;
    delete m_fullscreenAction;
    delete m_funcAction;
    delete m_manAction;
    delete m_quitAction;
    delete m_settingsAction;
    delete m_fileMenu;
    delete m_helpMenu;
    delete m_viewMenu;
    delete m_settings;
    delete m_aboutDialog;
    delete m_manDialog;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_settings->beginGroup("MainWindow");
    m_settings->setValue("Size", size());
    m_settings->setValue("FormViewOn", m_formAction->isChecked());
    m_settings->endGroup();

    m_settingsview->saveSettings(m_settings);

    event->accept();
}

void MainWindow::initActions(void)
{
    m_aboutAction->setShortcut(tr("Ctrl+A"));
    m_aboutAction->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/icons/help-about.png"));
    m_formAction->setShortcut(tr("Ctrl+I"));
    m_fullscreenAction->setShortcut(tr("Ctrl+R"));
    m_fullscreenAction->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/icons/view-fullscreen.png"));
    m_funcAction->setShortcut(tr("Ctrl+F"));
    m_manAction->setShortcut(tr("Ctrl+M"));
    m_manAction->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/icons/help-contents.png"));
    m_quitAction->setShortcut(tr("Ctrl+Q"));
    m_quitAction->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/icons/application-exit.png"));
    m_settingsAction->setShortcut(tr("Ctrl+S"));

    m_formAction->setCheckable(true);
    m_fullscreenAction->setCheckable(true);
    m_fullscreenAction->setChecked(false);
    m_funcAction->setCheckable(true);
    m_funcAction->setChecked(false);
    m_settingsAction->setCheckable(true);
}

void MainWindow::initConnects(void)
{
    // FormulaView.
    connect(m_formview->getPlotButton(), SIGNAL(clicked()), this, SLOT(plot()));
    connect(m_formview->getFormEdit(), SIGNAL(returnPressed()), this, SLOT(plot()));

    // FunctionsView.
    connect(m_functionsview->getColDialog(), SIGNAL(colorSelected(const QColor&)), this, SLOT(setFuncColor(const QColor&)));
    connect(m_functionsview->getDelButton(), SIGNAL(clicked()), this, SLOT(removeFunc()));
    connect(m_functionsview->getFuncEdit(), SIGNAL(returnPressed()), this, SLOT(setFuncExpression()));
    connect(m_functionsview->getFuncList(), SIGNAL(currentRowChanged(int)), this, SLOT(setFuncProperties(int)));
    connect(m_functionsview->getMaxCheck(), SIGNAL(clicked(bool)), this, SLOT(setFuncMaxOn(bool)));
    connect(m_functionsview->getMaxSpin(), SIGNAL(valueChanged(double)), this, SLOT(setFuncMaxNum(double)));
    connect(m_functionsview->getMinCheck(), SIGNAL(clicked(bool)), this, SLOT(setFuncMinOn(bool)));
    connect(m_functionsview->getMinSpin(), SIGNAL(valueChanged(double)), this, SLOT(setFuncMinNum(double)));
    connect(m_functionsview->getPrecCheck(), SIGNAL(clicked(bool)), this, SLOT(setFuncPrecOn(bool)));
    connect(m_functionsview->getPrecSpin(), SIGNAL(valueChanged(double)), this, SLOT(setFuncPrecNum(double)));
    connect(m_functionsview->getShowCheck(), SIGNAL(clicked(bool)), this, SLOT(showFunction(bool)));
    connect(m_functionsview->getStyleCombo(), SIGNAL(currentIndexChanged(int)), this, SLOT(setFuncStyle(int)));
    connect(m_functionsview->getWidthSpin(), SIGNAL(valueChanged(int)), this, SLOT(setFuncWidth(int)));

    // FuncView.
    connect(m_funcview, SIGNAL(resized()), this, SLOT(replotFunctions()));
    connect(m_funcview->getMagnifier(), SIGNAL(rescaleEvent()), this, SLOT(replotFunctions()));
    connect(m_funcview->getPanner(), SIGNAL(panned(int, int)), this, SLOT(replotFunctions()));

    // SettingsView.
    connect(m_settingsview->getColDialog(), SIGNAL(colorSelected(const QColor&)), this, SLOT(setSettingsColor(const QColor&)));
    connect(m_settingsview->getCoordMouseCheck(), SIGNAL(clicked(bool)), m_funcview, SLOT(setCoordMouseOn(bool)));
    connect(m_settingsview->getGridCheck(), SIGNAL(clicked(bool)), m_funcview, SLOT(setGridOn(bool)));
    connect(m_settingsview->getGridStyleCombo(), SIGNAL(currentIndexChanged(int)), m_funcview, SLOT(setGridStyle(int)));
    connect(m_settingsview->getGridWidthSpin(), SIGNAL(valueChanged(int)), m_funcview, SLOT(setGridWidth(int)));

    // Axis.
    connect(m_settingsview->getAxisArrowCheck(SettingsView::Hor), SIGNAL(clicked(bool)), m_funcview, SLOT(setHorArrowOn(bool)));
    connect(m_settingsview->getAxisGroup(SettingsView::Hor), SIGNAL(clicked(bool)), m_funcview, SLOT(setHorAxisOn(bool)));
    connect(m_settingsview->getAxisStyleCombo(SettingsView::Hor), SIGNAL(currentIndexChanged(int)), m_funcview, SLOT(setHorStyle(int)));
    connect(m_settingsview->getAxisWidthSpin(SettingsView::Hor), SIGNAL(valueChanged(int)), m_funcview, SLOT(setHorWidth(int)));
    connect(m_settingsview->getAxisLabelFontCombo(SettingsView::Hor), SIGNAL(currentFontChanged(QFont)), m_funcview, SLOT(setHorLabelFont(QFont)));
    connect(m_settingsview->getAxisLabelSizeSpin(SettingsView::Hor), SIGNAL(valueChanged(double)), m_funcview, SLOT(setHorLabelSize(double)));
    connect(m_settingsview->getAxisLabelGroup(SettingsView::Hor), SIGNAL(clicked(bool)), m_funcview, SLOT(setHorLabelOn(bool)));
    connect(m_settingsview->getAxisLabelEdit(SettingsView::Hor), SIGNAL(textChanged(const QString&)), m_funcview, SLOT(setHorLabel(const QString&)));
    connect(m_settingsview->getAxisTicsGroup(SettingsView::Hor), SIGNAL(clicked(bool)), m_funcview, SLOT(setHorTicsOn(bool)));
    connect(m_settingsview->getAxisTicsLengthSpin(SettingsView::Hor), SIGNAL(valueChanged(int)), m_funcview, SLOT(setHorTicsLength(int)));

    connect(m_settingsview->getAxisArrowCheck(SettingsView::Ver), SIGNAL(clicked(bool)), m_funcview, SLOT(setVerArrowOn(bool)));
    connect(m_settingsview->getAxisGroup(SettingsView::Ver), SIGNAL(clicked(bool)), m_funcview, SLOT(setVerAxisOn(bool)));
    connect(m_settingsview->getAxisStyleCombo(SettingsView::Ver), SIGNAL(currentIndexChanged(int)), m_funcview, SLOT(setVerStyle(int)));
    connect(m_settingsview->getAxisWidthSpin(SettingsView::Ver), SIGNAL(valueChanged(int)), m_funcview, SLOT(setVerWidth(int)));
    connect(m_settingsview->getAxisLabelFontCombo(SettingsView::Ver), SIGNAL(currentFontChanged(QFont)), m_funcview, SLOT(setVerLabelFont(QFont)));
    connect(m_settingsview->getAxisLabelSizeSpin(SettingsView::Ver), SIGNAL(valueChanged(double)), m_funcview, SLOT(setVerLabelSize(double)));
    connect(m_settingsview->getAxisLabelGroup(SettingsView::Ver), SIGNAL(clicked(bool)), m_funcview, SLOT(setVerLabelOn(bool)));
    connect(m_settingsview->getAxisLabelEdit(SettingsView::Ver), SIGNAL(textChanged(const QString&)), m_funcview, SLOT(setVerLabel(const QString&)));
    connect(m_settingsview->getAxisTicsGroup(SettingsView::Ver), SIGNAL(clicked(bool)), m_funcview, SLOT(setVerTicsOn(bool)));
    connect(m_settingsview->getAxisTicsLengthSpin(SettingsView::Ver), SIGNAL(valueChanged(int)), m_funcview, SLOT(setVerTicsLength(int)));

    // Actions.
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_aboutAction, SIGNAL(triggered()), m_aboutDialog, SLOT(exec()));
    connect(m_formAction, SIGNAL(toggled(bool)), m_formview, SLOT(setVisible(bool)));
    connect(m_funcAction, SIGNAL(toggled(bool)), m_functionsview, SLOT(setVisible(bool)));
    connect(m_fullscreenAction, SIGNAL(triggered(bool)), this, SLOT(setFullscreenOn(bool)));
    connect(m_manAction, SIGNAL(triggered()), m_manDialog, SLOT(exec()));
    connect(m_settingsAction, SIGNAL(toggled(bool)), m_settingsview, SLOT(setVisible(bool)));
}

void MainWindow::initMenus(void)
{
    menuBar()->addMenu(m_fileMenu);
    m_fileMenu->addAction(m_quitAction);
    menuBar()->addMenu(m_viewMenu);
    m_viewMenu->addAction(m_formAction);
    m_viewMenu->addAction(m_funcAction);
    m_viewMenu->addAction(m_settingsAction);
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(m_fullscreenAction);
    menuBar()->addMenu(m_helpMenu);
    m_helpMenu->addAction(m_manAction);
    m_helpMenu->addAction(m_aboutAction);
}

void MainWindow::initSettings(void)
{
    m_settings->beginGroup("MainWindow");
    resize(m_settings->value("Size", QSize(1060, 1100)).toSize());

    bool formViewOn = m_settings->value("FormViewOn", true).toBool();
    m_formAction->setChecked(formViewOn);
    m_formview->setVisible(formViewOn);
    m_settings->endGroup();

    m_settings->beginGroup("Settings");
    bool settingsviewOn = m_settings->value("IsOn", false).toBool();
    m_settingsAction->setChecked(settingsviewOn);
    m_settingsview->setVisible(settingsviewOn);
    m_settings->endGroup();

    m_settingsview->initSettings(m_settings);
    m_funcview->initSettings(m_settings);
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
            delete m_gfunc[index];
            m_gfunc.erase(m_gfunc.begin() + index);
            QMessageBox msgBox(QMessageBox::Warning, tr("Error"), tr("Input incorrect."));
            msgBox.exec();
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

void MainWindow::replotFunctions(void)
{
    unsigned short size = m_gfunc.size();
    for (unsigned short i = 0; i < size; ++i)
        m_funcview->plot(m_gfunc[i]);
}

void MainWindow::setFullscreenOn(bool on)
{
    if (on)
        showFullScreen();
    else
        showNormal();
}

void MainWindow::setFuncExpression(void) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        CParser *cpar = new CParser(m_functionsview->getFuncEdit()->text().toStdString(), m_gfunc, true);

        if (cpar->getType() == CParser::Func) {
            GFunction *gfunc = m_gfunc[list->currentRow()];
            gfunc->setName(cpar->getName());
            gfunc->setExpression(cpar->getExpression());

            if (m_funcview->plot(gfunc)) {
                m_functionsview->setFuncExpression(gfunc);
                m_funcview->getQwtPlot()->replot();
            } else {
                QMessageBox msgBox(QMessageBox::Warning, tr("Error"), tr("Input incorrect."));
                msgBox.exec();
            }
        } else {
            QMessageBox msgBox(QMessageBox::Warning, tr("Error"), tr("Input incorrect."));
            msgBox.exec();
        }
        delete cpar;
    }
}

void MainWindow::setFuncColor(const QColor &col) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setColor(col);
        m_funcview->plot(gfunc);
        m_functionsview->getColButton()->setPalette(col);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncMaxOn(bool on) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setMaxOn(on);

        if (on) {
            gfunc->setMaxNum(m_functionsview->getMaxSpin()->value());
            m_funcview->plot(gfunc);
        } else
            m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncMaxNum(double max) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setMaxNum(max);
        m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncMinOn(bool on) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setMinOn(on);

        if (on) {
            gfunc->setMinNum(m_functionsview->getMinSpin()->value());
            m_funcview->plot(gfunc);
        } else
            m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncMinNum(double min) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setMinNum(min);
        m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncPrecOn(bool on) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setPrecOn(on);

        if (on) {
            gfunc->setPrecNum(m_functionsview->getPrecSpin()->value());
            m_funcview->plot(gfunc);
        } else
            m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncPrecNum(double prec) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setPrecNum(prec);
        m_funcview->plot(gfunc);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncProperties(int row) const
{
    if (row >= 0) {
        m_functionsview->setProperties(m_gfunc[row]);
        if (row == 0)
            m_funcAction->setChecked(true);
    } else {
        m_functionsview->setProperties(0);
        m_funcAction->setChecked(false);
    }
}

void MainWindow::setFuncStyle(int i) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        m_gfunc[list->currentRow()]->setStyle((Qt::PenStyle) (i + 1));
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setFuncWidth(int width) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        m_gfunc[list->currentRow()]->setWidth(width);
        m_funcview->getQwtPlot()->replot();
    }
}

void MainWindow::setSettingsColor(const QColor &col) const
{
    // 0: Grid, 1: Axes, 2: BG.
    QTabWidget *tab = m_settingsview->getAxesTab();
    switch (m_settingsview->getToolBox()->currentIndex()) {
    case 0:     m_funcview->setGridCol(col);
                m_settingsview->getGridColButton()->setPalette(QPalette(col));
                break;

    case 1:     if (tab->currentIndex() == 0) {
                    m_funcview->setHorAxisCol(col);
                    m_settingsview->getAxisColButton(SettingsView::Hor)->setPalette(QPalette(col));
                } else if (tab->currentIndex() == 1) {
                     m_funcview->setVerAxisCol(col);
                     m_settingsview->getAxisColButton(SettingsView::Ver)->setPalette(QPalette(col));
                }
                break;

    case 2:     m_funcview->setBGCol(col);
                m_settingsview->getBGColButton()->setPalette(QPalette(col));
                break;
    }
}

void MainWindow::showFunction(bool on) const
{
    QListWidget *list = m_functionsview->getFuncList();
    if (list->count() > 0) {
        GFunction *gfunc = m_gfunc[list->currentRow()];
        gfunc->setShow(on);

        if (on)
            gfunc->getCurve()->attach(m_funcview->getQwtPlot());
        else
            gfunc->getCurve()->detach();
        m_funcview->getQwtPlot()->replot();
    }
}
