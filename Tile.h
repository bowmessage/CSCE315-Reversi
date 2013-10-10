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
    
    bool isBlack();
    bool isWhite();
    bool isEmpty();   //Chose "isEmpty" because "isBlank" looks too much like "isBlack" and could likely cause debugging hardships.
    void turnBlack();
    void turnWhite();
};


#endif
