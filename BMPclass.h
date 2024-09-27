#pragma once

#include "Extension.h" 

#include <string> 
#include <fstream> 
#include <vector> 
#include <windows.h> // struct BITMAPFILEHEADER && BITMAPINFOHEADER 
#include <iostream> 
#include <algorithm> // reverse vector


class BMPclass
{
private:
    /* data */
    int heightIm; 
    int widthIm;
    std::vector < std::string > buf;

public:
    /* functions */
    BMPclass();
    void openBMP(const std::string & fileName);
    void displayBMP(); 
    void closeBMP();
    ~BMPclass();
};
