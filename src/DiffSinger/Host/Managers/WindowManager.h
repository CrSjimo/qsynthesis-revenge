#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QMainWindow>

#include "Managers/QsAbstractManager.h"
#include "QDspxModel.h"

#include "QsMacros.h"

class HomeWindow;
class PianoWindow;
class WindowManagerPrivate;

#define qWindows WindowManager::instance()

class WindowManager : public QsAbstractManager {
    Q_OBJECT
    Q_DECLARE_PRIVATE(WindowManager)

    Q_SINGLETON(WindowManager)
public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

public:
    HomeWindow *showHome();
    void hideHome();

    PianoWindow *newProject();
    PianoWindow *openProject(const QDspxModel &model);

    QMainWindow *firstWindow() const;

    bool exit();

protected:
    WindowManager(WindowManagerPrivate &d, QObject *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // WINDOWMANAGER_H
