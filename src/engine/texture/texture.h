#pragma once
#include "../includes.h"
#include <stbi_image/stbi_image.h>
class Texture {
public:
	unsigned int id;
	int width;
	int height;
	int channels;

	Texture(std::string image, bool flip = true);
	void bind(int texture_unit_id);
	~Texture();
};
