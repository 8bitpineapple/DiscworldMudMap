#ifndef BRADLEY_MIN_VECTOR2
#define BRADLEY_MIN_VECTOR2

//Very basic 2d vector class for ints with Addition, Subtraction, Multiplication.
class Vector2{
public:
    Vector2(){x=0;y=0;};
    Vector2(int _x, int _y):x(_x), y(_y) {};
    Vector2(const Vector2& a):x(a.x),y(a.y){};
    Vector2 operator+(const Vector2& b)
    {
        return Vector2(x+b.x,y+b.y);
    }

    Vector2 operator-(const Vector2& b)
    {
    return Vector2(x-b.x,y-b.y);
    }

    Vector2 operator*(int i)
    {
        return Vector2(x*i,y*i);
    }

    //Keeping x and y public to make life easier
    int x;
    int y;
};

#endif