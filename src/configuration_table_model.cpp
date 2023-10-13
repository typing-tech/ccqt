#include "configuration_table_model.h"
#include "params.h"

ConfigurationTableModel::ConfigurationTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant ConfigurationTableModel::data(QModelIndex const &index,
                                       int role) const {
  if (index.parent().isValid() || index.row() < 0 ||
      (unsigned)index.row() > MESSAGES_LEN) {
    return QVariant();
  }

  if (role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();

  if (index.column() == 0)
    return MESSAGES[index.row()];
  else if (index.column() == 1) {
    auto &normal = params.parameters[index.row()];
    auto &modified = params.parameters_modified[index.row()];

    if (normal != modified) {
      if (role == Qt::DisplayRole)
        return QString("<font color=red>%1</font>").arg(modified);
      else
        return QString("%1").arg(modified);
    } else {
      return QString("%1").arg(normal);
    }
  }
  return QVariant();
}

QVariant ConfigurationTableModel::headerData(int section,
                                             Qt::Orientation orientation,
                                             int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == 0)
      return tr("Parameter");
    else if (section == 1)
      return tr("Value");
  }
  return QVariant();
}

Qt::ItemFlags ConfigurationTableModel::flags(QModelIndex const &index) const {
  auto flags = QAbstractTableModel::flags(index);
  if (index.column() == 1)
    flags |= Qt::ItemIsEditable;
  return flags;
}

bool ConfigurationTableModel::setData(QModelIndex const &index,
                                      QVariant const &value, int role) {
  if (!index.isValid() || role != Qt::EditRole || index.column() == 0)
    return false;

  QString str = value.toString().trimmed();
  if (str.isEmpty()) {
    params.parameters_modified[index.row()] = params.parameters[index.row()];
    return true;
  }
  bool ok = false;
  int num = str.toInt(&ok);
  if (!ok)
    return false;
  params.parameters_modified[index.row()] = num;
  return true;
}
