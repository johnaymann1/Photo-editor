// Program: Photoedit.cpp
// Purpose: program that can put a filter on a greyscale image
// Author:  John Ayman Naim Aziz
// Id:20210107
// Date:    7 April 2022
// Version: 3.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include<vector>
#include<algorithm>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void negativeimage ();
void rotateimage ();
void darkenligten ();
void merge_image();
void detect_image_edges();
void flip();


int main()
{
    int filter;
    char contin;
    int x=0;
program:
  loadImage();
cout<<"Please choose the filter you want to apply on the image: \n (1)-Invert colors \n (2)-Rotate image \n (3)-Merge \n (4)-Darken or lighten \n (5)-detect image edges \n (6)-Flip \n";
cin>>filter;
switch(filter){
case 1:
    negativeimage();
    break;
case 2:
    rotateimage();
    break;
case 3:
     merge_image();
     break;
case 4:
     darkenligten();
     break;
case 5:
     detect_image_edges();
     break;
case 6:
     flip();
     break;
}
  saveImage();
cout<<"Do you want to do another image ?\n";
cout<<"(y) for yes or (n) for no"<<endl;
contt:
cin>>contin;

if(contin=='y'|| contin=='Y'){
    goto program;
}
else if(contin=='n'|| contin=='N'){
    exit(0);
}
else{
    x=1;
}
while(x=1){
    cout<<"PLEASE ENTER A VALID LETTER (y) OR (n) \n";
    goto contt;
}
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the name of the image after edit: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void negativeimage() {//This function inverts the color of greyscale images
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        image[i][j] = 255-image[i][j];

    }
  }
}

void rotateimage(){//This function rotate the imagee by 90 degree clockwise direction
    for (int i=0;i<SIZE/2;i++) {
    for (int j=i;j<SIZE-i-1;j++)
    {
            int arr=image[i][j];
            image[i][j]=image[255-j][i];
            image[255-j][i]=image[255-i][255-j];
            image[255-i][255-j]=image[j][255-i];
            image[j][255-i]=arr;
    }
  }

}
void merge_image(){
  char image2FileName[100];
  //get the second image file name
   cout << "Enter the second image file name: ";
   cin >> image2FileName;
   strcat (image2FileName, ".bmp");
   readGSBMP(image2FileName, new_image);
   for(int i = 0; i<SIZE ; i++){
      for(int j = 0; j<SIZE ; j++){
        //get the avgerage of both images
        new_image[i][j] = new_image[i][j]/2;
         image[i][j] = image[i][j]/2;
         //merging the two images together
        image[i][j]+=new_image[i][j];
      }
   }
}
void darkenligten () {
  //taking the user choice
  cout << "1.Lighhten \n" << "2.Darken" << endl;
  int n;
  cin >> n;
    for(int i = 0; i<SIZE ; i++){
        for(int j = 0; j<SIZE ; j++){
          //making the picture ligter in a specefic range
          if(n ==1)
              if(image[i][j]>=200)
              continue;
              else
              image[i][j]+=50;
          //making the picture darker in a specefic range
          else if (n==2)
            if(image[i][j]<=70)
            continue;
            else
            image[i][j]-=60;
      }
    }
}
void detect_image_edges() {
  for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(image[i][j] - image[i+1][j] <= 25 && image[i][j] - image[i][j+1] <= 25)
                image[i][j] = 255 ;
            else
                image[i][j] = 0;
        }
    }
}
void flip() {
    char f;
    cout<<"Enter (v) to flip verically and (h) to flip horizontaly \n";
enterf:
    cin>>f;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (f == 'h' || f=='H'){
                new_image[i][j] = image[225 - i][j];}
            else if (f == 'v' || f=='V'){
                new_image[i][j] = image[i][255 - j];
            }
            else{
                cout<<"Please enter (v) to flip verically and (h) to flip horizontaly \n";
                goto enterf;
            }
        }
    }
      for (int k = 0; k < SIZE; k++) {
        for (int d = 0; d < SIZE; d++) {
            image[k][d]=new_image[k][d];
        }
    }

}
