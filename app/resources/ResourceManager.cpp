#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const string &executablePath) {
    size_t found = executablePath.find_last_of("/\\");
    path = executablePath.substr(0, found);
}

ResourceManager::~ResourceManager() {
    for (auto program: shaderPrograms) {
        delete program.second;
    }

    for (auto texture: textures) {
        delete texture.second;
    }

    for (auto sprite : sprites) {
        delete sprite.second;
    }
}

ShaderProgram *ResourceManager::loadShaders(
    const string &shaderName,
    const string &vertexPath,
    const string &fragmentPath
) {
    const string vertexString = getFileString(vertexPath);
    if (vertexString.empty()) {
        cerr << "No vertex shader" << endl;

        return nullptr;
    }

    const string fragmentString = getFileString(fragmentPath);
    if (fragmentString.empty()) {
        cerr << "No fragment shader" << endl;

        return nullptr;
    }

    auto newShader = shaderPrograms.emplace(shaderName, new ShaderProgram(vertexString, fragmentString)).first->second;
    if (!newShader->isCompiled()) {
        cerr << "cant load shader program" << endl << "Vertex:" << vertexPath << endl << "Fragment:" << fragmentPath <<
                endl;

        return nullptr;
    }

    return newShader;
}

ShaderProgram *ResourceManager::getShaderProgram(const string &shaderName) {
    auto iterator = shaderPrograms.find(shaderName);
    if (iterator == shaderPrograms.end()) {
        cerr << "No shader program " << shaderName << " found" << endl;

        return nullptr;
    }

    return iterator->second;
}

Texture2D *ResourceManager::loadTexture(const string &textureName, const string &texturePath) {
    int channels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(true);

    auto pixels = stbi_load((path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
    if (!pixels) {
        cerr << "Cant't load image " << textureName << endl;
        return nullptr;
    }

    auto newTexture = textures.emplace(textureName,
                                       new Texture2D(width, height, pixels, channels,GL_NEAREST,GL_CLAMP_TO_EDGE)).first
            ->second;

    stbi_image_free(pixels);

    return newTexture;
}

Texture2D *ResourceManager::getTexture(const string &textureName) {
    auto iterator = textures.find(textureName);
    if (iterator == textures.end()) {
        cerr << "No texture " << textureName << " found" << endl;
        return nullptr;
    }

    return iterator->second;
}

Sprite * ResourceManager::loadSprite(
    const string &spriteName,
    const string &textureName,
    const string &shaderName,
    const unsigned int spriteWidth,
    const unsigned int spriteHeight) {
    auto texture = getTexture(textureName);
    if (!texture) {
        cerr << "No texture " << textureName << "for sprite" << endl;
        return nullptr;
    }

    auto shader = getShaderProgram(shaderName);
    if (!shader) {
        cerr << "No shader " << textureName << "for sprite" << endl;
        return nullptr;
    }

    auto newSprite = new Sprite(
        texture,shader,
        glm::vec2(0.f,0.f),
        glm::vec2(spriteWidth,spriteHeight),
        0.f);
    sprites.emplace(spriteName,newSprite);


    return newSprite;
}

Sprite * ResourceManager::getSprite(const string &spriteName) {
    auto iterator = sprites.find(spriteName);
    if (iterator == sprites.end()) {
        cerr << "No Sprite " << spriteName << " found" << endl;
        return nullptr;
    }

    return iterator->second;
}

string ResourceManager::getFileString(const string &filePath) const {
    ifstream f;
    f.open(path + "/" + filePath.c_str(), ios::in | ios::binary);
    if (!f.is_open()) {
        cerr << "Failed to open file " << path + "/" + filePath << endl;

        return "";
    }

    stringstream buffer;

    buffer << f.rdbuf();

    return buffer.str();
}
