#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string data_ = data;
        std::reverse(data_.begin(), data_.end());
        text_->render(data_);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& data1, const std::string& data2) const {
        std::string data_ = "<a href=" + data1 + ">" + data2 + "</a>";
        text_->render(data_);
    }
};

int main() {

    auto text_block_01 = new ItalicText(new BoldText(new Text()));
    text_block_01->render("Hello world");
    std::cout << std::endl << std::endl;

    auto text_block_02 = new Paragraph(new Text());
    text_block_02->render("Hello world");
    std::cout << std::endl << std::endl;

    auto text_block_03 = new Reversed(new Text());
    text_block_03->render("Hello world");
    std::cout << std::endl << std::endl;

    auto text_block_04 = new Link(new Text());
    text_block_04->render("netology.ru", "Hello world");
    std::cout << std::endl << std::endl;

}