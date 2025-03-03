#pragma once

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "SimpleSprite.hpp"

namespace tmtb::other {
    class Background : public SimpleSprite {
        public:
        Background(const std::filesystem::path& img_path) : SimpleSprite(img_path){};
        Background() = default;
        bool BGEnable = false;
    };
}

#endif // BACKGROUND_HPP