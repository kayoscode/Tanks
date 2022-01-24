#ifndef INCLUDE_INPUT_H
#define INCLUDE_INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

/**
 * Base class that can be used to determine if a specific input event has 
 * taken place
 * @author Bryce Young 5/27/2021
 * */
class Input {
    public:
        /**
         * Should be called once before the input is checked
         * Calls the onActivate function if the state changed from false to true
         * */
        void update() {
            bool previousState = isActive;

            check();

            if(previousState != isActive && isActive) {
                onActivate();
            }
        }

        virtual void check() = 0;

        virtual void onActivate() {}

        bool getActive() {
            return isActive;
        }

        operator bool() {
            return isActive;
        }

    protected:
        bool isActive = false;
};

/**
 * Inputs involving single key inputs
 * @author Bryce Young 5/27/2021
 * */
class KeyInput : public Input{
    public:
        KeyInput(int key) : key(key) {}

    protected:
        int key;
};

/**
 * Inputs involving single mouse inputs
 * @author Bryce Young 5/27/2021
 * */
class MouseInput : public Input{
    public:
        MouseInput(int button) : button(button) {}

    protected:
        int button;
};

/**
 * Activates if a key is down
 * @author Bryce Young 5/27/2021
 * */
class KeyDownInput : public KeyInput {
    public:
        KeyDownInput(int key) : KeyInput(key) {}
        void check() {
            this->isActive = Keyboard::isKeyDown(this->key);
        }
};

/**
 * Activates the first frame the key is pressed
 * @author Bryce Young 5/27/2021
 * */
class KeyPressedInput : public KeyInput {
    public:
        KeyPressedInput(int key) : KeyInput(key) {}
        void check() {
            this->isActive = Keyboard::isKeyPressed(this->key);
        }
};

/**
 * Activates if a key is clicked
 * @author Bryce Young 5/27/2021
 * */
class KeyClickedInput : public KeyInput {
    public:
        KeyClickedInput(int key) : KeyInput(key) {}
        void check() {
            this->isActive = Keyboard::isKeyClicked(this->key);
        }
};

/**
 * Activates if a key is up
 * @author Bryce Young 5/27/2021
 * */
class KeyUpInput : public KeyInput {
    public:
        KeyUpInput(int key) : KeyInput(key) {}
        void check() {
            this->isActive = Keyboard::isKeyUp(this->key);
        }
};

/**
 * Activates if a key is up
 * @author Bryce Young 5/27/2021
 * */
class MouseUpInput : public MouseInput {
    public:
        MouseUpInput(int button) : MouseInput(button) {}
        void check() {
            this->isActive = Mouse::isButtonUp(this->button);
        }
};

/**
 * Activates if a key is down
 * @author Bryce Young 5/27/2021
 * */
class MouseDownInput : public MouseInput {
    public:
        MouseDownInput(int button) : MouseInput(button) {}
        void check() {
            this->isActive = Mouse::isButtonDown(this->button);
        }
};

/**
 * Activates the frame the key is pressed down
 * @author Bryce Young 5/27/2021
 * */
class MousePressedInput : public MouseInput {
    public:
        MousePressedInput(int button) : MouseInput(button) {}
        void check() {
            this->isActive = Mouse::isButtonPressed(this->button);
        }
};

/**
 * Activates the frame the key is released
 * @author Bryce Young 5/27/2021
 * */
class MouseClickedInput : public MouseInput {
    public:
        MouseClickedInput(int button) : MouseInput(button) {}
        void check() {
            this->isActive = Mouse::isButtonClicked(this->button);
        }
};

/**
 * Active if the mouse moved
 * */
class MouseMoveInput : public Input {
    public:
        void check() {
            this->isActive = Mouse::getPosDX() || Mouse::getPosDY();
        }
};

/**
 * Active if the mouse left
 * */
class MouseMoveLeftInput : public Input {
    public:
        void check() {
            this->isActive = Mouse::getPosDX() < 0;
        }
};

/**
 * Active if the mouse right
 * */
class MouseMoveRightInput : public Input {
    public:
        void check() {
            this->isActive = Mouse::getPosDX() < 0;
        }
};

/**
 * Active if the mouse down
 * */
class MouseMoveDownInput : public Input {
    public:
        void check() {
            this->isActive = Mouse::getPosDY() > 0;
        }
};

/**
 * Active if the mouse up
 * */
class MouseMoveUpInput : public Input {
    public:
        void check() {
            this->isActive = Mouse::getPosDY() < 0;
        }
};

/**
 * Active if the mouse scrolled left
 * */
class MouseScrollLeft : public Input {
    public:
        void check() {
            this->isActive = Mouse::getScrollDX() < 0;
        }
};

/**
 * Active if the mouse scrolled right
 * */
class MouseScrollRight : public Input {
    public:
        void check() {
            this->isActive = Mouse::getScrollDX() > 0;
        }
};

/**
 * Active if the mouse scrolled up
 * */
class MouseScrollUp : public Input {
    public:
        void check() {
            this->isActive = Mouse::getScrollDY() < 0;
        }
};

/**
 * Active if the mouse scrolled down
 * */
class MouseScrollDown : public Input {
    public:
        void check() {
            this->isActive = Mouse::getScrollDY() > 0;
        }
};

#endif