// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>


// Librería que contiene funciones matemáticas
#include <cmath>

// Librerías de OpenCV

// Se pueden cargar todas las Librerías incluyendo
//#include <opencv2/opencv.hpp>

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

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)

Mat img1;
Mat img2;
Mat rest;
Mat copy;

int main(int argc, char *argv[]){
    img1=imread("1.png");

    //resize(img1, img1, Size(), 0.7,0.7);
    img2=imread("2.png");
    //resize(img2, img2, Size(), 0.7,0.7);
    rest = Mat::zeros(img1.size(), CV_8UC3);

    //CAÑAR_UYAGUARI_JUAN_CARLOS{cx = 126 cy = 204 radio = 18}

    circle(img1,Point(126,204),18,Vec3b(0,0,0),1);
    //circle(img2,Point(126,204),18,Vec3b(0,0,0),1,LINE_4);

    for (int i = 0; i < img1.rows; i++) {
        for (int j = 0; j < img1.cols; j++) {
            //cout << img1.at<Scalar>(i,j);
            if (img1.at<Vec3b>(i, j) == Vec3b(0, 0, 0)) {
                rest.at<Vec3b>(i, j) = img2.at<Vec3b>(i, j);
            } else {
                rest.at<Vec3b>(i, j) = img1.at<Vec3b>(i, j);
            }
        }
    }

    namedWindow("1", WINDOW_AUTOSIZE);
    namedWindow("2", WINDOW_AUTOSIZE);
    namedWindow("Resultado", WINDOW_AUTOSIZE);

    imshow("1", img1);
    imshow("2", img2);
    imshow("Resultado", rest);

    imwrite("Resultado.png",rest);
    waitKey(0);
    return 0;
}



