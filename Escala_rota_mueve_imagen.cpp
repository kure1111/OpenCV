//GPA Proco
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define PI 3.14159265  /* pi */
using namespace cv;
using namespace std;
/// Global Variables
int AmpliarX = 600, AmpliarY= 400 ;
int slider, slider2, slider3;
int nCanales, nRen, nCol;

/// Matrices to store images
Mat src;
Mat srcR;



void Reduccion(int  reduc, void* ){
    int temp = pow(2, reduc);
    int k,i2;
    AmpliarY = floor(nRen / temp);
    AmpliarX = floor(src.cols / temp)*3;
    int aux = floor(src.cols / temp);
    Mat newR = Mat::zeros(AmpliarY,aux,CV_8UC3); // matriz de n x m n=AmpliarY, m=AmpliarX
    for(int i = 0, k = 0; i < newR.rows ; i++, k += temp){
      if(reduc == 0) k=i;
      uchar * renglon = src.ptr <uchar>(k);
      uchar * renglonR = newR.ptr <uchar>(i);
      for( int j = 0, i2 = 0; j < newR.cols*3; j += nCanales, i2 += temp*3){ //cada desplazamiento va de 3 entres porlo si quiero
        if (reduc == 0 ) i2 = j;                    //quiero dezplzarme 5 pixeles los multiplico por 3 y es el dezplam. real
        *( renglonR + j + 0 ) = *(renglon + i2 + 0);
        *( renglonR + j + 1 ) = *(renglon + i2 + 1);
        *( renglonR + j + 2 ) = *(renglon + i2 + 2);
      }
    }
        namedWindow( "Escalamiento", WINDOW_NORMAL );
        imshow("Porcentaje", newR);
}

void ReduccionProm(int  reduc, void* ){
    int temp = pow(2, reduc);
    int k,i2;
    AmpliarY = floor(nRen / temp);
    AmpliarX = floor(src.cols / temp)*3;
    int aux = floor(src.cols / temp);
    int RBs,RGs,RRs;
    Mat newR = Mat::zeros(AmpliarY,aux,CV_8UC3); // matriz de n x m n=AmpliarY, m=AmpliarX
    for(int i = 0, k = 0; i < newR.rows ; i++, k += temp){
      if(reduc == 0) k=i;
      uchar * renglon = src.ptr <uchar>(k);
      uchar * renglonR = newR.ptr <uchar>(i);
      for( int j = 0, i2 = 0; j < newR.cols*3; j += nCanales, i2 += temp*3){ //cada desplazamiento va de 3 entres porlo si quiero
        if (reduc == 0 ) i2 = j;                    //quiero dezplzarme 5 pixeles los multiplico por 3 y es el dezplam. real
        RBs=0;
        RGs=0;
        RRs=0;
        for(int m = i; m < temp+m; m++){
          uchar * sum = src.ptr <uchar>(m);
          for (int l = i2; l < temp*3+l; l+=nCanales){
              RBs += *(sum + l + 0);
              RGs += *(sum + l + 1);
              RRs += *(sum + l + 2);
          }
        }
        RBs /= temp*temp;
        RGs /= temp*temp;
        RRs /= temp*temp;
        *( renglonR + j + 0 ) = RBs;
        *( renglonR + j + 1 ) = RGs;
        *( renglonR + j + 2 ) = RRs;
      }
    }
        namedWindow( "EscalamientoPro", WINDOW_NORMAL );
        imshow("PorcentajePro", newR);
}



void funV(int  yl, void* )
{
    int y=yl;
    imshow( "VentanaV", srcR);
    if( y >= nRen){
      int pos = y-nRen;
      for(int i = 0; i < nRen*2-y; i++, pos++){
        uchar * renglon = src.ptr <uchar>(i);
        uchar * renglonr = srcR.ptr <uchar>(pos);
        for( int j = 0; j < nCol; j += nCanales ){
          *( renglonr + j + 0 ) = *( renglon + j + 0 );
          *( renglonr + j + 1 ) = *( renglon + j + 1 );
          *( renglonr + j + 2 ) = *( renglon + j + 2 );
        }
      }
      for( int i = 0; i < y-nRen; i++){
        uchar * renglonr = srcR.ptr <uchar>(i);
        for( int j = 0; j < nCol; j += nCanales ){
          *( renglonr + j + 0 ) = 0;
          *( renglonr + j + 1 ) = 0;
          *( renglonr + j + 2 ) = 0;
        }
      }
    }
    else{
      int pos = nRen-y;
      for( int i = 0; i < y; i++, pos++ ){
        uchar * renglon = src.ptr <uchar>(pos);
        uchar * renglonr = srcR.ptr <uchar>(i);
        for( int j = 0; j < nCol; j += nCanales ){
          *( renglonr + j + 0 ) = *( renglon + j + 0 );
          *( renglonr + j + 1 ) = *( renglon + j + 1 );
          *( renglonr + j + 2 ) = *( renglon + j + 2 );
        }
      }
      for( int i = y; i < nRen; i++){
        uchar * renglonr = srcR.ptr <uchar>(i);
        for( int j = 0; j < nCol; j += nCanales ){
          *( renglonr + j + 0 ) = 0;
          *( renglonr + j + 1 ) = 0;
          *( renglonr + j + 2 ) = 0;
        }
      }
    }
  }

