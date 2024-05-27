#include "TimeControl.h"

TimeControl::TimeControl(Player *player, FileUtility *filetm);
void TimeControl::autoSave();
void TimeControl::changePhaseInGame();
void TimeControl::changeStatesDueToPhase();