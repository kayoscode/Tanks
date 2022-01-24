#include "Keyboard.h"

bool Keyboard::keyState[KEY_COUNT] = { false };
bool Keyboard::keyPressed[KEY_COUNT] = { false };
bool Keyboard::keyClicked[KEY_COUNT] = { false };

char Keyboard::keyToChar(int key, bool numLock, bool shift, bool capsLock){
    static const char* shiftNumsTrans = ")!@#$%^&*(";
    static const char* numLockTrans = "0123456789";
    static const char* kpOpTrans = "./*-+\n=";

    int ret = 0;
    
    if(key == KEY_ENTER){
        ret = '\n';
    }
    else if(key == KEY_BACKSLASH){
        if(shift){
            ret = '|';
        }
        else{ 
            ret = '\\';
        }
    }
    else if(key == KEY_APOSTROPHE){
        if(shift){
            ret = '"';
        }
        else{
            ret = '\'';
        }
    }
    else if(key == KEY_LEFT_BRACKET){
        if(shift){
            ret = '{';
        }
        else{
            ret = '[';
        }
    }
    else if(key == KEY_RIGHT_BRACKET){
        if(shift){
            ret = '}';
        }
        else{
            ret = ']';
        }
    }
    else if(key == KEY_SEMICOLON){
        if(shift){
            ret = ':';
        }
        else{
            ret = ';';
        }
    }
    else if(key == KEY_SLASH){
        if(shift){
            ret = '?';
        }
        else{
            ret = '/';
        }
    }
    else if(key == KEY_PERIOD){
        if(shift){
            ret = '>';
        }
        else{
            ret = '.';
        }
    }
    else if(key == KEY_COMMA){
        if(shift){
            ret = '<';
        }
        else{
            ret = ',';
        }
    }
    else if(key == KEY_EQUAL){
        if(shift){
            ret = '+';
        }
        else{ 
            ret = '=';
        }
    }
    else if(key == KEY_MINUS){
        if(shift){
            ret = '_';
        }
        else{ 
            ret = '-';
        }
    }
    else if(key == KEY_GRAVE_ACCENT){
        if(shift){
            ret = '~';
        }
        else{ 
            ret = '`'	;
        }
    }
    else if(key >= KEY_0 && key <= KEY_9){
        if(shift){
            ret = shiftNumsTrans[key - KEY_0];
        }
        else{
            ret = key;
        }
    }
    else if(key >= KEY_KP_0 && key <= KEY_KP_9){
        if(numLock){
            ret = numLockTrans[key - KEY_KP_0];
        }
    }
    else if(key >= KEY_KP_DECIMAL && key <= KEY_KP_EQUAL){
        ret = kpOpTrans[key - KEY_KP_DECIMAL];
    }
    else if(key >= KEY_SPACE && key <= KEY_RIGHT_BRACKET) {
        if(shift ^ capsLock){
            ret = toupper(key);
        }
        else {
            ret = tolower(key);
        }
    }

    return ret;
}