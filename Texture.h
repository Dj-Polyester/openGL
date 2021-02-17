#if !defined(TEXTURE_H)
#define TEXTURE_H

#include "Global.h"
#include "Shader.h"

struct Texture
{
    int 
    textures[32] = { 0 }, 
    widths[32], 
    heights[32], 
    nrChannels[32], 
    bound, width, height, nrChannel;

    unsigned texture;

    Texture();
    void gen();
    void param(int wrapOrFilter, int method);
    void load(const char* filePath);
    void set(Shader& shader);
    void bind(unsigned index);
};

Texture::Texture() : bound(0) {
    stbi_set_flip_vertically_on_load(true);
}
void Texture::gen() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}
inline void Texture::param(int wrapOrFilter, int method) {
    glTexParameteri(GL_TEXTURE_2D, wrapOrFilter, method);
}
void Texture::load(const char* filePath) {
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannel, 0);
    if (data)
    {

        PRINT("%d %d\n",bound, nrChannel);
        int format = (nrChannel == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, nrChannel, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        DEBUG("failed to load texture");
    }
    stbi_image_free(data);
    widths[bound] = width;
    heights[bound] = height;
    nrChannels[bound] = nrChannel;
    textures[bound] = texture;
    ++bound;
}
#define SET_TEXTURE_UNIT(unit) shader.setInt("textures["#unit"]",unit);

inline void Texture::set(Shader& shader) {
    std::vector<float> weights(32,1./bound);
    PRINT("%d\n", bound);
    DEBUGARR(weights, 32);
    shader.use();
    GL_DEBUG();
    shader.setInt("bound", bound);
    GL_DEBUG();
    shader.setVectorFloat("weights", 32, weights.data());
    GL_DEBUG();
    // shader.setVectorInt("textures", 32, textures);
    // GL_DEBUG();
    
    SET_TEXTURE_UNIT(31);
    SET_TEXTURE_UNIT(30);
    SET_TEXTURE_UNIT(29);
    SET_TEXTURE_UNIT(28);
    SET_TEXTURE_UNIT(27);
    SET_TEXTURE_UNIT(26);
    SET_TEXTURE_UNIT(25);
    SET_TEXTURE_UNIT(24);
    SET_TEXTURE_UNIT(23);
    SET_TEXTURE_UNIT(22);
    SET_TEXTURE_UNIT(21);
    SET_TEXTURE_UNIT(20);
    SET_TEXTURE_UNIT(19);
    SET_TEXTURE_UNIT(18);
    SET_TEXTURE_UNIT(17);
    SET_TEXTURE_UNIT(16);
    SET_TEXTURE_UNIT(15);
    SET_TEXTURE_UNIT(14);
    SET_TEXTURE_UNIT(13);
    SET_TEXTURE_UNIT(12);
    SET_TEXTURE_UNIT(11);
    SET_TEXTURE_UNIT(10);
    SET_TEXTURE_UNIT(9);
    SET_TEXTURE_UNIT(8);
    SET_TEXTURE_UNIT(7);
    SET_TEXTURE_UNIT(6);
    SET_TEXTURE_UNIT(5);
    SET_TEXTURE_UNIT(4);
    SET_TEXTURE_UNIT(3);
    SET_TEXTURE_UNIT(2);
    SET_TEXTURE_UNIT(1);
    SET_TEXTURE_UNIT(0);
}
inline void Texture::bind(unsigned index) {
    unsigned tmp = index + GL_TEXTURE0;
    glActiveTexture(tmp);
    glBindTexture(GL_TEXTURE_2D, textures[index]);
}
#endif // TEXTURE_H
