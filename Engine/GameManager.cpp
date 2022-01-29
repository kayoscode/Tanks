#include "GameManager.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "Serializers/JSON Serializer/JsonSerializer.h"
#include "Logger/StaticLogger.h"
#include "Render Engine/Camera.h"
#include "Math/Math.h"

#include <iostream>
#include <sstream>

// Set platform definitions.
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(__WIN32)
#define OS_WINDOWS
#endif

#if defined(__linux__)
#define OS_LINUX
#error Operating System Unsupported
#endif

#if defined(__APPLE__) || defined(__MACH__)
#define OS_MAC
#error Operating System Unsupported
#endif

#include <cassert>

GameManager::constructor GameManager::cons;
Platform GameManager::platform;
std::string GameManager::resFolder = "";
GameResources GameManager::Resources;

GameManager::GameTime GameManager::mRenderTime;
GameManager::GameTime GameManager::mUpdateTime;

std::thread GameManager::mMainWindowRenderThread;

GameWindow* GameManager::mMainWindow = nullptr;
std::unique_ptr<Scene> GameManager::mScene = nullptr;

GameManager::constructor::constructor() 
{
    initializePlatform();
}

GameManager::constructor::~constructor() 
{
}

void GameManager::createWindow(const WindowConfig& windowConfig) 
{
    // Init glfw and create window.
    if(!glfwInit()) 
    {
        StaticLogger::instance.critical("Could not initialize [^'window]");
    }
    else 
    {
        bool fullScreen = windowConfig.fullscreen;
        int flags = 0;
        flags |= (fullScreen)? (int)WindowCreateFlags::WINDOW_FULL_SCREEN : 0;

        mMainWindow = new GameWindow(windowConfig.width, windowConfig.height, windowConfig.xPos, windowConfig.yPos, windowConfig.centered, windowConfig.gameName, flags);
        GLenum err = glewInit();

        if(err != 0) {
            StaticLogger::instance.critical("Could not initialize [^'OpenGL]: {string}", glewGetErrorString(err));
        }
        else {
            StaticLogger::instance.trace("Initialized [^'graphics instance] on [^'main thread]");
        }
    }
}

void GameManager::start()
{
    // Init: load resources.
    init();

    glClearColor(.0f, 1, 1, 1);

    // Spawn the render thread and move GL context to new thread.
    Framebuffer::unBind(mMainWindow->getWidth(), mMainWindow->getHeight());
    glfwMakeContextCurrent(nullptr);
    mMainWindowRenderThread = std::thread(executeRenderLoop);
    mMainWindowRenderThread.detach();

    executeUpdateLoop();
}

