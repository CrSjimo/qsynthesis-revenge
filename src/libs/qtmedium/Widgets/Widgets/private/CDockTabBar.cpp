#include "CDockTabBar.h"
#include "CDockSideBar.h"

#include <QDrag>
#include <QHBoxLayout>
#include <QMimeData>
#include <QVBoxLayout>

CDockTabBar::CDockTabBar(QWidget *parent) : CDockTabBar(QM::Forward, parent) {
}

CDockTabBar::CDockTabBar(QM::Direction barDirection, QWidget *parent) : QFrame(parent) {
    setAttribute(Qt::WA_StyledBackground);

    m_placeholderIndex = -1;
    m_placeholderWidth = 0;

    m_barDirection = barDirection;
    m_cardDirection = QM::Forward;
    m_orientation = Qt::Horizontal;

    resetLayout();
}

CDockTabBar::~CDockTabBar() {
}

Qt::Orientation CDockTabBar::orientation() const {
    return m_orientation;
}

void CDockTabBar::setOrientation(Qt::Orientation orient) {
    if (m_orientation != orient) {
        m_orientation = orient;
        resetLayout();
    }
}

QM::Direction CDockTabBar::barDirection() const {
    return m_barDirection;
}

void CDockTabBar::setBarDirection(QM::Direction barDirection) {
    if (m_barDirection != barDirection) {
        m_barDirection = barDirection;
        resetLayout();
    }
}

QM::Direction CDockTabBar::cardDirection() const {
    return m_cardDirection;
}

void CDockTabBar::setCardDirection(QM::Direction cardDirection) {
    m_cardDirection = cardDirection;
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        auto card = *it;
        card->setLongitudinalDirection(
            static_cast<CDockCard::LongitudinalDirection>(cardDirection));
    }
}

int CDockTabBar::placeholder() const {
    return m_placeholderIndex;
}

void CDockTabBar::setPlaceholder(int placeholder, int width) {
    removePlaceholder();

    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    if (!layout) {
        return;
    }
    if (placeholder >= 0 && placeholder < layout->count()) {
        QWidget *w = createPlaceholder(width);
        layout->insertWidget(placeholder, w);
        m_placeholderIndex = placeholder;
        m_placeholderWidth = width;
    }
}

void CDockTabBar::removePlaceholder() {
    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    if (!layout) {
        return;
    }
    if (m_placeholderIndex >= 0) {
        auto w = layout->itemAt(m_placeholderIndex)->widget();
        layout->removeWidget(w);
        delete w;
    }
    m_placeholderIndex = -1;
    m_placeholderWidth = 0;
}

void CDockTabBar::addCard(CDockCard *card) {
    insertCard(m_cards.size(), card);
}

void CDockTabBar::insertCard(int index, CDockCard *card) {
    if (!card->widget()) {
        qWarning().nospace() << "CCoupleTabBar: card \"" << card
                             << "\" doesn't have a valid widget pointer.";
        return;
    }

    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    if (m_cards.contains(card)) {
        return;
    }
    resetCardTransform(card);

    // Uncheck all other cards
    if (card->isChecked()) {
        for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
            auto cur = *it;
            cur->blockSignals(true);
            cur->setChecked(false);
            cur->blockSignals(false);
        }
    }

    if (index >= m_cards.size()) {
        layout->addWidget(card);
        m_cards.append(card);
    } else if (index <= 0) {
        layout->insertWidget(0, card);
        m_cards.prepend(card);
    } else {
        layout->insertWidget(index, card);
        m_cards.insert(index, card);
    }
    card->show();
    connect(card, &CDockCard::startDrag, this, &CDockTabBar::_q_tabDragStarted);
    connect(card, &CDockCard::toggled, this, &CDockTabBar::_q_tabToggled);

    emit cardAdded(card);
}

void CDockTabBar::insertCard(CDockCard *indexCard, CDockCard *card) {
    return insertCard(indexOf(indexCard), card);
}

void CDockTabBar::removeCard(CDockCard *card) {
    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    if (!m_cards.contains(card)) {
        return;
    }
    disconnect(card, &CDockCard::startDrag, this, &CDockTabBar::_q_tabDragStarted);
    disconnect(card, &CDockCard::toggled, this, &CDockTabBar::_q_tabToggled);
    m_cards.removeOne(card);
    layout->removeWidget(card);
    emit cardRemoved(card);
}

