#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in;
    return get_pixel(im,x+0.5,y+0.5,c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
	image g=make_image(w,h,im.c);
	int i,j,k;
	float a,a1,b,b1,m,n;
	//ax+b=y a*-.5+b=-.5 a*w+b=im.w
	a=im.w/(float)w;
	a1=im.h/(float)h;
	b=(a-1)/2;
	b1=(a1-1)/2;
	for(i=0;i<w;i++){
		m=a*i+b;
		for(j=0;j<h;j++){
			n=j*a1+b1;
			for(k=0;k<im.c;k++){
				set_pixel(g,i,j,k,nn_interpolate(im,m,n,k));
			}
		}
	}
	
    return g;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
	float v1,v2,v3,v4,d1,d2,d3,d4;
	v1=get_pixel(im,x,y,c);
	v2=get_pixel(im,x+1,y,c);
	v3=get_pixel(im,x,y+1,c);
	v4=get_pixel(im,x+1,y+1,c);
	d1=x-(int)x;
	d2=1-d1;
	d3=y-(int)y;
	d4=1-d3;
    return v1*d2*d4+v2*d1*d4+v3*d2*d3+v4*d1*d3;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
	image g=make_image(w,h,im.c);
	int i,j,k;
	float a,a1,b,b1,m,n;
	//ax+b=y a*-.5+b=-.5 a*w+b=im.w
	a=im.w/(float)w;
	a1=im.h/(float)h;
	b=(a-1)/2;
	b1=(a1-1)/2;
	for(i=0;i<w;i++){
		m=a*i+b;
		for(j=0;j<h;j++){
			n=j*a1+b1;
			for(k=0;k<im.c;k++){
				set_pixel(g,i,j,k,bilinear_interpolate(im,m,n,k));
			}
		}
	}
    return g;
}