void GameManager::createWindow(const std::string& settingsPath) {
    WindowConfig windowConf(800, 600);
    JsonFile file(settingsPath);

    if(!file.isLoadSuccessful()) {
        StaticLogger::instance.warning("Settings file provided but failed to load");
        createWindow(windowConf);
        return;
    }

    JsonObject* head = file.getHead()->objectValue;

    StaticLogger::instance.trace("Loading settings from {string}", settingsPath.c_str());

    //check for window preferences
    JsonValue* windowSettings = head->lookupNode("window");
    JsonValue* resPath = head->lookupNode("respath");

    //load required window settings
    if(windowSettings == nullptr || windowSettings->type != JsonValueType::Object) {
        StaticLogger::instance.warning("Settings file does not contain valid window data");
    }
    else {
        //height, width, title, are required
        JsonValue* height, *width, *posx, *posy, *title, *fullscreen, *vSync, *center;
        height = windowSettings->objectValue->lookupNode("height");
        width = windowSettings->objectValue->lookupNode("width");
        posx = windowSettings->objectValue->lookupNode("posx");
        posy = windowSettings->objectValue->lookupNode("posy");
        title = windowSettings->objectValue->lookupNode("title");
        fullscreen = windowSettings->objectValue->lookupNode("fullscreen");
        center = windowSettings->objectValue->lookupNode("center");
        vSync = windowSettings->objectValue->lookupNode("vsync");

        if(height == nullptr || height->type != JsonValueType::Number) {
            StaticLogger::instance.warning("height attribute must be of type Number");
        }
        else {
            windowConf.height = height->numberValue;
        }

        if(width == nullptr || width->type != JsonValueType::Number) {
            StaticLogger::instance.warning("width attribute must be of type Number");
        }
        else {
            windowConf.width = width->numberValue;
        }

        if(title == nullptr || title->type != JsonValueType::String) {
            StaticLogger::instance.warning("title attribute must be of type string");
        }
        else {
            windowConf.gameName = title->stringValue;
        }

        if(posx != nullptr) {
            if(posx->type == JsonValueType::Number) {
                windowConf.xPos = posx->numberValue;
            }
            else {
                StaticLogger::instance.warning("posx attribute provided, but is not of type number");
            }
        }

        if(posy != nullptr) {
            if(posy->type == JsonValueType::Number) {
                windowConf.yPos = posy->numberValue;
            }
            else {
                StaticLogger::instance.warning("posy attribute provided, but is not of type number");
            }
        }

        if(fullscreen != nullptr) {
            if(fullscreen->type == JsonValueType::Boolean) {
                windowConf.fullscreen = fullscreen->booleanValue;
            }
            else {
                StaticLogger::instance.warning("fullscreen attribute provided, but is not of type boolean");
            }
        }

        if(center != nullptr) {
            if(center->type == JsonValueType::Boolean) {
                //center the window
                windowConf.centered = center->booleanValue;
            }
            else {
                StaticLogger::instance.warning("center attribute provided, but is not of type boolean");
            }
        }

        if(vSync != nullptr) {
            if(vSync->type == JsonValueType::Boolean) {
                //center the window
                windowConf.vSync = vSync->booleanValue;
            }
            else {
                StaticLogger::instance.warning("vsync attribute provided, but is not of type boolean");
            }
        }
    }

    // Load the resources path.
    if(resPath != nullptr) {
        if(resPath->type == JsonValueType::String) {
            setResPath(resPath->stringValue);
        }
        else {
            StaticLogger::instance.warning("respath attribute provided, but is not of type string");
        }
    }

    createWindow(windowConf);
}

void GameManager::initializePlatform() {
    // Load the platform information.
    #ifdef OS_LINUX
    platform.os = OperatingSystem::LINUX;
    #endif

    #ifdef OS_WINDOWS
    GameManager::platform.os = OperatingSystem::WINDOWS;
    #endif

    #ifdef OS_MAC
    GameManager::platform.os = OperatingSystem::MACOS_DARWIN;
    #endif
}

void GameManager::executeUpdateLoop()
{
    mUpdateTime.start();

    while (!mMainWindow->isClosing())
    {
        mMainWindow->pollEvents();
        update();

        mUpdateTime.addFrame(1000000000);
    }
}

void GameManager::executeRenderLoop() 
{
    mMainWindow->setAsCurrent();
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Right after init, start the gametime.
    mRenderTime.start();

    while(!mMainWindow->isClosing()) 
    {
        render();
        mMainWindow->swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Add a frame and output the FPS if applicable.
        if(mRenderTime.addFrame(1000000000)) 
        {
            //StaticLogger::instance.trace("Frames per second: {int}", mRenderTime.getFPS());
        }
    }

    StaticLogger::instance.trace("Closing window");
}

void GameManager::init() 
{
    mScene->init();
}

void GameManager::update()
{
    mScene->update();
	Keyboard::update();
	Mouse::update();
}

void GameManager::render() 
{
	mScene->render();
}

//return program runtime given requested timeunit
float GameManager::getProgramRuntime(TimeUnit unit) {
    switch(unit) {
        case TimeUnit::HOURS:
            return mRenderTime.getRuntimeHours();
        break;
        case TimeUnit::MINUTES:
            return mRenderTime.getRuntimeMinutes();
        break;
        case TimeUnit::SECONDS:
            return mRenderTime.getRuntimeSeconds();
        break;
        case TimeUnit::MILLISECONDS:
            return mRenderTime.getRuntimeMillis();
        break;
        case TimeUnit::MICROSECONDS:
            return mRenderTime.getRuntimeMicros();
        break;
        case TimeUnit::NANOSECONDS:
            return (float)mRenderTime.getRuntimeNanoseconds();
        break;
    }

    return 0;
}

void GameManager::closeProgram()
{
	mMainWindow->close();
}

void GameManager::GameTime::start()
{
	deltaTime.reset();
	totalNanos = 0;
	elapsedNanosThisSecond = 0;
}
