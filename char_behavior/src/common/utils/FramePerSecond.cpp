//
// Created by Bing on 2023/11/23.
//

#include "FramePerSecond.hpp"

#include <utility>

void tmtb::utils::FramePerSecond::setFrames(std::chrono::microseconds fps) {
    if (this->m_mutex){
        std::unique_lock<std::mutex> lock(*this->m_mutex);
        this->m_frames = fps;
    } else this->m_frames = fps;
}

const std::chrono::microseconds &tmtb::utils::FramePerSecond::getFrames() {
    return this->m_frames;
}

tmtb::utils::FramePerSecond::FramePerSecond(FramePerSecond&& framePerSecond) noexcept {
    *this = std::move(framePerSecond);
}

tmtb::utils::FramePerSecond &tmtb::utils::FramePerSecond::operator=(const FramePerSecond& framePerSecond) {
    if (this == &framePerSecond)
        return *this;
    *this = framePerSecond;
    return *this;
}

tmtb::utils::FramePerSecond &tmtb::utils::FramePerSecond::operator=(FramePerSecond&& framePerSecond) noexcept {
    if (this == &framePerSecond)
        return *this;
    *this = std::move(framePerSecond);
    return *this;
}


tmtb::utils::FramePerSecond::FramePerSecond(std::shared_ptr<std::mutex> pmutex) : m_mutex{pmutex} {
}

void tmtb::utils::FramePerSecond::setMutex(std::shared_ptr<std::mutex> pmutex) {
    this->m_mutex = pmutex;
}

tmtb::utils::FramePerSecond::FramePerSecond(const tmtb::utils::FramePerSecond &framePerSecond) {
    *this = framePerSecond;
}

tmtb::utils::FramePerSecond::~FramePerSecond() {
    m_mutex.reset();
}

tmtb::utils::FramePerSecond::FramePerSecond(std::chrono::microseconds&& fps) : m_frames {fps} {}

tmtb::utils::FramePerSecond::FramePerSecond(const std::chrono::microseconds& fps) : m_frames {fps} {}

tmtb::utils::FramePerSecond::FramePerSecond(std::chrono::microseconds fps, std::shared_ptr<std::mutex> pmutex):
FramePerSecond(pmutex){
    this->m_frames = std::forward<std::chrono::microseconds>(fps);
}

tmtb::utils::FramePerSecond::FramePerSecond() = default;
