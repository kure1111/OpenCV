
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <string>
using namespace cv;
using namespace std;

//0 es negro, 255 es blanco
Mat recorte(string);
double D_2_Image(Mat A, Mat B);
void Img_2_vector(int cont, Mat Img_aux);
void imprime_matriz(int A[3025*2][46]);
void promedio_images(int A[3025*2][46]);
Mat vec_2_img();

int ntest = 45;
int ntes_aprobar = 1;
int tam_col = 3025*2;
int tamx = 55;
int tamy = 55;
int Vec_img[3025*2][46];
int promedio[3025*2];
Mat src;
int main(int argc, char** argv){

  if(argc!=2) //cantidad de argumentos, imagen1 y imagen 2  ---> 0,1,2
   {
      cout <<"no hay imagen\n";
      return -1;
    }
  src = imread(argv[1],0);
  if( !src.data ) { printf("Error loading src1 \n"); return -1; }
  string nombre = "I";
  string num;
  string aux;
  for(int cont = 0; cont < ntest; cont++){
    aux = nombre + to_string(cont+1) + ".png";
    cout << aux << " cargada" <<'\n';
    Mat Img_aux = recorte(aux); //regresa imagen cortada de la dimencion 55 x 55
    Img_2_vector(cont, Img_aux); //convierte imagenes en columnas
  }
  Mat solouna = recorte(argv[1]); // imagen de entrada de terminal
  Img_2_vector(ntest, solouna);
  promedio_images(Vec_img);
  Mat imProm = vec_2_img();
  //imprime_matriz(Vec_img);
  double distancia  = D_2_Image(imProm, solouna);
  printf("La distancia entre las dos imagenes es ::: %.2f\n", distancia);

  namedWindow( "img_Entrada", WINDOW_NORMAL); //normal para modificar ventana a gusto
  resizeWindow( "img_Entrada", 550, 400);
  imshow("img_Entrada", solouna);
  namedWindow( "img_Promedio_Model_2", WINDOW_NORMAL); //normal para modificar ventana a gusto
  resizeWindow( "img_Promedio_Model_2", 550, 400);
  imshow("img_Promedio_Model_2", imProm);

  waitKey(0);
  destroyAllWindows();
  return 0;
}

Mat vec_2_img(){
  Mat recortada = Mat::zeros(tamy, tamx, CV_8UC1); // matriz de n x m n=AmpliarY, m=AmpliarX
  int nCan = recortada.channels();
  int nR = recortada.rows;
  int nC = recortada.cols * nCan;
  for(int i = 0; i < nR; i++){
    uchar * renglonR = recortada.ptr < uchar >(i);
    for(int j = 0; j < nC; j += nCan){
      *( renglonR + j) = promedio[tamx*j*2+i];
    }
  }
  return recortada;
}

void Img_2_vector(int cont, Mat Img_aux){
  int nCanales = Img_aux.channels();
  int nRen = Img_aux.rows;
  int nCol = Img_aux.cols * nCanales;
  for( int i = 0; i < nRen; i++ ){
    uchar * renglon = Img_aux.ptr <uchar>(i);
    for( int j = 0; j < nCol; j += nCanales ){
        Vec_img[tamx*j*2+i][cont] = *( renglon + j);
        Vec_img[tamx+3*i*2+j][cont] = *( renglon + j);
    }
  }
}

void imprime_matriz(int A[3025*2][46]){
  for(int j = 0; j < 10; j++){
    for(int i = 0; i < ntest+ntes_aprobar; i++)
      printf("%d ", A[j][i]);
    printf("\n");
  }
}

void promedio_images(int A[3025*2][46]){
  float aux;
  for(int k = 0; k < tam_col; k++)
    promedio[k] = 0;
  for(int j = 0; j < tam_col; j++){
    for(int i = 0; i < ntest; i++){
      if(A[j][i] == 255)
        promedio[j] = promedio[j]+1;
    }
  }
  aux = 0.0;
  for(int k = 0; k < tam_col; k++){
      aux = promedio[k]/(ntest*1.0);
      if(aux < 0.65)//.55
        promedio[k] = 0;
      else promedio[k] = 255;
    }
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

Mat recorte(string name){
  Mat sep = imread(name, 0);
  if(!sep.data) { printf("Error loading src1 \n"); exit (-1);}
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
  //printf("xi: %d\n", xi);
  //printf("yi: %d\n", yi);
  //printf("xf: %d\n", xf);
  //printf("yf: %d\n", yf);
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

  Size size(tamx,tamy);//the dst image size,e.g.100x100
  Mat dst;
  resize(recortada,dst,size);//resize image
  threshold( dst, dst, 150, 255,0); //los que stanpor debajo de 230 mandalo a 0 y por aariba mando a 255, 0 solo 0 u 255
  //namedWindow( "ROI_2", WINDOW_NORMAL); //normal para modificar ventana a gusto
  //resizeWindow( "ROI_2", 550, 400);
  //imshow("ROI_2", dst);
  return dst;
}
