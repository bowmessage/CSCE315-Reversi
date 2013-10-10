#ifndef TILE_H
#define TILE_H

enum State{
  EMPTY, WHITE, BLACK
};

class Tile{
  public:

    Tile();
    Tile(State s);

    State state;

    void setState(State s);
    State getState();
    
};


#endif
