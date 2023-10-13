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

#include "configuration_table_model.h"
#include "html_delegate.h"
#include "raw_terminal.h"
#include "senderthread.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

  void refresh_serial_devices();

protected:
  void set_controls_enabled(bool state);

  HtmlDelegate m_delegate;

  RawTerminal m_raw_terminal;
  ConfigurationTableModel m_props_model;
  QTableView m_props_table;

  SenderThread m_sender_thread;

  QHBoxLayout m_devices_hbox_layout;
  QComboBox m_devices;

  QPushButton m_refresh_devices_button;

  QTabWidget m_tabs;

  QWidget m_main_widget;
  QVBoxLayout *m_main_layout;
};
