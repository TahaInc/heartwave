#ifndef MENUITEMSTYLE_H
#define MENUITEMSTYLE_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

#define FONTSIZE 18

class MenuItemStyle : public QStyledItemDelegate {

public:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    painter->save();

    QTextDocument doc;
    doc.setHtml(options.text);
    doc.setDefaultFont(QFont("Noto Sans", FONTSIZE));

    options.text = "";
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    painter->translate(options.rect.left(), options.rect.top());
    QRectF clip(0, 0, options.rect.width(), doc.size().height());

    QAbstractTextDocumentLayout::PaintContext ctx;
    if (option.state & QStyle::State_Selected){
        ctx.palette.setColor(QPalette::Text, QColor("white"));
    }
    ctx.clip = clip;

    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
  }

  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    QTextDocument text;
    text.setHtml(options.text);
    text.setDefaultFont(QFont("Noto Sans", FONTSIZE));

    return QSize(text.idealWidth(), text.size().height());
  }
};

#endif // MENUITEMSTYLE_H
