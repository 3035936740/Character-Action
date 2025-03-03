//
// Created by Bing on 2023/11/22.
//

#include "BackgroundMusic.hpp"
#include <iostream>
tmtb::other::BackgroundMusic::BackgroundMusic() = default;

tmtb::other::BackgroundMusic::~BackgroundMusic() = default;

tmtb::other::BackgroundMusic::BackgroundMusic(const tmtb::other::BackgroundMusic& music){
    *this = music;
}

tmtb::other::BackgroundMusic::BackgroundMusic(tmtb::other::BackgroundMusic&& music) noexcept {
    *this = std::move(music);
}

tmtb::other::BackgroundMusic& tmtb::other::BackgroundMusic::operator=(const tmtb::other::BackgroundMusic& music){
    if (this == &music)
        return *this;
    *this = music;
    return *this;
}

tmtb::other::BackgroundMusic& tmtb::other::BackgroundMusic::operator=(tmtb::other::BackgroundMusic&& music) noexcept {
    if (this == &music)
        return *this;
    *this = std::move(music);
    return *this;
}


void tmtb::other::BackgroundMusic::setMusic(const std::filesystem::path& filename, sf::Time&& start, sf::Time&& end){
    this->m_music_info.audioPath = filename;
    this->m_music_info.start_pos = start;
    this->m_music_info.end_pos = end;
    this->m_is_modify_music = true;

}
bool tmtb::other::BackgroundMusic::checkMusicModify(){
    if (this->m_is_modify_music){
        this->m_is_modify_music = false;
        return true;
    }
    return false;
}

tmtb::core::define::BackgroundMusic& tmtb::other::BackgroundMusic::getMusic() {
    return this->m_music_info;
}

void tmtb::other::BackgroundMusic::loopDetection(){
    if (this->checkMusicModify()){
        this->m_music.stop();

        if (!this->m_music.openFromFile(this->m_music_info.audioPath.string())){
            std::runtime_error("The audio path does not exist");
        }
        this->m_music.play();
    }

    if (this->m_music.getPlayingOffset() > this->m_music_info.end_pos) {
        this->m_music.setPlayingOffset(this->m_music_info.start_pos);
    }
}