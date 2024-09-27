#include "BMPclass.h"
// g++ -std=c++20 main.cpp BMPclass.cpp -o main


int main(int argc, char const *argv[])
{
    try
    {
        BMPclass image;

        image.openBMP( argv[ 1 ] );

        image.displayBMP();

        image.closeBMP();
    }
    catch (Error& e)
    {
        std::cerr << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown error" << "\n";
    }
    
    std::cout << std::endl;

    return 0;
}

