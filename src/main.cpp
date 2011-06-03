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

#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <QtGlobal>
#include <QtGui/QApplication>

#include "mainwindow.h"

using namespace std;

static struct option longOptions[] = {
    { "function", required_argument, 0, 'f' },
    { "help", no_argument, 0, 'h' },
    { "version", no_argument, 0, 'v' },
    { 0, 0, 0, 0 }
};

void usage(int status)
{
    if (status == EXIT_SUCCESS) {
        cout << "Usage: " << QCoreApplication::applicationName().toStdString() << " [Option]\n\nOptions:\n"
             << "    --function, -f <argument>\tInitial functions to plot.\n"
             << "    --help, -h\t\t\tShow help about options and quit.\n"
             << "    --version, -v\t\tShow version information and quit." << endl;
    } else
        cout << QCoreApplication::applicationName().toStdString() << ": Use \"" << QCoreApplication::applicationName().toStdString()
             << " --help\" to get a list of available command line options." << endl;
    exit(status);
}

void version(const string &progName, const string &author, const string &version)
{
    cout << "Qt: " << qVersion() << "\n" << progName << ": " << version

            << "\n\nCopyright (C) 2010 - 2011 " << author << "\n\n"

            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "(at your option) any later version.\n\n"

            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n\n"

            "You should have received a copy of the GNU General Public License\n"
            "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n"

            << progName << " was written by " << author << endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("David Jenni");
    QCoreApplication::setApplicationName("siplot");
    QCoreApplication::setApplicationVersion("0.04");

    if (argc < 2) {
        MainWindow win;
        win.show();
        return app.exec();
    } else if (argc == 2 || argc == 3) {
        int option_index = 0;
        int option = getopt_long(argc, argv, "f:hv", longOptions, &option_index);

        if (argc == 3 && option == 'f') {
            QString str = QString(optarg);
            MainWindow win(0, &str);
            win.show();
            return app.exec();
        }

        switch (option) {
        case 'h':   usage(EXIT_SUCCESS);

        case 'v':   version(QCoreApplication::applicationName().toStdString(), "David Jenni <dave.j@gmx.ch>", QCoreApplication::applicationVersion().toStdString());
                    exit(EXIT_SUCCESS);

        case '?':   usage(EXIT_FAILURE);

        default:    break;
        }
    } else
        usage(EXIT_FAILURE);

    return EXIT_SUCCESS;
}
