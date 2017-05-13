#include "CommandLineLauncherForm.h"

#include <QKeyEvent>
#include <QTimer>

#include "ui_CommandLineLauncherForm.h"
#include "CommandLineLauncherBackend.h"

CommandLineLauncherForm::CommandLineLauncherForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommandLineLauncherForm),
    terminateButtonTimer(new QTimer),
    backend(new CommandLineLauncherBackend) {

    ui->setupUi(this);
    ui->buttonTerminate->setVisible(false);

    terminateButtonTimer->setSingleShot(true);
    QObject::connect(terminateButtonTimer, SIGNAL(timeout()),
                     this, SLOT(OnTerminateButtonTimeout()));

    QObject::connect(backend, SIGNAL(statusChanged(Status)),
                     this, SLOT(onStatusChanged()));
    QObject::connect(backend, SIGNAL(outputChanged(const QString&)),
                     this, SLOT(onOutputChanged(const QString&)));

    ui->textCommand->setText("ping -n 6 127.0.0.1");
    run();
}

CommandLineLauncherForm::~CommandLineLauncherForm() {
    delete backend;
    delete terminateButtonTimer;
    delete ui;
}

void CommandLineLauncherForm::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return)
        run();
}

void CommandLineLauncherForm::on_buttonRun_clicked() {
    run();
}

void CommandLineLauncherForm::run() {
    if (!backend->isRunning())
        backend->start(ui->textCommand->text());
}

void CommandLineLauncherForm::on_buttonTerminate_clicked() {
    backend->terminate();
}

void CommandLineLauncherForm::onOutputChanged(const QString& output) {
    ui->textOutput->setText(output);
}

void CommandLineLauncherForm::onStatusChanged() {
    ui->textStatus->setText(backend->statusDescription());
    ui->textOutput->setText(backend->output());

    bool isRunning = backend->isRunning();
    ui->buttonRun->setEnabled(!isRunning);

    if (isRunning && !ui->buttonTerminate->isVisible() && !terminateButtonTimer->isActive()) {
        terminateButtonTimer->start(2000);
    }
    else if (!isRunning) {
        ui->buttonTerminate->setVisible(false);
        terminateButtonTimer->stop();
    }
}

void CommandLineLauncherForm::OnTerminateButtonTimeout() {
    if (backend->isRunning())
        ui->buttonTerminate->setVisible(true);
}