void CDockTabBar::removeAllCards() {
    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        auto card = *it;
        disconnect(card, &CDockCard::startDrag, this, &CDockTabBar::_q_tabDragStarted);
        disconnect(card, &CDockCard::toggled, this, &CDockTabBar::_q_tabToggled);
        layout->removeWidget(card);
        emit cardRemoved(card);
    }
    m_cards.clear();
}

int CDockTabBar::count() const {
    return m_cards.size();
}

int CDockTabBar::indexOf(CDockCard *card) const {
    return m_cards.indexOf(card);
}

QList<CDockCard *> CDockTabBar::cards() const {
    return m_cards;
}

CDockCard *CDockTabBar::cardAt(int index) const {
    if (index < 0 || index >= m_cards.size()) {
        return nullptr;
    }
    return m_cards.at(index);
}

CDockCard *CDockTabBar::cardAtPos(QPoint pos) const {
    return qobject_cast<CDockCard *>(childAt(pos));
}

int CDockTabBar::activeIndex() const {
    int i = 0;
    int res = -1;
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        auto card = *it;
        if (card->isChecked()) {
            res = i;
            break;
        }
        i++;
    }
    return res;
}

void CDockTabBar::setActiveIndex(int index) {
    if (index < 0 || index >= m_cards.size()) {
        int cur = activeIndex();
        if (cur >= 0) {
            m_cards.at(cur)->setChecked(false);
        }
        return;
    }
    auto card = m_cards.at(index);
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        auto cur = *it;
        cur->blockSignals(true);
        cur->setChecked(cur == card);
        cur->blockSignals(false);
    }
    emit cardToggled(card);
}

CDockSideBar *CDockTabBar::doubleTabBar() const {
    return qobject_cast<CDockSideBar *>(parentWidget());
}

void CDockTabBar::resetLayout() {
    // Store org
    QList<QWidget *> widgets;
    QBoxLayout *layout = static_cast<QBoxLayout *>(this->layout());
    if (layout) {
        for (int i = 0; i < layout->count(); ++i) {
            auto w = layout->itemAt(i)->widget();
            widgets.append(w);
        }
        delete layout;
    }

    // New
    if (m_orientation == Qt::Horizontal) {
        layout = new QHBoxLayout();
        layout->setDirection((m_barDirection == QM::Forward) ? QBoxLayout::LeftToRight
                                                             : QBoxLayout::RightToLeft);
        setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    } else {
        layout = new QVBoxLayout();
        layout->setDirection((m_barDirection == QM::Forward) ? QBoxLayout::TopToBottom
                                                             : QBoxLayout::BottomToTop);
        setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    }

    layout->setMargin(0);
    layout->setSpacing(0);

    // Insert
    for (auto it = widgets.begin(); it != widgets.end(); ++it) {
        layout->addWidget(*it);
    }

    for (auto it = m_cards.begin(); it != m_cards.end(); ++it) {
        auto card = *it;
        resetCardTransform(card);
    }

    setLayout(layout);
}

void CDockTabBar::resetCardTransform(CDockCard *card) const {
    if (card->orientation() != m_orientation) {
        card->setOrientation(m_orientation);
    }
    auto ld = static_cast<CDockCard::LongitudinalDirection>(m_cardDirection);
    if (card->longitudinalDirection() != ld) {
        card->setLongitudinalDirection(ld);
    }
}

void CDockTabBar::_q_tabDragStarted(const QPoint &pos, const QPixmap &pixmap) {
    auto card = qobject_cast<CDockCard *>(sender());
    emit dragStarted(card, pos, pixmap);
}

void CDockTabBar::_q_tabToggled(bool checked) {
    auto card = qobject_cast<CDockCard *>(sender());
    if (checked) {
        setActiveIndex(indexOf(card));
    } else {
        emit cardToggled(card);
    }
}

QWidget *CDockTabBar::createPlaceholder(int width) const {
    QWidget *w = new QWidget();
    if (m_orientation == Qt::Horizontal) {
        w->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
        w->resize(width, w->height());
    } else {
        w->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
        w->resize(w->width(), width);
    }
    return w;
}

void CDockTabBar::paintEvent(QPaintEvent *event) {
    return QWidget::paintEvent(event);
}
