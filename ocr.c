#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core_c.h>
using namespace cv;
using namespace std;


int pl=0;
int b,g,r;
int i , j;
long unsigned int h1=0;
long unsigned int h2=0;
long unsigned int w1=0;
long unsigned int w2=0;
long unsigned int cl=0;
IplImage* analyze;

void rect();
void endrect();

int main()
{

IplImage* input;
IplImage* blacknwhite;
char abc[30];
gets(abc);
fflush(stdin);
input=cvLoadImage(abc,1);
cvNamedWindow("ii", CV_WINDOW_NORMAL );
cvShowImage("ii",input);
printf("nChannels=%d width=%d height=%d widthstep=%d depth=%d align=%d color model=%s nsize=%d\n",
input->nChannels,input->width,input->height,input->widthStep,input->depth,input->align,input->colorModel,input->nSize);
blacknwhite=cvCreateImage(cvSize(input->width, input->height ),input->depth, input->nChannels );
uchar *pinput = (uchar*)input->imageData;               //saving data pointer of input image as pinput
uchar *poutput = ( uchar* )blacknwhite->imageData;           //saving data pointer of blacknwhite image as poutput
//FILE *p;p=fopen("art.txt","a");
for(i=0;i<input->height;i++)
{
   for(j=0;j<input->width;j++)
	{
	   //printf("(%d,%d) : %d %d %d\n",i+1,j,b,g,r);Sleep(0);
		r=pinput[i*input->widthStep + j*input->nChannels + 2];
		b=pinput[i*input->widthStep + j*input->nChannels + 0];
		g=pinput[i*input->widthStep + j*input->nChannels + 1];
		if((r>200)&&(b>200)&&(g>200))           //white bgrnd to black
		{
		   poutput[i*input->widthStep + j*input->nChannels + 2]=0;   //copying red elements of input to blacknwhite
			poutput[i*input->widthStep + j*input->nChannels + 0]=0;   //initialising blue elements of blacknwhite image as 0
			poutput[i*input->widthStep + j*input->nChannels + 1]=0;   //initializing green elements of blacknwhite image as 0;
			//Note: initialing B and G as 0 may be excluded but recommended as it may take garbage value, test it yourself
		}
		else
		//if((r<=220)&&(b<=220)&&(g<=220))                                    //anyclr to black except white
		{
			//fprintf(p,"%d",r);
			poutput[i*input->widthStep + j*input->nChannels + 2]=255;   //copying red elements of input to blacknwhite
			poutput[i*input->widthStep + j*input->nChannels + 0]=255;   //initialising blue elements of blacknwhite image as 0
			poutput[i*input->widthStep + j*input->nChannels + 1]=255;   //initializing green elements of blacknwhite image as 0;
		}
	}
	//fprintf(p,"\n");Sleep(0);
}
cvNamedWindow("aa",CV_WINDOW_AUTOSIZE);
cvShowImage("aa",blacknwhite);
cvSaveImage("blacknwhite.jpg",blacknwhite);
//cvWaitKey(0);
cvDestroyWindow("ii");
cvDestroyWindow( "aa" );
cvReleaseImage( &blacknwhite );
cvReleaseImage( &input );

//------------------------------------------------------------------------------------------------------------------------------------------------------------

int r1,b1,g1;

//IplImage* analyze;
IplImage* blackwhite;
blackwhite=cvLoadImage("blacknwhite.jpg",1);

analyze=cvCreateImage(cvSize(blackwhite->width, blackwhite->height ),blackwhite->depth, blackwhite->nChannels );

uchar *qinput = (uchar*)blackwhite->imageData;               //saving data pointer of input image as pinput

//FILE *p;p=fopen("art.txt","a");
cout<<endl<<blackwhite->height<<" "<<blackwhite->width<<endl;
for(i=0;i<blackwhite->height;i++)                                               // height = i = height
{
   for(j=0;j<blackwhite->width;j++)                                             // width = j = length
	{ //cout<<j<<" , ";Sleep(30);
		r=qinput[i*blackwhite->widthStep + j*blackwhite->nChannels + 2];
		b=qinput[i*blackwhite->widthStep + j*blackwhite->nChannels + 0];
		g=qinput[i*blackwhite->widthStep + j*blackwhite->nChannels + 1];
		
		if((r<220)&&(g<220)&&(b<220))     //anyclr to black except white
		{
			pl=1;
		}
		if((r==55)&&(g==248)&&(b==35))    //green to green
		{
			pl=2;
		}
		if((r>=220)&&(g>=220)&&(b>=220))  //white to white
		{
		        pl=2;
+			r1=qinput[(i+2)*blackwhite->widthStep + (j+2)*blackwhite->nChannels + 2];
+			b1=qinput[(i+2)*blackwhite->widthStep + (j+2)*blackwhite->nChannels + 0];
+			g1=qinput[(i+2)*blackwhite->widthStep + (j+2)*blackwhite->nChannels + 1];
+			if((r==r1)&&(b==b1)&&(g==g1))
+		        {
+			     if((h1==0)&&(w1==0))
+			     {h1=i;w1=j;}
+
+			     h2=i;w2=j;
+			     if((h2>h1+30)&&((w2-16)<(w1+16))) {rect();}
+			}
		}
		if(pl==1)
		{
		   qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 2]=0;
		   qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 0]=0;
		   qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 1]=0;
		}
		if(pl==2)
		{
         
                        //cout<<endl<<i<<" "<<j;
			qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 2]=r;
			qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 0]=b;
			qoutput[i*blackwhite->widthStep + j*blackwhite->nChannels + 1]=g;
		}
		pl=0;
	}
}
rect();
cout<<"\nh1 is : "<<h1<<" w1 is : "<<w1<<endl<<"h2 is : "<<h2<<" w2 is : "<<w2<<endl;

cvNamedWindow("analyze",CV_WINDOW_AUTOSIZE);
cvShowImage("analyze",analyze);
cvWaitKey(0);


return 0;
}
void rect()
{
	cvRectangle(analyze,cvPoint(w1+6,h1-3),cvPoint(w2+9,h2+3),cvScalar(55,248,35));

}
void endrect()
{
	cvRectangle(analyze,cvPoint(w1-20,h1-4),cvPoint(w2+6,h2+4),cvScalar(55,248,35));
	//cout<<endl<<w1-20<<" "<<h1-4<<endl<<w2+6<<" "<<h2+4;
}
