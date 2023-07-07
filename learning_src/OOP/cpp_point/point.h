class Point {
    public:
        Point(int x, int y);
        ~Point();
        int x() const;
        int y() const;
    private:
        const int x_;
        const int y_;
};