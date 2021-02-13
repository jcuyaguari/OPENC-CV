// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>
// Librería que contiene funciones matemáticas
#include <cmath>

// Librerías de OpenCV

// Se pueden cargar todas las Librerías incluyendo
#include <opencv2/opencv.hpp>

// Contiene las definiciones fundamentales de las matrices e imágenes
#include <opencv2/core/core.hpp>
// Procesamiento de imágenes
#include <opencv2/imgproc/imgproc.hpp>
// Códecs de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>
// Manejo de ventanas y eventos de ratón, teclado, etc.
#include <opencv2/highgui/highgui.hpp>
// Lectura de video
#include <opencv2/video/video.hpp>
// Escritura de video
#include <opencv2/videoio/videoio.hpp>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

//https://docs.opencv.org/4.5.1/d3/dbe/tutorial_opening_closing_hats.html
using namespace std;
using namespace cv;

int valore = 1;
int valord = 1;
int valort = 1;
int valorb = 1;
Mat img;
Mat kernel;
Mat dilatacion;
Mat erosion;
Mat topHat;
Mat hatBlack;

void Eroding(int,void*){
    Mat elementoEr = getStructuringElement(MORPH_RECT,Size(2*valore+1, 2*valore+1));
    erode(img,elementoEr,elementoEr);
    imshow("Erosion", elementoEr);
}

void Dilatation(int,void*){
    Mat elementoDi = getStructuringElement(MORPH_RECT,Size(2*valord+1, 2*valord+1));
    dilate(img,elementoDi,elementoDi);
    imshow("Dilatacion", elementoDi);
}

void hatTop(int,void*){
    kernel = getStructuringElement(MORPH_ELLIPSE, Size(valort, valort));
    morphologyEx(img,topHat,MORPH_TOPHAT,kernel);
    imshow("Tophat", topHat);
}

void hatBlak(int,void*){
    kernel = getStructuringElement(MORPH_ELLIPSE, Size(valorb, valorb));
    morphologyEx(img,hatBlack,MORPH_BLACKHAT,kernel);
    imshow("Blackhat", hatBlack);
}


int main(int argc, char *argv[]){

    img = imread("../craneo.jpg");
    //img = imread("../pelvis.jpg");
    //img = imread("../pulmon.jpg");
    resize(img,img,Size(365,365));
    cout << "llego";
    dilate(img, dilatacion, kernel);
    erode(img, erosion, kernel);
    morphologyEx(img,topHat,MORPH_TOPHAT,kernel);
    morphologyEx(img,hatBlack,MORPH_BLACKHAT,kernel);

    //Resta
    Mat resta;
    absdiff(topHat, hatBlack, resta);

    Mat suma;
    addWeighted(img,0.5,resta,0.5,0,suma);



    namedWindow("Original",WINDOW_AUTOSIZE);
    namedWindow("Erosion",WINDOW_AUTOSIZE);
    namedWindow("Dilatacion",WINDOW_AUTOSIZE);
    namedWindow("Tophat",WINDOW_AUTOSIZE);
    namedWindow("Blackhat",WINDOW_AUTOSIZE);
    namedWindow("SUMA",WINDOW_AUTOSIZE);

    createTrackbar("Erosion", "Original", &valore, 37, Eroding, 0);
    createTrackbar("Dilatacion", "Original", &valord, 37, Dilatation, 0);
    createTrackbar("TopHat", "Original", &valort, 37, hatTop, 0);
    createTrackbar("Blackhat", "Original", &valorb, 37, hatBlak, 0);

    imshow("Original", img);
    imshow("Erosion", erosion);
    imshow("Dilatacion", dilatacion);
    imshow("Tophat", topHat);
    imshow("Blackhat", hatBlack);
    imshow("SUMA", suma);

    Eroding(0,0);
    Dilatation(0,0);
    hatTop(0,0);
    hatBlak(0,0);
    waitKey(0);

    return 0;
}

