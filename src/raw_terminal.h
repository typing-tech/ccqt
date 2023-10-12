#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "senderthread.h"

class RawTerminal : public QWidget {
  Q_OBJECT

public:
  RawTerminal(SenderThread *thread, QComboBox *devices);

  void add_response(QString const &response);
  void add_error(QString const &err);

private:
  void send_data(void);

  SenderThread *m_thread = nullptr;
  QComboBox *m_devices = nullptr;

  QLineEdit m_line_edit;
  QPushButton m_send_btn;

  QScrollArea m_scroll_area;
  QLabel m_serial_output;

  QFont m_mono_font;

  QHBoxLayout m_layout_input;
  QVBoxLayout m_layout;
};
