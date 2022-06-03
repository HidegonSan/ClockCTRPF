#include "cheats.hpp"
#include <math.h>
#include <string>
#include <vector>

namespace CTRPluginFramework
{
    float degreeToRadian(float degree) {
        return degree*M_PI / 180;
    }

    int getPosByAngleX(float degree, float radius) {
        float radian = degreeToRadian(degree);
        return std::round(cos(radian)*radius);
    }

    int getPosByAngleY(float degree, float radius) {
        float radian = degreeToRadian(degree);
        return std::round(sin(radian)*radius);
    }

    // Thanks: https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
    void drawLine(const Screen& screen, const Color& color, int srcX, int srcY, int dstX, int dstY) {
        float x, y, dx, dy, step;
        int i;

        dx = (dstX - srcX);
        dy = (dstY - srcY);

        if (abs(dx) >= abs(dy)) {
            step = abs(dx);
        }
        else {
            step = abs(dy);
        }

        dx = dx / step;
        dy = dy / step;
        x = srcX;
        y = srcY;
        i = 1;

        while (i <= step) {
            screen.DrawPixel(x, y, color);
            x = x + dx;
            y = y + dy;
            i++;
        }
    }

    void clockImpl(MenuEntry* entry)
    {
        const Screen &topScreen = OSD::GetTopScreen();

        int clockRadius = 25;
        int clockPadding = 5;
        int clockBorderWidth = 1;
        int centerOfClockX = 400 - (clockPadding + clockRadius);
        int centerOfClockY = clockPadding + clockRadius;

        int dialPadding = 3;
        int dialLength = 4;

        int hourHandRadius = 12;
        int minuteHandRadius = 17;
        int secondHandRadius = 16;

        int dialStartRadius = clockRadius - (dialPadding + dialLength);
        int dialEndRadius = clockRadius - dialPadding;
        int dialStartX, dialStartY, dialEndX, dialEndY;

        Color clockBackgroundColor = Color::White;
        Color clockBorderColor = Color::Black;
        Color dialColor = Color::Black;
        Color hourHandColor = Color::Black;
        Color minuteHandColor = Color::Black;
        Color secondHandColor = Color::Gray;

        u64 currentOsUnixTime = (osGetTime() / 1000);
        int currentOsHour = (currentOsUnixTime / 3600) % 24;
        int currentOsMinute = currentOsUnixTime / 60 % 60;
        int currentOsSecond = currentOsUnixTime % 60;

        int tmpTime, hourHandAngle, minuteHandAngle, secondHandAngle, hourHandEndX, hourHandEndY, minuteHandEndX, minuteHandEndY, secondHandEndX, secondHandEndY;


        // Draw clock background
        for (int radius=0; radius<clockRadius; radius++) {
            for (int angle=0; angle<360; angle++) {
                // Draw border
                if ((clockRadius - radius) <= clockBorderWidth) {
                    topScreen.DrawPixel(getPosByAngleX(angle, radius) + centerOfClockX, getPosByAngleY(angle, radius) + centerOfClockY, clockBorderColor);
                }
                else {
                    topScreen.DrawPixel(getPosByAngleX(angle, radius) + centerOfClockX, getPosByAngleY(angle, radius) + centerOfClockY, clockBackgroundColor);
                }
            }
        } // End of Draw clock background


        // Draw dial
        for (int angle=0; angle<360; angle+=30) {
            dialStartX = getPosByAngleX(angle, dialStartRadius);
            dialStartY = getPosByAngleY(angle, dialStartRadius);
            dialEndX = getPosByAngleX(angle, dialEndRadius);
            dialEndY = getPosByAngleY(angle, dialEndRadius);
            drawLine(topScreen, dialColor, centerOfClockX + dialStartX, centerOfClockY + dialStartY, centerOfClockX + dialEndX, centerOfClockY + dialEndY);
        } // End of draw dial


        // Draw hour hand
        if (currentOsHour < 3) {
            hourHandAngle = 270 + 30*currentOsHour;
        }
        else {
            hourHandAngle = 30*(currentOsHour - 3);
        }
        // Slight tilt
        hourHandAngle += (currentOsMinute / 2);
        hourHandEndX = getPosByAngleX(hourHandAngle, hourHandRadius);
        hourHandEndY = getPosByAngleY(hourHandAngle, hourHandRadius);
        drawLine(topScreen, hourHandColor, centerOfClockX, centerOfClockY, centerOfClockX + hourHandEndX, centerOfClockY + hourHandEndY);
        // End of draw hour hand


        // Draw minute hand
        if (currentOsMinute < 15) {
            minuteHandAngle = 270 + 6*currentOsMinute;
        }
        else {
            minuteHandAngle = 6*(currentOsMinute - 15);
        }
        minuteHandEndX = getPosByAngleX(minuteHandAngle, minuteHandRadius);
        minuteHandEndY = getPosByAngleY(minuteHandAngle, minuteHandRadius);
        drawLine(topScreen, minuteHandColor, centerOfClockX, centerOfClockY, centerOfClockX + minuteHandEndX, centerOfClockY + minuteHandEndY);
        // End of draw minute hand


        // Draw second hand
        if (currentOsSecond < 15) {
            secondHandAngle = 270 + 6*currentOsSecond;
        }
        else {
            secondHandAngle = 6*(currentOsSecond - 15);
        }
        secondHandEndX = getPosByAngleX(secondHandAngle, secondHandRadius);
        secondHandEndY = getPosByAngleY(secondHandAngle, secondHandRadius);
        drawLine(topScreen, secondHandColor, centerOfClockX, centerOfClockY, centerOfClockX + secondHandEndX, centerOfClockY + secondHandEndY);
        // End of draw second hand

    } // End of clockImpl

} // CTRPluginFramework