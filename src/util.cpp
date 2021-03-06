#include "util.hpp"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
    float toDir(float vx, float vy)
    {
        return atan(vy / vx) + (vx < 0 ? PI : 0);
    }

    float toRad(float deg)
    {
        return deg / 180.f * util::PI;
    }

    float toDeg(float rad)
    {
        return rad * 180.f / util::PI;
    }

    float rotateRad(float rad, float amt)
    {
        rad += amt;
        while (rad < 0) rad += 2*PI;
        while (rad > 2*PI) rad -= 2*PI;
        return rad;
    }

    float rotateDeg(float deg, float amt)
    {
        deg += amt;
        while (deg < 0) deg += 360;
        while (deg > 360) deg -= 360;
        return deg;
    }

    float dot(sf::Vector2f v1, sf::Vector2f v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float crossZ(sf::Vector2f v1, sf::Vector2f v2)
    {
        return v2.y * v1.x - v2.x * v1.y;
    }

    float getLen(sf::Vector2f v)
    {
        return sqrt(dot(v,v));
    }

    float getMaxRad(sf::Vector2f s)
    {
        return getLen(sf::Vector2f(s.x/2, s.y/2));
    }

    float getMinRad(sf::Vector2f s)
    {
        return MIN(s.x / 2, s.y / 2);
    }

    float getDist(sf::Vector2f p1, sf::Vector2f p2)
    {
        return getLen(sf::Vector2f(p2.x-p1.x, p2.y-p1.y));
    }

    float getDist(sf::Vector2f p, sf::Vector2f p1, sf::Vector2f p2)
    {
        sf::Vector2f v(p2.x-p1.x, p2.y-p1.y);
        sf::Vector2f w(p.x-p1.x, p.y-p1.y);

        float dist, len;
        if ((dist = dot(w,v)) <= 0) return getDist(p, p1);
        if ((len = dot(v,v)) <= dist) return getDist(p, p2);
        float b = dist / len;
        sf::Vector2f pb(p1.x + b * v.x, p1.y + b * v.y);
        return getDist(p, pb);
    }

    sf::Vector2f getUnitVector(sf::Vector2f p1, sf::Vector2f p2)
    {
        sf::Vector2f v = p2 - p1;
        float len = getLen(v);
        return sf::Vector2f(v.x / len, v.y / len);
    }

    sf::Vector2f rotate(sf::Vector2f v, float rad)
    {
        sf::Transform tr;
        tr.rotate(toDeg(rad), sf::Vector2f(0, 0));
        return tr.transformPoint(v);
    }

    bool hasCollided(sf::Vector2f c1, sf::Vector2f c2, float r2)
    {
        return getDist(c1, c2) <= r2;
    }

    bool hasCollided(sf::Vector2f c1, sf::Vector2f c2, sf::Vector2f s2, float dir2)
    {
        // Basic distance check
        float dist = getDist(c1, c2);
        if (getMaxRad(s2) < dist) return false;
        if (getMinRad(s2) > dist) return true;

        // Transforming vectors
        float unitX2 = cos(dir2);
        float unitY2 = sin(dir2);
        sf::Vector2f rotWidth2(unitX2 * s2.x / 2.f, unitY2 * s2.x / 2.f);
        sf::Vector2f rotHeight2(-unitY2 * s2.y / 2.f, unitX2 * s2.y / 2.f);
        sf::Vector2f tr2[] = {c2 - rotWidth2 - rotHeight2,
            c2 + rotWidth2 - rotHeight2,
            c2 + rotWidth2 + rotHeight2,
            c2 - rotWidth2 + rotHeight2};

        // Inner check
        float si1 = crossZ(tr2[1] - tr2[0], c1 - tr2[0]);
        float si2 = crossZ(tr2[2] - tr2[1], c1 - tr2[1]);
        float si3 = crossZ(tr2[3] - tr2[2], c1 - tr2[2]);
        float si4 = crossZ(tr2[0] - tr2[3], c1 - tr2[3]);
        if (si1 < 0 && si2 < 0 && si3 < 0 && si4 < 0) return true;
        if (si1 > 0 && si2 > 0 && si3 > 0 && si4 > 0) return true;

        return false;
    }

    bool hasCollided(sf::Vector2f c1, sf::Vector2f c2, float r21, float r22)
    {
        float dist = getDist(c1, c2);
        if (dist < r21) return false;
        if (dist > r22) return false;
        return true;
    }

    bool hasCollided(sf::Vector2f c1, sf::Vector2f c2)
    {
        return c1 == c2;
    }

    bool hasCollided(sf::Vector2f c1, util::ShapeVector s1, float dir1, sf::Vector2f c2, util::ShapeVector s2, float dir2)
    {
        if (s1.s == Point && s2.s == Point) return hasCollided(c1, c2);
        if (s1.s == Point && s2.s == Circle) return hasCollided(c1, c2, s2.x);
        if (s1.s == Point && s2.s == Rectangle) return hasCollided(c1, c2, sf::Vector2f(s2.x, s2.y), dir2);
        if (s1.s == Point && s2.s == Stroke) return hasCollided(c1, c2, s2.x, s2.y);
        if (s1.s == Circle && s2.s == Point) return hasCollided(c2, c1, s1.x);
        if (s1.s == Circle && s2.s == Circle) return hasCollided(c1, s1.x, c2, s2.x);
        if (s1.s == Circle && s2.s == Rectangle) return hasCollided(c2, sf::Vector2f(s2.x, s2.y), dir2, c1, s1.x);
        if (s1.s == Circle && s2.s == Stroke) return hasCollided(c2, s2.x, s2.y, c1, s1.x);
        if (s1.s == Rectangle && s2.s == Point) return hasCollided(c2, c1, sf::Vector2f(s1.x, s1.y), dir1);
        if (s1.s == Rectangle && s2.s == Circle) return hasCollided(c1, sf::Vector2f(s1.x, s1.y), dir1, c2, s2.x);
        if (s1.s == Rectangle && s2.s == Rectangle) return hasCollided(c1, sf::Vector2f(s1.x, s1.y), dir1, c2, sf::Vector2f(s2.x, s2.y), dir2);
        if (s1.s == Rectangle && s2.s == Stroke) return hasCollided(c2, s2.x, s2.y, c1, sf::Vector2f(s1.x, s1.y), dir1);
        if (s1.s == Stroke && s2.s == Point) return hasCollided(c2, c1, s1.x, s1.y);
        if (s1.s == Stroke && s2.s == Circle) return hasCollided(c1, s1.x, s1.y, c2, s2.x);
        if (s1.s == Stroke && s2.s == Rectangle) return hasCollided(c1, s1.x, s1.y, c2, sf::Vector2f(s2.x, s2.y), dir2);
        return false;
    }

    // Circle vs circle
    bool hasCollided(sf::Vector2f c1, float r1, sf::Vector2f c2, float r2)
    {
        return (r1 + r2 > getDist(c1, c2));
    }

    // Stroke vs circle
    bool hasCollided(sf::Vector2f c1, float r11, float r12, sf::Vector2f c2, float r2)
    {
        float dist = getDist(c1, c2);
        if (r12 + r2 < dist) return false;
        if (r11 < 0) return true;
        return (dist + r2 > r11);
    }

    // Stroke vs rectangle
    bool hasCollided(sf::Vector2f c1, float r11, float r12, sf::Vector2f c2, sf::Vector2f s2, float dir2)
    {
        if (!hasCollided(c2, s2, dir2, c1, r12)) return false;
        if (r11 < 0) return false;

        // Transforming vectors
        float unitX2 = cos(dir2);
        float unitY2 = sin(dir2);
        sf::Vector2f rotWidth2(unitX2 * s2.x / 2.f, unitY2 * s2.x / 2.f);
        sf::Vector2f rotHeight2(-unitY2 * s2.y / 2.f, unitX2 * s2.y / 2.f);
        sf::Vector2f tr2[] = {c2 - rotWidth2 - rotHeight2,
            c2 + rotWidth2 - rotHeight2,
            c2 + rotWidth2 + rotHeight2,
            c2 - rotWidth2 + rotHeight2};

        // Inside edge cross check
        if (getDist(c1, tr2[0]) > r11) return true;
        if (getDist(c1, tr2[1]) > r11) return true;
        if (getDist(c1, tr2[2]) > r11) return true;
        if (getDist(c1, tr2[3]) > r11) return true;

        return false;
    }

    // Rectangle vs circle
    bool hasCollided(sf::Vector2f c1, sf::Vector2f s1, float dir1, sf::Vector2f c2, float r2)
    {
        // Basic distance check
        float dist = getDist(c1, c2);
        if (getMaxRad(s1) + r2 < dist) return false;
        if (getMinRad(s1) + r2 > dist) return true;

        // Transforming vectors
        float unitX1 = cos(dir1);
        float unitY1 = sin(dir1);
        sf::Vector2f rotWidth1(unitX1 * s1.x / 2.f, unitY1 * s1.x / 2.f);
        sf::Vector2f rotHeight1(-unitY1 * s1.y / 2.f, unitX1 * s1.y / 2.f);
        sf::Vector2f tr1[] = {c1 - rotWidth1 - rotHeight1,
            c1 + rotWidth1 - rotHeight1,
            c1 + rotWidth1 + rotHeight1,
            c1 - rotWidth1 + rotHeight1};

        // Inner check
        float si1 = crossZ(tr1[1] - tr1[0], c2 - tr1[0]);
        float si2 = crossZ(tr1[2] - tr1[1], c2 - tr1[1]);
        float si3 = crossZ(tr1[3] - tr1[2], c2 - tr1[2]);
        float si4 = crossZ(tr1[0] - tr1[3], c2 - tr1[3]);
        if (si1 < 0 && si2 < 0 && si3 < 0 && si4 < 0) return true;
        if (si1 > 0 && si2 > 0 && si3 > 0 && si4 > 0) return true;

        //Edge cross check
        if (getDist(c2, tr1[0], tr1[1]) < r2) return true;
        if (getDist(c2, tr1[1], tr1[2]) < r2) return true;
        if (getDist(c2, tr1[2], tr1[3]) < r2) return true;
        if (getDist(c2, tr1[3], tr1[0]) < r2) return true;

        return false;
    }

    // Rectangle vs rectangle
    bool hasCollided(sf::Vector2f c1, sf::Vector2f s1, float dir1, sf::Vector2f c2, sf::Vector2f s2, float dir2)
    {
        // Basic distance check
        float dist = getDist(c1, c2);
        if (getMaxRad(s1) + getMaxRad(s2) < dist) return false;
        if (getMinRad(s1) + getMinRad(s2) > dist) return true;

        // Transforming vectors
        float unitX1 = cos(dir1);
        float unitY1 = sin(dir1);
        sf::Vector2f rotWidth1(unitX1 * s1.x / 2.f, unitY1 * s1.x / 2.f);
        sf::Vector2f rotHeight1(-unitY1 * s1.y / 2.f, unitX1 * s1.y / 2.f);
        sf::Vector2f tr1[] = {c1 - rotWidth1 - rotHeight1,
            c1 + rotWidth1 - rotHeight1,
            c1 + rotWidth1 + rotHeight1,
            c1 - rotWidth1 + rotHeight1};
        float unitX2 = cos(dir2);
        float unitY2 = sin(dir2);
        sf::Vector2f rotWidth2(unitX2 * s2.x / 2.f, unitY2 * s2.x / 2.f);
        sf::Vector2f rotHeight2(-unitY2 * s2.y / 2.f, unitX2 * s2.y / 2.f);
        sf::Vector2f tr2[] = {c2 - rotWidth2 - rotHeight2,
            c2 + rotWidth2 - rotHeight2,
            c2 + rotWidth2 + rotHeight2,
            c2 - rotWidth2 + rotHeight2};

        // Axis separation theorem
        for (int i = 0; i < 4; i++) {
            sf::Vector2f separator = tr1[(i+1)%4] - tr1[i];
            float side = crossZ(tr1[(i+2)%4] - tr1[i], separator);
            int sign = (side > 0? -1 : 1);
            if (crossZ(tr2[0]-tr1[i], separator) * sign > 0 &&
                crossZ(tr2[1]-tr1[i], separator) * sign > 0 &&
                crossZ(tr2[2]-tr1[i], separator) * sign > 0 &&
                crossZ(tr2[3]-tr1[i], separator) * sign > 0)
                return false;
        }
        for (int i = 0; i < 4; i++) {
            sf::Vector2f separator = tr2[(i+1)%4] - tr2[i];
            float side = crossZ(tr2[(i+2)%4] - tr2[i], separator);
            int sign = (side > 0? -1 : 1);
            if (crossZ(tr1[0]-tr2[i], separator) * sign > 0 &&
                crossZ(tr1[1]-tr2[i], separator) * sign > 0 &&
                crossZ(tr1[2]-tr2[i], separator) * sign > 0 &&
                crossZ(tr1[3]-tr2[i], separator) * sign > 0)
                return false;
        }

        return true;
    }

    sf::Vector2f referenceToCenter(sf::Vector2f pos, sf::Vector2f size, int reference)
    {
        sf::Vector2f hSize(size.x / 2.f, size.y / 2.f);
        sf::Vector2f realPos = pos;
        if (reference == 1) {
            realPos.x += hSize.x;
            realPos.y += hSize.y;
        }
        else if (reference == 2) {
            realPos.x -= hSize.x;
            realPos.y += hSize.y;
        }
        else if (reference == 3) {
            realPos.x -= hSize.x;
            realPos.y -= hSize.y;
        }
        else if (reference == 4) {
            realPos.x += hSize.x;
            realPos.y -= hSize.y;
        }
        return realPos;
    }

    void copySprite(const sf::Vertex src[4], sf::Vertex dest[4])
    {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3];
    }

    void copyTexture(const sf::Vertex src[4], sf::Vertex dest[4])
    {
        dest[0].texCoords = src[0].texCoords;
        dest[1].texCoords = src[1].texCoords;
        dest[2].texCoords = src[2].texCoords;
        dest[3].texCoords = src[3].texCoords;
    }

    void setAlpha(sf::Vertex sprite[4], unsigned char alpha)
    {
        sprite[0].color.a = alpha;
        sprite[1].color.a = alpha;
        sprite[2].color.a = alpha;
        sprite[3].color.a = alpha;
    }

    void affixTexture(sf::Vertex sprite[4], sf::Vector2f texCoord, sf::Vector2f size)
    {
        sprite[0].texCoords = sf::Vector2f(texCoord.x, texCoord.y);
        sprite[1].texCoords = sf::Vector2f(texCoord.x + size.x, texCoord.y);
        sprite[2].texCoords = sf::Vector2f(texCoord.x + size.x, texCoord.y + size.y);
        sprite[3].texCoords = sf::Vector2f(texCoord.x, texCoord.y + size.y);
    }

    sf::Vector2f translatePos(sf::Vector2f pos, float dir, float offsetX, float offsetY)
    {
        float unitX, unitY;
        unitX = cos(dir);
        unitY = sin(dir);
        return translatePos(pos, unitX, unitY, offsetX, offsetY);
    }

    sf::Vector2f translatePos(sf::Vector2f pos, float unitX, float unitY, float offsetX, float offsetY)
    {
        float rotX, rotY, outX, outY;
        rotX = unitY * -1 * offsetY;
        rotY = unitX * offsetY;
        outX = unitX * offsetX;
        outY = unitY * offsetX;
        return sf::Vector2f(pos.x + outX + rotX, pos.y + outY + rotY);
    }

    void affixPos(sf::Vertex sprite[4], sf::Vector2f pos, sf::Vector2f size, int reference)
    {
        sf::Vector2f hSize(size.x / 2.f, size.y / 2.f);
        sf::Vector2f realPos = referenceToCenter(pos, size, reference);
        sprite[0].position = sf::Vector2f(realPos.x - hSize.x, realPos.y - hSize.y);
        sprite[1].position = sf::Vector2f(realPos.x + hSize.x, realPos.y - hSize.y);
        sprite[2].position = sf::Vector2f(realPos.x + hSize.x, realPos.y + hSize.y);
        sprite[3].position = sf::Vector2f(realPos.x - hSize.x, realPos.y + hSize.y);
    }

    void applyColor(sf::Vertex sprite[4], sf::Color c)
    {
        sprite[0].color = c;
        sprite[1].color = c;
        sprite[2].color = c;
        sprite[3].color = c;
    }

    void rotateSprite(sf::Vertex sprite[4], float dir, sf::Vector2f center)
    {
        sf::Transform tr;
        tr.rotate(dir, center);
        sprite[0].position = tr.transformPoint(sprite[0].position);
        sprite[1].position = tr.transformPoint(sprite[1].position);
        sprite[2].position = tr.transformPoint(sprite[2].position);
        sprite[3].position = tr.transformPoint(sprite[3].position);
    }

    void translateSprite(sf::Vertex sprite[4], sf::Vector2f translation)
    {
        sprite[0].position += translation;
        sprite[1].position += translation;
        sprite[2].position += translation;
        sprite[3].position += translation;
    }

    std::string trim(const std::string &s)
    {
        std::size_t idx1 = s.find_first_not_of("\t\n ");
        std::size_t idx2 = s.find_last_not_of("\t\n ");
        if (idx1 == std::string::npos) return "";
        std::size_t len = idx2 - idx1 + 1;
        return s.substr(idx1, len);
    }

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    // Split on whitespace [ \t\r\n]
    std::vector<std::string> split(const std::string &s)
    {
        const std::string match = " \t\r\n";
        std::vector<std::string> elems;
        std::size_t idx = s.find_first_not_of(match);
        while (idx != std::string::npos) {
            std::size_t endIdx = s.find_first_of(match, idx);
            elems.push_back(s.substr(idx, endIdx-idx));
            idx = s.find_first_not_of(match, endIdx);
        }
        return elems;
    }

    bool isPrefix(const std::string &p, const std::string &s)
    {
        if (p.size() > s.size()) return false;
        return !strncmp(p.c_str(), s.c_str(), p.size());
    }

    std::string appendNumber(const std::string &s, int n)
    {
        std::stringstream ss;
        ss << s << n;
        return ss.str();
    }

    // Allocates a dynamic contiguous 2 dimensional array
    // Memory structure: [pointers][data]
    // Each pointer simply points to a known offset (row) in the data
    // More cache-friendly compared to typical, non-contiguous 2D arrays. Also
    // easier to free
    void** alloc2D(unsigned esize, unsigned rows, unsigned cols)
    {
        char *mem, **ptrs, *data;
        if (!(mem = (char*)malloc(sizeof(char*) * rows + esize * rows * cols)))
            return NULL;
        ptrs = (char**)mem;
        data = mem + sizeof(char*) * rows;
        for (unsigned i = 0; i < rows; i++)
            ptrs[i] = data + i*esize*cols;
        memset(data, 0, esize*rows*cols);
        return (void**)ptrs;
    }

    int** alloc2Dint(unsigned rows, unsigned cols)
    {
        return (int**)alloc2D(sizeof(int), rows, cols);
    }

    bool** alloc2Dbool(unsigned rows, unsigned cols)
    {
        return (bool**)alloc2D(sizeof(bool), rows, cols);
    }

    void free2D(void* arr)
    {
        free(arr);
    }

    int rand(int min, int max)
    {
        return ((unsigned)std::rand() << 16 | std::rand()) % (max - min + 1) + min;
    }

    int atoi(const std::string &s)
    {
        int val = 0;
        int size = s.size();
        int i = 0;
        bool neg = s[0] == '-';
        if (neg)
            i++;
        while (i < size) {
            val = val * 10 + s[i] - '0';
            i++;
        }
        return neg ? -val : val;
    }

    std::string itoa(int val)
    {
        if (val == 0)
            return "0";
        const int MAXLEN = 11;
        std::string s(MAXLEN, 0);
        int count = 0;
        bool neg = val < 0;
        if (neg)
            val = -val;
        while (val) {
            s[count] = val % 10 + '0';
            count++;
            val /= 10;
        }
        if (neg) {
            s[count] = '-';
            count++;
        }
        s.resize(count);
        for (int i = 0; i < count/2; i++) {
            char tmp = s[i];
            s[i] = s[count-i-1];
            s[count-i-1] = tmp;
        }
        return s;
    }
}
