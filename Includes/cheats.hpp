#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
    void clockImpl(MenuEntry *entry);
    float degreeToRadian(float degree);
    int getPosByAngleX(float degree, float radius);
    int getPosByAngleY(float degree, float radius);
    void drawLine(const Screen& screen, const Color& color, int srcX, int srcY, int dstX, int dstY);
}

#endif
