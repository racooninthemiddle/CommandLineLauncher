#include "CommandLineLauncherBackend.h"

#include <QDebug>
#include <QTextCodec>

#include "ConsoleTextCodec.h"

CommandLineLauncherBackend::CommandLineLauncherBackend(QObject *parent) :
    QObject(parent),
    m_process(new QProcess(this)),
    m_status(NOT_RUNNING),
    m_codec(GetConsoleTextCodec()) {
    QObject::connect(m_process, SIGNAL(started()),
                     this, SLOT(onStarted()));
    QObject::connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
                     this, SLOT(onFinished(int, QProcess::ExitStatus)));
    QObject::connect(m_process, SIGNAL(errorOccurred(QProcess::ProcessError)),
                     this, SLOT(onErrorOccurred(QProcess::ProcessError)));
    QObject::connect(m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(onReadyReadStandardOutput()));
    QObject::connect(m_process, SIGNAL(readyReadStandardError()),
                     this, SLOT(onReadyReadStandardError()));
}

CommandLineLauncherBackend::~CommandLineLauncherBackend() {
    delete m_process;  // Can emit signals errorOccured and finished.
}

void CommandLineLauncherBackend::start(const QString& command) {
    qInfo() << "CommandLineLauncherBackend::start";
    m_output.clear();
    m_errors.clear();
    setStatus(STARTING);
    m_process->start(command);
}

void CommandLineLauncherBackend::terminate() {
    qInfo() << "CommandLineLauncherBackend::terminate";
    if (!isRunning() || (status() == TERMINATING))
        return;
    setStatus(TERMINATING);
    m_process->kill();
}

void CommandLineLauncherBackend::setStatus(Status newStatus) {
    if (newStatus == status())
        return;
    m_status = newStatus;
    emit statusChanged(status());
}

CommandLineLauncherBackend::Status CommandLineLauncherBackend::status() const {
    return m_status;
}

QString CommandLineLauncherBackend::statusDescription() const {
    switch (status()) {
        case NOT_RUNNING: return tr("Not running.");
        case FILE_NOT_FOUND: return tr("File not found.");
        case STARTING: return tr("Starting...");
        case RUNNING: return tr("Running...");
        case FINISHED: return tr("Finished with exit code %1.").arg(exitCode());
        case TERMINATING: return tr("Terminating...");
        case TERMINATED: return tr("Terminated.");
        case CRASHED: return tr("Crashed.");
        default: Q_ASSERT(false); return "";
    }
}

bool CommandLineLauncherBackend::isRunning() const {
    switch (status()) {
        case NOT_RUNNING:
        case FILE_NOT_FOUND:
        case FINISHED:
        case TERMINATED:
        case CRASHED: return false;
        case STARTING:
        case RUNNING:
        case TERMINATING: return true;
        default: Q_ASSERT(false); return "";
    }
}

int CommandLineLauncherBackend::exitCode() const {
    return m_process->exitCode();
}

QString CommandLineLauncherBackend::output() const {
    return m_output + m_errors;
}

void CommandLineLauncherBackend::onStarted() {
    qInfo() << "CommandLineLauncherBackend::onStarted";
    m_status = RUNNING;
    emit statusChanged(m_status);
}

void CommandLineLauncherBackend::onFinished(int /*exitCode*/, QProcess::ExitStatus exitStatus) {
    qInfo() << "CommandLineLauncherBackend::onFinished";
    if (status() == TERMINATING)
        setStatus(TERMINATED);
    else if (exitStatus == QProcess::NormalExit)
        setStatus(FINISHED);
    else
        setStatus(CRASHED);
}

void CommandLineLauncherBackend::onErrorOccurred(QProcess::ProcessError error) {
    qInfo() << "CommandLineLauncherBackend::onErrorOccurred";
    if (status() != TERMINATING) {
        if (error == QProcess::FailedToStart)
            setStatus(FILE_NOT_FOUND);
        else
            setStatus(CRASHED);
    }
}

void CommandLineLauncherBackend::onReadyReadStandardOutput() {
    qInfo() << "CommandLineLauncherBackend::onReadyReadStandardOutput";
    QByteArray bytes = m_process->readAllStandardOutput();
    m_output += m_codec->toUnicode(bytes);
    emit outputChanged(output());
}

void CommandLineLauncherBackend::onReadyReadStandardError() {
    qInfo() << "CommandLineLauncherBackend::onReadyReadStandardError";
    QByteArray bytes = m_process->readAllStandardError();
    m_errors += m_codec->toUnicode(bytes);
    emit outputChanged(output());
}
