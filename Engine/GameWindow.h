#pragma once

#include "../lib/glew/include/GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>

struct GLFWwindow;

/**
 * error codes for window creation
 * */
enum class WindowCreateStatus {
    SUCCESS,
    INIT_ERR,
    CREATE_ERR
};

/// <summary>
/// Flags that may be set when creating a window.
/// </summary>
enum WindowCreateFlags
{
    WINDOW_FULL_SCREEN = 1,
    WINDOW_VSYNC = 2
};

/**
 * Class that handles windows and input
 * @author Bryce Young 5/26/2021
 * */
class GameWindow {
    public:
        /**
         * Creates a new window with the specified parameters
         * @param width the width of the window in pixels
         * @param height the height of the window in pixels
         * @param flags flags for window creation such as full screen
         * */
        GameWindow(int width, int height, int posx, int posy, bool centered, const std::string& title = "untitled", int flags = 0);

        /**
         * Destructor
         * */
        ~GameWindow();

        /**
         * locks the mouse to the window and hides its position
         * */
        void grabMouse();

        /**
         * ungrabs the mouse returning it to its original settings
         * */
        void ungrabMouse();

        /**
         * Hides the mouse from view
         * */
        void hideMouse();

        /**
         * Shows the mouse again
         * */
        void showMouse();

        /**
         * @return the aspect ratio of the window width:height
         * */
        float getAspectRatio();

        /**
         * returns the dimensions of the window
         * */
        int getWidth();
        int getHeight();

        /**
         * @return the position of the window in coords
         * */
        int getPosX();
        int getPosY();

        /**
         * Sets the window to a closing status and will close on the next update
         * */
        void close();

        /**
         * stops the close process
         * */
        void cancelClose();

        /**
         * @return whether the window will close or not
         * */
        bool isClosing();

        /**
         * Sets the function that is called when the window closes
         * */
        void setCloseCallback(void(*callback)(GLFWwindow*));

        /**
         * Sets the window size
         * */
        void setSize(int width, int height);

        /**
         * the window's size cannot be changed from those bounds
         * */
        void setWindowSizeLimits(int minHeight, int minWidth, int maxHeight, int maxWidth);

        /**
         * Forces the window to adopt an aspect ratio
         * handled by OS
         * */
        void setAspectRatio(int x, int y);

        /**
         * Sets the position
         * */
        void setPos(int x, int y);

        /**
         * Sets the window's title
         * */
        void setTitle(const std::string& title);

        /**
         * Sets the window's icon
         * */
        void setIcon(const std::string& path);

        /**
         * Removes the icon
         * */
        void clearIcon();

        /**
         * Returns the window title as a string
         * */
        std::string getTitle() {
            return windowName;
        }
        
        /**
         * Sets the window as the current context
         * Updates will be sent to this window
         * */
        void setAsCurrent();

        /**
         * Updates the window
         * Sends OS events
         * */
        void pollEvents();

        /**
         * Swaps the window's buffers
         * */
        void swapBuffers();

        /**
         * Get center of primary monitor
         * */
        void getMonitorSize(int& sizex, int& sizey);

    private:

        /**
         * Creates a window based on the set parameters
         * */
        bool createWindow(int width, int height, int posx, int posy, bool centered, bool fullscreen);

        GLFWwindow* window;
        struct GLFWmonitor* monitor;
        std::string windowName;
};