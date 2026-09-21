#include <Game/Battle/Battle.h>
#include <Game/Battle/PlayerInBattle.h>
#include <Game/Battle/EnemyInBattle.h>
#include <Game/Cube.h>

Battle::Battle(float screenWidth, float screenHeight, std::string root, std::string loadFilePath) : Scene(screenWidth, screenHeight), 
    root(root), loadFilePath(loadFilePath)
{
    Init();
}

Battle::~Battle()
{
}

void Battle::Init()
{
    LoadBattle();
}

void Battle::LoadBattle()
{
    objectList.clear();
    objectMap.clear();
    enemies.clear();
    player.reset();
    std::ifstream loadFile(root + loadFilePath);
    if(!loadFile.is_open())
    {
        std::cerr << "Could not load file: " << root + loadFilePath << std::endl;
        return;
    }

    nlohmann::json j;
    loadFile >> j;
    glm::vec3 cameraOffSet = glm::vec3(0.0f);
    for(auto entry : j.items())
    {
        if(entry.key() == "objects")
        {
            for(auto object : entry.value())
            {
                std::string name = object["name"];
                glm::vec3 position = glm::vec3{object["position"][0], object["position"][1], object["position"][2]};
                glm::vec3 scale = glm::vec3{object["scale"][0], object["scale"][1], object["scale"][2]};
                glm::vec4 color = glm::vec4{object["color"][0], object["color"][1], object["color"][2], object["color"][3]};
                bool isStatic = object["isStatic"];
                float mass = object["mass"];
                glm::vec3 posOffset = glm::vec3{object["posOffset"][0], object["posOffset"][1], object["posOffset"][2]};

                glm::vec3 hitBoxScaleMulti = glm::vec3(1.0f, 1.0f, 1.0f);
                glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
                if(object.contains("hitBoxScaleMulti"))
                    hitBoxScaleMulti = glm::vec3(object["hitBoxScaleMulti"][0], object["hitBoxScaleMulti"][1], object["hitBoxScaleMulti"][2]);
                if(object.contains("rotation"))
                    rotation = glm::vec3(object["rotation"][0], object["rotation"][1], object["rotation"][2]);
                glm::vec3 hitBoxScale = glm::vec3(scale.x * hitBoxScaleMulti.x, scale.y * hitBoxScaleMulti.y, scale.z * hitBoxScaleMulti.z);
                std::shared_ptr<GameObject> gameObj;
                if(object["type"] == "player" || object["type"] == "enemy")
                {
                    int hp = object["hp"];
                    int damageOutput = object["damageOutput"];
                    std::string gltf = object["gltf"];
                    std::string gltfPath = root + gltf;
                    objectLoader.LoadGLTF(gltfPath, gltf, object["flipYZ"]);
                    std::vector<std::shared_ptr<Mesh>> submeshes = objectLoader.GetSubMeshes();
                    if(object["type"] == "player")
                    {
                        player = std::make_shared<PlayerInBattle>(name,submeshes,"",position,scale,color,mass,isStatic, hp, damageOutput);
                        player->SetTextures(objectLoader.GetTexturesGLTF());
                        player->transform.rotation = rotation;
                        player->SetRendPosOffSet(posOffset);
                        gameObj = player;
                    }
                    else if(object["type"] == "enemy")
                    {
                        std::shared_ptr<EnemyInBattle> enemy = std::make_shared<EnemyInBattle>(name,submeshes,"",position,scale,color,mass,isStatic, hp, damageOutput);
                        enemy->SetTextures(objectLoader.GetTexturesGLTF());
                        enemy->transform.rotation = rotation;
                        enemies.push_back(enemy);
                        gameObj = enemy;
                    }
                }
                else if(object["type"] == "cube")
                {
                    std::shared_ptr<Cube> cube = std::make_shared<Cube>(name, position, scale, color, mass, isStatic);
                    gameObj = cube;
                }
                AddObject(name, gameObj);
            }
        }
        else if(entry.key() == "levelParams")
        {
            for(auto param : entry.value())
            {
                if(param["type"] == "camera")
                {
                    glm::vec3 playerPosition = glm::vec3{param["playerPosition"][0], param["playerPosition"][1], param["playerPosition"][2]};
                    camera.Create(0.0f, screenWidth, 0.0f, screenHeight, param["minZ"], param["maxZ"], param["distanceFromPlayer"], playerPosition);
                    cameraOffSet = glm::vec3(param["offset"][0], param["offset"][1], param["offset"][2]);
                }
                else if(param["type"] == "lightPos")
                {
                    this->lightPos = glm::vec3(param["lightPos"][0], param["lightPos"][1], param["lightPos"][2]);
                }
                else if(param["type"] == "gravity")
                {
                    this->gravity = glm::vec3(param["gravity"][0], param["gravity"][1], param["gravity"][2]);
                }
            }
        }
    }
    player->lightPos = this->lightPos;
    this->cameraAnimationChange = glm::vec3(0.0f);
    camera.Update(player->transform.position, glm::vec3(0.0f,0.0f,0.0f), cameraOffSet.x, cameraOffSet.y, cameraOffSet.z);
    
    if(!enemies.empty())
    {
        enemies[selectedEnemy]->SetHighLightedColor();
    }    
}

