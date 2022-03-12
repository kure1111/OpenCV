//GPA Proco
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
void funB(int  x, void* );
void funG(int  x, void* );
void funR(int  x, void* );
/// Global Variables
const int alpha_slider_max = 100;
int slider;
int nCanales, nRen, nCol;

/// Matrices to store images
Mat src;
Mat srcR;


void funB(int R, int G, int B)
{
   //printf("\n x:: %d ", x);  //muestra valor actual del la barra
    nCanales = src.channels();
    nRen = src.rows;
    nCol = src.cols * nCanales;
    for( int i = 0; i < nRen; i++ ){
      uchar * renglon = src.ptr <uchar>(i);
      uchar * renglonR = srcR.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        *( renglonR + j + 0 ) = (int)((B * (*( renglon + j + 0)) )/100);
        *( renglonR + j + 1 ) = (int)((G * (*( renglon + j + 1)) )/100);
        *( renglonR + j + 2 ) = (int)((R * (*( renglon + j + 2)) )/100);
      }
  }

}

int main( int argc, char** argv )
{
 /// Read image ( same size, same type )
 if(argc!=2)
	{
		cout <<"no hay imagen";
		return -1;
	}

 src = imread(argv[1],CV_LOAD_IMAGE_COLOR);
 if( !src.data ) { printf("Error loading src1 \n"); return -1; }
 srcR = src.clone();

 nCanales = src.channels();
 nRen = src.rows;
 nCol = src.cols * nCanales;


  /// Create Windows
 namedWindow( "VentanaR", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaR", 550, 400 );//parte de lo deaariba

 /// Create Trackbars
 slider=0;
 createTrackbar("Cantidad", "VentanaR", &slider, alpha_slider_max, funB );

  //cada que se mueve la barra slider se llama a la funcion funB

 /// Wait until user press some key
 waitKey(0);
 destroyAllWindows();

 return 0;
}
