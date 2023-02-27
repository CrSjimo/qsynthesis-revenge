#ifndef QMDECORATORPRIVATE_H
#define QMDECORATORPRIVATE_H

#include "../QMDecorator.h"
#include "private/QMCoreDecorator_p.h"

#include "ThemeTemplate.h"

#include <set>

#include <QHash>
#include <QSet>
#include <QTranslator>

#define ENABLE_PARTIAL_OVERRIDE 1

/**
 * @brief Theme related
 *
 */
class ThemeGuard;
struct ThemePlaceholder;

struct ScreenSet {
    bool dirty;
    QScreen *screen;
    QHash<QWidget *, ThemeGuard *> widgets;

    ScreenSet(QScreen *screen);
};

struct ThemeSubscriber {
    QStringList keySeq;
    QHash<QScreen *, ScreenSet *> screens;
    QHash<QWidget *, ThemeGuard *> widgets;
    QHash<QString, ThemePlaceholder *> templates;

    ThemeSubscriber();
    void notifyAll();

    void installScreen(ThemeGuard *tg);
    void uninstallScreen(ThemeGuard *tg);
    void switchScreen(ThemeGuard *tg);

    bool isEmpty() const;
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
};

struct ThemePlaceholder {
    QString ns;
    QSet<ThemeSubscriber *> subscribers;

    struct ConfigSet {
        std::map<int, QHash<QString, QSharedPointer<ThemeConfig>>>
            data; // priority - (config_key - config)
    };
    QHash<QString, ConfigSet> configs; // theme_key - config_set

    QSharedPointer<ThemeTemplate> data;

    // Incremental update
    QHash<QScreen *, QString> stylesheetCaches;

    bool isEmpty() const;
    void invalidate();
    QString getAndCache(QScreen *screen);
};

struct ThemeConfigPack {
    QHash<QString, QSharedPointer<ThemeConfig>> data; // theme_key - config
};


class QMDecoratorPrivate : public QMCoreDecoratorPrivate {
    Q_DECLARE_PUBLIC(QMDecorator)
public:
    QMDecoratorPrivate();
    virtual ~QMDecoratorPrivate();

    void init();

    void screenChange_helper(QScreen *screen);

    QHash<QString, ThemeConfigPack> themeConfigs;                // configKey
    QHash<QString, ThemePlaceholder *> themeTemplates;           // templateKey
    QHash<QStringList, ThemeSubscriber *> themeSubscriberGroups; // templateKeys
    QHash<QWidget *, ThemeSubscriber *> themeSubscribers;        // w

    static std::list<ThemeGuard *> subscriberUpdateQueue;

    static void subscriberUpdateEnqueue(ThemeGuard *tg);

    // Internal use
    static QMDecoratorPrivate *self;
};

#endif // QMDECORATORPRIVATE_H