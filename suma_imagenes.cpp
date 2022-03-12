
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/// Global Variables
int nCanalesG, nRenG, nColG,  nCanales2G, nRen2G, nCol2G;

/// Matrices Originales
Mat srcG;      // mtriz con imagen original 1
Mat src2G;     // mtriz con imagen original 2

uchar normaliza(uchar aux){
  uchar r;
  r = (r * 255) / r;
  return r;
}

Mat Suma(Mat src, Mat src2){
   int nCanales = src.channels();
   int nRen = src.rows;
   int nCol = src.cols * nCanales;
   Mat srcRS = Mat::zeros(nRen, src.cols, CV_8UC3);
    for(int i = 0; i < nRen; i++){
      uchar * renglonM1 = src.ptr < uchar >(i);
      uchar * renglonM2 = src2.ptr < uchar >(i);
      uchar * renglonR = srcRS.ptr < uchar >(i);
      for(int j = 0; j < nCol; j += nCanales){
        uchar sumb = *(renglonM1  + j + 0) + *(renglonM2 + j + 0);
        uchar sumg = *(renglonM1  + j + 1) + *(renglonM2 + j + 1);
        uchar sumr = *(renglonM1  + j + 2) + *(renglonM2 + j + 2);

        if(sumb > 255){ sumb = normaliza(sumb); }
        if(sumg > 255){ sumg = normaliza(sumg); }
        if(sumr > 255){ sumr = normaliza(sumr); }

        *(renglonR + j + 0) = ( sumb);
        *(renglonR + j + 1) = ( sumg);
        *(renglonR + j + 2) = ( sumr);
      }
    }
    return srcRS;
}

Mat Suma2(Mat src, Mat src2){
   int nCanales = src.channels();
   int nRen = src.rows;
   int nCol = src.cols * nCanales;
   Mat srcRS2 = Mat::zeros(nRen, src.cols, CV_8UC3);
    for(int i = 0; i < nRen; i++){
      uchar * renglonM1 = src.ptr < uchar >(i);
      uchar * renglonM2 = src2.ptr < uchar >(i);
      uchar * renglonR = srcRS2.ptr < uchar >(i);
      for(int j = 0; j < nCol; j += nCanales){
        uchar sumb = *(renglonM1  + j + 0) + *(renglonM2 + j + 0);
        uchar sumg = *(renglonM1  + j + 1) + *(renglonM2 + j + 1);
        uchar sumr = *(renglonM1  + j + 2) + *(renglonM2 + j + 2);

        if(sumb > 255){ sumb = 255; }
        if(sumg > 255){ sumg = 255; }
        if(sumr > 255){ sumr = 255; }

        *(renglonR + j + 0) = ( sumb);
        *(renglonR + j + 1) = ( sumg);
        *(renglonR + j + 2) = ( sumr);
      }
    }
    return srcRS2;
}



int main(int argc, char** argv)
{
 if( argc!=3 ) //cantidad de argumentos, imagen1 y imagen 2  ---> 0,1,2
  {
     cout <<"no hay imagen o falta alguna o te pasaste\n";
     return -1;
   }
 srcG = imread(argv[1],CV_LOAD_IMAGE_COLOR);
 src2G = imread(argv[2],CV_LOAD_IMAGE_COLOR);

 if(!srcG.data) { printf("Error loading src1 \n"); return -1; }
 if(!src2G.data) { printf("Error loading src2 \n"); return -1; }

 nCanalesG = srcG.channels();
 nCanales2G = src2G.channels();
 nRenG = srcG.rows;
 nColG = srcG.cols * nCanalesG;
 nRen2G = src2G.rows;
 nCol2G = src2G.cols * nCanalesG;
 if( (nRenG!=nRen2G) || (nColG != nCol2G) ){
   printf("Diferentes tamaños de imagenes, Adios\n");
   return -1;
  }

  /// Create Windows
 namedWindow( "Suma_Normalizada", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Suma_Normalizada", 550, 400);//parte de lo dearriba define tamaño
//namedWindow( "Suma_NO_Normalizada", WINDOW_NORMAL); //normal para modificar ventana a gusto
//resizeWindow( "Suma_NO_Normalizada", 550, 400);

 //namedWindow( "Original A", WINDOW_NORMAL);
 //resizeWindow( "Original A", 550, 400);
 //namedWindow( "Original B", WINDOW_NORMAL);
 //resizeWindow( "Original B", 550, 400);

 Mat srcRS = Suma2(srcG, src2G); // sin normalizar
 Mat srcRS2 = Suma2(srcG, src2G); //Suma Normalizada

 imshow( "Suma_Normalizada", srcRS);
 //imshow( "Suma_NO_Normalizada", srcRS2);

 //imshow( "Original A", src);
 //imshow( "Original B", src2);

 waitKey(0);
 destroyAllWindows();
 return 0;
}
