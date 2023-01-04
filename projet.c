#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char string_inpu[256] ;
int end = 1;




void check()
{
    int eenndd = strstr(string_inpu,"exit()");
    // int temp_re = strstr(string_str,register_string);
    // int temp_de = strstr(string_str,deposit_string);
    // int temp_wi = strstr(string_str,withdraw_string);
    // int temp_ba = strstr(string_str,balance_string);
    // int temp_tr = strstr(string_str,transfer_string);
    // int temp_in = strstr(string_str,info_string);
    
    if(eenndd)
        end = 0 ;
    else
        printf("Invalid input\n");
}
void input_in()
{
    fgets(string_inpu,256,stdin);
    check();
}

int main()
{
    while(end)
    {
        input_in();
    }
}