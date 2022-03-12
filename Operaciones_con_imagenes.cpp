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
Mat src2;     // mtriz con imagen original2
Mat srcRS;    // mtriz con Resultado de Suma (RS)
Mat srcRR;    // Resultado de Resta (RR)
Mat srcRA;    // R de and
Mat srcRO;    // R de or
Mat srcRN;    // R de not
Mat srcRS2;   // otra manera de suma
Mat srcRR2;    // Resultado de Resta normalizada

// Suma normalizada
void Suma()
{
    for( int i = 0; i < nRen; i++ ){
      uchar * renglonM1 = src.ptr <uchar>(i);
      uchar * renglonM2 = src2.ptr <uchar>(i);
      uchar * renglonR = srcRS.ptr <uchar>(i);
      for( int j = 0; j < nCol; j += nCanales ){
        uchar sumb = *( renglonM1  + j + 0) + *( renglonM2 + j + 0);
        uchar sumg = *( renglonM1  + j + 1) + *( renglonM2 + j + 1);
        uchar sumr = *( renglonM1  + j + 2) + *( renglonM2 + j + 2);
        if( sumb > 255){
            sumb = normaliza(sumb); }
        if( sumg > 255){
            sumg = normaliza(sumg); }
        if( sumr > 255){
            sumr = normaliza(sumr); }
        *( renglonR + j + 0 ) = ( sumb);
        *( renglonR + j + 1 ) = ( sumg);
        *( renglonR + j + 2 ) = ( sumr);
      }
    }
}

uchar normaliza( uchar aux ){
  uchar r;
  r = (r*255)/r;
  return r;
}

// Resta con balor absoluto
void Resta(){
  for( int i = 0; i < nRen; i++ ){
    uchar * renglonM1 = src.ptr <uchar>(i);
    uchar * renglonM2 = src2.ptr <uchar>(i);
    uchar * renglonR = srcRR.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
      uchar sumb = *( renglonM1  + j + 0) - *( renglonM2 + j + 0);
      uchar sumg = *( renglonM1  + j + 1) - *( renglonM2 + j + 1);
      uchar sumr = *( renglonM1  + j + 2) - *( renglonM2 + j + 2);
      if( sumb < 0 ){
          sumb = abs(sumb);}
      if( sumg < 0 ){
          sumg = abs(sumg);}
      if( sumr < 0 ){
          sumr = abs(sumr);}
      *( renglonR + j + 0 ) = ( sumb);
      *( renglonR + j + 1 ) = ( sumg);
      *( renglonR + j + 2 ) = ( sumr);
    }
  }
}

int normaR(int a,int b){
  int x;
  int min = a < b? a: b;
  int max = a > b? a: b;
  if (( b - a ) == 0 ) return 0;
  x = ( ( ( a - b ) *(-1 ) ) * 255 ) / (b-a);

  return x;
}
//Resta normalizada
void Resta2(){
  for( int i = 0; i < nRen; i++ ){
    uchar * renglonM1 = src.ptr <uchar>(i);
    uchar * renglonM2 = src2.ptr <uchar>(i);
    uchar * renglonR = srcRR2.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
      uchar sumb = *( renglonM1  + j + 0) - *( renglonM2 + j + 0);
      uchar sumg = *( renglonM1  + j + 1) - *( renglonM2 + j + 1);
      uchar sumr = *( renglonM1  + j + 2) - *( renglonM2 + j + 2);
      if( sumb < 0 ){
          sumb = normaR( *( renglonM1  + j + 0), *( renglonM2 + j + 0) ); }
      if( sumg < 0 ){
          sumg = normaR( *( renglonM1  + j + 1), *( renglonM2 + j + 1) ); }
      if( sumr < 0 ){
          sumr = normaR( *( renglonM1  + j + 2), *( renglonM2 + j + 2) ); }
      *( renglonR + j + 0 ) = ( sumb);
      *( renglonR + j + 1 ) = ( sumg);
      *( renglonR + j + 2 ) = ( sumr);
    }
  }
}

