
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
using namespace cv;

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    Mat frame;
    Mat img = imread("../1.png");
    Mat img1 = imread("../2.png");
    Mat roi;
    Mat dest;
    int pixel = 0;
    double cx = 0;
    double cy = 0;
    cv::subtract(img,img1,dest);
//    for(int i=0;i<img.rows;i++){
//        for(int j=0;j<img.cols;j++){
//            cout << i << j;
//        }
//    }

    namedWindow("Frame", WINDOW_AUTOSIZE);
    namedWindow("Imgen",WINDOW_AUTOSIZE);
    namedWindow("Imagen",WINDOW_AUTOSIZE);
    double huMoments[7];
    Moments momentos; // Momentos generales

    for (int i = 0; i < roi.rows; ++i) {
        for (int j = 0; j < roi.cols; ++j) {
            pixel = roi.at<uchar>(i,j);
        }
    }

    momentos = moments(roi, true);
    HuMoments(momentos,huMoments);

    cx = momentos.m10/momentos.m00;
    cy = momentos.m01/momentos.m00;

    circle(frame,Point(cx,cy),5,Scalar(0,0,100),3);


    imshow("Imgen",img);
    imshow("Imagen",img1);
    imshow("Frame",frame);
    waitKey(0);
    return 0;
}