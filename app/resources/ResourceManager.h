#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <vector>

#include "../render/AnimatedSprite.h"
#include "../render/ShaderProgram.h"
#include "../render/Sprite.h"
#include "../render/Texture2D.h"


class ResourceManager {
public:
    ResourceManager(const std::string &executablePath);

    ~ResourceManager();

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&) = delete;

    ResourceManager(ResourceManager &&) = delete;

    ShaderProgram *loadShaders(const std::string &shaderName, const std::string &vertexPath,
                               const std::string &fragmentPath);

    ShaderProgram *getShaderProgram(const std::string &shaderName);

    Texture2D *loadTexture(const std::string &textureName, const std::string &texturePath);

    Texture2D *getTexture(const std::string &textureName);


    Sprite *loadSprite(const std::string &spriteName,
                       const std::string &textureName,
                       const std::string &shaderName,
                       const unsigned int spriteWidth,
                       const unsigned int spriteHeight,
                       const std::string &subTextureName);

    Sprite *getSprite(const std::string &spriteName);

    AnimatedSprite *loadAnimatedSprite(
        const std::string &spriteName,
        const std::string &textureName,
        const std::string &shaderName,
        const unsigned int spriteWidth,
        const unsigned int spriteHeight,
        const std::string &subTextureName);

    AnimatedSprite *getAnimatedSprite(const std::string &spriteName);

    Texture2D *loadTextureAtlas(
        const std::string &textureName,
        const std::string &texturePath,
        std::vector<std::string> subTextures,
        const unsigned int subTextureWidth,
        const unsigned int subTextureHeight);

private:
    std::string getFileString(const std::string &filePath) const;

    typedef std::map<const std::string, ShaderProgram *> ShaderProgramMap;
    ShaderProgramMap shaderPrograms;

    typedef std::map<const std::string, Texture2D *> TexturesMap;
    TexturesMap textures;

    typedef std::map<const std::string, Sprite *> SpritesMap;
    SpritesMap sprites;

    typedef std::map<const std::string, AnimatedSprite *> AnimatedSpritesMap;
    AnimatedSpritesMap animatedSprites;

    std::string path;
};


#endif
