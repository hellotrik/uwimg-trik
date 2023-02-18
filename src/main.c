#include <math.h>
#include <string.h>
#include "image.h"
#include "test.h"
#include "args.h"

int main(int argc, char **argv)
{
	
    if(argc < 2){
        printf("usage: %s test <hw0 | hw1...>\n", argv[0]);  
    } else if (0 == strcmp(argv[1], "test")){
        if (0 == strcmp(argv[2], "hw0")) test_hw0();
        if (0 == strcmp(argv[2], "hw1")) test_hw1();
        if (0 == strcmp(argv[2], "hw2")) test_hw2();
        if (0 == strcmp(argv[2], "hw3")) test_hw3();
        if (0 == strcmp(argv[2], "hw4")) test_hw4();
        if (0 == strcmp(argv[2], "hw5")) test_hw5();
        if (0 == strcmp(argv[2], "neg")) test_neg();
    }else if (0 == strcmp(argv[1], "opt")) {
		optical_flow_webcam(15, 4, 8,argv[2]);
	}
	
	//~ printf("optical_flow with %s",argv[1]?argv[1]:"usbcam");
	//~ optical_flow_webcam(8, 2,4, argv[1]);
    return 0;
}
