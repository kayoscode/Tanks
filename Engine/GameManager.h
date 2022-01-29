#pragma once
#include <string>
#include <thread>
#include <map>

#include "lib/glew/include/GL/glew.h"
#include "GLFW/glfw3.h"
#include "Utils/Timer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameWindow.h"

#include "Render Engine/Mesh.h"
#include "Render Engine/Texture.h"
#include "Render Engine/Shader.h"
#include "Render Engine/Framebuffer.h"

/// <summary>
/// Class responsible for handling all game resources.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class GameResources
{
public:
	/// <summary>
	/// Standard constructor.
	/// </summary>
	GameResources()
		:TextureResources("Textures"),
		ShaderResources("Shaders"),
		MeshResources("Meshes"),
		FramebufferResources("Framebuffers")
	{}

	virtual ~GameResources() {}

	ResourceManager<Texture> TextureResources;
	ResourceManager<ShaderProgram> ShaderResources;
	ResourceManager<Mesh> MeshResources;
	ResourceManager<Framebuffer> FramebufferResources;
};

/// <summary>
/// Interface for loading all game resources. Implement at the application level.
/// Given a render context so textures may be loaded.
/// </summary>
class IGlobalResourceLoader
{
public:
	IGlobalResourceLoader()
	{}

	~IGlobalResourceLoader() {}

	virtual void loadTextures(ResourceManager<Texture>& textureResources) = 0;
	virtual void loadShaders(ResourceManager<ShaderProgram>& shaderResources) = 0;
	virtual void loadMeshes(ResourceManager<Mesh>& meshResources) = 0;
	virtual void loadFramebuffers(ResourceManager<Framebuffer>& framebufferResources) = 0;

protected:

};


/**
 * All units of time.
 * */
enum class TimeUnit 
{
    HOURS,
    MINUTES,
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};

/**
 * Supported operating systems.
 * */
enum class OperatingSystem 
{
    WINDOWS,
    MACOS_DARWIN,
    LINUX
};

/**
 * Holds information about the operating system.
 * */
struct Platform 
{
public:
	OperatingSystem os;
};

/**
 * A class that handles all entities, updates, windows, rendering, time, etc.
 * @author Bryce Young 5/27/2021
 * */
class GameManager 
{
public:
	/**
	 * sets the state of the window on startup
	 * @param width window width
	 * @param height window height
	 * @param gameName the name of the window
	 * @param fullscreen whether the game is in fullscreen or not
	 * */
	struct WindowConfig 
	{
		WindowConfig(int width, int height, int posx = 0, int posy = 0, bool centered = true, const std::string& gameName = "Untitled", bool fullscreen = false, bool vSync = true)
			:width(width),
			height(height),
			xPos(posx),
			yPos(posy),
			centered(centered),
			gameName(gameName),
			fullscreen(fullscreen),
			vSync(vSync)
		{
		}

		int width, height;
		int xPos, yPos;
		bool centered;
		std::string gameName;
		bool fullscreen;
		bool vSync;
	};

	/**
	 * Creates a window and initializes graphics
	 * @param settingsPath path to settings JSON
	 * */
	static void createWindow(const std::string& settingsPath);

	/**
	 * Creates a window based on a window config
	 * */
	static void createWindow(const WindowConfig& windowConfig);

	/// <summary>
	/// Returns the window in which the game is being rendered.
	/// </summary>
	/// <returns></returns>
	static GameWindow* getGameWindow()
	{
		return mMainWindow;
	}

	/**
	 * Closes the main window and terminates the program
	 * */
	void closeProgram();

	/**
	 * A constant for the location of the res folder
	 * */
	static const std::string& resPath() 
	{
		return resFolder;
	}

	/**
	 * Sets the resFolder to @param resPath
	 * */
	static void setResPath(const std::string& resPath) 
	{
		resFolder = resPath;
	}

	/**
	 * Returns info about the platform
	 * */
	const static Platform& getPlatform() 
	{
		return platform;
	}

	/// <summary>
	/// Returns the elapsed time since last frame.
	/// </summary>
	/// <returns></returns>
	static float getRenderDeltaTime() 
	{
		return mRenderTime.getDelta();
	}

