#include "Headers/Headers.hpp"

#include "Entity/Entity.hpp"

#include "Entity/Components/Color.hpp"
#include "Entity/Components/Transform.hpp"
#include "Entity/Components/BorderRadius.hpp"
#include "Entity/Components/TextView.hpp"

#include "Core/Widgets/EditText/EditText.hpp"

void framebuffer_size_callback(GLFWwindow * /*window*/, int /*w*/, int /*h*/)
{
    int width = 1920;
    int height = 1080;

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

    Eclipt::Components::Color *color = new Eclipt::Components::Color();
    color->setBackgroundColor(1, 1, 0, 1);

    entity->addComponent(color);

    Eclipt::Components::Transform *transform = new Eclipt::Components::Transform();
    transform->setPosition(Eclipt::QTX::Vec3(0, 0, 0));
    transform->setScale(Eclipt::QTX::Vec3(0.2f, 0.2f, 0));

    entity->addComponent(transform);

    Eclipt::Widgets::EditText *editText = new Eclipt::Widgets::EditText();
    editText->onStart();

    Eclipt::Components::BorderRadius *borderRadius = new Eclipt::Components::BorderRadius();
    borderRadius->setBorderRadius(0.3f);

    entity->addComponent(borderRadius);

    Eclipt::Components::TextView *text = new Eclipt::Components::TextView("Hello World", "fonts/nunito.ttf", 24, 64);
    text->setColor(1, 0, 0, 1);

    entity->addComponent(text);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        processInput(window);

        // transform->setRotation(Eclipt::QTX::Vec3(transform->getEntity()->rotation.getX() + 0.5f, transform->getEntity()->rotation.getY() + 0.5f, transform->getEntity()->rotation.getZ() + 0.5f));

        // RENDER HERE
        entity->draw();
        // editText->onRender();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
