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


Mat frame;
Mat canny;
Mat laplacianBorde;
Mat laplacianBordeabs;
Mat imgBlur;
Mat imgRuidoSal;
Mat imgRuidoPimienta;
Mat medianMedianBlur;
Mat gaussianBlur;
//Mat mBlur;
int vsal = 1;
int vpim = 1;
int vmed= 1;
int vgau = 1;
int vlap = 1;
int vgab = 1;

void fTrackbar(int v,void *p){
    //imshow("Ruido Sal",imgRuidoSal);
    //imshow("Ruido Pimienta",imgRuidoPimienta);
}

void filtros(Mat imgRuidoSal){


    blur(imgRuidoSal,imgBlur,Size(vgab,vgab),Point(-1,-1));
    imshow("Blur",imgBlur);
    //MedianBlur
    if(vmed%2==1 ){
        medianBlur(imgRuidoSal,medianMedianBlur,vmed);
        imshow("MedianBlur", medianMedianBlur);
    }

    if(vgau%2==1){
        GaussianBlur(imgRuidoSal,gaussianBlur,Size(vgau,vgau),3,3,BORDER_DEFAULT);
        imshow("GaussianBlur", gaussianBlur);
    }

    //BORDES
    Laplacian(imgRuidoSal, laplacianBorde, CV_16S,vlap,1);
    convertScaleAbs(laplacianBorde,laplacianBordeabs);
    Canny(imgRuidoSal,canny,70,120,3);

    imshow("Laplace", laplacianBordeabs);
    imshow("Canny",canny);

}

int main(int argc, char *argv[]){

    VideoCapture video(0);
    if(video.isOpened()) {
        int fila = 0;
        int columna = 0;

        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("Ruido Sal", WINDOW_AUTOSIZE);
        namedWindow("Ruido Pimienta", WINDOW_AUTOSIZE);
        namedWindow("MedianBlur", WINDOW_AUTOSIZE);
        namedWindow("GaussianBlur", WINDOW_AUTOSIZE);
        namedWindow("Laplace", WINDOW_AUTOSIZE);
        namedWindow("Canny", WINDOW_AUTOSIZE);
        namedWindow("Blur", WINDOW_AUTOSIZE);


        createTrackbar("Sal", "Frame", &vsal, 50, fTrackbar, 0);
        createTrackbar("Pimienta", "Frame", &vpim, 50, fTrackbar, 0);
        createTrackbar("MedianBlur", "Frame", &vmed, 50, fTrackbar, 0);
        createTrackbar("GaussBlur", "Frame", &vgau, 50, fTrackbar, 0);
        createTrackbar("Blur", "Frame", &vgab, 50, fTrackbar, 0);

        while(2==2){
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame,imgRuidoSal,COLOR_BGR2GRAY);
            cvtColor(frame,imgRuidoPimienta,COLOR_BGR2GRAY);
            int totals = (int) (vsal/10* frame.rows * frame.cols);
            int totalp = (int) (vpim/10* frame.rows * frame.cols);
            cout << totals << " ";
            //imgRuidoSal = img;
            //imgRuidoPimienta = img;
            filtros(imgRuidoSal);
            for (int i = 0; i < totals; i++) {
                fila = rand() % imgRuidoSal.rows;
                columna = rand() % imgRuidoSal.cols;
                imgRuidoSal.at<uchar>(fila, columna) = 255;
            }

            for (int j = 0; j < totalp; j++) {
                fila = rand() % imgRuidoPimienta.rows;
                columna = rand() % imgRuidoPimienta.cols;
                imgRuidoPimienta.at<uchar>(fila, columna) = 0;
            }

            imshow("Frame", frame);
            imshow("Ruido Sal", imgRuidoSal);
            imshow("Ruido Pimienta", imgRuidoPimienta);
            imshow("Blur", imgBlur);


            if(waitKey(25)==27)
                break;
        }
        destroyAllWindows();
    }

    return 0;
}

