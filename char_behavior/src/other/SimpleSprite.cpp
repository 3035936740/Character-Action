/*** 
 * @Author: Bing
 * @Date: 2025-02-27 18:28:22
 * @LastEditors: Bing
 * @LastEditTime: 2025-02-27 18:55:15
 * @FilePath: \tomato_chat\tomato_behavior\src\other\SimpleSprite.cpp
 * @Description: 
 * @
 */

#include "SimpleSprite.hpp"

void tmtb::other::SimpleSprite::textureLoadImage(const std::filesystem::path& img_path){
    auto _ = Texture.loadFromFile(img_path);
    Sprite.setTexture(Texture, true);
};

tmtb::other::SimpleSprite::SimpleSprite(const std::filesystem::path& img_path) : Texture { sf::Texture(img_path) }, Sprite(Texture){

};

tmtb::other::SimpleSprite::SimpleSprite() : Sprite(Texture){

};

void tmtb::other::SimpleSprite::setPicture(const std::filesystem::path& img_path){
    textureLoadImage(img_path);
};