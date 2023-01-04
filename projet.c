#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char string_inpu[256] ;
char string_path[256] = "D:\C\project\project-kiarashkia138" ;
int end = 1;
FILE *fp;
FILE *undo ;

void create_fuc() // start from 16 
{
    int i = 16 ;
    if(string_inpu[i] == '"') // be careful
    {
        i++;
        while(string_inpu[i] != '"')
        {
            char temp[100] ;
            int j = 0;
            while(string_inpu[i] != '/')
            {
                temp[j] = string_inpu[i];
                j++;
                i++;
            }
            // add string between 17 & i-1 into "D:\C\project\project-kiarashkia138\"
            //  add with backslashe !! 
            i++ ;
        }
        // need ro check a direcrory exits or not and create it 
        fp = fopen("","w");  // will creat a file 
        fclose(fp);
    }
}


void check()
{
    int eenndd = strstr(string_inpu,"exit()");
    int create = strstr(string_inpu,"createfile--file");
    // int temp_de = strstr(string_str,deposit_string);
    // int temp_wi = strstr(string_str,withdraw_string);
    // int temp_ba = strstr(string_str,balance_string);
    // int temp_tr = strstr(string_str,transfer_string);
    // int temp_in = strstr(string_str,info_string);
    
    if(eenndd)
        end = 0 ;
    else if(create)
    {
        create_fuc();
    }
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