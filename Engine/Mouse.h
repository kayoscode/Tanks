#ifndef INCLUDE_MOUSE_H
#define INCLUDE_MOUSE_H

#include <memory.h>

/**
 * Constants representing mouse buttons
 * */
enum Button{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_4,
    MOUSE_BUTTON_5,
    MOUSE_BUTTON_6,
    MOUSE_BUTTON_7,
    MOUSE_BUTTON_LAST,
    BUTTON_COUNT
};

/**
 * Class updating the state of the mouse
 * @author Bryce Young 05/27/2021
 * */
class Mouse {
    public:
        /**
         * the current state of the mouse buttons
         * */
        static bool mouseState[BUTTON_COUNT];

        /**
         * Each button is in a pressed state if it was clicked down this frame
         * */
        static bool pressedState[BUTTON_COUNT];

        /**
         * This is set to true, but only the frame after the mouse button was released
         * */
        static bool clickedState[BUTTON_COUNT];

        /**
         * sets the x and y values for the mouse position
         * */
        static void updatePos(double x, double y) {
            posdx = x - posx;
            posdy = y - posy;
            posx = x;
            posy = y;
        }

        static void update() {
            memset(pressedState, 0, sizeof(pressedState));
            memset(clickedState, 0, sizeof(clickedState));
        }

        static double getPosX() {
            return posx;
        }

        static double getPosY() {
            return posy;
        }

        static double getScrollX() {
            return scrollx;
        }

        static double getScrollY() {
            return scrolly;
        }

        static double getPosDX() {
            return posdx;
        }

        static double getPosDY() {
            return posdy;
        }

        static double getScrollDX() {
            return scrolldy;
        }

        static double getScrollDY() {
            return scrolldy;
        }

        /**
         * sets the x and y values for the mouse scroll
         * */
        static void updateScroll(double x, double y) {
            scrolldx = x - scrollx;
            scrolldy = y - scrolly;
            scrollx = x;
            scrolly = y;
        }

        /**
         * returns if a mouse button is up
         * */
        static bool isButtonUp(int button) {
            if(button < BUTTON_COUNT) {
                return !mouseState[button];
            }

            return false;
        }

        /**
         * returns if a mouse button is down
         * */
        static bool isButtonDown(int button) {
            if(button < BUTTON_COUNT) {
                return mouseState[button];
            }

            return false;
        }

        /**
         * Returns if the button was released this frame
         * */
        static bool isButtonClicked(int button) {
            if(button < BUTTON_COUNT) {
                return clickedState[button];
            }

            return false;
        }

        /**
         * updates the state of a mouse button
         * */
        static void pressButton(int button) {
            if(button < BUTTON_COUNT) {
                if(!mouseState[button]) {
                    pressedState[button] = true;
                }

                mouseState[button] = true;
            }
        }

        /**
         * Udpates the state of a mouse button
         * */
        static void releaseButton(int button) {
            if(button < BUTTON_COUNT) {
                clickedState[button] = true;
                mouseState[button] = false;
            }
        }

        /**
         * Returns whether the button is pressed or not
         * Resets at the end of the frame
         * */
        static bool isButtonPressed(int button) {
            if(button < BUTTON_COUNT) {
                return pressedState[button];
            }

            return false;
        }

    private:
        static double posx;
        static double posy;
        static double posdx;
        static double posdy;

        static double scrollx;
        static double scrolly;
        static double scrolldx;
        static double scrolldy;
};

#endif