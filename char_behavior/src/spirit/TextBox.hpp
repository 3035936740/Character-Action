//
// Created by Bing on 2025/3/1.
//
#pragma once

#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <string>
#include <vector>
#include "core/define.hpp"
#include <SFML/Graphics.hpp>

namespace tmtb::spirit {
    class TextBox {
    private:
        tmtb::core::define::BubbleStruct m_bubble_struct;
        sf::Font m_font;
        sf::Text m_text;
        float font_max_width{0.0f}, font_max_height{0.0f};
        std::size_t lines_size {0};
        sf::Color bg_color, border_color;
        std::vector<sf::String> m_lines;
    public:
        TextBox(tmtb::core::define::BubbleStruct&& bubble_struct);
        void setText(const sf::String& text);
        void draw(sf::RenderWindow& window);
    };
}

#endif //TEXTBOX_HPP
