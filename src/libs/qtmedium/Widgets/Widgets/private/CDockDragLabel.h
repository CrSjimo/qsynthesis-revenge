#ifndef __CDOCKDRAGLABEL_H__
#define __CDOCKDRAGLABEL_H__

#include <QLabel>

#include "QMWidgetsGlobal.h"

class CDockCard;
class CDockSideBar;

class QMWIDGETS_API CDockDragLabel : public QLabel {
    Q_OBJECT
public:
    explicit CDockDragLabel(QWidget *parent = nullptr);
    ~CDockDragLabel();

public:
    CDockCard *currentCard;
    QPoint currentPos;
    CDockSideBar *originBar, *targetBar;
};

#endif // __CDOCKDRAGLABEL_H__