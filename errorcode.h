#ifndef ERR_H
#define ERR_H


enum _error_codes
{
    INVALID_INPUT = 22,
    PERMITED_OPERATION = 1,
    MEM_ALLOC_FAIL = 12,
};

void raise_error(int erroe_code, const char* error_messege);

#endif