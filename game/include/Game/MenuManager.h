#pragma once 

#include <Game/Menu.h>

class MenuManager {

public:
    MenuManager();
    ~MenuManager();

    void AddMenu(std::string name, std::shared_ptr<Menu> menu);

    std::shared_ptr<Menu> GetActiveMenu(){return this->activeMenu.lock();}
    void SetActiveMenu(std::string menuName);
    
    bool Contains(std::string menuName){return this->menus.count(menuName);}

private:
    std::weak_ptr<Menu> activeMenu;
    std::map<std::string, std::shared_ptr<Menu>> menus;
};