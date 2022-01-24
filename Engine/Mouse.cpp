#include "Mouse.h"

bool Mouse::pressedState[BUTTON_COUNT] = { false };
bool Mouse::mouseState[BUTTON_COUNT] = { false };
bool Mouse::clickedState[BUTTON_COUNT] = { false };

double Mouse::posx = 0;
double Mouse::posy = 0;
double Mouse::posdx = 0;
double Mouse::posdy = 0;

double Mouse::scrollx = 0;
double Mouse::scrolly = 0;
double Mouse::scrolldx = 0;
double Mouse::scrolldy = 0;