#pragma once

#include <QItemDelegate>
#include <QPainter>
#include <QTextDocument>

class HtmlDelegate : public QItemDelegate {
  Q_OBJECT

public:
  HtmlDelegate(QObject *parent = 0) : QItemDelegate(parent) {}

  void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                   const QRect &rect, const QString &text) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};
