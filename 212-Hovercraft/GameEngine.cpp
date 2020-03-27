#include "GameEngine.h"

//Initialise the window
void GameEngine::initGLFWWindow(const char* title, bool resizable)
{
    //Init GLFW
    glfwInit();

    //Creating the window 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_Version_Minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    this->window = glfwCreateWindow(this->Window_Width,this->window_Height, title, NULL, NULL);

    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
    glfwSetFramebufferSizeCallback(this->window, GameEngine::frameBuffer_resize_callback);

    //glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    //Important, needs to happen before loading GLEW.
    glfwMakeContextCurrent(this->window);
}

void GameEngine::InitiateEngine()
{
    //Initiate GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    //Initiate Options
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_FRONT);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Initiate MAtricies
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, this->nearPlane, this->farPlane);

    //Initiate Shader
    this->shaders.push_back(new Shader(this->GL_Version_Major, this->GL_Version_Minor, "vertex_core.glsl", "fragment_core.glsl"));
}

//Initialise Textures
void GameEngine::initTextures()
{
    //Texture 0
    this->textures.push_back(new Texture ("Images/Pine.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/PineSpecular.png", GL_TEXTURE_2D));

    //Texture 1
    //The grey texture from the hovercraft was extracted from this picture 
    //https://www.google.com/search?q=metal+seamless+texture&sxsrf=ALeKk03zMflO0UGqnOYUd2mampCquKH2SQ:1585274046976&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjA88ODxrnoAhWVEMAKHflTDxMQ_AUoAXoECA4QAw&biw=1920&bih=981#imgrc=OIcILsuru55BnM

    this->textures.push_back(new Texture("Images/Hovercraft.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/HovercraftSpecular.png", GL_TEXTURE_2D));

    //Texture 3
    //The texture used for the skybox was extracted taken from this picture
    //https://www.google.com/search?q=night+sky+seamless+texture&sxsrf=ALeKk00BRaCi0bCcTovXnjal44ji7nNyZQ:1585275133853&tbm=isch&source=iu&ictx=1&fir=cxzUI-6sGX9R7M%253A%252COAtNz4qvGkfkLM%252C_&vet=1&usg=AI4_-kRTgO6fXflX7EFCcArYh0eovcP63Q&sa=X&ved=2ahUKEwjxyeWJyrnoAhX8QEEAHeb-A-oQ9QEwDnoECAoQOA#imgrc=xjMd7Lcio5_OYM&imgdii=Gdr2VnaoQNnY_M

    this->textures.push_back(new Texture("Images/Skybox.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/SkyboxSpecular.png", GL_TEXTURE_2D));

    //Texture 4
    //This texture was extracted from the folowing picture
    //https://www.google.com/search?q=grass+seamless+texture&sxsrf=ALeKk02LGX3FbLFsztbcFi6Btn_JCg5E3Q:1585308693626&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjwwauMx7roAhWygVwKHXwGCugQ_AUoAXoECA4QAw&biw=1920&bih=915#imgrc=IUmBXe93QtkMuM

    this->textures.push_back(new Texture("Images/Grass.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/GrassSpecular.png", GL_TEXTURE_2D));

    //Texture 5
    //This texture was extracted from the folowing picture
    //https://www.google.com/search?q=race+track+texture+seamless&sxsrf=ALeKk01ExvZ5h75m3gFCuuBk7xTZbL9PUw:1585308093800&source=lnms&tbm=isch&sa=X&ved=2ahUKEwjZjanuxLroAhVYilwKHRMjCLoQ_AUoAXoECAwQAw&biw=1920&bih=981#imgrc=trzhbF9W4FTp0M

    this->textures.push_back(new Texture("Images/Track.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/TrackSpecular.png", GL_TEXTURE_2D));

    //Texture 5
    this->textures.push_back(new Texture("Images/Mountain.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/MountainSpecular.png", GL_TEXTURE_2D));

    //Texture 6
    this->textures.push_back(new Texture("Images/Spinner.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/SpinnerSpecular.png", GL_TEXTURE_2D));

    //Texture 6
    this->textures.push_back(new Texture("Images/SplashScreen.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/SplashScreenSpecular.png", GL_TEXTURE_2D));
}

