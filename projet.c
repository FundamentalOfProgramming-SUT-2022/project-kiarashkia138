#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char string_inpu[256] ;
char string_path[256] = "D:\\C\\project\\project-kiarashkia138" ;
char* firstofpath ;
int end = 1;
FILE *fp;
FILE *undo ;

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


void create_fuc() // start from 16 
{
    firstofpath = &string_path[0] ;
    int i = 16 ;
    if(string_inpu[i] == '"') // be careful
    {
        i++;
        int siz = 0;
        while(string_inpu[i] != '"')
        {
            char temp[100] ;
            int j = 0;
            while(string_inpu[i] != '/' )
            {
                temp[j] = string_inpu[i];
                j++;
                i++;
                siz++ ;
            }
            // add string between 17 & i-1 into "D:\C\project\project-kiarashkia138\"
            //  add with backslashe !! 
            char fin[siz] ;
            for (int k = 0; k < siz; k++)
            {
                fin[k] = temp[k] ;
            }
            siz = 0 ;
            firstofpath = concat(firstofpath, "\\");
            firstofpath = concat(firstofpath, fin);
            // printf("%s\n", firstofpath);
            i++ ;
        }
        // need ro check a direcrory exits or not and create it 
        fp = fopen(firstofpath,"w");  // will creat a file 
        fclose(fp);
    }
    else{

        while(string_inpu[i] != '\n' && string_inpu[i] != ' ' && string_inpu[i] != '\0')
        {
            // char* temp = (char*)malloc(100*sizeof(char));
            char temp[100] ;
            int siz = 0;
            int j = 0;
            while(string_inpu[i] != '/' && string_inpu[i] != '\n' && string_inpu[i] != ' ' && string_inpu[i] != '\0' )
            {
                temp[j] = string_inpu[i];
                j++;
                i++;
                siz++;
            }
            // add string between 17 & i-1 into "D:\C\project\project-kiarashkia138\"
            //  add with backslashe !! 
            char fin[siz] ;
            for (int k = 0; k < siz; k++)
            {
                fin[k] = temp[k] ;
            }
            siz = 0 ;
            firstofpath = concat(firstofpath, "\\");
            firstofpath = concat(firstofpath, fin);
            // printf("%s\n", firstofpath);
            i++ ;
        }
        // need ro check a direcrory exits or not and create it 
        fp = fopen(firstofpath,"w");  // will creat a file 
        fclose(fp);
    }
}


void check()
{
    int eenndd = strstr(string_inpu,"exit");
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