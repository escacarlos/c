class Shape {
    public:
        virtual ~Shape() {}
        virtual const char* name() const = 0;
        virtual int sides() const = 0;
};

