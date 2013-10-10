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
    
    bool isBlack();
    bool isWhite();
    bool isEmpty();
    void turnBlack();
    void turnWhite();
};


#endif