void funH(Mat srclocal,int xl)
{

    int x = xl;
    Mat srcRR = src.clone();

    int nCanales = srclocal.channels();
    int nRen = srclocal.rows;
    int nCol = srclocal.cols * nCanales;
    printf("\\n :::Cantidad %d\n",srclocal.cols*2);
    if( x >= src.cols){
      for( int i = 0; i < nRen; i++ ){
        uchar * renglon = srclocal.ptr <uchar>(i);
        uchar * renglonr = srcRR.ptr <uchar>(i);
        for( int j = src.cols; j < nCol*2 ; j += nCanales ){
          *( renglonr + j-src.cols + x*3 + 0 ) = *( renglon + j-src.cols + 0 );
          *( renglonr + j-src.cols + x*3 + 1 ) = *( renglon + j-src.cols + 1 );
          *( renglonr + j-src.cols + x*3 + 2 ) = *( renglon + j-src.cols + 2 );
        }
        for( int j = 0; j < (x-src.cols)*3; j += nCanales ){
            *( renglonr + j + 0 ) = 0;
            *( renglonr + j + 1 ) = 0;
            *( renglonr + j + 2 ) = 0;
        }
      }
    }
    else{
      for( int i = 0; i < nRen; i++ ){
        int jj;
        uchar * renglon = src.ptr <uchar>(i);
        uchar * renglonr = srcRR.ptr <uchar>(i);
        for( int j = (src.cols-x)*3,jj = 0; j < src.cols*3 ; j += nCanales, jj+=nCanales){
          *( renglonr + jj + 0 ) = *( renglon + j + 0 );
          *( renglonr + jj + 1 ) = *( renglon + j + 1 );
          *( renglonr + jj + 2 ) = *( renglon + j + 2 );
        }
        for( int j = nCol-x*3; j > 0; j -= nCanales ){
            *( renglonr + nCol-j + 0 ) = 0;
            *( renglonr + nCol-j + 1 ) = 0;
            *( renglonr + nCol-j + 2 ) = 0;
        }
      }
    }
    imshow( "VentanaH", srcRR );

  }


int main( int argc, char** argv )
{
 /// Read image ( same size, same type )
 if(argc!=2)
	{
		cout <<"Error: Solo recibe una imagen como unico argumento";
		return -1;
	}
 src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
 if( !src.data ) { printf("Error loading src1 \n"); return -1; }

 nCanales = src.channels();
 nRen = src.rows;
 nCol = src.cols * nCanales;
 //srcR = Mat::zeros( nRen, src.cols, CV_8UC3 );
 srcR = src.clone();

  /// Create Windows
 namedWindow( "VentanaH", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaH", 600, 400 );//parte de lo deaariba
 namedWindow( "VentanaV", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "VentanaV", 600, 400 );//parte de lo deaariba
 namedWindow( "Escalamiento", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 resizeWindow( "Escalamiento", 600, 400 );
 //namedWindow( "EscalamientoPro", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 //resizeWindow( "EscalamientoPro", 600, 400 );
 //namedWindow( "Rotacion", WINDOW_NORMAL ); //normal para modificar ventana a gustos
 //resizeWindow( "Rotacion", 600, 400 );
 //parte de lo deaariba
 /// Create Trackbars
 slider = src.cols;//(int)(nRen/2); //posiscion inicial del Trackbars
 slider2 = nRen;
 // cada que se mueve la barra slider se llama a la funcion funH
 imshow( "VentanaH", srcR );
 imshow( "VentanaV", srcR );
 imshow( "Escalamiento", src);
 //imshow( "EscalamientoPro", src);
 //probando funH(src, 2000);
 //createTrackbar("Horizontal", "VentanaH", &slider, src.cols * 2+2, funH );
 createTrackbar("Vertical", "VentanaV", &slider2, nRen*2, funV);
 createTrackbar("Reducir", "Escalamiento", 0, 4, Reduccion);
 //createTrackbar("Reducir", "EscalamientoPro", 0, 4, ReduccionProm);
 //createTrackbar("Grados", "Rotacion", 0, 360, Rota);
 //printf("Cantidad de renglones %d\n", src.rows);
 //printf("Cantidad de columnas %d\n", src.cols);
 /// Wait until user press some key
 waitKey(0);
 destroyAllWindows();

 return 0;
}
