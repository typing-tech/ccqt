#include "senderthread.h"

#include <QTime>
#include <cstdio>

SenderThread::SenderThread(QObject *parent) : QThread(parent) {}

SenderThread::~SenderThread() {
  m_mutex.lock();
  m_quit = true;
  m_cond.wakeOne();
  m_mutex.unlock();
  wait();
}

void SenderThread::transaction(const QString &portName, int waitTimeout,
                               const QString &request) {
  QMutexLocker const locker(&m_mutex);
  m_port_name = portName;
  m_wait_timeout = waitTimeout;
  m_request = request;

  printf("Port name : %s\n", portName.toStdString().c_str());
  fflush(stdout);

  if (!isRunning())
    start();
  else
    m_cond.wakeOne();
}

void SenderThread::run() {
  bool current_port_name_changed = false;

  m_mutex.lock();
  QString current_port_name;
  if (current_port_name != m_port_name) {
    current_port_name = m_port_name;
    current_port_name_changed = true;
  }

  int current_wait_timeout = m_wait_timeout;
  QString current_request = m_request;
  m_mutex.unlock();
  QSerialPort serial;
  serial.setBaudRate(115200);

  if (current_port_name.isEmpty()) {
    emit error(tr("No port name specified"));
    return;
  }

  while (!m_quit) {
    if (current_port_name_changed) {
      serial.close();
      serial.setPortName(current_port_name);
      emit connection_status(false);

      if (!serial.open(QIODevice::ReadWrite)) {
        emit error(tr("Can't open %1, error code %2")
                       .arg(m_port_name)
                       .arg(serial.error()));
        return;
      }
      emit connection_status(true);
    }

    const QByteArray request_data = current_request.toUtf8();
    serial.write(request_data);
    if (serial.waitForBytesWritten(m_wait_timeout)) {
      if (serial.waitForReadyRead(current_wait_timeout)) {
        QByteArray response_data = serial.readAll();
        while (serial.waitForReadyRead(10))
          response_data += serial.readAll();

        const QString response = QString::fromUtf8(response_data);
        emit this->response(response);
      } else {
        emit timeout(tr("Wait read response timeout %1")
                         .arg(QTime::currentTime().toString()));
      }
    } else {
      emit timeout(tr("Wait write request timeout %1")
                       .arg(QTime::currentTime().toString()));
    }
    m_mutex.lock();
    m_cond.wait(&m_mutex);
    if (current_port_name != m_port_name) {
      current_port_name = m_port_name;
      current_port_name_changed = true;
    } else {
      current_port_name_changed = false;
    }
    current_wait_timeout = m_wait_timeout;
    current_request = m_request;
    m_mutex.unlock();
  }
}
