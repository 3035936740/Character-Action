//
// Created by Bing on 2023/11/20.
//
#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include<locale>
#include <codecvt>

#define PRINT_FMT(function_name)  template <typename... Tn>inline void function_name(std::format_string<Tn...> fmt, Tn&&... args)

using namespace std::chrono_literals;
namespace tmtb::utils{
    namespace type{
        using rgba = std::array<std::uint8_t, 4>;
    }

    template <typename T>
    [[maybe_unused]] inline void print(const T& arg) {
        std::cout << arg; std::cout.flush();
    }
    template <typename T, typename... Tn>
    [[maybe_unused]] inline void print(const T& arg, const Tn&... args) {
        if constexpr (sizeof...(args) > 0) {
            std::cout << arg << ' ';
        } print(args...);
    }
    template <typename T, typename... Tn>
    [[maybe_unused]] inline void println(const T& arg, const Tn&... args) {
        print(arg, args...); std::cout << std::endl;
    }
    template <typename T>
    [[maybe_unused]] inline void print(T&& arg) {
        std::cout << arg; std::cout.flush();
    }
    template <typename T, typename... Tn>
    [[maybe_unused]] inline void print(T&& arg, Tn&&... args) {
        if constexpr (sizeof...(args) > 0) {
            std::cout << arg << ' ';
        }
        print(args...);
    }
    template <typename T, typename... Tn>
    [[maybe_unused]] inline void println(T&& arg, Tn&&... args) {
        print(arg, args...); std::cout << std::endl;
    }

    PRINT_FMT(print_fmt) {
        std::cout << std::format(fmt, std::forward<Tn>(args)...);
        std::cout.flush();
    }

    PRINT_FMT(println_fmt) {
        print_fmt(fmt, std::forward<Tn>(args)...);
        std::cout << std::endl;
    }

    [[maybe_unused]] inline constexpr auto operator""_f(const char* fmt, size_t) {
        return[=]<typename... T>(T&&... Args) { return std::vformat(fmt, std::make_format_args(std::forward<T>(Args)...)); };
    }

    [[maybe_unused]] inline constexpr type::rgba RGBA(uint8_t red, uint8_t green,uint8_t blue, uint8_t alpha){
        return type::rgba{red,green,blue,alpha};
    }

    namespace color{
        inline type::rgba ParseHexColor(const std::string& hex)
        {
            std::uint8_t red{0}, green{0}, blue{0}, alpha{255};
            // 去掉前面的 '#'
            std::string hexColor = hex;
            if (hexColor[0] == '#') {
                hexColor = hexColor.substr(1);
            }

            if (hexColor.length() == 6) {
                // RGB: #RRGGBB
                std::stringstream ss;
                ss << std::hex << hexColor.substr(0, 2);
                int r, g, b;
                ss >> r;
                red = static_cast<std::uint8_t>(r);
                
                ss.clear();
                ss.str(hexColor.substr(2, 2));
                ss >> g;
                green = static_cast<std::uint8_t>(g);
                
                ss.clear();
                ss.str(hexColor.substr(4, 2));
                ss >> b;
                blue = static_cast<std::uint8_t>(b);

                // 默认 alpha 为 255
                alpha = 255;
            } else if (hexColor.length() == 8) {
                // RGBA: #RRGGBBAA
                std::stringstream ss;
                ss << std::hex << hexColor.substr(0, 2);
                int r, g, b, a;
                ss >> r;
                red = static_cast<std::uint8_t>(r);
                
                ss.clear();
                ss.str(hexColor.substr(2, 2));
                ss >> g;
                green = static_cast<std::uint8_t>(g);
                
                ss.clear();
                ss.str(hexColor.substr(4, 2));
                ss >> b;
                blue = static_cast<std::uint8_t>(b);
                
                ss.clear();
                ss.str(hexColor.substr(6, 2));
                ss >> a;
                alpha = static_cast<std::uint8_t>(a);
            }

            return {red, green, blue, alpha};
        }

        inline std::uint32_t RGBAToUint32(const type::rgba& arr) {
            return (static_cast<std::uint32_t>(arr[0]) << 24) | 
                (static_cast<std::uint32_t>(arr[1]) << 16) |
                (static_cast<std::uint32_t>(arr[2]) << 8)  |
                static_cast<std::uint32_t>(arr[3]);
        }

        inline type::rgba Uint32ToRGBA(std::uint32_t value) {
            type::rgba arr;
            using rgbaSubType = type::rgba::value_type;
            arr[0] = static_cast<rgbaSubType>((value >> 24) & 0xFF);
            arr[1] = static_cast<rgbaSubType>((value >> 16) & 0xFF);
            arr[2] = static_cast<rgbaSubType>((value >> 8) & 0xFF);
            arr[3] = static_cast<rgbaSubType>(value & 0xFF);
            return arr;
        }
    }

    inline void ResizeSprite(sf::Sprite& sprite, std::uint16_t resize_x, std::uint16_t resize_y){
        auto [x, y] {sprite.getTexture().getSize()};
        float scale_x {static_cast<float>(resize_x) / static_cast<float>(x)}, scale_y{static_cast<float>(resize_y) / static_cast<float>(y)};
        sprite.setScale(sf::Vector2f(scale_x, scale_y));
    }
}

#undef PRINT_FMT
#endif //UTILS_HPP
