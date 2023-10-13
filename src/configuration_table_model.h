#pragma once

#include <QAbstractTableModel>

#include "params.h"

class ConfigurationTableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  ConfigurationTableModel(QObject *parent = nullptr);

  Parameters params;
  void updateData();

  int rowCount(QModelIndex const &) const override { return MESSAGES_LEN; }
  int columnCount(QModelIndex const &) const override { return 2; }
  QVariant data(QModelIndex const &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  Qt::ItemFlags flags(QModelIndex const &index) const override;
  bool setData(QModelIndex const &index, QVariant const &value,
               int role = Qt::EditRole) override;
};
