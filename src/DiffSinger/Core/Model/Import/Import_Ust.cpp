#include "../QDspxModel.h"

#include "QUstFile.h"

bool QDspx::fromUst(const QString &filename, QDspx::Model *out, QObject *parent) {
    QUstFile ust;
    if (!ust.load(filename)) {
        qDebug() << "Failed to parse UTAU file.";
        return false;
    }

    qDebug() << ust.sectionNotes.size();

    return true;
}
