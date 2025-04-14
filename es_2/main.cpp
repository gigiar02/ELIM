/*
    Data Creazione: 14/04/2025 ore 12:32 :)
    La traccia è nella directory
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#define path "img.jpg"
using namespace cv;
using namespace std;


//All'immagine passata in input vengono aggiunte righe sopra/sotto e colonne a sinistra/destra
 void zeroPadding(Mat in,Mat &out,int top,int bottom,int left,int right)
 {
      //Creazione della nuova matrice che andrebbe inizializzata a 0
      Mat output(top + bottom + in.rows,left + right + in.cols,in.type(), Scalar(0, 0));
      
      //Copia della matrice in nella matrice out che avrà delle righe e delle colonne in piu
      for(int x = 0; x < in.rows; x++)
      {
          //Scorri le colonne della riga corrente
          for(int y = 0; y < in.cols; y++)
          {
              //Il pixel della matrice output sarà uguale a quello della matrice di input
              output.at<uchar>(x + top,y + left) = in.at<uchar>(x,y);
          }
      }
      
      out = output.clone();
 }

//Effettua la convoluzioe dell'immagine con padding 1 e filtro 3*3
void convoluzione(Mat &src,Mat &output,Mat filter)
{
  cout<<"Start"<<endl;
  Mat out = output.clone() ;
  //Pixel out[i][j]
  for(int i = 1; i < src.rows-1; i++)
  {
    for(int j = 1; j < src.cols-1; j++)
    {
      
      int scalar = 0;
      //Calcola il valore del pixel corrente
      for(int h = -1; h < 2; h++)
      {
        for(int s = -1; s < 2; s++)
        {
          //Calcolo della somma dei prodotti
          scalar += src.at<uchar>(i+h,j+s) * filter.at<uchar>(1 + h,1 + s); 
          //cout<<"src = "<<(int) src.at<uchar>(i+h,j+s)<<"filter = "<< (int)filter.at<uchar>(1 + h,1 + s)<<endl; 
          
        }
      }
    
      //Assegnazione al pixel corrente
      scalar/=9;
      out.at<uchar>(i-1,j-1) = scalar;
      if(i < 2)
      {
        //cout<<out.at<uchar>(i-1,j-1)<<" scalar = "<<scalar<<endl;
      }
    }
  }
  
  output = out.clone();
}

//Effettua la convoluzioe dell'immagine con padding 1 e filtro 3*3
void correlazione(Mat &src,Mat &output,Mat filter)
{
  cout<<"Start"<<endl;
  Mat out = output.clone() ;
  //Pixel out[i][j]
  for(int i = 1; i < src.rows-1; i++)
  {
    for(int j = 1; j < src.cols-1; j++)
    {
      
      int scalar = 0;
      //Calcola il valore del pixel corrente
      for(int h = -1; h < 2; h++)
      {
        for(int s = -1; s < 2; s++)
        {
          //Calcolo della somma dei prodotti
          scalar += src.at<uchar>(i-h,j-s) * filter.at<uchar>(1 + h,1 + s); 
          //cout<<"src = "<<(int) src.at<uchar>(i+h,j+s)<<"filter = "<< (int)filter.at<uchar>(1 + h,1 + s)<<endl; 
          
        }
      }
    
      //Assegnazione al pixel corrente
      scalar/=9;
      out.at<uchar>(i-1,j-1) = scalar;
      if(i < 2)
      {
        //cout<<out.at<uchar>(i-1,j-1)<<" scalar = "<<scalar<<endl;
      }
    }
  }
  
  output = out.clone();
}


int main()
{
    Mat in,out,inCopy;
    //Inizializzo il filtro laplaciano
    Mat filter = (cv::Mat_<uchar>(3, 3) << 
        1,  1,   1,
        1,  1,   1,
        1,  1,   1);
    
    //Prendo l'immagine in input
    in = imread(path, IMREAD_GRAYSCALE);
    if ( !in.data ) return -1;
    inCopy = in.clone();
    
    //Applico lo zero padding di uno all'immagine
    zeroPadding(in,out,1,1,1,1);
     
     
    correlazione(out,inCopy,filter);
    
    //Mostro il risultato dell'immagine con il padding
    imshow("Original Image",in);
    //imshow("Padding Output",out);
    imshow("Convolution Output NOT NORMALIZED",inCopy);
    waitKey(0);
    //destroyAllWindows();
  
    return 0;
}

