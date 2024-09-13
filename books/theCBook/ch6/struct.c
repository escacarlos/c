struct point
{
    int x;
    int y;
};

struct rect
{
    struct point pt1;
    struct point pt2;
};

/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

/* addpoints: add two points */
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

struct string
{
    int len;
    char *str;
} *p;

#define NKEYS 20
struct key
{
    char *word;
    int count;
} keytab[NKEYS];

struct key1
{
    char *word;
    int count;
};

struct key1 keytab1[NKEYS];

struct key2
{
    char *word;
    int count;
} keytab2[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    /* ... */
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0};

int main()
{

    struct point pt;
    pt.x = 50;
    pt.y = 100;

    printf("%d,%d", pt.x, pt.y);

    double dist, sqrt(double);

    dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);

    struct rect screen;

    screen.pt1.x;

    struct point middle;
    struct point makepoint(int, int);
    screen.pt1 = makepoint(0, 0);
    struct point maxpt = {320, 200};
    screen.pt2 = makepoint(maxpt.x, maxpt.y);
    middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                       (screen.pt1.y + screen.pt2.y) / 2);

    struct point origin, *pp;
    pp = &origin;
    printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);
    printf("origin is (%d,%d)\n", pp->x, pp->y);

    struct rect r, *rp = &r;
    r.pt1.x;
    rp->pt1.x;
    (r.pt1).x;
    (rp->pt1).x;

    ++p->len;   // increments len, not p; ++(p->len)
    (++p)->len; // increments p before accessing len
    (p++)->len; // increments p afterward. (This last set of parentheses is unnecessary.)

    *p->str;     // fetches whatever str points to
    *p->str++;   // increments str after accessing whatever it points to (just like *s++);
    (*p->str)++; // increments whatever str points to;
    *p++->str;   // increments p after accessing whatever str points to

    // Parallel arrays
    char *keyword[NKEYS];
    int keycount[NKEYS];
}