//Initialise Materials
void GameEngine::initMaterials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f),0,1));
}

//Initialise Models
void GameEngine::initModels()
{
    //Creating the Player
    std::vector<Mesh*>player;

    std::vector<Vertex>hovercraft = objectLoader("ObjModels/Hovercraft.obj");

    player.push_back(new Mesh(hovercraft.data(), hovercraft.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.1f)));

    this->models.push_back(new Model(glm::vec3(playerMove), this->materials[0], this->textures[TEX_HOVERCRAFT], this->textures[TEX_HOVERCRAFT_SPECULAR], player));

    for (auto*& i : player)
    {
        delete i;
    }

    //Creating the other flying hovercrafts
    std::vector<Mesh*>hovercraftProps;

    //meshes.push_back(new Mesh(&Pyramid(), glm::vec3(0.f, 0.f, 0.f),glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    hovercraftProps.push_back(new Mesh(hovercraft.data(), hovercraft.size(), NULL, 0, glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.1f)));

    hovercraftProps.push_back(new Mesh(hovercraft.data(), hovercraft.size(), NULL, 0, glm::vec3(-4.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.1f)));

    this->models.push_back(new Model(glm::vec3(0.f,0.f,0.f), this->materials[0], this->textures[TEX_HOVERCRAFT], this->textures[TEX_HOVERCRAFT_SPECULAR], hovercraftProps));

    for (auto*& i : hovercraftProps)
    {
        delete i;
    }

    //Creating the skybox
    std::vector<Mesh*>skyboxMesh;

    std::vector<Vertex>skyBox = objectLoader("ObjModels/Skybox.obj");

    //meshes.push_back(new Mesh(&Pyramid(), glm::vec3(0.f, 0.f, 0.f),glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    skyboxMesh.push_back(new Mesh(skyBox.data(), skyBox.size(),NULL,0, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(50.f)));

    this->models.push_back(new Model(glm::vec3(0.f,0.f,0.f), this->materials[0], this->textures[TEX_SKYBOX], this->textures[TEX_SKYBOX_SPECULAR],skyboxMesh));

    for (auto*& i : skyboxMesh)
    {
        delete i;
    }

    //Creating the grass plane
    std::vector<Mesh*>grassPlaneMesh;

    std::vector<Vertex>grassPlane = objectLoader("ObjModels/GrassPlane.obj");

    grassPlaneMesh.push_back(new Mesh(grassPlane.data(), grassPlane.size(), NULL, 0, glm::vec3(0.f, -2.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(2.f)));

    this->models.push_back(new Model(glm::vec3(0.f, 0.f, 0.f), this->materials[0], this->textures[TEX_GRASS], this->textures[TEX_GRASS_SPECULAR], grassPlaneMesh));

    for (auto*& i : grassPlaneMesh)
    {
        delete i;
    }

    //Creating the Mountains
    std::vector<Mesh*>Mountains;

    std::vector<Vertex>Mountain = objectLoader("ObjModels/Mountain.obj");

    Mountains.push_back(new Mesh(Mountain.data(), Mountain.size(), NULL, 0, glm::vec3(0.f, -2.3f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(2.f)));

    this->models.push_back(new Model(glm::vec3(0.f, 0.f, 0.f), this->materials[0], this->textures[TEX_MOUNTAIN], this->textures[TEX_MOUNTAIN_SPECULAR], Mountains));

    for (auto*& i : Mountains)
    {
        delete i;
    }

    //Creating the Track
    std::vector<Mesh*>raceTrack;

    std::vector<Vertex>track = objectLoader("ObjModels/RaceTrack.obj");

    raceTrack.push_back(new Mesh(track.data(), track.size(), NULL, 0, glm::vec3(0.f, -2.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.4f)));

    this->models.push_back(new Model(glm::vec3(0.f, 0.f, 0.f), this->materials[0], this->textures[TEX_TRACK], this->textures[TEX_TRACK_SPECULAR], raceTrack));

    for (auto*& i : raceTrack)
    {
        delete i;
    }

    //Placing Trees
    std::vector<Mesh*>trees;

    std::vector<Vertex>tree = objectLoader("ObjModels/Pine.obj");

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(-3.f, -1.95f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(0.f, -1.95f, -2.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(-3.f, -1.95f, 2.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(3.f, -1.95f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(3.2f, -1.95f, 2.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(4.f, -1.95f, 4.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    trees.push_back(new Mesh(tree.data(), tree.size(), NULL, 0, glm::vec3(4.f, -1.95f, -4.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(.1f)));

    this->models.push_back(new Model(glm::vec3(0.f, 0.f, 0.f), this->materials[0], this->textures[TEX_PINE], this->textures[TEX_PINE_SPECULAR], trees));

    for (auto*& i : trees)
    {
        delete i;
    }

    //Creating the Spinner
    std::vector<Mesh*>wheels;

    std::vector<Vertex>wheel = objectLoader("ObjModels/MassiveSpinnyWheel.obj");

    wheels.push_back(new Mesh(wheel.data(), wheel.size(), NULL, 0, glm::vec3(-3.f, 0.f, -2.f), glm::vec3(0.f), glm::vec3(0.f,-40.f,0.f), glm::vec3(4.f)));

    this->models.push_back(new Model(glm::vec3(-3.f, -2.3f, -2.f), this->materials[0], this->textures[TEX_SPINNER], this->textures[TEX_SPINNER_SPECULAR], wheels));

    for (auto*& i : wheels)
    {
        delete i;
    }

    //Creating the Plane
    std::vector<Mesh*>Plane;

    Plane.push_back(new Mesh(&Quad(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f)));

    this->models.push_back(new Model(glm::vec3(0.f, 0.f, 0.f), this->materials[0], this->textures[TEX_SPLASH], this->textures[TEX_SPLASH_SPECULAR], Plane));

    for (auto*& i : Plane)
    {
        delete i;
    }
}

//Initialise Lights in scene
void GameEngine::initLights()
{
    this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

//Initialise Uniforms
void GameEngine::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void GameEngine::updateUniforms()
{
    //Update Camera
    UpdateCamera();

    //Update framebuffer size and projection matrix
    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

    ProjectionMatrix = glm::mat4(1.f);
    ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, this->nearPlane, this->farPlane);

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
}

void GameEngine::UpdateCamera()
{
    if (camnumber % 2 == 0)
    {
        camLook = camPosition;
        std::cout << camPosition.x<<" "<<camPosition.y<<" "<<camPosition.z<< "\r";
    }
    else if (camnumber % 2 != 0)
    {
        camLook = glm::vec3(0.f, 0.03f, 6.9f);
    }

    this->ViewMatrix = glm::lookAt(this->camLook, this->camLook + this->camFront, this->worldUp);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
}

//Constructors & Distructors
GameEngine::GameEngine(const char* title, const int Window_Width, const int Window_Height, const int GL_Version_Major, const int GL_Version_Minor, bool resizable
)
    : Window_Width(Window_Width),window_Height(Window_Height), GL_Version_Major(GL_Version_Major),GL_Version_Minor(GL_Version_Minor)
{
    //Init variables
    this->frameBufferHeight = this->window_Height;
    this->frameBufferWidth = this->Window_Width;
    this->window = nullptr;

    this->camPosition = glm::vec3(0.f, 0.f, 1.f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3 (0.f, 0.f, -1.f);

    this->fov = 90.f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.f;

    //Run all the initialisation functions
	this->initGLFWWindow(title,resizable);
    this->InitiateEngine();

    this->initTextures();
    this->initMaterials();
    this->initModels();
    this->initLights();
    this->initUniforms();
}

GameEngine::~GameEngine()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    //Delete the elements vectors
    for (size_t i = 0; i < this->shaders.size(); i++)
    {
        delete this->shaders[i];
    }

    for (size_t i = 0; i < this->textures.size(); i++)
    {
        delete this->textures[i];
    }

    for (size_t i = 0; i < this->materials.size(); i++)
    {
        delete this->materials[i];
    }

    for (auto*& i : this->models)
    {
        delete i;
    }

    for (size_t i = 0; i < this->lights.size(); i++)
    {
        delete this->lights[i];
    }
}

//Accessor
int GameEngine::GetWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

//Modifiers
void GameEngine::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions
void GameEngine::update()
{
    //Update input
    glfwPollEvents();

    //Moving the camera
    this->UpdateCameraInput();

    //Moving the player
    this->UpdatePlayerInput();

    //Other input functions
    this->CloseWindow();

    //Animate models
    modelAnimations();

}

void GameEngine::render()
{
    //Update--
    //updateInput(window);

    //Draw--
    //Clear
    glClearColor(0.f, 0.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Update the uniforms
    this->updateUniforms();

    //Rendering the models
    for (auto& i : this->models)
    {
        i->render(this->shaders[SHADER_CORE_PROGRAM]);
    }

    //End draw
    glfwSwapBuffers(window);
    glFlush();

    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::frameBuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}

//Camera movement function
void GameEngine::UpdateCameraInput()
{
    //Z axys
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        this->camPosition.z -= 0.01f;
    }

    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        this->camPosition.z += 0.01f;
    }

    //X axys
    if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        this->camPosition.x -= 0.01f;
    }

    if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        this->camPosition.x += 0.01f;
    }

    //Y axys
    if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
    {
        this->camPosition.y += 0.005f;
    }

    if (glfwGetKey(this->window, GLFW_KEY_V) == GLFW_PRESS)
    {
        this->camPosition.y -= 0.005f;
    }

    //Camera change
    if (glfwGetKey(this->window, GLFW_KEY_M) == GLFW_PRESS)
    {
        camnumber++;

        //wait before inputing anything else
        glfwWaitEventsTimeout(0.7);
    }
}

//Player input
void GameEngine::UpdatePlayerInput()
{
    //y axys rotate
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        models[0]->move(glm::vec3(0.f, 0.f, -0.001f));

        models[0]->moveModel(glm::vec3(0.f, 0.f, -0.001f));

        models[0]->rotate(glm::vec3(0.f, 0.05f, 0.f));
    }

    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        models[0]->move(glm::vec3(0.f, 0.f, 0.001f));

        models[0]->moveModel(glm::vec3(0.f, 0.f, 0.001f));

        models[0]->rotate(glm::vec3(0.f, -0.05f, 0.f));
    }

    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        models[0]->move(glm::vec3(-0.001f, 0.f, -0.f));

        models[0]->moveModel(glm::vec3(-0.001f, 0.f, -0.f));

        models[0]->rotate(glm::vec3(0.f, 0.05f, 0.f));
    }

    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        models[0]->move(glm::vec3(0.001f, 0.0f, 0.f));

        models[0]->moveModel(glm::vec3(0.001f, 0.0f, 0.f));

        models[0]->rotate(glm::vec3(0.f, -0.05f, 0.f));
    }

    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        models[8]->~Model();
    }
}

void GameEngine::modelAnimations()
{
    //Rotate Flying hovercrafts
    models[1]->rotate(glm::vec3(0.f, 0.05f, 0.f));
}

//Other input functions
void GameEngine::CloseWindow()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwWindowShouldClose(this->window);
    }
}
