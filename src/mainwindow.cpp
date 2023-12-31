#include "mainwindow.h"
#include "properties.h"

#include <QTimer>
#include <QtSerialPort/QSerialPortInfo>
#include <cstdio>
#include <iostream>

void MainWindow::set_controls_enabled(bool state) {
  m_devices.setEnabled(state);
  m_refresh_devices_button.setEnabled(state);
}

MainWindow::MainWindow() : m_raw_terminal(&m_sender_thread, &m_devices) {
  refresh_serial_devices();

  m_main_layout = new QVBoxLayout();

  connect(&m_sender_thread, &SenderThread::response, this,
          [&](QString const &response) {
            set_controls_enabled(false);
            m_raw_terminal.add_response(response);
          });
  connect(&m_sender_thread, &SenderThread::error, [&](QString const &err) {
    set_controls_enabled(true);
    m_raw_terminal.add_error(err);
  });
  connect(&m_sender_thread, &SenderThread::timeout,
          [&]() { set_controls_enabled(true); });
  connect(&m_sender_thread, &SenderThread::connection_status,
          [&](bool connected) { set_controls_enabled(!connected); });
  connect(&m_properties, &PropertiesWidget::set_param, this,
          [&](unsigned parameter, unsigned value) -> bool {
            m_sender_thread.transaction(
                m_devices.currentText().split(" ").at(0).trimmed(), 1000,
                QString("VAR B2 %1 %2\r\n").arg(parameter).arg(value));
            // FIXME: Do not assume.
            return true;
          });

  m_devices.setPlaceholderText("No CC device detected.");
  m_devices_hbox_layout.addWidget(&m_devices, true);

  m_refresh_devices_button.setText("Refresh");
  connect(&m_refresh_devices_button, &QPushButton::clicked, this,
          &MainWindow::refresh_serial_devices);
  m_devices_hbox_layout.addWidget(&m_refresh_devices_button);

  m_main_layout->addLayout(&m_devices_hbox_layout);

  m_tabs.addTab(&m_raw_terminal, "Raw Serial");
  m_tabs.addTab(&m_properties, "Properties");
  m_main_layout->addWidget(&m_tabs);

  m_main_widget.setLayout(m_main_layout);
  setCentralWidget(&m_main_widget);
}

void MainWindow::refresh_serial_devices() {
  m_devices.clear();
  const auto serialPortInfos = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo &portInfo : serialPortInfos) {
    if (portInfo.manufacturer() == "CharaChorder")
      m_devices.addItem(portInfo.portName() + " (" + portInfo.description() +
                        ")");
  }

  if (m_devices.maxVisibleItems())
    m_devices.setCurrentIndex(0);
}
