/*
    Data Creazione: 14/04/2025 ore 12:32 :)
    La traccia è nella directory
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#define PATH "img.jpg"
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
void convoluzione(Mat &src,Mat&out,Mat filter)
{
  //Pixel out[i][j]
  for(int i = 0; i < src.rows; i++)
  {
    for(int j = 0; j < src.cols; j++)
    {
      int scalar = 0;
      //Calcola il valore del pixel corrente
      for(int h = -1; h < 2; h++)
      {
        for(int s = -1; s < 2; s++)
        {
          //Calcolo della somma dei prodotti
          scalar += src.at<float>(i+h,j+s) * filter.at<float>(1 + h,1 + s); 
        }
      }
      
      //Assegnazione al pixel corrente
      out.at<float>(i,j) = scalar;
    }
  }
}

//La prerotazione per una maggiore efficienza viene implementata a riga 53 invertendo i segni del pixel preso in src
void correlazione(Mat &src,Mat &out,Mat filter)
{
  //Pixel out[i][j]
  for(int i = 0; i < src.rows; i++)
  {
    for(int j = 0; j < src.cols; j++)
    {
      int scalar = 0;
      //Calcola il valore del pixel corrente
      for(int h = -1; h < 2; h++)
      {
        for(int s = -1; s < 2; s++)
        {
          //Calcolo della somma dei prodotti
          scalar += src.at<float>(i-h,j-s) * filter.at<float>(1 + h,1 + s); 
        }
      }
      
      //Assegnazione al pixel corrente
      out.at<float>(i,j) = scalar;
    }
  }
}

int main()
{
    Mat in,out;
    Mat filter(3,3);

    //Inizializzo il filtro
    for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        filter.at<float>(i,j) = i + j;
      }
    }
    
    //Prendo l'immagine in input
    in = imread(path, IMREAD_GRAYSCALE);
    if ( !in.data ) return -1;
    
    //Applico lo zero padding di uno all'immagine
    zeroPadding(in,out,1,1,1,1);
     
    //Mostro il risultato dell'immagine con il padding
    imshow(in);
    imshow(out);
      
    convoluzione(in,out,filter);
      waitKey(0);
    
  
    return 0;
}

