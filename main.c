#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "test.h"


int main(int argc, char **argv)
{
    char *opts = "m:"; 
    char *mode = "menu";
    int opt; 
    while(optind < argc){
    	if ((opt = getopt(argc, argv, opts)) != -1){
	        switch(opt) {
	            case 'm':{ 
	                mode = optarg;
	                if(strcmp(mode,"menu") != 0 && strcmp(mode,"test") != 0){
	                	printf("You can choose onle between test and menu modes\n");
	                	return 1;
	                }
	                break;
	            }
	        }
	    }
    }
    if(strcmp(mode,"menu") == 0){
    	create_and_print_menu();
    }
    else{
    	run_tests();
    }
    return 0;
}