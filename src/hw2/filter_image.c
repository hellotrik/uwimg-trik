#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

void l1_normalize(image im)
{
    // TODO
	int i,j=im.w*im.h*im.c;
	float v=0;
	for(i=0;i<j;i++)v+=im.data[i];
	if(v!=0){
		v=1/v;
		for(i=0;i<j;i++)im.data[i]*=v;
	}
}

image make_box_filter(int w)
{
    // TODO
	int i,j=w*w;
	float v=1./j;
	image box=make_image(w,w,1);
	for(i=0;i<j;++i)box.data[i]=v;
    return box;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
	image g;
	int i,j,k,l,t,n,i1,j1,k1;
	float v;
	if(preserve==1){
		g=make_image(im.w,im.h,im.c);
		n=filter.c>>1;
	}
	else {
		g=make_image(im.w,im.h,1);
		n=0;
	}
	l=filter.w>>1;
	t=filter.h>>1;
	
	for(k=0;k<(preserve==1?im.c:1);k++)for(i=0;i<im.w;i++)for(j=0;j<im.h;j++){
		v=0;
		for(k1=0;k1<filter.c;k1++)for(i1=0;i1<filter.w;i1++)for(j1=0;j1<filter.h;j1++){
				if(filter.c==1&&preserve!=1){
					int k2;
					for(k2=0;k2<im.c;k2++)
					v+=get_pixel(im,i+i1-l,j+j1-t,k+k2+k1-n)*get_pixel(filter,i1,j1,k1);
				}else
					v+=get_pixel(im,i+i1-l,j+j1-t,k+k1-n)*get_pixel(filter,i1,j1,k1);
			}
		//printf("%d,%d,%f",i,j,v);
		set_pixel(g,i,j,k,v);
	}
	return g;
}

image make_highpass_filter()
{
    // TODO
	image g=make_image(3,3,1);
	g.data[1]=-1;
	g.data[3]=-1;
	g.data[4]=4;
	g.data[5]=-1;
	g.data[7]=-1;
	//~ l1_normalize(g);
    return g;
}

image make_sharpen_filter()
{
    // TODO
    image g=make_image(3,3,1);
	g.data[1]=-1;
	g.data[3]=-1;
	g.data[4]=5;
	g.data[5]=-1;
	g.data[7]=-1;
	//~ l1_normalize(g);
    return g;
}

image make_emboss_filter()
{
    // TODO
    image g=make_image(3,3,1);
	g.data[0]=-2;
	g.data[1]=-1;
	g.data[3]=-1;
	g.data[4]=1;
	g.data[5]=1;
	g.data[7]=1;
	g.data[8]=2;
	//~ l1_normalize(g);
    return g;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
	int hw=6*sigma+1;
	if((hw&1)==0)++hw;
	int hf=hw>>1;
	image g=make_image(hw,hw,1);
	int i,j;
	float sig2=sigma*sigma;
	float twopisig2=1/(TWOPI*sig2);
	float sig2two=1/(2*sig2);
	for(i=0;i<hw;i++)for(j=0;j<hw;j++)set_pixel(g,i,j,0,exp(-((i-hf)*(i-hf)+(j-hf)*(j-hf))*sig2two)*twopisig2);
	l1_normalize(g);
    return g;
}

image add_image(image a, image b)
{
    // TODO
	image g =copy_image(a);
	int i,j,k;
	for(i=0;i<a.w;i++)for(j=0;j<a.h;j++)for(k=0;k<a.c;k++)g.data[(k*a.h+j)*a.w+i]+=(i>=b.w||j>=b.h||k>=b.c)?0:get_pixel(b,i,j,k);
    return g;
}

image sub_image(image a, image b)
{
    // TODO
	image g =copy_image(a);
	int i,j,k;
	for(i=0;i<a.w;i++)for(j=0;j<a.h;j++)for(k=0;k<a.c;k++)g.data[(k*a.h+j)*a.w+i]-=(i>=b.w||j>=b.h||k>=b.c)?0:get_pixel(b,i,j,k);
    return g;
}

image make_gx_filter()
{
    // TODO
    image g=make_image(3,3,1);
	g.data[0]=-1;
	g.data[2]=1;
	g.data[3]=-2;
	g.data[5]=2;
	g.data[6]=-1;
	g.data[8]=1;
	//~ l1_normalize(g);
    return g;
}

image make_gy_filter()
{
    // TODO
    image g=make_image(3,3,1);
	g.data[0]=-1;
	g.data[1]=-2;
	g.data[2]=-1;
	g.data[6]=1;
	g.data[7]=2;
	g.data[8]=1;
	//~ l1_normalize(g);
    return g;
}

void feature_normalize(image im)
{
    // TODO
	float mi=im.data[0],ma=im.data[0],delta;
	int i;
	for(i=1;i<im.w*im.h*im.c;i++){
		if(mi>im.data[i])mi=im.data[i];
		if(ma<im.data[i])ma=im.data[i];
	}
	delta=ma-mi;
	if(delta!=0){
		delta=1/delta;
		for(i=0;i<im.w*im.h*im.c;i++)
			im.data[i]=(im.data[i]-mi)*delta;
	}
}

void threshold_image(image im, float thresh){
	int i;
	for(i=0;i<im.w*im.h*im.c;++i)im.data[i]=im.data[i]>thresh?1:0;
}


image *sobel_image(image im)
{
    // TODO
	image gx=make_gx_filter(),gy=make_gy_filter();
	image gxx=convolve_image(im,gx,0),gyy=convolve_image(im,gy,0);
	free_image(gx);free_image(gy);
	
	image *gt=calloc(2, sizeof(image));
	gt[0]=make_image(im.w,im.h,1);
	gt[1]=make_image(im.w,im.h,1);
	int i;
	for(i=0;i<im.w*im.h;i++){
		gt[0].data[i]=sqrt(gxx.data[i]*gxx.data[i]+gyy.data[i]*gyy.data[i]);
		gt[1].data[i]=atan2(gyy.data[i],gxx.data[i]);
	}
	
	free_image(gxx);	
	free_image(gyy);
    return gt;
}
image sobel(image im)
{
    // TODO
	image gx=make_gx_filter(),gy=make_gy_filter();
	image gxx=convolve_image(im,gx,0),gyy=convolve_image(im,gy,0);
	free_image(gx);free_image(gy);
	image gt=make_image(im.w,im.h,3);
	int i,n=im.w*im.h,n2=sizeof(float)*n;
	for(i=0;i<n;i++){
		gt.data[i]=atan2(gyy.data[i],gxx.data[i]);
	}
	memcpy(gt.data+n,gxx.data,n2);
	memcpy(gt.data+2*n,gyy.data,n2);
	free_image(gxx);	
	free_image(gyy);
    return gt;
}

image colorize_sobel(image im)
{
    // TODO
	image *sobel = sobel_image(im);
    feature_normalize(sobel[0]);
    feature_normalize(sobel[1]);
    image res = make_image(im.w, im.h, im.c);
	int n=im.w*im.h;
	int size=sizeof(float)*n;
    memcpy(res.data,sobel[1].data,size);
    memcpy(res.data+n,sobel[0].data,size);
    memcpy(res.data+2*n,sobel[0].data,size);
    	
    free_image(sobel[1]);
    free_image(sobel[0]);
    free(sobel);
    hsv_to_rgb(res);
    return res;
}