void Battle::LoadPhysics(PhysicsSystem &physics)
{
    Scene::LoadPhysics(physics);
}

void Battle::OnEvent(const Input &input)
{
    if(introAnimation)
        return;
    
    Scene::OnEvent(input);

    if(input.IsKeyDown("D") || input.IsKeyDown("A"))
    {
        glm::vec4 baseColor = glm::vec4(0.0f);
        enemies[selectedEnemy]->color = baseColor;
        if(input.IsKeyDown("D"))
        {
            if(selectedEnemy < enemies.size() - 1)
                ++selectedEnemy;
            else
                selectedEnemy = 0;
        }
        if(input.IsKeyDown("A"))
        {
            if(selectedEnemy > 0)
                --selectedEnemy;
            else
                selectedEnemy = enemies.size() - 1;
        }
        enemies[selectedEnemy]->SetHighLightedColor();
    }

    if(input.IsKeyDown("X"))
    {
        EndScene("level");
    }
}

void Battle::OnUpdate(const Input &input, PhysicsSystem &physics, float dt)
{
    if(introAnimation)
    {
        AnimateIntro();
    }
    if(enemies.empty())
    {
        EndScene("level");
    }
    Scene::OnUpdate(input, physics, dt);
   
    std::vector<CollisionEvent> collisions = physics.Update(dt);
    
    if(!player->IsMoving() && !enemies[selectedEnemy]->IsMoving())
    {
        HandleAttackTurn();
    }

}

void Battle::HandleAttackTurn()
{
    glm::vec3 nullDirection = glm::vec3(0.0f);
    std::shared_ptr<ActorInBattle> attacker;
    std::shared_ptr<ActorInBattle> attackee;
    if(playerTurn && !player->IsAttacking())
    {
        return;
    }
    else if(playerTurn)
    {
        attacker = player;
        attackee = enemies[selectedEnemy];
    }
    else
    {
        attacker = enemies[selectedEnemy];
        attackee = player;
    }
    if(attacker->GetAttackPosition() != nullDirection)
    {
        attackee->TakeDamage(attacker->GetDamageOutput());
        if(attacker == player)
        {
            if(!attackee->IsAlive())
            {
                RemoveObject(attackee->name);
                enemies.erase(enemies.begin() + selectedEnemy);
                if(selectedEnemy > 0)
                {
                    --selectedEnemy;
                }
                if(!enemies.empty())
                {
                    enemies[selectedEnemy]->SetHighLightedColor();
                }
            }
        }
        attacker->ReturnToStart();
        this->playerTurn = !this->playerTurn;
    }
    else
    {
        if(attacker->GetAttackPosition() == nullDirection)
        {
            glm::vec3 attackPosition = attackee->transform.position;
            attacker->SetAttackPosition(attackPosition);
        }
        attacker->SetAttacking(true);
    }
}

void Battle::AnimateIntro()
{
    
    if(cameraAnimationChange.x >= 360.0f)
    {
        introAnimation = false;
    }
    else
    {
        camera.Update(player->transform.position, glm::vec3(0.0f,0.0f,0.0f), 1.0f, 0.0f, 0.0f);
        cameraAnimationChange.x += 1.0f;
    }
}
