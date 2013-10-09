#ifndef TILE_H
#define TILE_H

enum State{
  BLANK, WHITE, BLACK
};

class Tile{
  public:

    Tile();
    Tile(State s);

    State state;
};

#endif
