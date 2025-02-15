#include "texture.h"

Texture::Texture(std::string image, bool flip) {

	int texture_width;
	int texture_height;
	int channels;

	if (flip) {
		stbi_set_flip_vertically_on_load(1);
	}

	unsigned char* texture_data = stbi_load(image.c_str(), &texture_width, &texture_height, &channels, 4);
	if (texture_data == NULL) {
		std::cout << "ERROR: Cannot find texture " << image << std::endl;
	}
	unsigned int texture_buffer;
	glc(glGenTextures(1, &texture_buffer));

	glc(glBindTexture(GL_TEXTURE_2D, texture_buffer));

	// Setting parameters
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
	glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data));

	if (texture_buffer) {
		stbi_image_free(texture_data);
	}
	else {
		std::cout << "ERROR: Unable to create texture " << image << std::endl;
	}

	this->id = texture_buffer;
	this->width = texture_width;
	this->height = texture_height;
	this->channels = channels;
}

void Texture::bind(int texture_unit_id) {
	// Binding Texture unit
	glc(glBindTextureUnit(texture_unit_id, this->id));
}

Texture::~Texture() {
	glc(glDeleteTextures(1, &this->id));
}
