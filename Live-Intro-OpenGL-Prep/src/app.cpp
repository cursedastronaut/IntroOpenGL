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

//Loads the textures
GLuint App::LoadTexture(const char* filename, GLuint width, GLuint height)
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
        //Since the whole data is already almost good, I just send everything to the data buffer
        data = (char*)malloc(width * height * 3);
        texture.read(data, width * height * 3);
        texture.close();

        //This part wouldn't exist if BMP switched red and blue.
        //This parts simply switch back red and blue to follow the RGB format.
        for (int i = 0; i < width * height; ++i)
        {
            unsigned char blue, red;
            blue = data[i * 3];
            red = data[i * 3 + 2];
            data[i * 3] = red;
            data[i * 3 + 2] = blue;
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