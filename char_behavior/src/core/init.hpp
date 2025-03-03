#pragma once

#include <memory>
#include "yaml-cpp/yaml.h"

#ifndef INIT_HPP
#define INIT_HPP

namespace tmtb::core::init{
    // 加载配置
    [[maybe_unused]] const bool LoadYamlConfig { [](){
        using namespace tmtb::core::global;
        const YAML::Node config_yaml{ YAML::LoadFile("config.yaml") };

        // 服务器配置相关
        {
            const auto& server_conf{ config_yaml["server"] };
            core::global::server_conf.host = server_conf["host"].as<std::string>();
            core::global::server_conf.port = server_conf["port"].as<std::uint16_t>();
            core::global::server_conf.server_timeout = server_conf["timeout"].as<std::uint32_t>();
        }

        // 窗口内容相关
        {
            const auto& window_conf{ config_yaml["window"] };
            config::window::hidden_console = window_conf["hidden-console"].as<std::uint8_t >();
            config::window::title = window_conf["title"].as<std::string>();
            config::window::background = window_conf["background"].as<std::string>();
            config::window::fps = window_conf["fps"].as<std::uint64_t>();
            if (config::window::fps == 0) config::window::fps = std::numeric_limits<decltype(config::window::fps)>::max();
            framePerSecond.setFrames(tmtb::utils::FPS(config::window::fps));

            config::window::width = window_conf["width"].as<std::uint32_t>();
            config::window::height = window_conf["height"].as<std::uint32_t>();

            const auto& bgm_conf {window_conf["bgm"]};
            config::window::bgm::enable = bgm_conf["enable"].as<std::uint8_t>();
            config::window::bgm::loop_begin = bgm_conf["loop-begin"].as<std::uint32_t>();
            config::window::bgm::loop_end = bgm_conf["loop-end"].as<std::uint32_t>();
            config::window::bgm::audio_path = bgm_conf["audio"].as<std::string >();
        }


        {
            tmtb::core::define::BubbleStruct bubble_struct;
            const auto& bubble_conf { config_yaml["bubble"] };

            // 气泡框
            {
                bubble_struct.max_width = bubble_conf["max-width"].as<float>();
                bubble_struct.bg_color = bubble_conf["bg-color"].as<std::string>();
                bubble_struct.border_color = bubble_conf["border-color"].as<std::string>();
                bubble_struct.default_text = bubble_conf["default-text"].as<std::string>();
                bubble_struct.border_size = bubble_conf["border-size"].as<float>();
                bubble_struct.border_size = bubble_conf["border-size"].as<float>();
                bubble_struct.direction = bubble_conf["direction"].as<std::uint8_t>();

                // 气泡发出选项设置
                {
                    const auto &emit_conf{bubble_conf["emit"]};
                    tmtb::core::define::BubbleEmitStruct emit_struct
                    {
                        .tail_start = emit_conf["tail-start"].as<float>(),
                        .tail_end = emit_conf["tail-end"].as<float>(),
                        .head_add_pos_x = emit_conf["head-add-pos"]["x"].as<float>(),
                        .head_add_pos_y = emit_conf["head-add-pos"]["y"].as<float>()
                    };
                    bubble_struct.emit = emit_struct;
                }

                // 气泡框位置
                {
                    const auto &position_conf{bubble_conf["position"]};
                    bubble_struct.position.x = position_conf["x"].as<float>();
                    bubble_struct.position.y = position_conf["y"].as<float>();
                }

                // 间距
                {
                    const auto& padding_conf {bubble_conf["padding"]};
                    bubble_struct.padding.top = padding_conf["top"].as<float>();
                    bubble_struct.padding.bottom = padding_conf["bottom"].as<float>();
                    bubble_struct.padding.left = padding_conf["left"].as<float>();
                    bubble_struct.padding.right = padding_conf["right"].as<float>();
                }

                // 文本框输出内容
                {
                    tmtb::core::define::FontStruct font_struct;
                    const auto& font_conf { bubble_conf["font"] };
                    font_struct.font_path = font_conf["path"].as<std::string>();
                    font_struct.font_color = font_conf["color"].as<std::string>();
                    font_struct.font_size = font_conf["size"].as<std::uint32_t>();
                    // font_struct.await_message = font_conf["await-message"].as<std::uint32_t>();
                    font_struct.max_lines = font_conf["max-line"].as<std::size_t>();
                    font_struct.line_spacing = font_conf["line-spacing"].as<float>();

                    const auto& style_conf {font_conf["style"]};
                    font_struct.is_bold = style_conf["bold"].as<std::uint8_t>();
                    font_struct.is_underlined = style_conf["underlined"].as<std::uint8_t>();
                    font_struct.is_italic = style_conf["italic"].as<std::uint8_t>();
                    font_struct.is_strike_through = style_conf["strike-through"].as<std::uint8_t>();
                    bubble_struct.font_info = font_struct;
                }
            }


            tmtb::core::global::sprite::textbox = std::make_unique<tmtb::spirit::TextBox>(std::move(bubble_struct));
        }

        // 角色塑造
        {
            tmtb::core::define::CharacterAttr character_attr;

            const auto& char_conf { config_yaml["character"] };

            {
                const auto& position_conf {char_conf["position"]};
                character_attr.position.x = position_conf["x"].as<float>();
                character_attr.position.y = position_conf["y"].as<float>();
            }

            {
                const auto& scale_conf {char_conf["scale"]};
                character_attr.scale.x = scale_conf["x"].as<float>();
                character_attr.scale.y = scale_conf["y"].as<float>();
            }

            {
                const auto& moods_conf {char_conf["moods"]};
                std::string default_mood {moods_conf["default"].as<std::string>()};

                // static
                {
                    const auto& static_conf {moods_conf["static"]};
                    for (auto it = static_conf.begin(); it != static_conf.end(); ++it) {
                        auto key = it->first.as<std::string>();  // 获取键
                        auto value = it->second.as<std::string>();  // 获取值

                        tmtb::core::define::CharacterMood mood{
                            .is_animation = false ,
                            .delay = 0 ,
                            .images {value},
                        };
                        character_attr.moods[key] = mood;
                    }
                }

                // animation
                {
                    const auto& animation_conf {moods_conf["animation"]};
                    for (auto it = animation_conf.begin(); it != animation_conf.end(); ++it) {
                        auto key = it->first.as<std::string>();  // 获取键
                        auto single_mood = it->second;  // 获取值

                        auto delay {single_mood["delay"].as<std::uint32_t >()};

                        std::vector<std::filesystem::path> images;

                        {
                            auto images_node {single_mood["images"]};
                            for(auto && image : images_node){
                                images.emplace_back(image.as<std::string>());
                            }
                        }

                        tmtb::core::define::CharacterMood mood{
                                .is_animation = true ,
                                .delay = delay ,
                                .images {images},
                        };
                        character_attr.moods[key] = mood;
                    }
                }

                if (character_attr.moods.count(default_mood) == 0){
                    throw std::runtime_error("non-existent default mood");
                }
                character_attr.default_mood = default_mood;

                tmtb::core::global::sprite::character = std::make_unique<tmtb::spirit::CharacterSpirit>(std::move(character_attr));
            }
        }
        return true;
    }() };

    [[maybe_unused]] const bool UniformInit { [](){
        using namespace tmtb::core::global;

        framePerSecond.setFrames(tmtb::utils::FPS(config::window::fps));

        if(config::window::background.empty()){
            config::window::background = "#FFFFFFFF";
        } else if (config::window::background[0] != '#'){
            sprite::bg.setPicture(config::window::background);
            sprite::bg.BGEnable = true;
            tmtb::utils::ResizeSprite(sprite::bg.Sprite, config::window::width, config::window::height);
        }
        return true;
    }() };
}

#endif //INIT_HPP
