#include <Game/MenuManager.h>

MenuManager::MenuManager()
{
}

MenuManager::~MenuManager()
{
}

void MenuManager::AddMenu(std::string name, std::shared_ptr<Menu> menu)
{
    if(menus.count(name))
    {
        std::cout << "Already Contains menu: " << std::endl;
        return;
    }
    if(menus.empty())
    {
        activeMenu = menu;
    }
    menus[name] = menu;
}

void MenuManager::SetActiveMenu(std::string menuName)
{
    if(menus.count(menuName))
    {
        this->activeMenu = menus[menuName];
    }
    else
    {
        std::cerr << "Menu: " << menuName << " does not exist" << std::endl;
    }
}
