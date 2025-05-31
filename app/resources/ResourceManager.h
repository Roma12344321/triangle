#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "../render/ShaderProgram.h"

using namespace std;

class ResourceManager {
public:
    ResourceManager(const string &executablePath);

    ~ResourceManager();

    ResourceManager(const ResourceManager &) = delete;

    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager &operator=(ResourceManager &&) = delete;

    ResourceManager(ResourceManager &&) = delete;

    ShaderProgram *loadShaders(const string &shaderName, const string &vertexPath, const string &fragmentPath);

    ShaderProgram *getShaderProgram(const string &shaderName);

private:
    string getFileString(const string &filePath) const;
    typedef map<const string,ShaderProgram*> ShaderProgramMap;
    ShaderProgramMap shaderPrograms;

    string path;
};


#endif
