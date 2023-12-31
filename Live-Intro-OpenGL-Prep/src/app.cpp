#include "app.h"
#include <cstdio>
#include < stdio.h >
#include <cwchar>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_FREE
//Loads the textures
GLuint App::LoadTexture(const char* filename, GLuint width, GLuint height, bool isAlpha)
{
    //Opening file in binary
    std::ifstream texture(filename, std::ios::binary);
    //Checking if it worked
    if (!texture.is_open())
    {
        std::cout << "Error! Couldn't open file." << std::endl;
        return 0;
    }
    
    int type = 0;
    GLint format = GL_RGB;
    char c = texture.get();
    //Check if file is neither PBM or BMP
    if (c != 'P' && c != 'B')
    {
        std::cout << "Error! File " << filename << " doesn't start with P or B!" << std::endl; 
        return 0;
    }
    
    //Find the type of texture
    switch (texture.get())
    {
        case '4':
            format = GL_LUMINANCE;
            type = 4;
            break;
        case 'M':
            format = GL_RGB;
            type = 0;
    }

    //If the texture is PBM
    if (type == 4)
    {
        for (char nara = texture.get(); nara != '\n'; nara = texture.get())
        {
            std::cout << nara << std::endl;;
        };
       
        width = texture.get() - '0';
        texture.get();
        height = texture.get() - '0';
        texture.get();
        char* data = new char[width * height];
        char* data_ = data;
        #if n
        for  (int i = 0; !texture.eof() && i < width + height; )
        {
            char hex = texture.get();

            if (hex == EOF)
                break;
            printf("%x\n", hex);
            printf("%d\n", i);
            for (int j = 7; j >= width; j--)
            {
                *data_++ = hex & (1 << j) ? 0 : 0xFF;
                i++;
                if (i >= width * height)
                    break;
            }
            printf("%d\n", i);
        }
        #endif

        for (int y = 0; y < height; y++)
        {
            char hex = texture.get();
            printf("%x\n", hex);
            for (int x = 7; x >= width; --x)
            {
                if (hex == EOF)
                    break;
                unsigned char test = hex & (1 << x) ? 0x00 : 0xFF;
                *data_ = test;
                printf("d:%u\n", (unsigned int)*data_);
                data_++;
            }
        }

        printf("Diff: %x\n", data_ - data);

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        GLuint texture_map;
        glGenTextures(1, &texture_map);
        glBindTexture(GL_TEXTURE_2D, texture_map);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        texture.close();

        delete[] data;

        return texture_map;
    }
    //If the texture is BMP
    else if (type == 0)
    {
        //Closing and reopening the file resets the pointer. It still works without but it causes color issues.
        texture.close();
        std::ifstream texture(filename, std::ios::binary);
        GLuint texmap;
        char* data;
        int colorChannels = 3;
        if (isAlpha)
        {
            colorChannels = 4;
            format = GL_RGBA;
        }
        //Since the whole data is already almost good, I just send everything to the data buffer
        data = (char*)malloc(width * height * colorChannels);
        texture.read(data, width * height * colorChannels);
        texture.close();

        

        //This part wouldn't exist if BMP switched red and blue.
        //This parts simply switch back red and blue to follow the RGB format.
        for (int i = 0; i < width * height; ++i)
        {
            unsigned char blue, red;
            blue = data[i * colorChannels];
            red = data[i * colorChannels + 2];
            data[i * colorChannels] = red;
            data[i * colorChannels + 2] = blue;
        }

        glGenTextures(1, &texmap);
        glBindTexture(GL_TEXTURE_2D, texmap);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        free(data);

        return texmap;
    }

}

//WARNING!!
//This part was done after the project was finished. It is not meant to be marked.
GLuint App::LoadTexturePNG(const char* filename)
{
    int x, y, n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 4);
    // ... process data if not NULL ...
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
    GLuint texmap;
    glGenTextures(1, &texmap);
    glBindTexture(GL_TEXTURE_2D, texmap);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, n, x, y, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return texmap;
}

void App::Update()
{
    if (ImGui::IsKeyDown(ImGuiKey_1))
        currentExercise = 1;
    if (ImGui::IsKeyDown(ImGuiKey_2))
        currentExercise = 2;
    if (ImGui::IsKeyDown(ImGuiKey_3))
        currentExercise = 3;
    if (ImGui::IsKeyDown(ImGuiKey_4))
        currentExercise = 4;
    if (ImGui::IsKeyDown(ImGuiKey_5))
        currentExercise = 5;

    GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat  shininess = 1;
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

    switch (currentExercise)
    {
    
    case 4: //Lighting is already enabled
        glEnable(GL_LIGHTING);
    case 2: //You can already move the camera, no matter the exercise.
    case 1 :
        //Gizmo
        glPushMatrix();
        glTranslatef(0, 0, -6.f);
        draw::drawGizmo();
        glPopMatrix();

        //Cone
        glPushMatrix();
        glTranslatef(1, -1, -3.f);
        glRotatef(angle, 1.0f, 1.0f, 0.f);
        draw::drawCone(5);
        glPopMatrix();

        //Sphere
        glPushMatrix();
        glTranslatef(-1.0, 1.0, -3.f);
        glRotatef(angle, 1.0, 0.0f, 1.0f);
        draw::drawSphere(35, 35); //ACTUAL SPHERE DRAWING
        glPopMatrix();


        //Cube
        glPushMatrix();
        glTranslatef(2.0, 2.0, -5.f);
        glRotatef(angle, 1.0, 0.0f, 1.0f);
        draw::drawCube(10, 10, 30); //ACTUAL CUBE DRAWING
        glPopMatrix();


        //Quad
        //2D Shapes aren't rotating for visual clarity reasons.
        glPushMatrix();
        glTranslatef(0.0, 2.0, -7.f);
        draw::drawQuad(0.5f); //Actual Quad Drawing
        glPopMatrix();

        //Triangle
        //2D Shapes aren't rotating for visual clarity reasons.
        glPushMatrix();
        glTranslatef(0, -1.5f, -5.f);
        draw::drawTriangle();
        glPopMatrix();

        //Point Sphere
        glPushMatrix();
        glTranslatef(-1.0, -1.0, -3.f);
        glRotatef(angle, 1.0, 0.0f, 1.0f);
        draw::drawPointSphere(50, 50); //Actual Point Sphere Drawing
        glPopMatrix();
        break;
    
    case 3:
        glBindTexture(GL_TEXTURE_2D, tex[1]);
        glPushMatrix();
        glTranslatef(0.0, 2.0, -7.f);
        draw::drawQuad(0.5f); //Actual Quad Drawing
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);

        draw::drawCubeNoRes({ -4, -2, -7 }, { -2, 0, -5 }, { 1,1,1 }, tex[1], true); 
        break;
    
    case 5:
        glEnable(GL_LIGHTING);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
        glMateriali(GL_FRONT, GL_SHININESS, shininess);
        draw::drawMaze(tex[0]);
    default:
        break;
    }
}