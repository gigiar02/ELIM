/*
    Data Creazione: 06/04/2025 ore 14:08 :)
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
 
 //Ogni pixel è dato dal valore medio del suo intorno 3*3
 void mask(Mat postPadding,Mat &postMask)
 {
    int value = 0;
    Mat out(postPadding.rows - 1, postPadding.cols - 1,postPadding.type(),Scalar(0,0));
    
    //Scorro ogni pixel
    for(int x = 1; x < postPadding.rows - 1; x++)
    {
      for(int y = 1; y < postPadding.cols - 1; y++)
      {
          //Intorno 3*3
          for(int i = x - 1; i < (x-1) + 3; i++)
          {
            for(int j = y - 1; j < (y-1) + 3; j++)
            {
              //Calcolo valore
              value += postPadding.at<uchar>(i,j);
            }
          }
          
          //Media e inserimento del valore nel pixel corrente
          value = value/9;
          out.at<uchar>(x-1,y-1) = value;
          value = 0;
      }
    }
    
    //Salvo il risultato ottenuto
    postMask = out.clone();
    
 }
 
 
int main()
{
    Mat in,postPadding,postMask;
    string path(PATH);
    in = imread(path, IMREAD_GRAYSCALE);
 
    if ( !in.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    //Applica un padding di 1 alla matrice
    zeroPadding(in,postPadding,1,1,1,1);
    //Applica una maschera 3*3 ad ogni pixel
    mask(postPadding,postMask);
    
    
    //Mostra il risultato
      imshow("in",in);
      imshow("padding", postPadding);
      imshow("mask:",postMask);
      
      waitKey(0);
    
  
    return 0;
}

