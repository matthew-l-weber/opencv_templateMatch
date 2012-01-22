/*
 * TemplateMatching 1.0
 *
 *
 * © Copyright 2012, Rockwell Collins, Inc.  All rights reserved.
 *           Modifications added by Matt Weber
 *
 *
 *
 * @author 	  Nashruddin Amin <me@nashruddin.com>
 * @version   1.0
 * @website	  http://www.nashruddin.com
 */
#define TEMPLATE_MATCH 0
#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "time.h"

int main()
{
	IplImage	*img;
	IplImage	*tpl;
	IplImage	*res;
	IplImage	*tmp;
	IplImage	*thrsh;
	IplImage	*tmpThrsh;
	CvPoint		minloc, maxloc;
	double		minval, maxval;
	int		img_width, img_height;
	int		tpl_width, tpl_height;
	int		res_width, res_height;
	int		quality[3];

	
	
	
	/* load reference image */
	img = cvLoadImage( "a.bmp", CV_LOAD_IMAGE_GRAYSCALE );
	/* always check */
	if( img == 0 ) {
		fprintf( stderr, "Cannot load file %s!\n", "a.bmp" );
		return 1; 
	}

	/* load template image */
	tpl = cvLoadImage( "b.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	/* always check */
	if( tpl == 0 ) {
		fprintf( stderr, "Cannot load file %s!\n", "b.bmp" );
		return 1;
	}
	
	
	/* get image's properties */
	img_width  = img->width;
	img_height = img->height;
	tpl_width  = tpl->width;
	tpl_height = tpl->height;
	res_width  = img_width - tpl_width + 1;
	res_height = img_height - tpl_height + 1;

	/* create new image for template matching computation */
	res = cvCreateImage( cvSize( res_width, res_height ), IPL_DEPTH_32F, img->nChannels );
	
	printf("WORKING>>> \n");
	
	clock_t t1=clock();	
	
	/*cvMatchTemplate( img, tpl, res, CV_TM_SQDIFF );
	cvMatchTemplate( img, tpl, res, CV_TM_SQDIFF_NORMED );
	cvMatchTemplate( img, tpl, res, CV_TM_CCORR );*/
	cvMatchTemplate( img, tpl, res, CV_TM_CCORR_NORMED );
	/*cvMatchTemplate( img, tpl, res, CV_TM_CCOEFF );
	cvMatchTemplate( img, tpl, res, CV_TM_CCOEFF_NORMED );*/

	clock_t t2=clock();
        printf("%f seconds of processing\n t1: %d   t2: %d  \n Clockspersec: %d \n", 
                 (double)(t2-t1)/(double)CLOCKS_PER_SEC, t1,t2, CLOCKS_PER_SEC);
	
	cvMinMaxLoc( res, &minval, &maxval, &minloc, &maxloc, 0 );
	
	/* draw red rectangle */
	cvRectangle( img, 
				 cvPoint( minloc.x, minloc.y ), 
				 cvPoint( minloc.x + tpl_width, minloc.y + tpl_height ),
				 cvScalar( 0, 0, 255, 0 ), 1, 0, 0 );

	/* save images */	
	tmp=cvCreateImage( cvSize( res->width, res->height ), IPL_DEPTH_8U, res->nChannels );
	cvConvertScaleAbs(res, tmp, 256.0,0.0);
	quality[0] = CV_IMWRITE_JPEG_QUALITY;
	quality[1] = 100;
	quality[2] = 0;
	cvSaveImage("output.bmp",tmp,quality);
	cvSaveImage("square.bmp",img,quality);	
	
	cvReleaseImage( &img );
	cvReleaseImage( &tpl );
	cvReleaseImage( &res );
	cvReleaseImage( &tmp );

	return 0;
}

