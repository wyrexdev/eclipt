#include "Entity/Entity.hpp"

namespace Eclipt
{
    Entity::Entity() : position(0, 0, 0),
                       rotation(0, 0, 0),
                       scale(0, 0, 0)
    {
        QTX::Color backgroundColor = QTX::Color(255, 255, 255, 255);
        colors.insert({"backgroundColor", backgroundColor});

        shader = Eclipt::Shader();

        for (Eclipt::Component *comp : components)
        {
            comp->start();
        }

        std::string fragSrcStr = shader.loadShader("shaders/Entity/fragment.glsl");
        std::string vertSrcStr = shader.loadShader("shaders/Entity/vertex.glsl");

        const char *fragmentShaderSource = fragSrcStr.c_str();
        const char *vertexShaderSource = vertSrcStr.c_str();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float vertices[] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f};

        int drawOrder[] = {
            0, 1, 2,
            0, 2, 3};

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Entity::~Entity()
    {
        colors.clear();
        components.clear();
    }

    void Entity::draw()
    {
        for (Eclipt::Component *comp : components)
        {
            comp->render();
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int backgroundColorLoc = glGetUniformLocation(shaderProgram, "backgroundColor");
        glUniform4f(backgroundColorLoc, colors.at("backgroundColor").getColor().r, colors.at("backgroundColor").getColor().b, colors.at("backgroundColor").getColor().g, colors.at("backgroundColor").getColor().a);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Entity::addComponent(Eclipt::Component *comp) {
        comp->setEntity(this);
        components.push_back(comp);
    }
}