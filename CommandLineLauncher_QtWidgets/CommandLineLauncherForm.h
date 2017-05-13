#ifndef COMMAND_LINE_LAUNCHER_FORM_H
#define COMMAND_LINE_LAUNCHER_FORM_H

#include <QMainWindow>
class CommandLineLauncherBackend;

namespace Ui {
class CommandLineLauncherForm;
}

class CommandLineLauncherForm : public QMainWindow {
    Q_OBJECT

public:
    explicit CommandLineLauncherForm(QWidget *parent = 0);
    ~CommandLineLauncherForm();

private slots:
    void on_buttonRun_clicked();
    void on_buttonTerminate_clicked();
    void onStatusChanged();
    void onOutputChanged(const QString& output);
    void OnTerminateButtonTimeout();

private:
    void keyPressEvent(QKeyEvent *event) override;
    void run();

    Ui::CommandLineLauncherForm* ui;
    QTimer* terminateButtonTimer;
    CommandLineLauncherBackend* backend;
};

#endif // COMMAND_LINE_LAUNCHER_FORM_H
