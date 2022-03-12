#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
using namespace cv;
using namespace std;

Mat recorte(Mat A);
double D_2_Image(Mat A, Mat B);
/// Global Variables
int nCanalesG, nRenG, nColG,  nCanales2G, nRen2G, nCol2G;
/// Matrices Originales
Mat src;      // mtriz con imagen original 1
Mat src1;     // mtriz con imagen original 2
int main(int argc, char** argv)
{
 if( argc != 3 ) //cantidad de argumentos, imagen1 y imagen 2  ---> 0,1,2
  {
     cout <<"no hay imagen o falta image\n";
     return -1;
   }
 src = imread(argv[1],0);
 src1 = imread(argv[2],0);

 if(!src.data | !src1.data) { printf("Error loading src1 \n"); return -1; }

 //Mat img;
 //src.convertTo(img, CV_8UC1);
 //double val = threshold(src, Umbral, 100, 250, cv::THRESH_OTSU | cv::THRESH_BINARY); //threshold(src, Umbral, thresh, maxValue, THRESH_BINARY);
 Mat aux = recorte(src);
 Mat aux2 = recorte(src1);
 double distancia  = D_2_Image(aux, aux2);
 printf("La distanciaentre las dos imagenes es ::: %.2f\n", distancia);
 namedWindow( "ROI_1", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "ROI_1", 550, 400);//parte de lo dearriba define tamaño
 namedWindow( "ROI_2", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "ROI_2", 550, 400);
 imshow("ROI_1", aux);
 imshow("ROI_2", aux2);

 waitKey(0);
 destroyAllWindows();
 return 0;
}
double D_2_Image(Mat A, Mat B){
  int col = A.cols;
  int ren = A.rows;
  int cont = 0;
  for(int i = 0; i < ren; i++){
    uchar * renglonM1 = A.ptr < uchar >(i);
    uchar * renglonM2 = B.ptr < uchar >(i);
    for(int j = 0; j < col; j += 1){
      if (*(renglonM1 + j) != *(renglonM2 + j)){
        cont++;
      }
    }
  }
  return sqrt(cont);
}
Mat recorte(Mat sep){
  Mat Umbral;
  double val = threshold(sep, Umbral, 100, 250, cv::ADAPTIVE_THRESH_MEAN_C| cv::THRESH_BINARY); //threshold(src, Umbral, thresh, maxValue, THRESH_BINARY);
  Mat A;
  GaussianBlur(Umbral, A, Size( 9, 9 ), 1.0);
  int nCanales = A.channels();
  int nRen = A.rows;
  int nCol = A.cols * nCanales;
  int xi, yi, xf, yf;
  yi = nRen;
  xi = nCol;
  yf = 0;
  xf = 0;
  for(int i = 0; i < nRen; i++){
    uchar * renglon = A.ptr < uchar >(i);
    for(int j = 0; j < nCol; j += nCanales){
      uchar sumb = *(renglon  + j + 0);
      //printf("val : %d ", sumb);
      if(sumb == 0){
        if(i < yi)
          yi = i;
        if(j < xi)
          xi = j;
        if(i > yf)
          yf = i;
        if (j > xf)
          xf = j;
      }
    }
  }
  printf("xi: %d\n", xi);
  printf("yi: %d\n", yi);
  printf("xf: %d\n", xf);
  printf("yf: %d\n", yf);
  Mat recortada = Mat::zeros(yf-yi, xf-xi,CV_8UC1); // matriz de n x m n=AmpliarY, m=AmpliarX
  int nCan = recortada.channels();
  int nR = recortada.rows;
  int nC = recortada.cols * nCan;
  for(int i = 0; i < nR; i++){
    uchar * renglonM1 = A.ptr < uchar >(i+yi);
    uchar * renglonR = recortada.ptr < uchar >(i);
    for(int j = 0; j < nC; j += nCan){
      *(renglonR  + j + 0) = *(renglonM1  + j + xi + 0);
    }
  }

  Size size(55,55);//the dst image size,e.g.100x100
  Mat dst;//src image
  resize(recortada,dst,size);//resize image
  //imshow("threshold", A);
  return dst;
}
