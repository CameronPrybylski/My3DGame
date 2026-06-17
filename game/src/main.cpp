#include <Engine/Engine.h>
#include <Engine/Scene/Application.h>
#include <Game/Level.h>

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
        std::shared_ptr<Level> level = std::make_shared<Level>(1067.0f, 800.0f, std::string(root));

        app.AddScene("level", level);
        app.SetScene("level");
        
        AssetManager::LoadShader("objectShader", (std::string(root) + "/shaders/basic.vert").c_str(), (std::string(root) + "/shaders/basic.frag").c_str());
        AssetManager::LoadShader("textureShader", (std::string(root) + "/shaders/texture.vert").c_str(), (std::string(root) + "/shaders/texture.frag").c_str());
        //AssetManager::LoadShader("textureBatchShader", (std::string(root) + "/shaders/batchtexture.vert").c_str(), (std::string(root) + "/shaders/batchtexture.frag").c_str());
        app.Run();
    }
    return 0;
}