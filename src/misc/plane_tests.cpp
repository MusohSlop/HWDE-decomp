// Plane tests for convex shapes (0x71004fe40c-0x71004fec94): take the shape's support point in the
// direction opposite the plane normal and report whether it lies on or below the plane. One per
// shape type, each with its own support function. Names are descriptive placeholders. Status:
// matching/README.md.

struct SupportPoint {
    SupportPoint() {}
    SupportPoint(float x, float y, float z) : x(x), y(y), z(z) {}
    SupportPoint operator-() const { return SupportPoint(-x, -y, -z); }

    float x;                  // +00
    float y;                  // +04
    float z;                  // +08
    int w;                    // +0c
};

struct Plane {
    float x;                  // +00
    float y;                  // +04
    float z;                  // +08
    float d;                  // +0c
};
struct Shape506264;
SupportPoint support_506264(Shape506264* shape, const SupportPoint* direction, void* cache);  // 0x7100506264

// 0x71004fe40c
unsigned char below_plane_4fe40c(Shape506264* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_506264(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape5065fc;
SupportPoint support_5065fc(Shape5065fc* shape, const SupportPoint* direction, void* cache);  // 0x71005065fc

// 0x71004fe578
unsigned char below_plane_4fe578(Shape5065fc* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_5065fc(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape507140;
SupportPoint support_507140(Shape507140* shape, const SupportPoint* direction, void* cache);  // 0x7100507140

// 0x71004fe6e4
unsigned char below_plane_4fe6e4(Shape507140* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_507140(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape50584c;
SupportPoint support_50584c(Shape50584c* shape, const SupportPoint* direction, void* cache);  // 0x710050584c

// 0x71004fe850
unsigned char below_plane_4fe850(Shape50584c* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_50584c(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape508314;
SupportPoint support_508314(Shape508314* shape, const SupportPoint* direction, void* cache);  // 0x7100508314

// 0x71004fe9bc
unsigned char below_plane_4fe9bc(Shape508314* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_508314(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape4ff0e8;
SupportPoint support_4ff0e8(Shape4ff0e8* shape, const SupportPoint* direction, void* cache);  // 0x71004ff0e8

// 0x71004feb28
unsigned char below_plane_4feb28(Shape4ff0e8* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_4ff0e8(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
struct Shape4e5994;
SupportPoint support_4e5994(Shape4e5994* shape, const SupportPoint* direction, void* cache);  // 0x71004e5994

// 0x71004fec94
unsigned char below_plane_4fec94(Shape4e5994* shape, const Plane* plane) {
    SupportPoint direction = -SupportPoint(plane->x, plane->y, plane->z);
    SupportPoint point = support_4e5994(shape, &direction, nullptr);
    float distance = plane->x * point.x + plane->y * point.y + point.z * plane->z + plane->d;
    return distance <= 0.0f;
}
