#include <Game/Level.h>
#include <Game/Cube.h>
#include <Game/Player.h>
#include <Game/NPC.h>
#include <Game/Enemy.h>
#include <Game/Object.h>
#include <Game/Battle/Battle.h>
#include <Game/Battle/BattleManager.h>


Level::Level(float screenWidth, float screenHeight, std::string root, std::string loadFilePath, std::shared_ptr<BattleManager> battleManager) : Scene(screenWidth, screenHeight), root(root), loadFilePath(loadFilePath), battleManager(battleManager)
{
    Init();
}

Level::~Level()
{
}

void Level::Init()
{
    LoadLevel();
}

void Level::LoadLevel()
{

    objectList.clear();
    objectMap.clear();
    enemies.clear();

    std::ifstream file(root + loadFilePath);
    if(!file.is_open())
    {
        std::cerr << "Error loading level file" << std::endl;
    }

    nlohmann::json j;
    file >> j;
    
    for(auto item : j.items())
    {
        for(auto obj : item.value())
        {
            if(item.key() == "objects")
            {
                std::string name = obj["name"];
                glm::vec3 position = glm::vec3{obj["position"][0], obj["position"][1], obj["position"][2]};
                glm::vec3 scale = glm::vec3{obj["scale"][0], obj["scale"][1], obj["scale"][2]};
                glm::vec4 color = glm::vec4{obj["color"][0], obj["color"][1], obj["color"][2], obj["color"][3]};
                bool isStatic = obj["isStatic"];
                float mass = obj["mass"];
                glm::vec3 posOffset = glm::vec3{obj["posOffset"][0], obj["posOffset"][1], obj["posOffset"][2]};

                glm::vec3 hitBoxScaleMulti = glm::vec3(1.0f, 1.0f, 1.0f);
                glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
                if(obj.contains("hitBoxScaleMulti"))
                    hitBoxScaleMulti = glm::vec3(obj["hitBoxScaleMulti"][0], obj["hitBoxScaleMulti"][1], obj["hitBoxScaleMulti"][2]);
                if(obj.contains("rotation"))
                    rotation = glm::vec3(obj["rotation"][0], obj["rotation"][1], obj["rotation"][2]);
                glm::vec3 hitBoxScale = glm::vec3(scale.x * hitBoxScaleMulti.x, scale.y * hitBoxScaleMulti.y, scale.z * hitBoxScaleMulti.z);
                std::shared_ptr<GameObject> gameObj;
                if(obj["texturesFilePath"] == "" && obj["type"] == "object")
                {
                    std::string filePath = root + std::string(obj["gltf"]);
                    objectLoader.LoadGLTF(filePath, filePath, obj["flipYZ"]);
                    std::vector<std::shared_ptr<Mesh>> subMeshes = objectLoader.GetSubMeshes();
                    std::shared_ptr<TexturedObject> object = std::make_shared<TexturedObject>(name, subMeshes, root + "/res/crash_bandicoot/textures", position, scale, color, mass, isStatic);
                    object->transform.rotation = glm::vec3(obj["rotation"][0], obj["rotation"][1], obj["rotation"][2]);
                    object->SetTextures(objectLoader.GetTexturesGLTF());
                    object->SetRendPosOffSet(posOffset);
                    gameObj = object;
                }
                else if(obj["texturesFilePath"] != "")
                {
                    std::vector<std::shared_ptr<Mesh>> submeshes;// = objectLoader.GetSubMeshes(); 
                    if(name == "player")
                    {
                        std::string path = root + (std::string)obj["gltfPath"];
                        objectLoader.LoadGLTF(path, path, obj["flipYZ"]);
                        submeshes = objectLoader.GetSubMeshes();
                        player = std::make_shared<Player>(name, submeshes, root + std::string(obj["texturesFilePath"]), position, scale, color, mass, isStatic, obj["hp"]);
                        player->SetRendPosOffSet(posOffset);
                        player->SetTextures(objectLoader.GetTexturesGLTF());
                        gameObj = player;
                    }
                    else if(obj["type"] == "enemy")
                    {
                        if(obj["alive"] == false)
                        {
                            continue;
                        }
                        std::string path = root + (std::string)obj["gltf"];
                        objectLoader.LoadGLTF(path, path, true);
                        submeshes = objectLoader.GetSubMeshes();
                        float maxDistance = obj["maxDistance"];
                        glm::vec3 velocity = glm::vec3(obj["velocity"][0], obj["velocity"][1], obj["velocity"][2]);
                        glm::vec3 direction = glm::vec3(obj["direction"][0], obj["direction"][1], obj["direction"][2]);
                        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(name, submeshes, root + std::string(obj["texturesFilePath"]), position, scale, color, mass, isStatic, maxDistance, velocity, direction, obj["hp"]);
                        enemy->SetTextures(objectLoader.GetTexturesGLTF());
                        enemy->SetRendPosOffSet(posOffset);
                        enemy->SetBattle(obj["battle"]);
                        enemies[name] = enemy;
                        gameObj = enemy;
                    }
                    else if(obj["type"] == "object")
                    {
                        std::string path = root + (std::string)obj["gltf"];
                        objectLoader.LoadGLTF(path, path, obj["flipYZ"]);
                        submeshes = objectLoader.GetSubMeshes();
                        std::shared_ptr<TexturedObject> object = std::make_shared<TexturedObject>(name,submeshes,root + std::string(obj["texturesFilePath"]),position,scale,color,mass,isStatic);
                        object->SetTextures(objectLoader.GetTexturesGLTF());
                        gameObj = object;
                    }
                }
                else if(obj["type"] == "cube")
                {
                    std::shared_ptr<Cube> cube = std::make_shared<Cube>(name, position, scale, color, mass, isStatic);
                    gameObj = cube;
                }
                gameObj->hitBox.scale = hitBoxScale;
                gameObj->transform.rotation = rotation;
                AddObject(name, gameObj);
            }
            else if(item.key() == "levelParams")
            {
                if(obj["type"] == "camera")
                {
                    glm::vec3 playerPosition = glm::vec3{obj["playerPosition"][0], obj["playerPosition"][1], obj["playerPosition"][2]};
                    camera.Create(0.0f, screenWidth, 0.0f, screenHeight, obj["minZ"], obj["maxZ"], obj["distanceFromPlayer"], playerPosition);
                }
                if(obj["type"] == "gravity")
                {
                    this->gravity = glm::vec3(obj["gravity"][0], obj["gravity"][1], obj["gravity"][2]);
                }
                if(obj["type"] == "lightPos")
                {
                    this->lightPos = glm::vec3(obj["lightPos"][0], obj["lightPos"][1], obj["lightPos"][2]);
                }
            }
        }
    }

    leftScreenEdge = 0.0f;
    rightScreenEdge = screenWidth;
    bottomScreenEdge = 0.0f;
    topScreenEdge = screenHeight;

}

