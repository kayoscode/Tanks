#include "GameWindow.h"

#include "../Logger/StaticLogger.h"
#include "Mouse.h"
#include "Keyboard.h"

constexpr int mini(int x, int y)
{
    return x < y? x : y;
}

constexpr int maxi(int x, int y) 
{
    return x > y? x : y;
}

static GLFWmonitor* getBestMonitor(GLFWwindow *window) {
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap, bestoverlap;
    GLFWmonitor *bestmonitor;
    GLFWmonitor **monitors;
    const GLFWvidmode *mode;

    bestoverlap = 0;
    bestmonitor = NULL;

    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);

    for (i = 0; i < nmonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            maxi(0, mini(wx + ww, mx + mw) - maxi(wx, mx)) *
            maxi(0, mini(wy + wh, my + mh) - maxi(wy, my));

        if (bestoverlap < overlap) {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor;
}

/**
 * Called if there is an error
 * Logs a critical message
 * */
void windowErrorCallback(int error, const char* msg) {
    StaticLogger::instance.critical("GLFW ERROR {int} {string}", error, msg);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_RELEASE){
        Keyboard::releaseKey(key);
    }
    else if(action == GLFW_PRESS){
        Keyboard::pressKey(key);
    }
    else if(action == GLFW_REPEAT){
    }
}

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods) {
    if(action == GLFW_PRESS) {
        Mouse::pressButton(button);
    }
    else if(action == GLFW_RELEASE) {
        Mouse::releaseButton(button);
    }
}

void mousepos_callback(GLFWwindow* window, double x, double y) {
    Mouse::updatePos(x, y);
}

void mousescroll_callback(GLFWwindow* window, double x, double y) {
    Mouse::updateScroll(x, y);
}

GameWindow::GameWindow(int width, int height, int posx, int posy, bool centered, const std::string& title, int flags) 
    :window(nullptr),
    monitor(nullptr),
    windowName(title)
{
    if(createWindow(width, height, posx, posy, centered, flags & (int)WindowCreateFlags::WINDOW_FULL_SCREEN)) {
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mousebutton_callback);
        glfwSetCursorPosCallback(window, mousepos_callback);
    }
    else {
        StaticLogger::instance.critical("Window initialization failed :/\n");
    }
}

void GameWindow::getMonitorSize(int& sizex, int& sizey) {
    if(monitor == nullptr) {
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
        sizex = mode->width;
        sizey = mode->height;
    }
    else {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        sizex = mode->width;
        sizey = mode->height;
    }
}

void GameWindow::setAsCurrent() {
    glfwMakeContextCurrent(window);
}

bool GameWindow::createWindow(int width, int height, int posx, int posy, bool centered, bool fullScreen) {
    glfwSetErrorCallback(windowErrorCallback);
    monitor = glfwGetPrimaryMonitor();

    //create the window
    //last two params nullptr
    //first nullptr param can set the monitor
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    if(centered) {
        int monitorWidth, monitorHeight;
        getMonitorSize(monitorWidth, monitorHeight);

        posx = monitorWidth / 2 - (width / 2);
        posy = monitorHeight / 2 - (height / 2);
    }

    window = glfwCreateWindow(width, height, this->windowName.c_str(), nullptr, nullptr);

    glfwSetWindowPos(window, posx, posy);

    if(fullScreen) {
        GLFWmonitor* bestMonitor = getBestMonitor(window);
        monitor = bestMonitor;
        const GLFWvidmode* mode = glfwGetVideoMode(bestMonitor);

        glfwSetWindowMonitor(window, bestMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    if(!window) {
        glfwTerminate();
        StaticLogger::instance.critical("Window failed to initialize");
        return false;
    }

    setAsCurrent();
    StaticLogger::instance.trace("Successfully created window({string}) {int}x{int} Aspect ratio: {.2float}", this->windowName.c_str(), this->getWidth(), this->getHeight(), this->getAspectRatio());
    return true;
}

int GameWindow::getPosX() {
    int x, y;
    glfwGetWindowPos(window, &x, &y);

    return x;
}

int GameWindow::getPosY() {
    int x, y;
    glfwGetWindowPos(window, &x, &y);

    return y;
}

void GameWindow::clearIcon() {
    glfwSetWindowIcon(window, 0, nullptr);
}

void GameWindow::setIcon(const std::string& path) {
    GLFWimage images[1];
    //images[0] = load_icon(path.c_str())
    //TODO!
    glfwSetWindowIcon(window, 1, images);
}

void GameWindow::setTitle(const std::string& title) {
    glfwSetWindowTitle(window, title.c_str());
}

void GameWindow::setAspectRatio(int w, int h) {
    glfwSetWindowAspectRatio(window, w, h);
}

void GameWindow::setWindowSizeLimits(int minHeight, int minWidth, int maxHeight, int maxWidth) {
    glfwSetWindowSizeLimits(window, minHeight, minWidth, maxHeight, maxWidth);
}

void GameWindow::setPos(int x, int y) {
    glfwSetWindowPos(window, x, y);
}

void GameWindow::setSize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

void GameWindow::setCloseCallback(void (*close)(GLFWwindow*)) {
    glfwSetWindowCloseCallback(window, close);
}

void GameWindow::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void GameWindow::cancelClose() {
    glfwSetWindowShouldClose(window, GLFW_FALSE);
}

bool GameWindow::isClosing() {
    return glfwWindowShouldClose(window);
}

void GameWindow::pollEvents() {
    glfwPollEvents();
}

float GameWindow::getAspectRatio() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return (float)width / height;
}

int GameWindow::getWidth() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return width;
}

int GameWindow::getHeight() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return height;
}

void GameWindow::swapBuffers() {
    //glfwSwapInterval(swapSpeed);
    glfwSwapBuffers(window);
}

GameWindow::~GameWindow() {
    glfwTerminate();
}
