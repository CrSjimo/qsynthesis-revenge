#ifndef CONFIGURABLEDIALOG_H
#define CONFIGURABLEDIALOG_H

#include <QDialog>

#include "coreplugin/CoreGlobal.h"

namespace Core {

    class ConfigurableDialogPrivate;

    class CORE_EXPORT ConfigurableDialog : public QDialog {
        Q_OBJECT
        Q_DECLARE_PRIVATE(ConfigurableDialog)
    public:
        explicit ConfigurableDialog(QWidget *parent = nullptr);
        ~ConfigurableDialog();

        void done(int r) override;

    public:
        QWidget *widget() const;
        QWidget *takeWidget();
        void setWidget(QWidget *w);

    protected:
        virtual void apply();
        virtual void finish();

    signals:
        void applied();
        void finished();

    protected:
        ConfigurableDialog(ConfigurableDialogPrivate &d, QWidget *parent = nullptr);

        QScopedPointer<ConfigurableDialogPrivate> d_ptr;
    };

}

#endif // CONFIGURABLEDIALOG_H