#ifndef TETRIMINO_BLOCK
#define TETRIMINO_BLOCK

class Tetromino
{
    private:
        enum tetr; 
        int x, y;

    public:
        Tetromino(char type);

        bool isValidPosition();
}

#endif
