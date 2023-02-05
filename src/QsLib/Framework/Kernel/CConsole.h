#ifndef CCONSOLE_H
#define CCONSOLE_H

#include "QsCoreConsole.h"
#include "QsFrameworkGlobal.h"

class CConsolePrivate;

class QSFRAMEWORK_API CConsole : public QsCoreConsole {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CConsole)
public:
    explicit CConsole(QObject *parent = nullptr);
    ~CConsole();

    void MsgBox(QObject *parent, MessageBoxFlag flag, const QString &title,
                const QString &text) override;

protected:
    CConsole(CConsolePrivate &d, QObject *parent = nullptr);
};

#endif // CCONSOLE_H