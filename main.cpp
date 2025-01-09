#include "mainwindow.h"
#include "schedule.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SecuritySystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    // Schedule graph;
    // graph.setGuards({"Иванов", "Петров", "Сидоров"});
    // graph.setMonth(2025, 1);  // Январь 2025
    // graph.resize(800, 600);
    // graph.show();

    return a.exec();
}
