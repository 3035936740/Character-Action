/*** 
 * @Author: Bing
 * @Date: 2025-02-27 11:47:16
 * @LastEditors: Bing
 * @LastEditTime: 2025-02-27 18:59:48
 * @FilePath: \tomato_chat\tomato_behavior\src\core\define.hpp
 * @Description: 
 * @
 */
#pragma once

#ifndef DEFINE_HPP
#define DEFINE_HPP
#include <filesystem>
#include <unordered_map>
#include "common/utils/FramePerSecond.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"

namespace tmtb::core::define{
  struct BackgroundMusic {
      std::filesystem::path audioPath;
      sf::Time start_pos;
      sf::Time end_pos;
      bool hidden_console;
  };

  using namespace tmtb::utils::fps_literals;

  struct CharacterMood{
      bool is_animation {false};
      std::uint32_t delay { 0 };
      std::vector<std::filesystem::path> images;
  };

    using moods_type = std::unordered_map<std::string, tmtb::core::define::CharacterMood>;
    struct CharacterAttr{
        std::string default_mood;
        sf::Vector2f scale, position;
        moods_type moods;
    };

    struct ServerConfStruct {
        std::string host;
        std::uint16_t port;
        std::uint32_t server_timeout;
    };

    struct FontStruct{
        std::string font_path, font_color;
        std::uint32_t font_size;
        float line_spacing;
        std::size_t max_lines;
        bool is_bold, is_underlined, is_italic, is_strike_through;
    };

    struct PaddingStruct{
        float top, left, bottom, right;
    };

    struct BubbleEmitStruct {
        float tail_start, tail_end, head_add_pos_x, head_add_pos_y;
    };

    struct BubbleStruct {
        std::uint8_t direction;
        std::string bg_color, border_color, default_text;
        BubbleEmitStruct emit;
        float border_size, max_width, max_height;
        PaddingStruct padding;
        sf::Vector2f position;
        FontStruct font_info;
    };
}

#endif //DEFINE_HPP