void fun_and (){
  for( int i = 0; i < nRen; i++ ){
    uchar * renglonM1 = src.ptr <uchar>(i);
    uchar * renglonM2 = src2.ptr <uchar>(i);
    uchar * renglonR = srcRA.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
      *( renglonR + j + 0 ) = (*( renglonM1 + j + 0 ) & *( renglonM2 + j + 0 ));
      *( renglonR + j + 1 ) = (*( renglonM1 + j + 1 ) & *( renglonM2 + j + 1 ));
      *( renglonR + j + 2 ) = (*( renglonM1 + j + 2 ) & *( renglonM2 + j + 2 ));
    }
  }
}

void fun_or (){
  for( int i = 0; i < nRen; i++ ){
    uchar * renglonM1 = src.ptr < uchar >( i );
    uchar * renglonM2 = src2.ptr < uchar >( i );
    uchar * renglonR = srcRO.ptr < uchar >( i );
    for( int j = 0; j < nCol; j += nCanales ){
      *( renglonR + j + 0 ) = (*( renglonM1 + j + 0 ) | *( renglonM2 + j + 0 ));
      *( renglonR + j + 1 ) = (*( renglonM1 + j + 1 ) | *( renglonM2 + j + 1 ));
      *( renglonR + j + 2 ) = (*( renglonM1 + j + 2 ) | *( renglonM2 + j + 2 ));
    }
  }
}

void fun_not (){
  for( int i = 0; i < nRen; i++ ){
    uchar * renglonM1 = src.ptr < uchar >( i );
    uchar * renglonR = srcRN.ptr < uchar >( i );
    for( int j = 0; j < nCol; j += nCanales ){
      *( renglonR + j + 0 ) = ~( *( renglonM1 + j + 0 ) );
      *( renglonR + j + 1 ) = ~( *( renglonM1 + j + 1 ) );
      *( renglonR + j + 2 ) = ~( *( renglonM1 + j + 2 ) );
    }
  }
}

// Suma solo si se pasa lepone 255
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
 nCol2 = src2.cols * nCanales2;

 if( (nRen!=nRen2) || (nCol != nCol2) ){
   printf("Diferentes tamaños de imagenes, Adios\n");
   return -1;
  }
 srcRS = src.clone();
 srcRR = src.clone();
 srcRA = src.clone();
 srcRO = src.clone();
 srcRN = src.clone();
 srcRS2 = src.clone();
 srcRR2 = src.clone();

  /// Create Windows
 namedWindow( "Suma", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Suma", 550, 400);//parte de lo dearriba define tamaño
 namedWindow( "Suma2", WINDOW_NORMAL); //normal para modificar ventana a gusto
 resizeWindow( "Suma2", 550, 400);
 namedWindow( "Resta", WINDOW_NORMAL);
 resizeWindow( "Resta", 550, 400);
 namedWindow( "RestaNorma", WINDOW_NORMAL);
 resizeWindow( "RestaNorma", 550, 400);
 namedWindow( "AND", WINDOW_NORMAL);
 resizeWindow( "AND", 550, 400);
 namedWindow( "OR", WINDOW_NORMAL);
 resizeWindow( "OR", 550, 400);
 namedWindow( "NOT", WINDOW_NORMAL);
 resizeWindow( "NOT", 550, 400);
 namedWindow( "Original A", WINDOW_NORMAL);
 resizeWindow( "Original A", 550, 400);
 namedWindow( "Original B", WINDOW_NORMAL);
 resizeWindow( "Original B", 550, 400);

 Suma();
 imshow( "Suma", srcRS);

 Suma2();
 imshow( "Suma2", srcRS2);

 Resta();
 imshow( "Resta", srcRR);

 Resta2();
 imshow( "RestaNorma", srcRR2);

 fun_and();
 imshow( "AND", srcRA);

 fun_or();
 imshow( "OR", srcRO);

 fun_not();
 imshow( "NOT", srcRN);

 imshow( "Original A", src);
 imshow( "Original B", src2);
 imwrite("Suma_Normalizada_3.jpg", srcRS);
 imwrite("Suma_NO_Normalizada_3.jpg", srcRS2);

 waitKey(0);
 destroyAllWindows();

 return 0;
}
