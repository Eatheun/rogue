#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#define ISPLAYER(x, y) (x == _px && y == _py)
#define ISWALL(x, y) (x == 0 || x == _currRoomW - 1 || y == 0 || y == _currRoomH - 1)

bool move(void);

#endif // MOVEMENTS_H