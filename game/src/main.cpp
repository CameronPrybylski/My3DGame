#include <Engine/Engine.h>
#include <Engine/Scene/Application.h>
#include <Game/Level.h>
#include <Game/GameOver.h>
#include <Game/Battle/Battle.h>
#include <Game/Battle/BattleManager.h>
#include <Game/MenuManager.h>

#include <iostream>

int main()
{
    
    Application app;
    const char* root = getenv("My3DGame_ROOT");

    
    if(!app.Create("Game", 1067, 800)){
        //1067 / 600 = 1.7783333
        std::cout << "Error Creating Engine" << std::endl;
    }
    else{
    
        auto quadMesh = std::make_shared<QuadMesh>();
        AssetManager::LoadMesh("quadMesh", quadMesh);
        auto batchMesh = std::make_shared<BatchMesh>();
        AssetManager::LoadMesh("batchMesh", batchMesh);

        auto cubeMesh = std::make_shared<CubeMesh>();
        AssetManager::LoadMesh("cubeMesh", cubeMesh);
        
        //Scene scene;
        std::shared_ptr<BattleManager> battleManager = std::make_shared<BattleManager>();
        std::shared_ptr<MenuManager> menuManager = std::make_shared<MenuManager>();
        std::shared_ptr<Level> level = std::make_shared<Level>(1067.0f, 800.0f, std::string(root), "/levels/testlevel.json", battleManager);
        std::shared_ptr<Level> level2 = std::make_shared<Level>(1067.0f, 800.0f, std::string(root), "/levels/level2.json", battleManager);
        std::shared_ptr<GameOver> gameOver = std::make_shared<GameOver>(1067.0f, 800.0f, std::string(root), "/levels/gameover.json", "level");
        std::shared_ptr<Battle> battle = std::make_shared<Battle>(1067.0f, 800.0f, std::string(root), "/levels/battle.json", "/levels/testlevel.json", menuManager);
        std::shared_ptr<Battle> battle2 = std::make_shared<Battle>(1067.0f, 800.0f, std::string(root), "/levels/battle2.json", "/levels/testlevel.json", menuManager);
        battleManager->AddBattle("battle1", battle);
        battleManager->AddBattle("battle2", battle2);
        //level->AddBattle("battle1", battle);
        //level->AddBattles(app);
        app.AddScene("level", level);
        app.AddScene("level2", level2);
        app.AddScene("gameOver", gameOver);
        app.AddScene("battle1", battle);
        app.AddScene("battle2", battle2);
        app.SetScene("level");
        
        AssetManager::LoadShader("objectShader", (std::string(root) + "/shaders/basic.vert").c_str(), (std::string(root) + "/shaders/basic.frag").c_str());
        AssetManager::LoadShader("textureShader", (std::string(root) + "/shaders/texture.vert").c_str(), (std::string(root) + "/shaders/texture.frag").c_str());
        //AssetManager::LoadShader("textureBatchShader", (std::string(root) + "/shaders/batchtexture.vert").c_str(), (std::string(root) + "/shaders/batchtexture.frag").c_str());
        app.Run();
    }
    return 0;
}