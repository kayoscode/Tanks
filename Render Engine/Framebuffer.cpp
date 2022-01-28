#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
	:mWidth(width),
	mHeight(height)
{
	createFbo();
}

Framebuffer::~Framebuffer() 
{
	if (mFbo != -1)
	{
		glDeleteFramebuffers(1, &mFbo);
	}
}

bool Framebuffer::createFbo()
{
	glGenFramebuffers(1, (GLuint*) &mFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, mFbo);  

	return true;
}

void Framebuffer::addColorAttachment()
{
	int texture;
	glGenTextures(1, (GLuint*)&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	mColorTexture = std::make_unique<Texture>();
	mColorTexture->loadFromTextureID(texture);
}

void Framebuffer::addDepthAttachment()
{
	//attach depth buffer
	int renderBuffer;
	glGenRenderbuffers(1, (GLuint*)&renderBuffer);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mWidth, mHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	mDepthTexture = std::make_unique<Texture>();
	mDepthTexture->loadFromTextureID(renderBuffer);
}

void Framebuffer::addDepthTextureAttachment()
{
	int texture = 0;

	glGenTextures(1, (GLuint*)&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT32,
		mWidth,
		mHeight,
		0,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	mDepthTexture = std::make_unique<Texture>();
	mDepthTexture->loadFromTextureID(texture);
}
