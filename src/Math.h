#pragma once

typedef struct Vec3 {
    float x, y, z;
    Vec3() {};
    Vec3(float x, float y, float z) : x(x), y(x), z(x) {};
    Vec3 operator * (float a) const { return Vec3(x * a, y * a, z * a); }
    Vec3 operator + (Vec3 a) const { return Vec3(x + a.x, y + a.y, z + a.z); }
    Vec3 operator += (Vec3 a) const { return Vec3(x + a.x, y + a.y, z + a.z); }

} Vec3;
