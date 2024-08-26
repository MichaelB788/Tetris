#ifndef BLOCK_H
#define BLOCK_H

class Block
{
    private:
        int x, y;

        void createBlock(int x, int y, char type);

    public:
        Block(int x, int y, char type);

        bool isValidPosition();

};

#endif
