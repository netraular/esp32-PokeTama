#ifndef GLOBALS_H
#define GLOBALS_H

#include "persistent_data_manager.h"

// Declarar la instancia de PersistentDataManager como un puntero
extern PersistentDataManager* dataManager;
// Declarar la variable para verificar si pet_stats.json existe
extern bool petStatsExists;

#endif