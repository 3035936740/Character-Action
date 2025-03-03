#pragma once

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <unordered_map>
#include <filesystem>
#include "other/BackgroundMusic.hpp"
#include "common/utils/FramePerSecond.hpp"
#include "other/Background.hpp"
#include "spirit/CharacterSpirit.hpp"
#include "spirit/TextBox.hpp"

using namespace std::chrono_literals;
using namespace tmtb::utils;
using namespace tmtb::utils::fps_literals;

namespace tmtb::core::global {
    const inline std::shared_ptr<std::mutex> mutex;

    inline tmtb::other::BackgroundMusic bgMusic;
    inline tmtb::utils::FramePerSecond framePerSecond(30_fps, mutex);

    inline core::define::ServerConfStruct server_conf;

    namespace sprite {
        inline other::Background bg;
        inline std::shared_ptr<tmtb::spirit::CharacterSpirit> character;
        inline std::shared_ptr<tmtb::spirit::TextBox> textbox;
    };

    namespace config {
        namespace window{
            std::string title{"Untitle"}, background;
            bool hidden_console {false};
            std::uint64_t fps {0}, width {640}, height {480};
            namespace bgm {
                bool enable {false};
                std::uint32_t loop_begin, loop_end;
                std::filesystem::path audio_path;
            }
        }
    }
}
#endif // !GLOBAL_HPP
