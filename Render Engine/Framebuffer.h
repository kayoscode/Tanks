#pragma once

#include <memory>
#include "Texture.h"

/// <summary>
/// Class responsible for setting up a framebuffer object.
/// <author>Bryce Young 1/26/2022</author>
/// </summary>
class Framebuffer
{
public:
	/// <summary>
	/// Standard constructor.
	/// </summary>
	Framebuffer(int width, int height);

	~Framebuffer();

	/// <summary>
	/// Get the textures.
	/// </summary>
	/// <returns></returns>
	Texture* getColorTexture() { return mColorTexture.get(); }
	Texture* getDepthTexture() { return mDepthTexture.get(); }

	/// <summary>
	/// Adds a color texture
	/// </summary>
	/// <returns>
	/// Returns the texture index created
	/// </returns>
	void addColorAttachment();

	/// <summary>
	/// Adds a depth buffer attachment
	/// </summary>
	/// <returns>
	/// The index of the returned texturej
	/// </returns>
	void addDepthAttachment();
	
	/// <summary>
	/// Adds the depth texture
	/// </summary>
	/// <returns>
	/// Returns the depth texture
	/// </returns>
	void addDepthTextureAttachment();

	/// <summary>
	/// Clears the currently bound framebuffer
	/// </summary>
	static void clearDepthAndColor()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/// <summary>
	/// Sets the clear color.
	/// </summary>
	static void clearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	/// <summary>
	/// Clears the depth only.
	/// </summary>
	static void clearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	/// <summary>
	/// Binds the frame buffer for render
	/// </summary>
	void bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
		glViewport(0, 0, mWidth, mHeight);
	}

	/// <summary>
	/// Unbinds the current frame buffer
	/// Binding the default texture
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	static void unBind(int width, int height)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}

protected:
private:
	/// <summary>
	/// Creates a framebuffer at the specified width and height.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	bool createFbo();

	int mWidth, mHeight;

	unsigned int mFbo = -1;

	std::unique_ptr<Texture> mColorTexture;
	std::unique_ptr<Texture> mDepthTexture;
};

