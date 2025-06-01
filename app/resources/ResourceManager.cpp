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

    auto newShader =  shaderPrograms.emplace(shaderName, new ShaderProgram(vertexString, fragmentString)).first->second;
    if (!newShader->isCompiled()) {
        cerr << "cant load shader program" << endl << "Vertex:" << vertexPath << endl << "Fragment:" << fragmentPath << endl;

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

void ResourceManager::loadTexture(const string &textureName, const string &texturePath) const {
    int channels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(true);

    auto pixels = stbi_load((path+"/"+texturePath).c_str(), &width, &height, &channels, 0);
    if (!pixels) {
        cerr << "Cant't load image " << textureName << endl;
        return;
    }

    stbi_image_free(pixels);
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
