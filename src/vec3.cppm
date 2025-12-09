export module vec3;

template <typename T>
struct Vec3
{
    T x;
    T y;
    T z;
};

export typedef Vec3<int> IntVec3;
export typedef Vec3<float> FloatVec3;

export template <typename T>
inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
};

export template <typename T>
inline bool operator<(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y) || (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z < rhs.z);
};

export template <typename T>
inline Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
};

export template <typename T>
inline Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
};

export template <typename T>
inline Vec3<T> operator/(const Vec3<T>& lhs, int rhs)
{
    return Vec3{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs.z };
};

export template <typename T>
inline void operator+=(Vec3<T>& lhs, const Vec3<T>& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
};