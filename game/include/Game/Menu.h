#pragma once

#include <Game/Cube.h>

class StringText;

class Menu : public Cube {
public:
    Menu(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic);
    ~Menu();
    virtual void OnEvent(const Input& input) override;
    virtual void Render(Renderer &renderer, const Camera& camera) override;
    
    void AddMenuItem(std::shared_ptr<StringText> text, std::string action);

    std::string GetMove(){return this->move;}
    void SetMove(std::string move){this->move = move;}
    
protected:
    std::vector<std::shared_ptr<StringText>> menuItems;
    std::map<std::shared_ptr<StringText>, std::string> menuItemsMoves;
    std::string move = "";
    int selectedText = 0;
};