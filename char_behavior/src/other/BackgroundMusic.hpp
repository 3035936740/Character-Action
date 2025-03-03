#pragma once

#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <utility>
#include <array>
#include <filesystem>
#include <stdexcept>
#include <SFML/Audio/Music.hpp>
#include "core/define.hpp"

namespace tmtb::other {
    class BackgroundMusic {
    private:
        sf::Music m_music;
        bool m_is_modify_music{false};
        tmtb::core::define::BackgroundMusic m_music_info{};
    public:
        BackgroundMusic();

        virtual ~BackgroundMusic();

        BackgroundMusic(const BackgroundMusic &);

        BackgroundMusic(BackgroundMusic &&) noexcept;

        virtual BackgroundMusic &operator=(const BackgroundMusic &);

        virtual BackgroundMusic &operator=(BackgroundMusic &&) noexcept;

        void setMusic(const std::filesystem::path &filename, sf::Time &&start, sf::Time &&end);

        bool checkMusicModify();

        tmtb::core::define::BackgroundMusic& getMusic();

        void loopDetection();
    };
}

#endif // MUSIC_HPP
