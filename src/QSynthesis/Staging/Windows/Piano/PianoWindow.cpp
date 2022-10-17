#include "PianoWindow.h"
#include "PianoWindow_p.h"

#include "Application/Managers/DataManager.h"
#include "Application/Managers/WindowManager.h"
#include "Application/Types/Events.h"
#include "qsmedia_version.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

PianoWindow::PianoWindow(QWidget *parent) : PianoWindow(*new PianoWindowPrivate(), parent) {
}

PianoWindow::~PianoWindow() {
}

void PianoWindow::reloadStrings() {
    Q_D(PianoWindow);
    d->reloadStrings_helper();
}

PianoWindow::PianoWindow(PianoWindowPrivate &d, QWidget *parent) : BasicWindow(parent), d_ptr(&d) {
    d.q_ptr = this;

    d.init();

    Q_TR_NOTIFY(PianoWindow)
}

bool PianoWindow::event(QEvent *event) {
    Q_D(PianoWindow);
    switch (event->type()) {
        case QEvent::Hide: {
            QEventImpl::WindowCloseEvent e(d->closeFlag);
            QApplication::sendEvent(this, &e);
            break;
        }
        default:
            break;
    }
    return BasicWindow::event(event);
}

void PianoWindow::closeEvent(QCloseEvent *event) {
}

void PianoWindow::_q_actionTriggered(int actionId) {
    Q_D(PianoWindow);
    switch (actionId) {
        case ActionImpl::File_Close: {
            d->closeFlag = true;
            close();
            break;
        }
        case ActionImpl::File_Exit: {
            qWindows->exit();
            break;
        }
        case ActionImpl::Help_AboutApplication: {
            auto ffmpeg = FF::GetFFmpegInfo();
            auto sdl = FF::GetSDLInfo();

            QString ffmpegStr;
            for (auto it = ffmpeg.begin(); it != ffmpeg.end(); ++it) {
                ffmpegStr += tr("<p>%1 %2</p>")
                                 .arg(it->name, QString::asprintf("%d.%d.%d", it->version[0],
                                                                  it->version[1], it->version[2]));
            }
            ffmpegStr += tr("<p>License: %3</p>"
                            "<p>Configuration: %4</p>")
                             .arg(ffmpeg.front().license, ffmpeg.front().configuration);

            QString sdlStr = tr("<p>%1 %2</p>")
                                 .arg("SDL2", QString::asprintf("%d.%d.%d", sdl.version[0],
                                                                sdl.version[1], sdl.version[2]));

            QString text =
                tr("<h2>%1 %2</h2>"
                   "<p>Diffusion Singer using "
                   "<span style=\"font-weight: bold;\">QSynthesis</span> framework.</p>"
                   "<p>Copyright (C) OpenVPI, 2020-2022. </p>"
                   "<h3>FFmpeg</h3>"
                   "%3"
                   "<h3>SDL2</h3>"
                   "%4")
                    .arg(qApp->applicationName(), qApp->applicationVersion(), ffmpegStr, sdlStr);

            QMessageBox::about(this, tr("About %1").arg(qApp->applicationName()), text);
            break;
        }
        case ActionImpl::Help_AboutQt:
            QMessageBox::aboutQt(this, tr("About Qt"));
            break;
        default:
            break;
    }
}