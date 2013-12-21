#ifndef __GUI_MASTER_PANEL_H_
#define __GUI_MASTER_PANEL_H_

#include <stdint.h>
#include "guiWidgets.h"




extern guiPanel_t     guiMasterPanel;


void guiMasterPanel_Initialize(guiGenericWidget_t *parent);


void updateVoltageIndicator(void);
void updateCurrentIndicator(void);
void updateTemperatureIndicator(void);
void updatePowerIndicator(void);


#endif