	/// <summary>
	/// Returns the elapsed time since last update.
	/// </summary>
	/// <returns></returns>
	static float getUpdateDeltaTime()
	{
		return mUpdateTime.getDelta();
	}

	/// <summary>
	/// Sets the current scene.
	/// </summary>
	/// <param name="scene"></param>
	static void setScene(std::unique_ptr<Scene> scene)
	{
		mScene = std::move(scene);
	}

	/// <summary>
	/// Returns the active scene.
	/// </summary>
	/// <returns></returns>
	static Scene* getScene()
	{
		return mScene.get();
	}

	/// <summary>
	/// Loads all global resources.
	/// </summary>
	/// <param name="loader"></param>
	static void loadResources(IGlobalResourceLoader& loader)
	{
		loader.loadFramebuffers(Resources.FramebufferResources);
		loader.loadShaders(Resources.ShaderResources);
		loader.loadTextures(Resources.TextureResources);
		loader.loadMeshes(Resources.MeshResources);
	}

	/// <summary>
	/// Starts the engine run process.
	/// </summary>
		/// <summary>
	/// Starts the engine run process.
	/// </summary>
	static void start();

	/// <summary>
	/// Returns the program runtime.
	/// </summary>
	/// <param name="timeUnit"></param>
	/// <returns></returns>
	static float getProgramRuntime(TimeUnit timeUnit);
	static GameResources Resources;

private:
	/// <summary>
	/// Performs render on thread.
	/// </summary>
	static void executeRenderLoop();

	/// <summary>
	/// Performs update on thread.
	/// </summary>
	static void executeUpdateLoop();

	/// <summary>
	/// Initializes the engine with platform information and other init necessities.
	/// </summary>
	static void initializePlatform();

	static void init();
	static void update();
	static void render();

	/// <summary>
	/// Every window is registered with a thread for rendering.
	/// </summary>
	static GameWindow* mMainWindow;
	static std::thread mMainWindowRenderThread;

	static std::string resFolder;
	static Platform platform;

	// Static constructor.
	friend class constructor;

	class constructor {
	public:
		constructor();
		~constructor();
	};

	static GameManager::constructor cons;

	/**
	 * Class to handle time within the engine
	 * @author Bryce Young 5/31/2021
	 * */
	class GameTime 
	{
	public:
		GameTime() : totalNanos(0), elapsedNanosThisSecond(0), delta(0) 
		{
		}

		/**
		 * Called after the user starts the gameloop
		 * resets all timers
		 * */
		void start();

		/**
		 * Adds a frame. If there is a rollover in the FPS, the function returns true
		 * */
		inline bool addFrame(uint64_t rollOverRateNanos)
		{

			bool ret = false;
			uint64_t elapsed = deltaTime.nanoseconds();
			this->totalNanos += elapsed;
			this->elapsedNanosThisSecond += elapsed;
			this->frameCount++;

			//check for elapsed time overflow
			if (this->elapsedNanosThisSecond >= rollOverRateNanos) {
				this->previousFPS = frameCount;
				this->frameCount = 0;
				this->elapsedNanosThisSecond = 0;
				ret = true;
			}

			this->delta = elapsed / 1e9f;

			deltaTime.reset();
			return ret;
		}

		inline float getRuntimeHours() 
		{
			return totalNanos / 3.6e12f;
		}

		inline float getRuntimeMinutes() 
		{
			return totalNanos / 6e10f;
		}

		inline float getRuntimeSeconds() 
		{
			return totalNanos / 1e9f;
		}

		inline float getRuntimeMillis() 
		{
			return totalNanos / 1e6f;
		}

		inline float getRuntimeMicros() 
		{
			return totalNanos / 1000.0f;
		}

		inline uint64_t getRuntimeNanoseconds() 
		{
			return totalNanos;
		}

		inline uint32_t getFPS() 
		{
			return previousFPS;
		}

		inline float getDelta() 
		{
			return delta;
		}

	private:
		Timer deltaTime;

		uint64_t totalNanos;
		uint64_t elapsedNanosThisSecond;
		int frameCount = 0;
		int previousFPS = 0;
		float delta;
	};

	static GameTime mRenderTime;
	static GameTime mUpdateTime;
	static std::unique_ptr<Scene> mScene;
};
