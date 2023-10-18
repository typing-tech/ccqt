#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMutex>
#include <QPushButton>
#include <QTabWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

#include "params.h"

#include "properties.h"
#include "raw_terminal.h"
#include "senderthread.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

  void refresh_serial_devices();
  void load_parameters(int current_index = 0, int max = MESSAGES_LEN);

protected:
  void set_controls_enabled(bool state);

  RawTerminal m_raw_terminal;
  PropertiesWidget m_properties;

  SenderThread m_sender_thread;

  QHBoxLayout m_devices_hbox_layout;
  QComboBox m_devices;

  QPushButton m_refresh_devices_button;

  QTabWidget m_tabs;

  QWidget m_main_widget;
  QVBoxLayout *m_main_layout;
};
