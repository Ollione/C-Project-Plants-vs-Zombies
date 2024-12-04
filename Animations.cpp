
#include "../Headers/Animations.h"

Animation::Animation(TextureManager* textureManager, const std::string& filename, int frameCount, sf::Time frameDuration)
: textureManager(textureManager), frameCount(frameCount), frameDuration(frameDuration), currentFrame(0), elapsedTime(sf::Time::Zero) {
    texture = textureManager->getTexture(filename);
    int textureWidth = texture->getSize().x / frameCount;   //calculate the width of the frame by taking the width of the texture and dividing it by the frame count
    int textureHeight = texture->getSize().y;   //get the height of the texture OBS used single line png. in theory u can use multiple rows of frames which is more common when using spritesheets and doing larger games.
    frames = std::make_unique<sf::IntRect[]>(frameCount);   //create a unique pointer array of sf::IntRects with the size of the frame count
    for (int i = 0; i < frameCount; ++i) {
        frames[i] = sf::IntRect(i * textureWidth, 0, textureWidth, textureHeight);  //fill the array with the frames by taking the width of the frame and the height of the texture
    }
}
Animation::~Animation() {
    textureManager = nullptr;
}

int Animation::getCurrentFrameIndex() const{
    return currentFrame;
}

void Animation::update(sf::Time deltaTime) {
    elapsedTime += deltaTime;   //add the delta time to the elapsed time
    if (elapsedTime >= frameDuration) { //if the elapsed time is greater than the frame duration
        currentFrame = (currentFrame + 1) % frameCount; //increment the current frame by 1 and take the modulo of the frame count to loop the animation
        elapsedTime -= frameDuration;   //subtract the frame duration from the elapsed time
    }
}

sf::Texture* Animation::getTexture() const {
    return texture;
}

sf::IntRect Animation::getCurrentFrame() const {
    return frames[currentFrame];
}