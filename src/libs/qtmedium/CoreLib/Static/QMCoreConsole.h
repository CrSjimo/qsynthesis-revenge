#ifndef QMCORESONSOLE_H
#define QMCORESONSOLE_H

#include <QObject>

#include "QMGlobal.h"

#define qmCon QMCoreConsole::instance()

class QsFileManager;
class QsPluginManager;
class QMCoreConsolePrivate;

class QMCORELIB_API QMCoreConsole : public QObject {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMCoreConsole)
    Q_SINGLETON(QMCoreConsole)
public:
    explicit QMCoreConsole(QObject *parent = nullptr);
    ~QMCoreConsole();

public:
    enum MessageBoxFlag {
        Critical,
        Warning,
        Question,
        Information,
    };

    /**
     * @brief MsgBox            Execute a message box displaying information
     * @param parent            Parent window or object
     * @param flag              Message type
     * @param title             Message box title
     * @param text              Message box text
     */
    virtual void MsgBox(QObject *parent, MessageBoxFlag flag, const QString &title, const QString &text);

    struct SelectOption {
        std::function<QString()> previewr; // A function returning a string to display
        QString title;                     // The item title
        QString caption;                   // The item caption (Maybe no need)
        bool selectable;                   // Whether the item can be selected
        bool *selected;                    // Result address
    };

    /**
     * @brief SelectBox         Select a subset of options referring to given information
     * @param parent            Parent window or object
     * @param supportPreview    Whether to use previewer during the selection
     * @param max               Maximum items can be selected
     * @param title             Select box title
     * @param caption           Select box caption
     * @param arguments         Items to select
     */
    virtual void SelectBox(QObject *parent, bool supportPreview, int max, const QString &title, const QString &caption,
                           const QList<SelectOption> &arguments);

protected:
    QMCoreConsole(QMCoreConsolePrivate &d, QObject *parent = nullptr);

    QScopedPointer<QMCoreConsolePrivate> d_ptr;
};

#endif // QMCORESONSOLE_H
