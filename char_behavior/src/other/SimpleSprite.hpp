#pragma once

#ifndef SIMPLE_SPIRITE_HPP
#define SIMPLE_SPIRITE_HPP
#include <utility>
#include <filesystem>
#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace tmtb::other {
    class SimpleSprite {
    public:
            sf::Texture Texture;
            sf::Sprite Sprite;
    private:
            virtual void textureLoadImage(const std::filesystem::path& img_path);
    public:
            explicit SimpleSprite(const std::filesystem::path& img_path);

            SimpleSprite();

            virtual ~SimpleSprite() = default;

            void setPicture(const std::filesystem::path& img_path);
    };
};

#endif // !SIMPLE_SPIRITE_HPP