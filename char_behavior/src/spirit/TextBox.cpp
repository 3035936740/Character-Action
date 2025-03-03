//
// Created by Bing on 2025/3/1.
//

#include "TextBox.hpp"
#include "common/utils.hpp"

void tmtb::spirit::TextBox::setText(const sf::String &text) {
    if (text.isEmpty()){
        lines_size = 0;
        return;
    }
    const auto& font_info {m_bubble_struct.font_info};
    m_lines.clear();
    const auto& character_size {font_info.font_size};
    sf::String currentLine;
    float lineWidth = 0.f;
    sf::Text tempText(m_font, "", character_size);

    for (auto c : text) {
        if (c == '\r') continue;  // 忽略 '\r'，只处理 '\n'

        currentLine += c;
        tempText.setString(currentLine);

        if (c == '\n') {
            m_lines.push_back(currentLine);
            currentLine.clear();
        } else if (tempText.getLocalBounds().size.x > m_bubble_struct.max_width) {
            m_lines.push_back(currentLine);
            currentLine.clear();
        }
    }
    m_lines.push_back(currentLine);

    bool is_exceeds {false};
    while(m_lines.size() > font_info.max_lines){
        m_lines.pop_back();
        is_exceeds = true;
    }

    if(is_exceeds){
        auto exceed_str { m_lines.back() + "..." };
        m_lines.pop_back();
        m_lines.push_back(exceed_str);
    }

    lines_size = m_lines.size();

    std::vector<float> widths, height;
    for (const auto& str : m_lines){
        tempText.setString(str);
        auto [x, y] = tempText.getLocalBounds().size;
        widths.push_back(x);
        height.push_back(y);
    }

    {
        {
            auto max_element = std::max_element(widths.cbegin(), widths.cend());
            font_max_width = *max_element;
        }
        {
            auto max_element = std::max_element(height.cbegin(), height.cend());
            font_max_height = *max_element;
        }
    }
}

tmtb::spirit::TextBox::TextBox(tmtb::core::define::BubbleStruct&& bubble_struct) :
    m_bubble_struct {std::move(bubble_struct)},
    m_font(m_bubble_struct.font_info.font_path),
    m_text(m_font)
{
    m_text.setString("");
    m_text.setCharacterSize(m_bubble_struct.font_info.font_size);

    {
        auto [r,g,b,a] = tmtb::utils::color::ParseHexColor(m_bubble_struct.bg_color);
        bg_color = sf::Color(r,g,b,a);
    }
    {
        auto [r,g,b,a] = tmtb::utils::color::ParseHexColor(m_bubble_struct.border_color);
        border_color = sf::Color(r,g,b,a);
    }
    const auto& font_info {m_bubble_struct.font_info};
    {
        auto [r,g,b,a] = tmtb::utils::color::ParseHexColor(font_info.font_color);
        m_text.setFillColor(sf::Color(r,g,b,a));
    }
    int font_style {sf::Text::Regular};

    if (font_info.is_underlined) font_style |= sf::Text::Underlined;
    if (font_info.is_bold) font_style |= sf::Text::Bold;
    if (font_info.is_italic) font_style |= sf::Text::Italic;
    if (font_info.is_strike_through) font_style |= sf::Text::StrikeThrough;
    m_text.setStyle(font_style);
    auto default_text{m_bubble_struct.default_text};
    if (not default_text.empty()){
        setText(std::filesystem::path(default_text).wstring());
    }
}

void tmtb::spirit::TextBox::draw(sf::RenderWindow &window) {
    if (lines_size == 0){
        return;
    }
    const auto& position {m_bubble_struct.position};
    const auto& padding {m_bubble_struct.padding};

    auto direction {m_bubble_struct.direction};

    // 气泡显示
    {
        const auto& character_size {m_bubble_struct.font_info.font_size};
        const auto line_spacing {m_bubble_struct.font_info.line_spacing};

        auto
        max_width { font_max_width + padding.left + padding.right},
        max_height { padding.bottom + padding.top + static_cast<float>(lines_size) * static_cast<float>(character_size) * line_spacing };

        // utils::println(static_cast<float>((lines_size - 1) * character_size));

        sf::ConvexShape convex;

        auto& emit {m_bubble_struct.emit};

        convex.setPointCount(7);

        convex.setPoint(0, {0.0f, 0.0f});
        convex.setPoint(1, {max_width, 0.0f});
        convex.setPoint(2, {max_width, max_height});
        if (direction == 0){ // 0 左
            sf::Vector2f emit_pos {0 + emit.head_add_pos_x, max_height + emit.head_add_pos_y};
            convex.setPoint(3, {max_width * emit.tail_end, max_height});
            convex.setPoint(4, emit_pos);
            convex.setPoint(5, {max_width * emit.tail_start, max_height});
            convex.setOrigin(emit_pos);
            m_text.setOrigin(emit_pos);
        } else if(direction == 1){ // 1 右
            sf::Vector2f emit_pos {max_width - emit.head_add_pos_x, max_height + emit.head_add_pos_y};
            convex.setPoint(3, {max_width * (1.0f - emit.tail_start), max_height});
            convex.setPoint(4, emit_pos);
            convex.setPoint(5, {max_width * (1.0f - emit.tail_end), max_height});
            convex.setOrigin(emit_pos);
            m_text.setOrigin(emit_pos);
        } else {
            throw std::runtime_error("unimplemented direction");
        }
        convex.setPoint(6, {0.0, max_height});

        // sf::RectangleShape rectangle({max_width, max_height});
        convex.setFillColor(bg_color);
        convex.setPosition(position);
        convex.setOutlineColor(border_color);
        convex.setOutlineThickness(m_bubble_struct.border_size);


        window.draw(convex);
    }
    // 文本显示
    {
        const auto& font_info {m_bubble_struct.font_info};
        float y_offset = 0.0f;
        const auto line_spacing {font_info.line_spacing};
        const auto& character_size {font_info.font_size};
        const auto& [x, y] {position};
        for (const auto& line : m_lines) {
            m_text.setString(line);
            m_text.setPosition(sf::Vector2f(x + padding.left, y + y_offset + padding.top));
            window.draw(m_text);
            y_offset += static_cast<float>(character_size) * line_spacing;  // 行间距
        }
    }
}
