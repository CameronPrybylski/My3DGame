#include <Game/Menu.h>
#include <Engine/Scene/StringText.h>

#include <algorithm>

Menu::Menu(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic) : Cube(name,position,scale,color,mass,isStatic)
{
    this->transform.rotation = rotation;
    this->selectedText = 0;
}

Menu::~Menu()
{
}

void Menu::AddMenuItem(std::shared_ptr<StringText> text, std::string action)
{
    menuItems.push_back(text);
    menuItemsMoves[text] = action;
}

void Menu::OnEvent(const Input& input)
{
    if(selectedText + 1 < menuItems.size() && input.IsKeyDown("W"))
    {
        ++selectedText;
    }
    else if(input.IsKeyDown("W"))
    {
        selectedText = 0;
    }
    if(selectedText - 1 >= 0 && input.IsKeyDown("S"))
    {
        --selectedText;
    }
    else if(input.IsKeyDown("S"))
    {
        selectedText = menuItems.size() - 1;
    }
    if(input.IsKeyDown("RETURN"))
    {
        std::shared_ptr<StringText> textMove = menuItems[selectedText];
        this->move = menuItemsMoves.at(textMove);
    }
    
    glm::vec4 highlightColor = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    glm::vec4 defaultColor = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    for(int i = 0; i < menuItems.size(); ++i)
    {
        if(i == selectedText)
        {
            menuItems[i]->ChangeTextColor(highlightColor);
        }
        else
        {
            menuItems[i]->ChangeTextColor(defaultColor);
        }
    }
}

void Menu::Render(Renderer &renderer, const Camera& camera)
{
    Cube::Render(renderer, camera);
    for(int i = 0; i < menuItems.size(); ++i)
    {
        menuItems[i]->Render(renderer, camera);
    }
}