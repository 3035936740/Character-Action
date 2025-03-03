// #define CHAR_ACTION_TEST

#ifndef CHAR_ACTION_TEST
#include "main.hpp"

int main()
{
    // httplib::Server svr;
    // svr.listen("0.0.0.0", 8080);
    // return 0;
    // cv::imwrite("result.png", core::utils::clearColor("data/spirit/kirby.png", {207, 176, 255, 255}));
    using namespace tmtb::core::global;

    auto clear_color { sf::Color(tmtb::utils::color::RGBAToUint32(tmtb::utils::color::ParseHexColor(config::window::background))) };

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(config::window::width, config::window::height)), config::window::title, sf::Style::Close);
    window.setFramerateLimit(config::window::fps); // 帧率限制
    window.setIcon(sf::Image("favicon.png"));

    // tmtb::core::global::sprite::textbox->setText(std::filesystem::path("这是一个测试文本啊啊啊啊1啊3啊4啊6啊7啊8啊9\n\n啊000啊啊00啊啊啊啊啊啊啊啊啊啊endendendendendendendend").wstring());

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }
        window.clear(clear_color);
        if (sprite::bg.BGEnable)
        {
            window.draw(sprite::bg.Sprite);
        }

        tmtb::core::global::sprite::textbox->draw(window);

        window.draw(tmtb::core::global::sprite::character->Sprite);
        // Remainder of main loop
        window.display();
    }

    return 0;
}
#else
#include <iostream>
#include "nlohmann/json.hpp"
int main(){
    nlohmann::json body {nlohmann::json::parse(R"({"test": 124})")};
    std::cout << body << std::endl;
}
#endif
