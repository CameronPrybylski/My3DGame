#include <Game/Level.h>
#include <Game/Cube.h>
#include <Game/Player.h>
#include <Game/Object.h>

Level::Level(float screenWidth, float screenHeight, std::string root) : Scene(screenWidth, screenHeight), root(root)
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

    objectLoader.LoadVertInd(root + "/res/teapot.obj");
    std::vector<unsigned int> indecies = objectLoader.GetIndecies();
    std::vector<float> vertices = objectLoader.GetVertexPos();
    std::shared_ptr<Object> object = std::make_shared<Object>("object", vertices, indecies);
    std::shared_ptr<GameObject> gameObj = object;
    AddObject(object->name, gameObj);
    
    objectLoader.LoadVertIndTex(root + "/res/tidus/High Poly Tidus.obj", root + "/res/tidus/High Poly Tidus.mtl");  
    std::vector<std::shared_ptr<Mesh>> submeshes = objectLoader.GetSubMeshes();
    player = std::make_shared<Player>("player", submeshes, root + "/res/tidus/");
    
    player->SetMaterialMap(objectLoader.GetMaterialMap());
    player->color = glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
    player->transform.position += glm::vec3(150.0f, 300.0f, 0.0f);
    player->transform.scale = glm::vec3(300.0f, 300.0f, 300.0f);
    player->rigidBody.mass = 10.0f;
    std::shared_ptr<GameObject> go = player;
    AddObject(player->name, go);

    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>("cube2");
    cube2->rigidBody.mass = 20.0f;
    std::shared_ptr<GameObject> go2 = cube2;
    AddObject(cube2->name, go2);

    std::shared_ptr<Cube> cube3 = std::make_shared<Cube>("cube3");
    cube3->transform.position += glm::vec3(0.0f, 150.0f, 0.0f);
    cube3->rigidBody.mass = 15.0f;
    std::shared_ptr<GameObject> go3 = cube3;
    AddObject(cube3->name, go3);

    std::shared_ptr<Cube> cube4 = std::make_shared<Cube>("cube4");
    cube4->transform.position += glm::vec3(0.0f, -150.0f, 0.0f);
    cube4->transform.scale = glm::vec3(3000.0f, 10.0f, 3000.0f);
    cube4->color = glm::vec4{0.0f, 0.7f, 0.4f, 1.0f};
    cube4->rigidBody.isStatic = true;
    cube4->rigidBody.mass = 100.0f;
    std::shared_ptr<GameObject> go4 = cube4;
    AddObject(cube4->name, go4);

    camera.Create(0.0f, 1067.0f, 0.0f, 800.0f, -100.0f, 100.0f, 1000.0f, player->transform.position);

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
        physics.RegisterBody(obj.second->transform, obj.second->rigidBody, obj.second->name);
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