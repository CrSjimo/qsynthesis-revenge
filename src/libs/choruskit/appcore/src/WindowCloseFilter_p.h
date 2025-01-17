#ifndef WINDOWCLOSEFILTER_P_H
#define WINDOWCLOSEFILTER_P_H

#include <QWidget>

namespace Core {

    class WindowCloseFilter : public QObject {
        Q_OBJECT
    public:
        explicit WindowCloseFilter(QWidget *w);
        ~WindowCloseFilter();

        QWidget *w;

    signals:
        void windowClosed(QWidget *w);

    protected:
        bool eventFilter(QObject *obj, QEvent *event) override;
    };

}

#endif // WINDOWCLOSEFILTER_P_H
