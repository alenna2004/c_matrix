#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "errorcode.h"


void raise_error(int error_code, const char* error_messege){
	errno = error_code;
	perror(error_messege);
	exit(1);
}