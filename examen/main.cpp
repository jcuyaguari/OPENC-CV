
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

int * obtenerHistorgrama(Mat imagen) {
    // Cálculo del histograma de la imagen
    int * histograma  = new int[256];

    for (int i = 0; i < 256; i++)
        histograma[i] = 0;

    Vec3b pixel;
    for (int i = 0; i < imagen.rows; i++) {
        for (int j = 0; j < imagen.cols; j++) {
            pixel = imagen.at<Vec3b>(i, j);
            histograma[pixel[2]]++;
        }
    }

    return histograma;
}

double metododistanciaEuclidea(int *m1, int *m2) {
    double sumaTot = 0.0;
    for (int i = 0; i < 256; i++) {
        sumaTot += (m1[i] - m2[i]) * (m1[i] - m2[i]);
    }
    sumaTot = sqrt(sumaTot);
    return sumaTot;
}

void momentos(){
    uchar imgMoment[4][4] = {{123, 97, 10, 91}, {89, 47, 19, 101}, {7, 3, 250, 28}, {13, 1, 0, 200}};
    Mat img(4,4,CV_8UC1,&imgMoment);
    Mat imgbinaria;
    threshold(img, imgbinaria, 12, 1, THRESH_BINARY);
    Moments momentos = moments(imgbinaria, true);
    cout << "Momentos: "<< momentos.m10<< endl;
}


Mat imgGris;
double suma = 0.0;
double respuesta = 0.0;
int pixel;
int *histoImg [2];
Mat imagen1 ;
Mat imagen2 ;
double distancia = 0.0;
double distanciaminTotal = 999999999999999999.9;
string numero;
string nombre;

int main(int argc, char *argv[]){
    std::cout << "Hello, World!" << std::endl;

    //Distancia
    nombre = "CORPUS-IMAGENES-1/image_00";
    for (int i = 1; i < 57; i++) {
        numero = i < 10 ? "0" + to_string(i) : to_string(i);
        cout << nombre + numero + ".jpg" << endl;
        if (i % 2 == 0) {
            imagen1 = imread(nombre + numero + ".jpg");
            histoImg[0] = obtenerHistorgrama(imagen1);
            histoImg[1] = obtenerHistorgrama(imagen2);
            distancia = metododistanciaEuclidea(histoImg[0], histoImg[1]);
            if (distancia < distanciaminTotal)
                distanciaminTotal = distancia;
            cout <<" --> : "<< distancia << endl;
        }
        else {
            imagen1 = imread(nombre + numero + ".jpg");
        }
    }

    cout << "Distancia: " << distanciaminTotal << endl;

    // Momentos
    momentos();

    //Intensidad Gris Pixel
    imgGris = imread("CORPUS-IMAGENES-1/image_0033.jpg", IMREAD_GRAYSCALE);

    for (int i = 0; i < imgGris.rows; i++) {
        for (int j = 0; j < imgGris.cols; j++) {
            pixel = imgGris.at<uchar>(i, j);
            suma += pixel;
        }
    }
    respuesta = suma / (imgGris.rows * imgGris.cols);
    cout << "Valor intensidad : " << respuesta << endl;



    waitKey(0);
    destroyAllWindows();

    return 0;
}


