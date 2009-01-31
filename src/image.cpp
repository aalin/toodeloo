#include "common.hpp"
#ifdef __APPLE__
#include <SDL_Image/SDL_image.h>
#else
#include <SDL/SDL_image.h>
#endif

Image::Image(std::string filename)
{
	_image = IMG_Load(filename.c_str());

	if(!_image)
	{
		std::string msg = "IMG_Load: " + std::string(IMG_GetError());
		throw std::runtime_error(msg.c_str());
	}

	std::cout << "Image loaded: " << filename << std::endl;
	std::cout << "\tSize: " << getHeight() << "x" << getWidth() << std::endl;
	std::cout << "\tBPP: " << getBpp() << std::endl;
	std::cout << "\tPitch: " << getPitch() << std::endl;
}

Image::~Image()
{
	if(_image)
		SDL_FreeSurface(_image);
}

int
Image::getBpp() const
{
	return _image->format->BytesPerPixel;
}

int
Image::getWidth() const
{
	return _image->w;
}

int
Image::getHeight() const
{
	return _image->h;
}

int
Image::getPitch() const
{
	return _image->pitch;
}

void
Image::setTexture() const
{
	std::cout << "setTexture, in " << getBpp() << std::endl;

	if(getBpp() == 4)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, _image->pixels);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, getWidth(), getHeight(), GL_RGB, GL_UNSIGNED_BYTE, _image->pixels);

	std::cout << "setTexture, out" << std::endl;
}

const uint8_t*
Image::getPixelData() const
{
	return reinterpret_cast<uint8_t*>(_image->pixels);
}

uint32_t
Image::at(int x, int y) const
{
	const uint8_t *p = getPixelData() + y * getPitch() + x * getBpp();
	*reinterpret_cast<const uint32_t*>(p);
}

