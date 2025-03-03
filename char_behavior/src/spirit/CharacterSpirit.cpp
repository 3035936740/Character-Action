//
// Created by Bing on 2025/2/28.
//

#include <iostream>
#include "CharacterSpirit.hpp"

tmtb::spirit::CharacterSpirit::CharacterSpirit(CharacterAttr&& character_attr) :
    tmtb::other::SimpleSprite(),
    m_character_attr { std::move(character_attr) },
    m_current_mood{m_character_attr.moods.at(m_character_attr.default_mood)},
    m_clock(){
    last_time_mood = m_character_attr.default_mood;
    m_clock.start();
    this->setPicture(m_current_mood.images.at(0));
    Sprite.setScale(m_character_attr.scale);
    Sprite.setPosition(m_character_attr.position);
}

void tmtb::spirit::CharacterSpirit::ToggleMood(const moods_type::key_type& mood_key) {
    const moods_type::key_type& default_mood {m_character_attr.default_mood};

    const auto& moods{m_character_attr.moods};

    if (moods.count(mood_key) == 0){
        m_current_mood = moods.at(last_time_mood);
    } else {
        m_current_mood = moods.at(mood_key);
        last_time_mood = mood_key;
    }
    is_toggle_mood = true;
}

void tmtb::spirit::CharacterSpirit::LoopCheck() {
    static std::size_t LoopImgIndex {0}, LoopImgSize {0};
    // 执行代码
    if (is_toggle_mood){
        LoopImgIndex = 0;
        LoopImgSize = 0;
        is_toggle_mood = false;
        m_clock.restart();
        const auto& images{m_current_mood.images};
        LoopImgSize = images.size();
        this->setPicture(images.at(0));
    }

    // 如果是逐帧动画
    if (m_current_mood.is_animation){
        auto ms{ m_clock.getElapsedTime().asMilliseconds() };
        // std::cout << ms;
        if (ms > m_current_mood.delay){
            ++LoopImgIndex;
            if (LoopImgIndex >= LoopImgSize) LoopImgIndex = 0;

            const auto& image{m_current_mood.images[LoopImgIndex]};
            this->setPicture(image);
            m_clock.restart();
        }
    }
}