#ifndef MINIMAP_H
#define MINIMAP_H

//////////////////////// MINI ////////////////////////

void printMinimap(void);
void remPrevRoomMinM(int prevFx, int prevFy);
void updateMinM(int newFx, int newFy, int corrX, int corrY, bool isHCorrUpdate);

//////////////////////// OPEN ////////////////////////

bool openMapMode(void);

#endif // MINIMAP_H