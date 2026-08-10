#include <Game/GameOver.h>
#include <Engine/Scene/StringText.h>

GameOver::GameOver(float screenWidth, float screenHeight, std::string root, std::string loadFilePath, std::string nextScene) 
    : Scene(screenWidth, screenHeight), root(root), loadFilePath(loadFilePath)
{
    this->nextScene = nextScene;
    Init();
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    std::ifstream file(root + loadFilePath);
    if(!file.is_open())
    {
        std::cerr << "Error loading level file" << std::endl;
    }

    nlohmann::json j;
    file >> j;
    
    float minX, minY, minZ, maxX, maxY, maxZ, distanceFrom;
    glm::vec3 lookAt;
    for(auto item : j.items())
    {
        for(auto obj : item.value())
        {
            if(item.key() == "objects")
            {
                std::shared_ptr<GameObject> go;
                if(obj["type"] == "StringText")
                {
                    glm::vec3 position = glm::vec3(obj["position"][0],obj["position"][1], obj["position"][2]);
                    glm::vec4 color = glm::vec4(obj["color"][0],obj["color"][1], obj["color"][2], obj["color"][3]);
                    std::string fontPath = root + (std::string)obj["fontPath"];
                    std::shared_ptr<StringText> gameOverText = std::make_shared<StringText>(obj["text"], position, color, fontPath, obj["fontSize"]);
                    lookAt = (gameOverText->GetEndPosition() - gameOverText->transform.position);
                    lookAt /= 2;
                    go = gameOverText;
                }
                AddObject(obj["name"], go);
            }
            else if(item.key() == "levelParams")
            {
                minX = 0.0f;
                maxX = screenWidth;
                minY = 0.0f;
                maxY = screenHeight;
                minZ = obj["minZ"];
                maxZ = obj["maxZ"];
                distanceFrom = obj["distanceFrom"];
            }
        }
    }
    camera.Create(minX, maxX, minY, maxY, minZ, maxZ, distanceFrom, lookAt);
}

void GameOver::OnEvent(const Input& input)
{
    if(input.IsKeyDown("SPACE"))
    {
        EndScene(nextScene);
    }
}
