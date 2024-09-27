#include "BMPclass.h"


void BMPclass::openBMP(const std::string & fileName)
{
    /* Initialization */
    std::fstream out;

    /* Open fileName as read binary */
    out.open( fileName, std::ios::binary | std::ios::in );

    /* check open file */
    if ( !out.is_open() ) { 
        throw Error("Cannot open file"); }

    /* Initialization struct from windows.h (winApi32) */
    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER bmpInfo;

    /* write BITMAPFILEHEADER bmpHeader */
    out.read( (char*)&bmpHeader, sizeof(bmpHeader) );

    /* Check Format (BM=0x4D42) */
    if ( bmpHeader.bfType != 0x4D42 ) {
        throw Error("Unrecognized file format"); }

    /* read DIB header */
    out.read( (char*)&bmpInfo, sizeof(bmpInfo) );

    /* check bit count */
    int bit = bmpInfo.biBitCount;
    if ( !( bit == 32 || bit == 24 ) ){ 
        throw Error("Only 24 or 32 bit"); } 

    /* save wight and height */
    widthIm = bmpInfo.biWidth;
    heightIm = bmpInfo.biHeight;

    /* select pixel-data */
    out.seekg( bmpHeader.bfOffBits, out.beg );

    std::cout << "Height: " << heightIm << "\t";
    std::cout << "Wight: " << widthIm << "\n";

    std::string strBytes;

    for ( size_t i = 0 ; i < heightIm ; i++ )
    {
        for ( size_t j = 0 ; j < widthIm ; j++ )
        {
            /* read data */
            unsigned char a, b, c;
            out.read( (char*)&a, sizeof( a ) );
            out.read( (char*)&b, sizeof( b ) );
            out.read( (char*)&c, sizeof( c ) );

            /* if we have big image, need create 2 loop with alpha and without alpha */
            /* skeep alpha if ( 32 bit ) */
            if ( bit == 32 ){ 
                out.seekg( 1, out.cur );  }

            /* add symbols */
            if ( ( int )a + ( int )b + ( int )c < 382.5 ) { 
                strBytes += '1'; }

            else { strBytes += '0'; }

            strBytes += ' ';
        }

        buf.push_back( strBytes );

        /* refresh container */
        if ( bit == 24 ){ 
            int lenstr = widthIm * 3;
            int offset = 0;

            while ( lenstr % 4 != 0 ){ 
                offset ++; lenstr ++; }

            out.seekg( offset, out.cur );  }

        strBytes.clear();
    }
    
    /* flip images to store image correctly */
    std::reverse( buf.begin(), buf.end() );

    /* close file */
    out.close();
}


void BMPclass::displayBMP()
{
    std::cout << "Black is 1\tWhite is 0\n";

    /* loop */
    for ( size_t i = 0; i < heightIm ; i++ ) { 
        std::cout << buf[ i ] << std::endl; }
}


void BMPclass::closeBMP()
{
    /*  */
}

BMPclass::BMPclass(/* args */)
{
}

BMPclass::~BMPclass()
{
}
