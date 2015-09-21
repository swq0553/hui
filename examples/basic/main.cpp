#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/glew.h>
#include <GL/glu.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "include/hui.h"

#include "gl_render_handler.h"


class MyRoute : public HUI::Route {
public:
    MyRoute(void) : HUI::Route(std::regex("basic_html")) {
        //
    }


    HUI::Response *HandleRequest(std::string url, std::string method,
                            std::vector<std::pair<std::string, std::string> > get,
                            std::vector<std::pair<std::string, std::string> > post) {
        return new HUI::Response("text/html", "Made it");
    }
};

class MyRESTRoute : public HUI::RESTRoute {
public:
    MyRESTRoute(void) : HUI::RESTRoute(std::regex("basic_rest")) {
        //
    }

    HUI::Response *Get(std::string id) {
        return new HUI::Response("text/html", "Weeeeeeee " + id);
    }

    HUI::Response *Post(std::vector<std::pair<std::string, std::string> > post) {
        std::vector<std::pair<std::string, std::string> >::iterator post_iter = post.begin();
        while (post_iter != post.end()) {
            std::pair<std::string, std::string> p = (*post_iter);
            return new HUI::Response("text/html", p.second + " was posted");
            ++post_iter;
        }
        return new HUI::Response("text/html", "ERROR");
    }

    HUI::Response *Put(std::string id, std::vector<std::pair<std::string, std::string> > post) {
        std::vector<std::pair<std::string, std::string> >::iterator post_iter = post.begin();
        while (post_iter != post.end()) {
            std::pair<std::string, std::string> p = (*post_iter);
            return new HUI::Response("text/html", p.second + " was putted with id " + id);
            ++post_iter;
        }
        return new HUI::Response("text/html", "ERROR");
    }

    HUI::Response *Delete(std::string id) {
        return new HUI::Response("text/html", "Deleted ID " + id);
    }
};

class MyJSONRESTRoute : public HUI::JSONRESTRoute {
public:
    MyJSONRESTRoute(void) : HUI::JSONRESTRoute(std::regex("basic_json")) {
        //
    }

    HUI::Response *Get(std::string id) {
        return new HUI::Response("application/json", "{\"id\": \"" + id + "\"}");
    }

    HUI::Response *Post(std::string post_json) {
        return new HUI::Response("application/json", post_json);
    }

    HUI::Response *Put(std::string id, std::string data) {
        return new HUI::Response("application/json", data);//"{\"id\": \"" + id + "\"}");
    }

    HUI::Response *Delete(std::string id) {
        return new HUI::Response("application/json", "{\"id\": \"" + id + "\"}");
    }
};


bool ErrorCheck(std::string prefix) {
    GLenum result = glGetError();
    switch (result){
        case GL_INVALID_ENUM:{
            std::cout << prefix.c_str() << ": GLERROR: Invalid enumeration parameter." << std::endl;
        }break;
        case GL_INVALID_VALUE:{
            std::cout << prefix.c_str() << ": GLERROR: Invalid value parameter." << std::endl;
        }break;
        case GL_INVALID_OPERATION:{
            std::cout << prefix.c_str() << "()" << ": GLERROR: Invalid method called." << std::endl;
        }break;
        case GL_STACK_OVERFLOW:{
            std::cout << prefix.c_str() << ": GLERROR: Stack overflow." << std::endl;
        }break;
        case GL_STACK_UNDERFLOW:{
            std::cout << prefix.c_str() << ": GLERROR: Stack underflow." << std::endl;
        }break;
        case GL_OUT_OF_MEMORY:{
            std::cout << prefix.c_str() << ": GLERROR: Out of memory." << std::endl;
        }break;
        case GL_NO_ERROR:{
            return false;
        }break;
        default:{
            std::cout << prefix.c_str() << ": GLERROR: Unknown error." << std::endl;
        }break;
    }
    return true;
}

std::string ShaderShaderLog(unsigned int shader_object_id){
    GLint ret;
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &ret);
    if (ret == true) {
        return "";
    }

    int info_log_length = 0;
    int characters_written  = 0;
    char *info_log;
    std::string out;
    glGetShaderiv(shader_object_id, GL_INFO_LOG_LENGTH, &info_log_length);

    info_log = (char *)malloc(info_log_length);
    glGetShaderInfoLog(shader_object_id, info_log_length, &characters_written, info_log);
    out = std::string(info_log);
    free(info_log);
    return out;
}

class MyJSFunction : public HUI::JSFunction {
    public:
        MyJSFunction(void) : HUI::JSFunction("test_function") {
            //
        }

        HUI::JSValue *Call(std::string _name, HUI::JSObjectValue *obj_this,
                      std::vector<HUI::JSValue *> parameters, std::string exception) {
            return new HUI::JSStringValue("Darf-snarf!");
        }

    private:
};

