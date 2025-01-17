#ifndef ACTIONSYSTEM_H
#define ACTIONSYSTEM_H

#include <QMenuBar>

#include "ActionContext.h"

namespace Core {

    class ActionSystemPrivate;

    class CKAPPCORE_API ActionSystem : public QObject {
        Q_OBJECT
    public:
        explicit ActionSystem(QObject *parent = nullptr);
        ~ActionSystem();

    public:
        bool addContext(ActionContext *context);
        bool removeContext(ActionContext *context);
        bool removeContext(const QString &id);

        ActionContext *context(const QString &id) const;
        QList<ActionContext *> contexts() const;
        QStringList contextIds() const;

        QStringList loadContexts(const QString &filename);

    public:
        QMap<QString, QStringList> stateCache(const QString &id);
        void setStateCache(const QString &id, const QMap<QString, QStringList> &state);

    protected:
        QScopedPointer<ActionSystemPrivate> d_ptr;
        ActionSystem(ActionSystemPrivate &d, QObject *parent = nullptr);

        Q_DECLARE_PRIVATE(ActionSystem)

        friend class ActionContext;
    };

}

#endif // ACTIONSYSTEM_H