void Level::LoadPhysics(PhysicsSystem& physics)
{
    Scene::LoadPhysics(physics);
}

void Level::OnEvent(const Input& input)
{
    Scene::OnEvent(input);
   
    if(input.IsKeyDown("L"))
    {
        cameraRight = true;
    }
    else if(!input.IsKeyDown("L"))
    {
        cameraRight = false;
    }
    if(input.IsKeyDown("J"))
    {
        cameraLeft = true;
    }
    else if(!input.IsKeyDown("J"))
    {
        cameraLeft = false;
    }
    if(input.IsKeyDown("I"))
    {
        cameraUp = true;
    }
    else if(!input.IsKeyDown("I"))
    {
        cameraUp = false;
    }
    if(input.IsKeyDown("K"))
    {
        cameraDown = true;
    }
    else if(!input.IsKeyDown("K"))
    {
        cameraDown = false;
    }

    if(input.IsKeyDown("UP"))
    {
        cameraTowards = true;
    }
    else if(!input.IsKeyDown("UP"))
    {
        cameraTowards = false;
    }
    if(input.IsKeyDown("DOWN"))
    {
        cameraAway = true;
    }
    else if(!input.IsKeyDown("DOWN"))
    {
        cameraAway = false;
    }
    
}

void Level::OnUpdate(const Input& input, PhysicsSystem& physics, float dt)
{
    std::vector<CollisionEvent> collisions = physics.Update(dt);
    OnCollision(collisions, dt);

    if(!player->IsAlive())
    {
        RemoveObject(player->name);
        physics.RemoveBody(player->name);
        EndScene("gameOver");
    }
    std::map<std::string, std::shared_ptr<Enemy>>::iterator enemy = this->enemies.begin();
    for(; enemy != enemies.end();)
    {
        if(!enemy->second->IsAlive())
        {
            RemoveObject(enemy->first);
            physics.RemoveBody(enemy->first);
            enemy = enemies.erase(enemy);
        }
        else
        {
            ++enemy;
        }
    }
    
    Scene::OnUpdate(input, physics, dt);

    UpdateCamera(input, dt);

}

