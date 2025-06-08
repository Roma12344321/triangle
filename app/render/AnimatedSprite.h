#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include <vector>

#include "Sprite.h"

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite(
        const Texture2D *texture,
        const std::string& initialSubTexture,
        ShaderProgram *shaderProgram,
        const glm::vec2 &position = glm::vec2(0.0f),
        const glm::vec2 &size = glm::vec2(1.0f),
        const float rotation = 0.0f);

    void insertState(std::string state,std::vector<std::pair<std::string, uint64_t> > subTexturesDuration);

    void render() const override;

    void setState(const std::string& newState);

    void update(const uint64_t delta);

    ~AnimatedSprite() override;

private:
    std::map<std::string, std::vector<std::pair<std::string, uint64_t> > > statesMap;
    size_t currentFrame = 0;
    uint64_t currentAnimationTime = 0;
    std::map<std::string, std::vector<std::pair<std::string, uint64_t> > >::const_iterator currentAnimationDurations;
    mutable bool isDirty = false;
};


#endif //ANIMATEDSPRITE_H
