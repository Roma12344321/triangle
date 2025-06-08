#include "AnimatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(
    const Texture2D *texture,
    const std::string &initialSubTexture,
    ShaderProgram *shaderProgram,
    const glm::vec2 &position,
    const glm::vec2 &size,
    const float rotation
) : Sprite(std::move(texture), std::move(initialSubTexture), std::move(shaderProgram), position, size) {
    currentAnimationDurations = statesMap.end();
}

void AnimatedSprite::insertState(std::string state,
                                 std::vector<std::pair<std::string, uint64_t> > subTexturesDuration) {
    statesMap.emplace(std::move(state), std::move(subTexturesDuration));
}

void AnimatedSprite::setState(const std::string &newState) {
    auto it = statesMap.find(newState);
    if (it == statesMap.end()) {
        std::cout << "Cant find animation state: " << newState << std::endl;

        return;
    }

    if (it != currentAnimationDurations) {
        currentAnimationTime = 0;
        currentFrame = 0;
        currentAnimationDurations = it;
        isDirty = true;
    }
}

AnimatedSprite::~AnimatedSprite() {
    Sprite::~Sprite();
}

void AnimatedSprite::update(const uint64_t delta) {
    if (currentAnimationDurations != statesMap.end()) {
        currentAnimationTime += delta;

        while (currentAnimationTime >= currentAnimationDurations->second[currentFrame].second) {
            currentAnimationTime -= currentAnimationDurations->second[currentFrame].second;
            currentFrame++;
            isDirty = true;

            if (currentFrame == currentAnimationDurations->second.size()) {
                currentFrame = 0;
            }
        }
    }
}


void AnimatedSprite::render() const {
    if (isDirty) {
        auto subTexture = texture->getSubTexture(currentAnimationDurations->second[currentFrame].first);

        const GLfloat textCoords[] = {
            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.rightTopUV.y,

            subTexture.rightTopUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
        };

        glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textCoords), &textCoords);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        isDirty=false;
    }

    Sprite::render();
}
