#include "properties.h"

#include <QHeaderView>

#include "mainwindow.h"

#include "params.h"

PropertiesWidget::PropertiesWidget(QWidget *parent) : QWidget(parent) {
  m_props_table.setModel(&m_props_model);
  m_props_table.setItemDelegateForColumn(1, &m_delegate);
  m_props_table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_props_table.setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
  m_layout.addWidget(&m_props_table);

  m_set_btn.setText("Set values");
  // m_set_btn.setToolTip("A CC device is only guaranteed a minimum of 10000 "
  //                      "writes! Do not overuse.");

  connect(&m_set_btn, &QPushButton::clicked, this,
          &PropertiesWidget::set_pressed);
  m_layout.addWidget(&m_set_btn);

  setLayout(&m_layout);
}

void PropertiesWidget::set_pressed() {
  for (unsigned i = 0; i < MESSAGES_LEN; i++) {
    auto &modified = m_props_model.params.parameters_modified[i];
    auto &current = m_props_model.params.parameters[i];
    if (modified == current)
      continue;
    auto result = emit set_param(PARAM_IDS[i], modified);
    if (result) {
      current = modified;
    }
  }
}
