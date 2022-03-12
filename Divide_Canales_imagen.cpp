//GPA Proco
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
uchar normaliza( uchar aux);

using namespace cv;
using namespace std;

void Suma(); //si primero van las funciones y luego el main no es necesario la cabezera de funcion como esta

/// Global Variables
int nCanales, nRen, nCol, nCanales2, nRen2, nCol2;

/// Matrices de resultado de magenes
Mat src;      // mtriz con imagen original
Mat srcR;     // mtriz con imagen original2
Mat srcG;
Mat srcB;
// Suma normalizada
void BGR()
{
    for( int i = 0; i < nRen; i++ ){
      uchar * renglon = src.ptr <uchar>(i);
      uchar * renglonM1 = srcR.ptr <uchar>(i);
      uchar * renglonM2 = srcG.ptr <uchar>(i);
      uchar * renglonM3 = srcB.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        *( renglonM3 + j + 0 ) = *( renglon + j+ 0); //se queda el blue
        *( renglonM3 + j + 1 ) = 0;
        *( renglonM3 + j + 2 ) = 0;

        *( renglonM2 + j + 0 ) = 0;
        *( renglonM2 + j + 1 ) = *( renglon + j+ 1);//se queda el green
        *( renglonM2 + j + 2 ) = 0;

        *( renglonM1 + j + 0 ) = 0;
        *( renglonM1 + j + 1 ) = 0;
        *( renglonM1 + j + 2 ) = *( renglon + j+ 2);//se queda el rojo

      }
    }
}

int main( int argc, char** argv)
{
 if(argc!=2) //cantidad de argumentos, imagen1 y imagen 2  ---> 0,1,2
  {
     cout <<"no hay imagen o falta alguna o te pasaste\n";
     return -1;
   }
 src = imread(argv[1],CV_LOAD_IMAGE_COLOR);

 if( !src.data ) { printf("Error loading src1 \n"); return -1; }

 nCanales = src.channels();
 nRen = src.rows;
 nCol = src.cols * nCanales;

 srcR = src.clone();
 srcG = src.clone();
 srcB = src.clone();

 namedWindow( "Original", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Original", 550, 400);
  /// Create Windows
 namedWindow( "Red", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Red", 550, 400);//parte de lo dearriba define tamaño
 /// Create Windows
namedWindow( "Green", WINDOW_NORMAL); //normal para modificar ventana a gusto
resizeWindow( "Green", 550, 400);//parte de lo dearriba define tamaño
/// Create Windows
namedWindow( "Blue", WINDOW_NORMAL); //normal para modificar ventana a gusto
resizeWindow( "Blue", 550, 400);//parte de lo dearriba define tamaño

 BGR();

 imshow( "Red", srcR);
 imshow( "Green", srcG);
 imshow( "Blue", srcB);
 imshow( "Original", src);
 imwrite("RED.jpg", srcR);
 imwrite("BLUE.jpg", srcB);
 imwrite("GREEN.jpg", srcG);


 waitKey(0);
 destroyAllWindows();

 return 0;
}
