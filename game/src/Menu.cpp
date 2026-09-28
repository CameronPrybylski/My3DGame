#include <Game/Menu.h>
#include <Engine/Scene/StringText.h>

#include <algorithm>

Menu::Menu(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic, glm::vec3 letterPosOffset, glm::vec3 letterRotation) : Cube(name,position,scale,color,mass,isStatic)
{
    this->transform.rotation = rotation;
    glm::vec4 textColor = glm::vec4(0.0f, 0.0f,0.0f, 1.0f);
    std::string hello = "Attack";
    std::string goodBye = "Przybylski";
    std::shared_ptr<StringText> text = std::make_shared<StringText>(hello, position, rotation, textColor, "/Users/cameronprzybylski/Documents/C++/C++ Projects/My3DGame/fonts/OpenSans-Bold.ttf", 10, glm::vec3(0.0f));
    position += glm::vec3(200.0f, 0.0f, 0.0f);
    std::shared_ptr<StringText> text2 = std::make_shared<StringText>(goodBye, position, rotation, textColor, "/Users/cameronprzybylski/Documents/C++/C++ Projects/My3DGame/fonts/OpenSans-Bold.ttf", 10, glm::vec3(0.0f));
    menuItems.push_back(text);
    menuItems.push_back(text2);
    menuItemsMoves[text] = "attack";
    menuItemsMoves[text2] = "";
    selectedText = 0;
}

Menu::~Menu()
{
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