#include "Texture.h"

Texture::Texture(const char* filename, GLenum type)
{
    this->type = type;

    unsigned char* image = SOIL_load_image(filename, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(type);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: "<<filename << "\n";
    }

    glActiveTexture(0);
    glBindTexture(type, 0);
    SOIL_free_image_data(image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}

void Texture::bind(const GLint texture_unit)
{
    glActiveTexture(GL_TEXTURE0 +texture_unit);
    glBindTexture(this->type, this->id);
}

void Texture::unbind()
{
    glActiveTexture(0);
    glBindTexture(this->type, 0);
}
