#include "raw_terminal.h"

#include <QFontDatabase>
#include <QScrollBar>
#include <QTimer>

RawTerminal::RawTerminal(SenderThread *thread, QComboBox *devices)
    : m_thread(thread), m_devices(devices) {

  m_line_edit.setPlaceholderText("Data to send");
  m_layout_input.addWidget(&m_line_edit, true);

  m_mono_font = QFontDatabase::systemFont(QFontDatabase::FixedFont);

  m_serial_output.setAlignment(Qt::AlignmentFlag::AlignTop);
  m_serial_output.setTextFormat(Qt::TextFormat::RichText);
  m_serial_output.setWordWrap(true);
  m_serial_output.setFont(m_mono_font);

  m_scroll_area.setWidget(&m_serial_output);
  m_scroll_area.setWidgetResizable(true);
  m_scroll_area.ensureWidgetVisible(&m_serial_output, 0, 0);

  m_reset_line.setChecked(true);
  m_reset_line.setText("Auto-clean");
  m_layout_input.addWidget(&m_reset_line);

  m_send_btn.setText("Send");
  m_layout_input.addWidget(&m_send_btn);

  connect(&m_line_edit, &QLineEdit::returnPressed, this,
          &RawTerminal::send_data);

  connect(&m_send_btn, &QPushButton::clicked, this, &RawTerminal::send_data);

  m_layout.addLayout(&m_layout_input);

  m_layout.addWidget(&m_scroll_area, true);

  setLayout(&m_layout);
}

void RawTerminal::add_response(QString const &response) {
  m_serial_output.setText(m_serial_output.text() + "<br><font color=blue>" +
                          response + "</font>");
  QTimer::singleShot(0, this, [&]() {
    QScrollBar *bar = m_scroll_area.verticalScrollBar();
    bar->setValue(bar->maximum());
  });
}

void RawTerminal::add_error(QString const &err) {
  m_serial_output.setText(m_serial_output.text() + "<br><font color=red>!!! " +
                          err + " !!!</font>");
  QTimer::singleShot(0, this, [&]() {
    QScrollBar *bar = m_scroll_area.verticalScrollBar();
    bar->setValue(bar->maximum());
  });
}

void RawTerminal::send_data(void) {
  m_serial_output.setText(m_serial_output.text() + "<br>&gt;" +
                          m_line_edit.text());
  QTimer::singleShot(0, this, [&]() {
    QScrollBar *bar = m_scroll_area.verticalScrollBar();
    bar->setValue(bar->maximum());
    if (m_reset_line.isChecked())
      m_line_edit.setText("");
  });
  m_thread->transaction(m_devices->currentText().split(" ").at(0).trimmed(),
                        1000, m_line_edit.text() + "\r\n");
}
