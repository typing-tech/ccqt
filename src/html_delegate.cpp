#include "html_delegate.h"

void HtmlDelegate::drawDisplay(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QRect &rect, const QString &text) const {
  QTextDocument doc;

  QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
                                ? QPalette::Normal
                                : QPalette::Disabled;
  if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
    cg = QPalette::Inactive;
  QColor textColor = option.palette.color(cg, QPalette::Text);
  doc.setDefaultStyleSheet(QString("body { color: %1}").arg(textColor.name()));
  doc.setDefaultFont(option.font);
  doc.setHtml(text);
  doc.setDocumentMargin(4); // the default is 4 which is too much

  painter->save();
  painter->translate(rect.topLeft());
  doc.drawContents(painter);
  painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
  QTextDocument doc;
  doc.setDefaultFont(option.font);
  doc.setHtml(index.data(Qt::DisplayRole).toString());
  doc.setDocumentMargin(1);
  return doc.size().toSize();
}
