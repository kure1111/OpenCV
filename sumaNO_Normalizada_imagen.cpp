
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/// Global Variables
int nCanales, nRen, nCol,  nCanales2, nRen2, nCol2;

/// Matrices de resultado de magenes
Mat src;      // mtriz con imagen original
Mat src2;     // mtriz con imagen original2
Mat srcRS;
Mat srcRS2;   // otra manera de suma

uchar normaliza( uchar aux ){
  uchar r;
  r = (r*255)/r;
  return r;
}


void Suma2()
{
    for( int i = 0; i < nRen; i++ ){
      uchar * renglonM1 = src.ptr < uchar >( i );
      uchar * renglonM2 = src2.ptr < uchar >( i );
      uchar * renglonR = srcRS2.ptr < uchar >( i );
      for( int j = 0; j < nCol; j += nCanales ){
        uchar sumb = *( renglonM1  + j + 0) + *( renglonM2 + j + 0);
        uchar sumg = *( renglonM1  + j + 1) + *( renglonM2 + j + 1);
        uchar sumr = *( renglonM1  + j + 2) + *( renglonM2 + j + 2);

        if( sumb > 255){ sumb = 255; }
        if( sumg > 255){ sumg = 255; }
        if( sumr > 255){ sumr = 255; }

        *( renglonR + j + 0 ) = ( sumb);
        *( renglonR + j + 1 ) = ( sumg);
        *( renglonR + j + 2 ) = ( sumr);
      }
    }
}

int main( int argc, char** argv)
{
 if(argc!=3) //cantidad de argumentos, imagen1 y imagen 2  ---> 0,1,2
  {
     cout <<"no hay imagen o falta alguna o te pasaste\n";
     return -1;
   }
 src = imread(argv[1],CV_LOAD_IMAGE_COLOR);
 src2 = imread(argv[2],CV_LOAD_IMAGE_COLOR);

 if( !src.data ) { printf("Error loading src1 \n"); return -1; }
 if( !src2.data ) { printf("Error loading src2 \n"); return -1; }

 nCanales = src.channels();
 nCanales2 = src2.channels();
 nRen = src.rows;
 nCol = src.cols * nCanales;
 nRen2 = src2.rows;
 nCol2 = src2.cols * nCanales;
 if( (nRen!=nRen2) || (nCol != nCol2) ){
   printf("Diferentes tamaños de imagenes, Adios\n");
   return -1;
  }
 srcRS = src.clone();
 srcRS2 = src.clone();

  /// Create Windows
 namedWindow( "Suma_Normalizada", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Suma_Normalizada", 550, 400);//parte de lo dearriba define tamaño
 namedWindow( "Suma_NO_Normalizada", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Suma_NO_Normalizada", 550, 400);

 namedWindow( "Original A", WINDOW_NORMAL);
 resizeWindow( "Original A", 550, 400);
 namedWindow( "Original B", WINDOW_NORMAL);
 resizeWindow( "Original B", 550, 400);

 //Suma();  // normalizada
 Suma2(); // sin normalizar

 imshow( "Suma_Normalizada", srcRS);
 imshow( "Suma_NO_Normalizada", srcRS2);

 imshow( "Original A", src);
 imshow( "Original B", src2);

 waitKey(0);
 destroyAllWindows();
 return 0;
}
