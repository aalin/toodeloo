#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image
{
	public:
		Image(std::string);
		~Image();
		int getBpp() const;
		int getPitch() const;
		int getWidth() const;
		int getHeight() const;
		void setTexture() const;
		uint32_t at(int, int) const;

	private:
		SDL_Surface *_image;
		const uint8_t* getPixelData() const;
};

#endif

