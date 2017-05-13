#ifndef COMMAND_LINE_LAUNCHER_BACKEND_H
#define COMMAND_LINE_LAUNCHER_BACKEND_H

#include <QObject>
#include <QProcess>

class CommandLineLauncherBackend : public QObject
{
    Q_OBJECT

public:
    enum Status {
        NOT_RUNNING,
        FILE_NOT_FOUND,
        STARTING,
        RUNNING,
        FINISHED,
        TERMINATING,
        TERMINATED,
        CRASHED,
    };
    Q_ENUM(Status)

    explicit CommandLineLauncherBackend(QObject *parent = 0);
    ~CommandLineLauncherBackend();

    Q_INVOKABLE void start(const QString& command);
    Q_INVOKABLE void terminate();

    Status status() const;
    QString statusDescription() const;
    bool isRunning() const;
    int exitCode() const;
    QString output() const;

    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusDescription READ statusDescription)
    Q_PROPERTY(bool isRunning READ isRunning)
    Q_PROPERTY(int exitCode READ exitCode)
    Q_PROPERTY(QString output READ output NOTIFY outputChanged)

signals:
    void statusChanged(Status status);
    void outputChanged(const QString& output);

private slots:
    void onStarted();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onErrorOccurred(QProcess::ProcessError error);
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();

private:
    void setStatus(Status status);

    QProcess* m_process;
    Status m_status;
    QTextCodec* m_codec;
    QString m_output;
    QString m_errors;
};

#endif // COMMAND_LINE_LAUNCHER_BACKEND_H
