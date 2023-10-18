#pragma once

#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

#include "configuration_table_model.h"
#include "html_delegate.h"
#include "senderthread.h"

#include "params.h"

class PropertiesWidget : public QWidget {
  Q_OBJECT

public:
  PropertiesWidget(QWidget *parent = nullptr);

signals:
  bool set_param(unsigned parameter, unsigned value);
  void start_read();

private:
  void set_pressed();
  void start_read_pressed();

  QTableView m_props_table;
  HtmlDelegate m_delegate;
  ConfigurationTableModel m_props_model;

  QPushButton m_set_btn;

  QVBoxLayout m_layout;
};
