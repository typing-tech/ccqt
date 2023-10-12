#pragma once

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QtSerialPort/QSerialPort>

class SenderThread : public QThread {
  Q_OBJECT

public:
  explicit SenderThread(QObject *parent = nullptr);
  ~SenderThread();

  void transaction(const QString &portName, int waitTimeout,
                   const QString &request);

signals:
  void response(const QString &s);
  void error(const QString &s);
  void timeout(const QString &s);
  void connection_status(bool connected);

private:
  void run() override;

  QString m_port_name;
  QString m_request;
  int m_wait_timeout = 0;
  QMutex m_mutex;
  QWaitCondition m_cond;
  bool m_quit = false;
};
