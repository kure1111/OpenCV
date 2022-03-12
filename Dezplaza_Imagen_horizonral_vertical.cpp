//GPA Proco
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global Variables
int nCanales, nRen, nCol;
Mat img_gray;
Mat result;
Mat result2;

int main( int argc, char** argv )
{
 /// Read image ( same size, same type )
 if(argc!=2)
	{
		cout <<"no hay imagen";
		return -1;
	}
  img_gray = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  result2 = img_gray.clone();
  result = img_gray.clone();
  if( !img_gray.data ) { cout << "Error loading src1" << endl; return -1; }

  int x,y;
  int nRen = img_gray.rows;
  int nCol = img_gray.cols;
  for(x = 0; x < nRen; x++)
  {
    uchar * original = img_gray.ptr <uchar>(x);
    uchar * copia = result2.ptr <uchar>(x);
    for(y = 1; y < nCol; y++ )
    {
      *( copia + y ) = abs(*( original + y) - *( original + (y-1) ));
      if(*( copia + y ) > 255)
        *( copia + y ) = 255;
    }
  }
   for(x = 1; x < nRen; x++)
  {
    uchar * original = img_gray.ptr <uchar>(x);
    uchar * original2 = img_gray.ptr <uchar>(x-1);
    uchar * copia = result.ptr <uchar>(x);
    for(y = 0; y < nCol; y++ )
    {
     *( copia + y ) = abs(*( original + y) - *( original2+y));
    }
  }
  namedWindow( "horizontal", WINDOW_NORMAL ); //normal para modificar ventana a gustos
  resizeWindow( "horizontal", 550, 400 );//parte de lo deaariba
  namedWindow( "vertical", WINDOW_NORMAL ); //normal para modificar ventana a gustos
  resizeWindow( "vertical", 550, 400 );
  imshow("horizontal",result);
  imshow("vertical",result2);
  
 waitKey(0);
 destroyAllWindows();

 return 0;
}
