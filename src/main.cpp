#include "Headers/Headers.hpp"

#include "Entity/Entity.hpp"

#include "Entity/Components/Color.hpp"
#include "Entity/Components/Transform.hpp"
#include "Entity/Components/BorderRadius.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    int size = (width < height) ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "GLFW Window Cannot Create\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "GLAD Cannot Load\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Eclipt::Entity *entity = new Eclipt::Entity();

    Eclipt::Color *color = new Eclipt::Color();
    color->setBackgroundColor(1, 1, 0, 1);

    entity->addComponent(color);

    Eclipt::Transform *transform = new Eclipt::Transform();
    transform->setPosition(Eclipt::QTX::Vec3(0, 0, 0));
    transform->setScale(Eclipt::QTX::Vec3(0.1f, 0.1f, 0));

    entity->addComponent(transform);

    Eclipt::BorderRadius *borderRadius = new Eclipt::BorderRadius();
    borderRadius->setBorderRadius(0.3f);

    entity->addComponent(borderRadius);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        transform->setRotation(Eclipt::QTX::Vec3(0, 0, transform->getEntity()->rotation.getZ() + 0.5f));
        // RENDER HERE
        entity->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
