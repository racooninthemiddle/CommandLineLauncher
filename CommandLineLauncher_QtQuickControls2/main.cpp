#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "CommandLineLauncherBackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator translator;
    translator.load(QLocale(), ":/translation_");
    app.installTranslator(&translator);

    qmlRegisterType<CommandLineLauncherBackend>("CommandLineLauncherBackend", 1, 0, "CommandLineLauncherBackend");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///CommandLineLauncherForm.qml")));

    return app.exec();
}
