#include "load_texture.h"

#include "pch.h"

GLuint load_texture(const char* path)
{
    int            width, height, channels;
    unsigned char* img = stbi_load(path, &width, &height, &channels, 0);
    if(img == nullptr) {
        std::cout << "Error in loading image '" << path << "'" << std::endl;
        return 0;
    }
    std::cout << "Loaded image '" << path << "' of width " << width << ", height " << height << " and " << channels << " channels." << std::endl;

    GLuint texture_id;
    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    stbi_image_free(img);

    // trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // when minifying, use linear blend of two mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture_id;
}
