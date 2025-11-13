export module vec2;

template <typename T>
struct Vec2
{
    T x;
    T y;
};

export typedef Vec2<int> Point;
export typedef Vec2<int> IntVec2;
export typedef Vec2<float> FloatVec2;

export template <typename T>
inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
};

export template <typename T>
inline bool operator<(const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
};

export template <typename T>
inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    return Vec2<T>{ lhs.x + rhs.x, lhs.y + rhs.y };
};

export template <typename T>
inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    return Vec2{ lhs.x - rhs.x, lhs.y - rhs.y };
};

export template <typename T>
inline Vec2<T> operator/(const Vec2<T>& lhs, int rhs)
{
    return Vec2{ lhs.x / rhs, lhs.y / rhs };
};

export template <typename T>
inline void operator+=(Vec2<T>& lhs, const Vec2<T>& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
};