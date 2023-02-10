#include "app.h"
#include <cstdio>
#include < stdio.h >
#include <cwchar>
#include <fstream>
#include <iostream>
enum textype {
    binary,
    ascii
};

/*void decimalToBinary(int n, char* binary) {
    long long decimal = 0;
    int last, i = 1;
    while (n != 0) {
        last = n % 2;
        decimal += last * i;
        i = i * 10;
        n = n / 2;
    }
    std::cout << decimal << std::endl;
    sprintf_s(binary, sizeof(int) * 4 * 8, "%d", decimal);
    std::cout << binary[0] << std::endl;
}*/

void decimalToBinary(int decimal, char* binary) {
    int index = 0;
    while (decimal > 0) {
        binary[index++] = (decimal % 2 == 0) ? '0' : '1';
        decimal /= 2;
    }

    // Reverse the binary string
    int start = 0, end = index - 1;
    while (start < end) {
        char temp = binary[start];
        binary[start++] = binary[end];
        binary[end--] = temp;
    }
}

void App::LoadTexture()
{
    std::ifstream texture("binary.pbm", std::ifstream::in);
    if (!texture.is_open())
    {
        std::cout << "Error! Couldn't open file." << std::endl;
        return;
    }
        
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

    for (char nara = texture.get(); nara != '\n'; nara = texture.get())
    {
        std::cout << nara << std::endl;;
    };
    
    if (type == 4)
    {
        width = texture.get() - '0';
        texture.get();
        height = texture.get() - '0';
        texture.get();
        char* data = new char[width * height];
        char* data_ = data;

        while (!texture.eof())
        {
            char hex = texture.get();

            if (hex == EOF)
                break;
            printf("%x\n", hex);
            for (int j = 7; j >= width; j--)
            {
                *data_++ = hex & (1 << j) ? 0 : 0xFF;
            }
        }

        printf("%x", data_ - data);

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
    }
}