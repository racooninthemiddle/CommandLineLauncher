#include <QApplication>
#include <QTranslator>

#include "CommandLineLauncherForm.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load(QLocale(), ":/translation_");
    app.installTranslator(&translator);

    CommandLineLauncherForm form;
    form.show();

    return app.exec();
}