int main(int argc, char **argv) {
    HUI::RenderProcessHandlerValues values;

    HUI::JSStringValue *str = new HUI::JSStringValue("Test String");
    values["test_string"] = str;

    HUI::JSArrayValue *arr = new HUI::JSArrayValue();
    arr->Push(new HUI::JSStringValue("Array 0"));
    arr->Push(new HUI::JSBoolValue(true));
    arr->Push(new HUI::JSDoubleValue(1.42));
    values["test_array"] = arr;

    HUI::JSObjectValue *obj = new HUI::JSObjectValue();
    obj->Set("sub_value", new HUI::JSStringValue("Weeeeeeeeeee Object Sub-Value"));
    obj->Set("test_function", new MyJSFunction());
    values["test_obj"] = obj;

    int code = HUI::HUI::Init(argc, argv, values);
    if (code >= 0) {
        return code;
    }

    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setActive();

    // HUIOS Init
    GLRenderHandler *render_handler = new GLRenderHandler();
    HUI::HUI *huios = new HUI::HUI(window.getSystemHandle(), render_handler);
    huios->RegisterRoute(new MyRoute());
    huios->RegisterRoute(new MyRESTRoute());
    huios->RegisterRoute(new MyJSONRESTRoute());
    huios->Reshape(1280, 720);
    huios->Load("file:///home/douglas/Projects/huios/examples/basic/assets/index.html");

    // Enable Z-buffer read and write
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    GLuint vao, projection_matrix_location, view_matrix_location, model_matrix_location, gui_texture_location, vbo[2];

    const GLfloat vertices[6][4] = {{0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}};
    const GLfloat texcoords[6][4] = {{0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}};

    GLchar *vertexsource, *fragmentsource;
    GLuint vertexshader, fragmentshader;
    GLuint shaderprogram;

    glewExperimental = GL_TRUE;
    glewInit();

    size_t count = 6 * 4 * sizeof(float);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertices
    glGenBuffers(1, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Texcoords
    glGenBuffers(1, &vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, count, texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    /* Read our shaders into the appropriate buffers */
    vertexsource = (GLchar *)"#version 130\n"
            "uniform mat4 projection_matrix;"
            "uniform mat4 view_matrix;"
            "uniform mat4 model_matrix;"
            "in vec4 vertex_position;"
            "in vec4 vertex_texcoord;"
            "smooth out vec2 texcoord;"
            "smooth out vec4 vertex;"
            "void main() {"
            "    vertex = projection_matrix * view_matrix * model_matrix * vertex_position;"
            "    gl_Position = vertex;"
            "    texcoord = vertex_texcoord.st;"
            "}";
    fragmentsource = (GLchar *)"#version 130\n"
            "smooth in vec2 texcoord;"
            "smooth in vec4 vertex;"
            "uniform sampler2D gui_texture;"
            "out vec4 fragment_output;"
            "void main() {"
            "    vec4 gui_output = texture(gui_texture, vec2(texcoord.x, 1.0 - texcoord.y));"
            "    fragment_output = vec4(gui_output.b, gui_output.g, gui_output.r, gui_output.a);"
            "}";

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
    glCompileShader(vertexshader);

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
    glCompileShader(fragmentshader);

    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);

    glBindAttribLocation(shaderprogram, 0, "vertex_position");
    glBindAttribLocation(shaderprogram, 1, "vertex_texcoord");
    glBindFragDataLocation(shaderprogram, 0, "fragment_output");

    glLinkProgram(shaderprogram);
    glUseProgram(shaderprogram);

    projection_matrix_location = glGetUniformLocation(shaderprogram, "projection_matrix");
    view_matrix_location = glGetUniformLocation(shaderprogram, "view_matrix");
    model_matrix_location = glGetUniformLocation(shaderprogram, "model_matrix");
    gui_texture_location = glGetUniformLocation(shaderprogram, "gui_texture");

    glm::mat4 projection_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 model_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1280.0, 720.0, 1.0));

    // Start game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape key: exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Adjust the viewport when the window is resized
            if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }

            if (event.type == sf::Event::MouseMoved) {
                huios->MouseMove(event.mouseMove.x, event.mouseMove.y);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                huios->MouseButtonPress(HUI::HUI::MB_LEFT);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                huios->MouseButtonRelease(HUI::HUI::MB_LEFT);
            }

//            if (event.type == sf::Event::KeyPressed) {
//                huios->KeyPress(event.key.code);
//            }

//            if (event.type == sf::Event::KeyReleased) {
//                huios->KeyRelease(event.key.code);
//            }

            if (event.type == sf::Event::TextEntered) {
                huios->KeyChar(event.text.unicode);
            }
       }

        // Clear the depth buffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        huios->Update();
        huios->Draw();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, render_handler->GetTextureHandle());
        glUniform1i(gui_texture_location, 0);
        glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, (float *)(glm::value_ptr(projection_matrix)));
        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, (float *)(glm::value_ptr(view_matrix)));
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, (float *)(glm::value_ptr(model_matrix)));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        ErrorCheck("done");

        // Finally, display the rendered frame on screen
        window.display();
    }

    HUI::HUI::Shutdown();

    return EXIT_SUCCESS;
}
