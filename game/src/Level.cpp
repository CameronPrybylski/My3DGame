#include <Game/Level.h>
#include <Game/Cube.h>
#include <Game/Player.h>
#include <Game/Object.h>

Level::Level(float screenWidth, float screenHeight, std::string root, std::string loadFilePath) : Scene(screenWidth, screenHeight), root(root), loadFilePath(loadFilePath)
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
                if(obj.contains("hitBoxScaleMulti"))
                    hitBoxScaleMulti = glm::vec3(obj["hitBoxScaleMulti"][0], obj["hitBoxScaleMulti"][1], obj["hitBoxScaleMulti"][2]);
                glm::vec3 hitBoxScale = glm::vec3(scale.x * hitBoxScaleMulti.x, scale.y * hitBoxScaleMulti.y, scale.z * hitBoxScaleMulti.z);
                std::shared_ptr<GameObject> gameObj;
                if(obj["texturesFilePath"] == "" && obj["type"] == "object")
                {
                    std::string filePath = root + std::string(obj["obj"]);
                    objectLoader.LoadVertInd(root + std::string(obj["obj"]));
                    std::vector<unsigned int> indecies = objectLoader.GetIndecies();
                    std::vector<float> vertices = objectLoader.GetVertexPos();
                    std::shared_ptr<Object> object = std::make_shared<Object>(name, vertices, indecies, position, scale, color, mass, isStatic);
                    gameObj = object;
                }
                else if(obj["texturesFilePath"] != "")
                {
                    objectLoader.LoadVertIndTex(root + std::string(obj["obj"]), root + std::string(obj["mtl"]));
                    //objectLoader.LoadVertIndTex(root + "/res/crashbandicoot/crashbandicoot.obj", root + "/res/crashbandicoot/crashbandicoot.mtl"); 
                    //"obj" : "/res/tidus/High Poly Tidus.obj",
                    //"mtl" : "/res/tidus/High Poly Tidus.mtl", 
                    std::vector<std::shared_ptr<Mesh>> submeshes = objectLoader.GetSubMeshes();
                    player = std::make_shared<Player>(name, submeshes, root + std::string(obj["texturesFilePath"]), position, scale, color, mass, isStatic);
                    player->SetMaterialMap(objectLoader.GetMaterialMap());
                    player->SetRendPosOffSet(posOffset);
                    gameObj = player;
                }
                else if(obj["type"] == "cube")
                {
                    std::shared_ptr<Cube> cube = std::make_shared<Cube>(name, position, scale, color, mass, isStatic);
                    gameObj = cube;
                }
                gameObj->hitBox.scale = hitBoxScale;
                AddObject(name, gameObj);
            }
            else if(item.key() == "levelParams")
            {
                if(obj["type"] == "camera")
                {
                    glm::vec3 playerPosition = glm::vec3{obj["playerPosition"][0], obj["playerPosition"][1], obj["playerPosition"][2]};
                    camera.Create(0.0f, screenWidth, 0.0f, screenHeight, obj["minZ"], obj["maxZ"], obj["distanceFromPlayer"], playerPosition);
                }
            }
        }
    }
    glm::vec3 playerCubeScale = glm::vec3(player->transform.scale.x * 0.125f, player->transform.scale.y * 0.5f, player->transform.scale.z * 0.125f);

    playerCube = std::make_shared<Cube>("cubePlayer", player->transform.position, playerCubeScale, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f), 1.0f, false);
    leftScreenEdge = 0.0f;
    rightScreenEdge = screenWidth;
    bottomScreenEdge = 0.0f;
    topScreenEdge = screenHeight;

}

void Level::LoadPhysics(PhysicsSystem& physics)
{
    glm::vec3 gravity;
    gravity.x = 0.0f;
    gravity.z = 0.0f;
    gravity.y = -500.0f;
    physics.SetGravity(gravity);
    for(auto& obj : objectMap)
    {
        physics.RegisterBody(obj.second->hitBox, obj.second->rigidBody, obj.second->name);
    }
}

void Level::OnEvent(const Input& input)
{
   
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
    

    for(auto obj : objectList)
    {
        obj->OnEvent(input);
    }
}

void Level::OnUpdate(const Input& input, PhysicsSystem& physics, float dt)
{
    std::vector<CollisionEvent> collisions = physics.Update(dt);
    OnCollision(collisions, dt);
    for(auto& obj : objectList)
    {
        obj->Update(input, dt);
    }
    playerCube->transform.position = player->transform.position;
    playerCube->hitBox.position = player->hitBox.position;
    playerCube->transform.position.y += 75.0f;
    playerCube->Update(input, dt);
    UpdateCamera(input, dt);

}

void Level::DrawObjects(Renderer& renderer)
{
    for(auto& obj : objectList)
    {
        obj->Render(renderer, camera);
    }
    playerCube->Render(renderer, camera);
}

void Level::OnCollision(std::vector<CollisionEvent> collisions, float dt)
{
    for(auto& collision : collisions)
    {
        std::shared_ptr<GameObject> gameObject1 = objectMap.at(collision.body1.id);
        std::shared_ptr<GameObject> gameObject2 = objectMap.at(collision.body2.id);
        gameObject1->OnCollision(gameObject2, collision.collisionNormalBody1, dt);
        gameObject2->OnCollision(gameObject1, collision.collisionNormalBody2, dt);
    }
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