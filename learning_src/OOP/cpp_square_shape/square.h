#include "shape.h"

class Square : public Shape {
    public:
        Square(int x, int y, int width, int height)
            : x_(x), y_(x), width_(width), height_(height) {}
        virtual ~Square() {}

        const char* name() const override { return "Square";}
        int sides() const override { return 4; }

        int x() const {return x_;}
        int y() const {return y_;}
        int width() const { return width_;}
        int height() const {return height_;}

    private:
        int x_;
        int y_;
        int width_;
        int height_;
};