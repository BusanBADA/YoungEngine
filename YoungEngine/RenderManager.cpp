
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "RenderManager.h"

static std::string LoadShaderSource(const char* filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool RendererManager::Init(SDL_Window* window) {
    m_window = window;

    m_glContext = SDL_GL_CreateContext(window);
    if (!m_glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_MakeCurrent(window, m_glContext);

    if (!gladLoadGL()) {
        std::cerr << "GLAD 초기화 실패!" << std::endl;
        return false;
    }
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    std::string vertexShaderSource = LoadShaderSource("vertex_shader.glsl");
    std::string fragmentShaderSource = LoadShaderSource("fragment_shader.glsl");

    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cerr << "Shader 소스 불러오기 실패!" << std::endl;
        return false;
    }

    const char* vertexShaderSrc = vertexShaderSource.c_str();
    const char* fragmentShaderSrc = fragmentShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader 컴파일 실패: " << infoLog << std::endl;
        return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader 컴파일 실패: " << infoLog << std::endl;
        return false;
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program 링크 실패: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
    0.0f, 0.0f,  0.0f, 0.0f,
    1.0f, 0.0f,  1.0f, 0.0f,
    1.0f, 1.0f,  1.0f, 1.0f,
    0.0f, 1.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 위치 aPos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 텍스처 좌표 aTexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void RendererManager::BeginFrame()
{
    int width, height;
    SDL_GetWindowSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererManager::EndFrame()
{
    SDL_GL_SwapWindow(m_window);
}

void RendererManager::DrawObjects(const std::vector<std::shared_ptr<DrawableObject>>& objects)
{
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);

    GLint posLoc = glGetUniformLocation(m_shaderProgram, "uPosition");
    GLint sizeLoc = glGetUniformLocation(m_shaderProgram, "uSize");
    GLint colorLoc = glGetUniformLocation(m_shaderProgram, "uColor");
    GLint texLoc = glGetUniformLocation(m_shaderProgram, "uTexture");
    GLint uvOffsetLoc = glGetUniformLocation(m_shaderProgram, "uTexOffset");
    GLint uvScaleLoc = glGetUniformLocation(m_shaderProgram, "uTexScale");

    glUniform1i(texLoc, 0); // texture unit 0

    int width = 0, height = 0;
    SDL_GetWindowSize(m_window, &width, &height);

    for (const auto& obj : objects) {
        SDL_FRect* rect = obj->GetRect();
        SDL_Color* color = obj->GetColor();

        glUniform2f(posLoc, rect->x / width, rect->y / height);
        glUniform2f(sizeLoc, rect->w / width, rect->h / height);
        glUniform4f(colorLoc, color->r / 255.0f, color->g / 255.0f, color->b / 255.0f, color->a / 255.0f);

        const glm::vec2& offset = obj->GetTexOffset();
        const glm::vec2& scale = obj->GetTexScale();
        glUniform2f(uvOffsetLoc, offset.x, offset.y);
        glUniform2f(uvScaleLoc, scale.x, scale.y);
        
        if (obj->GetTexture()) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, obj->GetTexture());
        }

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

GLuint RendererManager::LoadTexture(const char* path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texID;
}

void RendererManager::Destroy() {
    if (m_glContext) {
        SDL_GL_DestroyContext(m_glContext);
        m_glContext = nullptr;
    }

    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    if (m_shaderProgram) {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}