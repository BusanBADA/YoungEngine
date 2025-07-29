
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
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

    // 사각형 정점 데이터 (0,0), (1,0), (1,1), (0,1)
    float vertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    // VAO, VBO 생성
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 위치 속성 설정
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(m_window, &width, &height);
    for (const auto& obj : objects) {
        SDL_FRect* rect = obj->GetRect();
        SDL_Color* color = obj->GetColor();

        // 위치와 크기 (0~1 정규화 좌표 변환은 셰이더에서 수행)
        
        glUniform2f(posLoc, rect->x / width, rect->y / height);
        glUniform2f(sizeLoc, rect->w / width, rect->h / height);

        // 색상 (0~1 범위)
        glUniform4f(colorLoc, color->r / 255.0f, color->g / 255.0f, color->b / 255.0f, color->a / 255.0f);

        // 4개의 정점으로 이루어진 사각형을 그립니다 (삼각형 2개로 쪼개서 그리기)
        // 인덱스 없이 GL_TRIANGLE_FAN 사용 가능
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glBindVertexArray(0);
    glUseProgram(0);
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