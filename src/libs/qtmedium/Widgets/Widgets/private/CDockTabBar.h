#ifndef CDOCKTABBAR_H
#define CDOCKTABBAR_H

#include <QFrame>

#include "CDockCard.h"
#include "QMNamespace.h"

class CDockSideBar;

class QMWIDGETS_API CDockTabBar : public QFrame {
    Q_OBJECT
public:
    explicit CDockTabBar(QWidget *parent = nullptr);
    CDockTabBar(QM::Direction barDirection, QWidget *parent = nullptr);
    ~CDockTabBar();

public:
    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orient);

    QM::Direction barDirection() const;
    void setBarDirection(QM::Direction barDirection);

    QM::Direction cardDirection() const;
    void setCardDirection(QM::Direction cardDirection);

    int placeholder() const;
    void setPlaceholder(int placeholder, int width);
    void removePlaceholder();

    void addCard(CDockCard *card);
    void insertCard(int index, CDockCard *card);
    void insertCard(CDockCard *indexCard, CDockCard *card);
    void removeCard(CDockCard *card);
    void removeAllCards();

    int count() const;
    int indexOf(CDockCard *card) const;
    QList<CDockCard *> cards() const;
    CDockCard *cardAt(int index) const;

    CDockCard *cardAtPos(QPoint pos) const;

    int indexAtPos(QPoint pos) const;

    int activeIndex() const;
    void setActiveIndex(int index);

    CDockSideBar *doubleTabBar() const;

protected:
    void resetLayout();
    void resetCardTransform(CDockCard *card) const;

private:
    void _q_tabDragStarted(const QPoint &pos, const QPixmap &pixmap);
    void _q_tabToggled(bool checked);

protected:
    int m_placeholderIndex;
    int m_placeholderWidth;

    Qt::Orientation m_orientation;

    QM::Direction m_barDirection;
    QM::Direction m_cardDirection;

    QList<CDockCard *> m_cards;

    QWidget *createPlaceholder(int width) const;

    void paintEvent(QPaintEvent *event) override;

signals:
    void dragStarted(CDockCard *card, const QPoint &pos, const QPixmap &pixmap);

    void cardAdded(CDockCard *card);
    void cardRemoved(CDockCard *card);
    void cardToggled(CDockCard *card);
};

#endif // CDOCKTABBAR_H
