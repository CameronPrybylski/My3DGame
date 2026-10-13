#pragma once

#include <Game/Cube.h>

class StringText;

class Menu : public Cube, public std::enable_shared_from_this<Menu> {
public:
    Menu(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic);
    ~Menu();
    virtual void OnEvent(const Input& input) override;
    virtual void Render(Renderer &renderer, const Camera& camera) override;
    
    void AddMenuItem(std::shared_ptr<StringText> text, std::string action);
    void AddSubMenu(std::shared_ptr<StringText> text, std::shared_ptr<Menu> submenu);

    std::shared_ptr<Menu> GetSubMenu(std::shared_ptr<StringText> text){return subMenus[text];}

    std::shared_ptr<StringText> GetSelectedText(){return menuItems[selectedText];}

    std::string GetMove(){return this->move;}
    void SetMove(std::string move){this->move = move;}

    std::shared_ptr<Menu> GetPreviousMenu();
    int GetSubMenuCount(){return this->subMenus.size();}

    void Clear(){
        menuItems.clear();
        menuItemsMoves.clear();
        subMenus.clear();
    }

    
protected:
    std::vector<std::shared_ptr<StringText>> menuItems;
    std::map<std::shared_ptr<StringText>, std::string> menuItemsMoves;
    std::string move = "";
    int selectedText = 0;
    std::map<std::shared_ptr<StringText>, std::shared_ptr<Menu>> subMenus;
    std::weak_ptr<Menu> previousMenu;
};