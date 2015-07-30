#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "include/huios.h"

#include "gl_render_handler.h"

int main(int argc, char **argv) {
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setActive();

    // HUIOS Init
    GLRenderHandler *render_handler = new GLRenderHandler();
    HUIOS *cefui = new HUIOS(argc, argv, window.getSystemHandle(), render_handler);
    cefui->reshape(800, 600);
//    cefui->load("http://www.google.com");

    // Enable Z-buffer read and write
//    glEnable(GL_DEPTH_TEST);
//    glDepthMask(GL_TRUE);
//    glClearDepth(1.f);

    // Disable lighting
//    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
//    glViewport(0, 0, window.getSize().x, window.getSize().y);

    // Setup a perspective projection
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
//    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    // Create a clock for measuring the time elapsed
//    sf::Clock clock;

    // Start game loop
    while (window.isOpen())
    {
//        // Process events
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // Close window: exit
//            if (event.type == sf::Event::Closed)
//                window.close();

//            // Escape key: exit
//            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
//                window.close();

//            // Adjust the viewport when the window is resized
//            if (event.type == sf::Event::Resized)
//                glViewport(0, 0, event.size.width, event.size.height);
//        }

//        // Clear the depth buffer
//        glClear(GL_DEPTH_BUFFER_BIT);

        cefui->draw();

        // Finally, display the rendered frame on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
