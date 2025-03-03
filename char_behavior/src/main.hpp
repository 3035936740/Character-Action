/*** 
 * @Author: Bing
 * @Date: 2025-02-27 11:47:16
 * @LastEditors: Bing
 * @LastEditTime: 2025-02-27 18:39:08
 * @FilePath: \tomato_chat\tomato_behavior\src\main.hpp
 * @Description: 
 * @
 */
#pragma once

#ifndef MAIN_HPP
#define MAIN_HPP

#include <core_game>
#include <chrono>
#include "nlohmann/json.hpp"
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <mswsock.h>
#include <Windows.h>
#endif
#include "httplib.h"

[[maybe_unused]] inline const int init { []()->int {
    using namespace tmtb::core::global;
    core::hidden_console(config::window::hidden_console);
    auto rtime {tmtb::core::global::framePerSecond.getFrames()};

    auto bgm_enable {config::window::bgm::enable};
    auto loop_begin {config::window::bgm::loop_begin}, loop_end {config::window::bgm::loop_end};
    auto bgm_path {config::window::bgm::audio_path};

    std::jthread([=]()  {
            if(bgm_enable) {
                tmtb::core::global::bgMusic.setMusic(bgm_path,
                        sf::milliseconds(loop_begin),
                        sf::milliseconds(loop_end));
            }
            while (true) {
                if(bgm_enable) {
                    tmtb::core::global::bgMusic.loopDetection();
                }
                tmtb::core::global::sprite::character->LoopCheck();
                std::this_thread::sleep_for(rtime);
            }
    }).detach();

    auto server_conf_struct{tmtb::core::global::server_conf};

    std::jthread([=]  {
        auto textbox {tmtb::core::global::sprite::textbox};
        auto character {tmtb::core::global::sprite::character};

        httplib::Server server;

        server.Get("/", [](const httplib::Request &, httplib::Response &response) {
            response.set_header("Content-Type", "text/plain; charset=utf-8");
            response.set_content("Character☆Action", "text/plain; charset=utf-8");
        });

        /*
         * request:
         * {
         *  message: "内容"
         *  mood: "情绪"
         * }
         * response:
         * ok
         * */
        server.Post("/send", [=](const httplib::Request& request, httplib::Response& response) {
            // 解析 JSON 请求体
            auto body = nlohmann::json::parse(request.body);

            // 访问 JSON 数据
            std::string message = body["message"];
            std::string mood = body["mood"];

            textbox->setText(std::filesystem::path(message).wstring());
            character->ToggleMood(mood);
            // 返回响应
            response.set_content("ok", "text/plain; charset=utf-8");
        });

        server.listen(server_conf_struct.host, server_conf_struct.port);
    }).detach();

    std::this_thread::sleep_for(50ms);
    return 0;
    }()
};

#endif // !MAIN_HPP