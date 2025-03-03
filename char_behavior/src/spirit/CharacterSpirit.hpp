//
// Created by Bing on 2025/2/28.
//
#pragma once

#ifndef CHARACTION_CHARACTERSPIRIT_HPP
#define CHARACTION_CHARACTERSPIRIT_HPP

#include "other/SimpleSprite.hpp"
#include "core/define.hpp"

namespace tmtb::spirit {
    using namespace tmtb::core::define;
    class CharacterSpirit : public tmtb::other::SimpleSprite {
    private:
        CharacterAttr m_character_attr;
        CharacterMood m_current_mood;
        moods_type::key_type last_time_mood;
        sf::Clock m_clock;
        bool is_toggle_mood { true };
    public:
        explicit CharacterSpirit(CharacterAttr&&);

        void ToggleMood(const moods_type::key_type &);

        void LoopCheck();
    };
};


#endif //CHARACTION_CHARACTERSPIRIT_HPP
