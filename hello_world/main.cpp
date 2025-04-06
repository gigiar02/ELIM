/*
    Data Creazione: 06/04/2025 ore 10:30 :)
    Mostra l'immagine il cui percorso è specificato in PATH
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#define PATH "img.jpg"
using namespace cv;
using namespace std;
 
int main()
{
    Mat image;
    string path(PATH);
    image = imread(path, IMREAD_COLOR );
 
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    imshow("Hello World", image);
    waitKey(0);
 
    return 0;
}

