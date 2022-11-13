#ifndef LVELEMAPPLICATIONPRIVATE_H
#define LVELEMAPPLICATIONPRIVATE_H

#include "../LvElemApplication.h"
#include "Kernel/private/QsApplication_p.h"

#include "Managers/FileManager.h"
#include "Managers/PluginManager.h"

#include "../LvDistConfig.h"

class LVELEM_API LvElemApplicationPrivate : public QsApplicationPrivate {
    Q_DECLARE_PUBLIC(LvElemApplication)
public:
    LvElemApplicationPrivate();
    ~LvElemApplicationPrivate();

    void init();
    void deinit();
};

#endif // LVELEMAPPLICATIONPRIVATE_H
