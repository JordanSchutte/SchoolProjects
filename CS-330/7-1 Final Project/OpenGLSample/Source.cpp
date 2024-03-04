#include <iostream>             // cout, cerr
#include <cstdlib>              // EXIT_FAILURE
#include <glad/glad.h>
#include <GLFW/glfw3.h>         // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h" // Camera class

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "4-5 Lamp v2"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbos[2];         // Handle for the vertex buffer object
        GLuint nIndices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // mesh data
    GLMesh planeMesh;
    GLMesh gMesh;
    GLMesh poleMesh;
    GLMesh bulbMesh;
    GLMesh baseMesh;
    // Shader program
    GLuint gProgramId;

    // Textures
    GLuint texturePlaneID;
    GLuint textureLampshadeID;
    GLuint texturePoleID;
    GLuint textureBaseID;

    // camera
    Camera gCamera(glm::vec3(0.0f, 3.0f, 10.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Global variable to track the current projection mode
    bool isPerspective = true;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void UCreateMesh(GLMesh& mesh);
void UCreatePlane(GLMesh& mesh);
void UCreatePole(GLMesh& mesh);
void UCreateBulb(GLMesh& mesh);
void UCreateBase(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
bool UCreateTexture(const char* filename, GLuint& textureId);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);

float gCameraSpeed = 2.5f; // Default speed


/* Vertex Shader Source Code*/
const GLchar* vertexShaderSource = GLSL(440,
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;
    layout(location = 2) in vec2 textureCoordinate;

    out vec3 vertexColor;
    out vec2 vertexTextureCoordinate;
    out vec3 FragPos;
    out vec3 Normal;

    //Global variables for the transform matrices
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

void main()
{
    // Your existing transformation code
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // Output the transformed normal
    Normal = mat3(transpose(inverse(model))) * vec3(color); // Assuming 'color' holds your normal data, which might not be correct. Adjust as needed.

    // Output the transformed position
    FragPos = vec3(model * vec4(position, 1.0f));
    vertexColor = color;
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Fragment Shader Source Code*/
const GLchar* fragmentShaderSource = GLSL(440,
    in vec3 vertexColor;
    in vec2 vertexTextureCoordinate;
    // Fragment shader
    in vec3 Normal;
    in vec3 FragPos;

    out vec4 fragmentColor;

    uniform sampler2D uTexture;

    uniform vec3 keyLightPos; // Key light position
    uniform vec3 keyLightColor; // Key light color
    uniform vec3 objectColor; // Object color

    uniform bool isBulb;

    void main()
    {
        // Ambient light
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * keyLightColor;

        // Diffuse light
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(keyLightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * keyLightColor;

        // Texture color
        vec4 texColor = texture(uTexture, vertexTextureCoordinate);

        // Combine the two components and multiply by texture color
        // If you want the object's color to affect the texture, multiply by objectColor as well
        vec3 result = (ambient + diffuse) * texColor.xyz; // Multiply by objectColor if needed

        if(isBulb)
    {
        fragmentColor = vec4(1.0, 1.0, 1.0, 1.0); // Render white if it's the bulb
    }
    else
    {
        fragmentColor = texture(uTexture, vertexTextureCoordinate); // Original texture rendering
    }
    }
);

// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so let's flip it
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}

int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    UCreateMesh(gMesh); // Calls the function to create the Vertex Buffer Object
    UCreatePlane(planeMesh);
    UCreatePole(poleMesh);
    UCreateBulb(bulbMesh);
    UCreateBase(baseMesh);

    // Create the shader program
    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    // Load Textures
    if (!UCreateTexture("planeTexture.png", texturePlaneID))
    {
        cout << "Failed to load plane texture" << endl;
    }
    if (!UCreateTexture("lampTexture.png", textureLampshadeID))
    {
        cout << "Failed to load lampshade texture" << endl;
    }
    if (!UCreateTexture("poleTexture.png", texturePoleID))
    {
        cout << "Failed to load pole texture" << endl;
    }
    if (!UCreateTexture("baseTexture.png", textureBaseID))
    {
        cout << "Failed to load base texture" << endl;
    }


    // Create the shader program
    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(gMesh);

    // Release shader program
    UDestroyShaderProgram(gProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // GLAD: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window) {
    static const float cameraSpeed = 0.25f * gDeltaTime; // Ensure gDeltaTime is updated each frame
    static bool pKeyPressed = false; // Track the state of the 'P' key press

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    // Up and Down movement
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.Position += cameraSpeed * gCamera.Up;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.Position -= cameraSpeed * gCamera.Up;

    // Toggle between perspective and orthographic projection
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pKeyPressed) {
        isPerspective = !isPerspective; // Toggle the projection mode
        pKeyPressed = true; // Mark the 'P' key as pressed
    }
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
        pKeyPressed = false; // Reset the 'P' key state when released
    }
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Adjust the camera's speed based on scroll input
    gCameraSpeed += static_cast<float>(yoffset) * 0.1f; // Adjust the multiplier as needed for sensitivity

    // Clamp the camera speed to a minimum and maximum value if desired
    if (gCameraSpeed < 0.1f)
        gCameraSpeed = 0.1f;
    if (gCameraSpeed > 10.0f)
        gCameraSpeed = 10.0f;
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}


// Function called to render a frame
void URender()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = gCamera.GetViewMatrix();
    glm::mat4 projection;
    if (isPerspective) {
        projection = glm::perspective(glm::radians(gCamera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    }
    else {
        projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    }

    glUseProgram(gProgramId);

    // Set up key light properties
    glm::vec3 keyLightPos = glm::vec3(0.0f, 3.3f, 0.0f); // Example position inside the lamp
    glm::vec3 keyLightColor = glm::vec3(1.0f, 1.0f, 1.0f); // White light

    GLuint keyLightPosLoc = glGetUniformLocation(gProgramId, "keyLightPos");
    GLuint keyLightColorLoc = glGetUniformLocation(gProgramId, "keyLightColor");
    GLuint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");

    glUniform3f(keyLightPosLoc, keyLightPos.x, keyLightPos.y, keyLightPos.z);
    glUniform3f(keyLightColorLoc, keyLightColor.x, keyLightColor.y, keyLightColor.z);
    glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f); // Assuming the object color is white


    GLint modelLoc = glGetUniformLocation(gProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gProgramId, "view");
    GLint projLoc = glGetUniformLocation(gProgramId, "projection");
    GLint textureLoc = glGetUniformLocation(gProgramId, "uTexture");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Render the plane with its texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePlaneID);
    glm::mat4 planeModel = glm::mat4(1.0f);
    planeModel = glm::scale(planeModel, glm::vec3(5.0f, 0.0f, 5.0f));
    planeModel = glm::translate(planeModel, glm::vec3(0.0f, 0.75f, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(planeModel));
    glBindVertexArray(planeMesh.vao);
    glDrawElements(GL_TRIANGLES, planeMesh.nIndices, GL_UNSIGNED_SHORT, 0);

    // Render the Lampshade with its texture
    glBindTexture(GL_TEXTURE_2D, textureLampshadeID);
    glm::mat4 lampshadeModel = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lampshadeModel));
    glBindVertexArray(gMesh.vao);
    glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, 0);

    // Render the pole with its texture
    glBindTexture(GL_TEXTURE_2D, texturePoleID);
    glm::mat4 poleModel = glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(poleModel));
    glBindVertexArray(poleMesh.vao);
    glDrawElements(GL_TRIANGLES, poleMesh.nIndices, GL_UNSIGNED_SHORT, 0);

    // Draw the bulb mesh
    GLint isBulbLoc = glGetUniformLocation(gProgramId, "isBulb");
    glUniform1i(isBulbLoc, GL_TRUE); // Tell the shader it's rendering the bulb

    glBindVertexArray(bulbMesh.vao);
    glm::mat4 bulbModel = glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)) * glm::scale(glm::vec3(0.5f)); // Scale the bulb mesh as needed
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bulbModel));
    glDrawArrays(GL_TRIANGLES, 0, bulbMesh.nIndices);
    glBindVertexArray(0); // Unbind the VAO

    glUniform1i(isBulbLoc, GL_FALSE);

    // Render the base with its texture
    glBindTexture(GL_TEXTURE_2D, textureBaseID);
    glm::mat4 baseModel = glm::mat4(1.0f);
    baseModel = glm::scale(baseModel, glm::vec3(1.0f, 0.2f, 1.0f));
    baseModel = glm::translate(baseModel, glm::vec3(0.0f, 0.75f, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(baseModel));
    glBindVertexArray(baseMesh.vao);
    glDrawElements(GL_TRIANGLES, baseMesh.nIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glfwSwapBuffers(gWindow);
}



// Implements the UCreateMesh function
void UCreateMesh(GLMesh& mesh)
{
    const GLuint precision = 36; // Number of slices
    const GLfloat height = 1.0f; // Height of the lampshade
    const GLfloat bottomRadius = 0.5f; // Bottom radius of the lampshade
    const GLfloat topRadius = 0.25f; // Top radius of the lampshade (smaller for a cone effect)
    const GLfloat yOffset = 1.6f; // Height offset from the ground

    std::vector<GLfloat> vertices;
    std::vector<GLushort> indices;

    // Create vertices
    for (GLuint i = 0; i <= precision; ++i) {
        GLfloat angle = 2.0f * M_PI * i / precision;

        // Explicitly cast the result of cos and sin to GLfloat
        GLfloat cosValue = static_cast<GLfloat>(cos(angle));
        GLfloat sinValue = static_cast<GLfloat>(sin(angle));

        // Bottom circle vertex
        vertices.push_back(bottomRadius * cosValue); // x
        vertices.push_back(0.0f + yOffset); // y
        vertices.push_back(bottomRadius * sinValue); // z
        vertices.push_back(1.0f); // Color (R)
        vertices.push_back(1.0f); // Color (G)
        vertices.push_back(1.0f); // Color (B)

        // Top circle vertex
        vertices.push_back(topRadius * cosValue); // x
        vertices.push_back(height + yOffset); // y
        vertices.push_back(topRadius * sinValue); // z
        vertices.push_back(1.0f); // Color (R)
        vertices.push_back(1.0f); // Color (G)
        vertices.push_back(1.0f); // Color (B)
    }

    // Create indices
    for (GLuint i = 0; i < precision; ++i) {
        indices.push_back(2 * i);
        indices.push_back(2 * i + 1);
        indices.push_back(2 * ((i + 1) % precision));
        indices.push_back(2 * ((i + 1) % precision));
        indices.push_back(2 * i + 1);
        indices.push_back(2 * ((i + 1) % precision) + 1);
    }

    // Create and bind VAO
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Create VBOs and send the data to the GPU
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    mesh.nIndices = static_cast<GLuint>(indices.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

    // Set up vertex attribute pointers
    GLint stride = 6 * sizeof(GLfloat); // 3 for vertex coords, 3 for color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UCreatePlane(GLMesh& mesh) {
    GLfloat baseVertices[] = {
        // Positions          // Colors
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back bottom left
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back bottom right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back top right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back top left
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front bottom left
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front bottom right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front top right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front top left
    };

    // Define indices for 12 triangles (two per face)
    GLuint baseIndices[] = {
        // Back face
        0, 1, 2, 0, 2, 3,
        // Front face
        4, 5, 6, 4, 6, 7,
        // Left face
        0, 4, 7, 0, 7, 3,
        // Right face
        1, 5, 6, 1, 6, 2,
        // Top face
        3, 2, 6, 3, 6, 7,
        // Bottom face
        0, 1, 5, 0, 5, 4
    };

    // Generate and bind VAO and VBO for vertices
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);
    glGenBuffers(2, mesh.vbos);

    // Buffer for vertices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);

    // Buffer for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(baseIndices), baseIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Update mesh.nIndices for rendering
    mesh.nIndices = sizeof(baseIndices);
}

void UCreatePole(GLMesh& mesh) {
    const GLuint segments = 36; // Number of segments for the circle
    const float radius = 0.05f; // Pole radius
    const float height = 1.5f; // Pole height
    const float halfHeight = height * 0.5f;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    // Calculate vertices for the top and bottom caps and the side surface
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Top vertex
        vertices.push_back(x);
        vertices.push_back(halfHeight);
        vertices.push_back(z);
        vertices.push_back(1.0f); // Color (R)
        vertices.push_back(1.0f); // Color (G)
        vertices.push_back(1.0f); // Color (B)

        // Bottom vertex
        vertices.push_back(x);
        vertices.push_back(-halfHeight);
        vertices.push_back(z);
        vertices.push_back(1.0f); // Color (R)
        vertices.push_back(1.0f); // Color (G)
        vertices.push_back(1.0f); // Color (B)
    }

    // Top cap indices
    GLuint centerTopIndex = segments * 2;
    for (GLuint i = 0; i < segments; ++i) {
        indices.push_back(i * 2);
        indices.push_back((i * 2 + 2) % (segments * 2));
        indices.push_back(centerTopIndex);
    }

    // Bottom cap indices
    GLuint centerBottomIndex = centerTopIndex + 1;
    for (GLuint i = 0; i < segments; ++i) {
        indices.push_back(i * 2 + 1);
        indices.push_back((i * 2 + 3) % (segments * 2) + 1);
        indices.push_back(centerBottomIndex);
    }

    // Side indices
    for (GLuint i = 0; i < segments; ++i) {
        indices.push_back(i * 2);
        indices.push_back((i * 2 + 2) % (segments * 2));
        indices.push_back(i * 2 + 1);

        indices.push_back(i * 2 + 1);
        indices.push_back((i * 2 + 2) % (segments * 2));
        indices.push_back((i * 2 + 3) % (segments * 2) + 1);
    }

    // Create and bind VAO
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Create VBOs and send the data to the GPU
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    mesh.nIndices = static_cast<GLuint>(indices.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

    // Set up vertex attribute pointers
    GLint stride = 6 * sizeof(GLfloat); // 3 for vertex coords, 3 for color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UCreateBulb(GLMesh& mesh) {
    float radius = 0.2f; // Radius of the bulb
    unsigned int latitudeBands = 20;
    unsigned int longitudeBands = 20;
    float poleHeight = 1.5f;
    float bulbHeightOffset = poleHeight + radius; // Place bulb on top of the pole

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    // Generate sphere vertices and indices
    for (unsigned int latNumber = 0; latNumber <= latitudeBands; ++latNumber) {
        for (unsigned int longNumber = 0; longNumber <= longitudeBands; ++longNumber) {
            float theta = M_PI * latNumber / latitudeBands;
            float phi = 2 * M_PI * longNumber / longitudeBands;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            float u = 1 - (float(longNumber) / longitudeBands);
            float v = 1 - (float(latNumber) / latitudeBands);

            vertices.push_back(radius * x);
            vertices.push_back(radius * y + bulbHeightOffset);
            vertices.push_back(radius * z);
            vertices.push_back(1.0f); // Color (R)
            vertices.push_back(1.0f); // Color (G)
            vertices.push_back(1.0f); // Color (B)
            vertices.push_back(u);    // Texture U
            vertices.push_back(v);    // Texture V
        }
    }

    // Generate indices
    for (unsigned int latNumber = 0; latNumber < latitudeBands; ++latNumber) {
        for (unsigned int longNumber = 0; longNumber < longitudeBands; ++longNumber) {
            unsigned int first = (latNumber * (longitudeBands + 1)) + longNumber;
            unsigned int second = first + longitudeBands + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    // Create and bind VAO
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Create VBO for vertices
    glGenBuffers(1, &mesh.vbos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Create EBO for indices
    glGenBuffers(1, &mesh.vbos[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);

    mesh.nIndices = indices.size(); // Update mesh indices count
}

void UCreateBase(GLMesh& mesh) {
    GLfloat baseVertices[] = {
        // Positions          // Colors
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back bottom left
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back bottom right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back top right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Back top left
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front bottom left
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front bottom right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front top right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Front top left
    };

    // Define indices for 12 triangles (two per face)
    GLuint baseIndices[] = {
        // Back face
        0, 1, 2, 0, 2, 3,
        // Front face
        4, 5, 6, 4, 6, 7,
        // Left face
        0, 4, 7, 0, 7, 3,
        // Right face
        1, 5, 6, 1, 6, 2,
        // Top face
        3, 2, 6, 3, 6, 7,
        // Bottom face
        0, 1, 5, 0, 5, 4
    };

    // Generate and bind VAO and VBO for vertices
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);
    glGenBuffers(2, mesh.vbos);

    // Buffer for vertices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);

    // Buffer for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(baseIndices), baseIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Update mesh.nIndices for rendering
    mesh.nIndices = sizeof(baseIndices) / sizeof(baseIndices[0]);
}

void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}

/*Generate and load the texture*/
bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}

void UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}

// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}

void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}