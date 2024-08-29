#ifndef COORDINATE_POINT
#define COORDINATE_POINT

class CoordinatePoint
{
    private:
        int posx;
        int posy;

    public:
        CoordinatePoint(int x, int y);
        CoordinatePoint getCoordinates();

        int getX();
        int getY();

        void shiftX(int amount);    
        void shiftY(int amount);    
};

#endif 