void Level::DrawObjects(Renderer& renderer)
{
    for(auto& obj : objectList)
    {
        obj->Render(renderer, camera);
    }
}

void Level::OnCollision(std::vector<CollisionEvent> collisions, float dt)
{
    for(auto& collision : collisions)
    {
        std::shared_ptr<GameObject> gameObject1 = objectMap.at(collision.body1.id);
        std::shared_ptr<GameObject> gameObject2 = objectMap.at(collision.body2.id);
        gameObject1->OnCollision(gameObject2, collision.collisionNormalBody1, dt);
        gameObject2->OnCollision(gameObject1, collision.collisionNormalBody2, dt);
        if( (enemies.count(collision.body1.id) || enemies.count(collision.body2.id) )&&
            (gameObject1->name == "player" || gameObject2->name == "player"))
        {
            EnemyPlayerCollision(collision.body1.id, collision.body2.id, collision.collisionNormalBody1, collision.collisionNormalBody2);
        }
    }
}

void Level::EnemyPlayerCollision(std::string body1Name, std::string body2Name, glm::vec3 body1CollNorm, glm::vec3 body2CollNorm)
{
    std::shared_ptr<Enemy> enemy;
    glm::vec3 playerCollisionNormal;
    if(body1Name == "player")
    {
        enemy = enemies.at(body2Name);
        playerCollisionNormal = body1CollNorm;
    }
    else
    {
        enemy = enemies.at(body1Name);
        playerCollisionNormal = body2CollNorm;
    }
    std::string battle = enemy->GetBattle();
    if(battleManager->HasBattle(battle))
    {
        battleManager->GetBattle(battle)->SetEnemyName(enemy->name);
        SetPlayerPosition();
        EndScene(battle);
    }
    else
    {
        std::cerr << "Battle: " << battle << " does not exist" << std::endl;
    }
}

void Level::SetPlayerPosition()
{
    std::ifstream file(root + loadFilePath);
    if(!file.is_open())
    {
        std::cerr << "Issue opening: " << loadFilePath;
    }
    nlohmann::json j;
    file >> j;
    file.close();
    for(auto& entry : j.items())
    {
        if(entry.key() == "objects")
        {
            for(auto& obj : entry.value())
            {
                if(obj["name"] == player->name)
                {
                    for(int i = 0; i < 3; ++i) {
                        obj["position"][i] = player->transform.position[i];
                    }
                    break;
                }
            }
        }
    }
    std::ofstream outFile(root + loadFilePath);
    if(!outFile.is_open()) {
        std::cerr << "Cannot write to file: " + loadFilePath;
    }
    outFile << std::setw(4) << j;
    outFile.close();
}

void Level::UpdateCamera(const Input& input, float dt)
{
    glm::vec3 cameraPos = camera.GetPos();
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float changeDist = 0.0f;
    
    if(cameraRight)
    {
        xOffset = -1.0f;
    }
    if(cameraLeft)
    {
        xOffset = 1.0f;
    }
    if(cameraUp)
    {
       yOffset = -1.0f;
    }
    if(cameraDown)
    {
        yOffset = 1.0f;
    }
    if(cameraTowards)
    {
        changeDist = -10.0f;
    }
    if(cameraAway)
    {
        changeDist = 10.0f;
    }
    //cameraPos += glm::vec3{0.0f, 0.0f, -500.0f};
    camera.Update(player->transform.position, player->transform.rotation,xOffset, yOffset, changeDist);
    player->SetDirection(camera.GetAngleAroundPlayer());
    
}