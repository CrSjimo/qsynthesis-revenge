#ifndef QSCROLLABLETABWIDGETPRIVATE_H
#define QSCROLLABLETABWIDGETPRIVATE_H

#include <QDockWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QtGlobal>

#include "QMWidgetsGlobal.h"
#include "QScrollableTabBar.h"

class QScrollableTabWidget;

class QMWIDGETS_API QScrollableTabWidgetPrivate {
    Q_DECLARE_PUBLIC(QScrollableTabWidget)
public:
    QScrollableTabWidgetPrivate();
    virtual ~QScrollableTabWidgetPrivate();

    void init();

    QScrollableTabWidget *q_ptr;

    QHBoxLayout *barLayout;
    QWidget *tabBarWidget;

    QVBoxLayout *mainLayout;

    QScrollableTabBar *tabBar;
    QStackedWidget *stack;
};

#endif // QSCROLLABLETABWIDGETPRIVATE_H
