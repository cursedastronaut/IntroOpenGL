#include "app.h"
#include <cstdio>
#include <fstream>
#include <iostream>
enum textype {
    binary,
    ascii
};


void App::LoadTexture()
{
    std::ifstream texture("kim.temp", std::ifstream::in);
    if (!texture.is_open())
    {
        std::cout << "Error! Couldn't open file kim.temp." << std::endl;
        return;
    }
        
    char data[9] = {0};
    int type = 0;
    GLint format = GL_RGB;
    GLint width, height = { 0 };
    if (texture.get() != 'P')
    {
        std::cout << "Error! File Kim.temp doesn't start with P!" << std::endl; 
        return;
    }
    
    //Find the type of texture
    switch (texture.get())
    {
        case '4':
            format = GL_LUMINANCE;
            type = 4;
            break;
        case '5':
            format = GL_LUMINANCE;
            type = 5;
            break;
    }
    char nara = texture.get();
    while (nara != '\n');
    

    if (type)
    {
        width  = texture.get();
        height = texture.get();
        for (int i = 0; i < width * height; i++)
        {
            data[i] = texture.get();
            if ( type == 4 && data[i] > 0x00)
                data[i] = 0xFF;
        }
    }

    GLuint texture_map;
    glGenTextures(1, &texture_map);
    glBindTexture(GL_TEXTURE_2D, texture_map);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    texture.close();
}