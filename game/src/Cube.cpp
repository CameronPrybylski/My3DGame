#include <Game/Cube.h>

Cube::Cube(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec4 color, float mass, bool isStatic)
{
    mesh = AssetManager::GetMesh("cubeMesh");
    shaderName = "objectShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    rigidBody.mass = mass;
    hitBox = transform;
    this->color = color;
    this->name = name;
    
    rigidBody.friction = glm::vec3(10.0f, 0.0f, 10.0f);
    
}

Cube::~Cube()
{
}

void Cube::OnEvent(const Input& input)
{
    /*
    if(color.x == 0.0f && color.z == 1.0f && rigidBody.isCollidingVec.x == 0.0f && rigidBody.isCollidingVec.z == 0.0f)
    {
        if(input.IsKeyDown("B"))
            rigidBody.velocity.y = 200.0f;
        if(input.IsKeyDown("V"))
        {
            rigidBody.velocity.x = 100.0f;
        }
        else if(input.IsKeyDown("C"))
        {
            rigidBody.velocity.x = -100.0f;
        }
        else
        {
            //rigidBody.velocity.x = 0.0f;
        }
        if(input.IsKeyDown("N"))
        {
            rigidBody.velocity.z = 100.0f;
        }
        else if(input.IsKeyDown("M"))
        {
            rigidBody.velocity.z = -100.0f;
        }
        else
        {
            //rigidBody.velocity.z = 0.0f;
        }
    }
    */
    
}

void Cube::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
}

void Cube::Update(const Input& input, float dt)
{
    GameObject::Update(input, dt);
}

void Cube::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawCube(*mesh, transform, camera, AssetManager::GetShader(shaderName), color);
    GameObject::Render(renderer, camera);
}