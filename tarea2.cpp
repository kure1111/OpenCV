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
Mat srcB;
Mat srcG;
Mat srcR;
Mat srcf;

void funB(int  x, void* )
{
   //printf("\n x:: %d ", x);  //muestra valor actual del la barra
      for( int i = 0; i < nRen; i++ ){
      uchar * renglonb = srcB.ptr <uchar>(i);
      uchar * renglon = src.ptr <uchar>(i);
      uchar * renglonf = srcf.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        *( renglonb + j + 0 ) = (int)((x * (*( renglon + j + 0)) )/100);
        *( renglonf + j + 0 ) = (int)((x * (*( renglon + j + 0)) )/100);
      }
  }
  imshow( "VentanaRGB", srcf );
  imshow( "VentanaB", srcB );
   //hconcat(src,srcB,srcf);
   //imshow( "Ventana", srcf );
  //imshow( "Ventana", srcB );
}

void funG(int  x, void* )
{
    for( int i = 0; i < nRen; i++ ){
      uchar * renglong = srcG.ptr <uchar>(i);
      uchar * renglon = src.ptr <uchar>(i);
      uchar * renglonf = srcf.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        *( renglong + j + 1 ) = (int)((x * (*( renglon + j + 1)) )/100);
        *( renglonf + j + 1 ) = (int)((x * (*( renglon + j + 1)) )/100);
      }
  }
  imshow( "VentanaRGB", srcf );
  imshow( "VentanaG", srcG );
}

void funR(int  x, void* )
{
    for( int i = 0; i < nRen; i++ ){
      uchar * renglonr = srcR.ptr <uchar>(i);
      uchar * renglon = src.ptr <uchar>(i);
      uchar * renglonf = srcf.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        *( renglonr + j + 2 ) = (int)((x * (*( renglon + j + 2)) )/100);
        *( renglonf + j + 2 ) = (int)((x * (*( renglon + j + 2)) )/100);
      }
  }
  imshow( "VentanaRGB", srcf );
  imshow( "VentanaR", srcR );
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
 srcB=src.clone();
 srcG=src.clone();
 srcR=src.clone();
 srcf=src.clone();
 nCanales = src.channels();
 nRen = src.rows;
 nCol = src.cols * nCanales;
 //azul
   for( int i = 0; i < nRen; i++ ){
    uchar * renglonb = srcB.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
        *( renglonb + j + 1 ) = 0;
        *( renglonb + j + 2 ) = 0;
    }
  }
  //verde
  for( int i = 0; i < nRen; i++ ){
    uchar * renglong = srcG.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
        *( renglong + j + 0 ) = 0;
        *( renglong + j + 2 ) = 0;
    }
  }

  //Rojo
    for( int i = 0; i < nRen; i++ ){
    uchar * renglonr = srcR.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
        *( renglonr + j + 0 ) = 0;
        *( renglonr + j + 1 ) = 0;
    }
  }

  /// Create Windows
 namedWindow( "VentanaR", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaR", 550, 400 );//parte de lo deaariba
 namedWindow( "VentanaG", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaG", 550, 400 );//parte de lo deaariba
 namedWindow( "VentanaB", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaB", 550, 400 );//parte de lo deaariba
 namedWindow( "VentanaRGB", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaRGB", 550, 400 );//parte de lo deaariba

 /// Create Trackbars
 slider=0;
 createTrackbar("BLUE", "VentanaB", &slider, alpha_slider_max, funB );
 createTrackbar("GREEN", "VentanaG", &slider, alpha_slider_max, funG );
 createTrackbar("RED", "VentanaR", &slider, alpha_slider_max, funR );
 createTrackbar("BLUE", "VentanaRGB", &slider, alpha_slider_max, funB );
 createTrackbar("GREEN", "VentanaRGB", &slider, alpha_slider_max, funG );
 createTrackbar("RED", "VentanaRGB", &slider, alpha_slider_max, funR );

  //cada que se mueve la barra slider se llama a la funcion funB

 /// Wait until user press some key
 waitKey(0);
 destroyAllWindows();

 return 0;
}
