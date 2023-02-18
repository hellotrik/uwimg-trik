#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"
// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}


float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
	x=x<0?0:x>=im.w?im.w-1:x;
	y=y<0?0:y>=im.h?im.h-1:y;
	c=c<0?0:c>=im.c?im.c-1:c;
    return im.data[im.w*(c*im.h+y)+x];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
	if(x<0||x>=im.w||y<0||y>=im.h||c<0||c>=im.c) return;
	im.data[im.w*(c*im.h+y)+x]=v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
	memcpy(copy.data, im.data, sizeof(float) * im.w * im.h * im.c);
    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
	int i,k=im.h*im.w;
	for(i=0;i<k;i++)
		gray.data[i]=im.data[i]*0.299+im.data[k+i]*0.587+im.data[2*k+i]*0.114;
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
	c=c<0?0:c>=im.c?im.c-1:c;
	int i;
	int cc=c*im.w*im.h;
	for(i=cc;i<cc+im.w*im.h;i++)im.data[i]+=v;
}

void scale_image(image im, int c, float v)
{
    // TODO Fill this in
	c=c<0?0:c>=im.c?im.c-1:c;
	int i;
	int cc=c*im.w*im.h;
	for(i=cc;i<cc+im.w*im.h;i++)im.data[i]*=v;
}

image get_channel(image im, int c){
	c=c<0?0:c>=im.c?im.c-1:c;
	image r=make_image(im.w,im.h,1);
	int n=im.w*im.h;
	memcpy(r.data,im.data+n*c,sizeof(float)*n);
	return r;
}

void clamp_image(image im)
{
    // TODO Fill this in
	int i;
	for(i=0;i<im.w*im.h*im.c;i++)
		if(im.data[i]>1)im.data[i]=1;
		else if(im.data[i]<0)im.data[i]=0;
	
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
	int i,k=im.w*im.h;
	float h,h1,s,v,c;
	float r,g,b;
	for(i=0;i<k;i++){
		r=im.data[i];
		g=im.data[k+i];
		b=im.data[2*k+i];
		v=three_way_max(r,g,b);
		c=v-three_way_min(r,g,b);
		s=v==0?0:c/v;
		h1=c==0?0:r==v?(g-b)/c:
			g==v?(b-r)/c+2:
			(r-g)/c+4;
		h=h1<0?h1/6+1:h1/6;
		im.data[i]=h;
		im.data[i+k]=s;
		im.data[i+2*k]=v;
	}	
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
	int i,hi,k=im.w*im.h;
	float h,h1,s,v,c,f;
	float r,g,b;
	float p,q,t;
	for(i=0;i<k;i++){
		h=im.data[i];
		s=im.data[k+i];
		v=im.data[2*k+i];
		c=v*s;
		h1=6*h;
		hi=(int)h1;
		f=h1-hi;
		p= v-c;
		q= v*(1-f*s);
		t=v*(1-(1-f)*s);
		switch(hi){
		case 0:
			r=v;g=t;b=p;break;
		case 1:
			r=q;g=v;b=p;break;
		case 2:
			r=p;g=v;b=t;break;
		case 3:
			r=p;g=q;b=v;break;
		case 4:
			r=t;g=p;b=v;break;
		default:
			r=v;g=p;b=q;break;			
		}
		im.data[i]=r;
		im.data[i+k]=g;
		im.data[i+2*k]=b;
	}	
}



