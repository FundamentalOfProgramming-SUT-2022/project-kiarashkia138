#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <stdbool.h>


# define MAX_line 2048 


char string_inpu[256] ;
char filename[MAX_line] ; // filename 
int end = 1;


void bringefilename(int start) // will create directory
{
    // char filename[MAX_line] ;
    // char* filename ;
    int temp_cnt = 0;
    int cnt_dir = 0;
    if(string_inpu[start] == '"')
    {
        start += 2; // after slash 
        // char temp[MAX_line] ;
        char temp_dir[MAX_line] ;
        while(string_inpu[start] != '"')
        {
            filename[temp_cnt] = string_inpu[start] ;
            if(string_inpu[start] != '/')
                temp_dir[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                temp_dir[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                CreateDirectory (temp_dir, NULL);
                temp_dir[temp_cnt] = string_inpu[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
        }
    }

    else
    {
        start++ ; // after slash
        // char temp[MAX_line] ;
        char temp_dir[MAX_line] ;
        while(string_inpu[start] != '\0' && string_inpu[start] != '\n' && string_inpu[start] != ' ')
        {
            filename[temp_cnt] = string_inpu[start] ;
            if(string_inpu[start] != '/')
                temp_dir[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                temp_dir[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                CreateDirectory (temp_dir, NULL);
                temp_dir[temp_cnt] = string_inpu[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
        }
    }
    filename[temp_cnt] = '\0' ;
}


void error(int number) 
{
    switch(number)
    {
        case 1:
            printf("coudn't create file \n");
            break;
        case 2:
            printf("coudn't open file \n");
            break;
    }
}


void create_func() // start from 16     // will create only one directory need work for second and more directories !!!!!!!!
{
    bringefilename(16);
    FILE* file = fopen(filename,"a");
    if(file == NULL)
        error(1) ;
    fclose(file);
}



// undo 
void undo_func() // will copy undo temp to this file
{
    
}

void save_for_undo() // must be used before undo
{
    char temp[MAX_line] = "root/undo/temp";
    int i = 0 , j = 0;
    char format[10] ;
    while(filename[i] != '\0' && filename[i] != '\n') // for file format
    {
        if(filename[i] == '.')
        {
            format[j] = filename[i];
            j++ ;
        }
        i++ ;    
    }
    strcat(temp,format) ;
    FILE* undo = fopen(temp,"w") ;
    FILE* file = fopen(filename,"r") ;

    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        fgets(buffer,MAX_line,file) ;
        if(feof(file)) keep_reading = false ;
        else fputs(buffer,undo) ;
    }
}

void check()
{
    int eenndd = strstr(string_inpu,"exit");
    int create = strstr(string_inpu,"createfile--file");
    int insert = strstr(string_inpu,"insertstr--file");
    int undoo = strstr(string_inpu,"undo--file");
    
    if(eenndd)
        end = 0 ;
    else if(create)
    {
        create_func();
    }
    // else if(insert)
    // {
    //     // insert_func();
    // }
    else if(undoo)
    {
        undo_func();
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