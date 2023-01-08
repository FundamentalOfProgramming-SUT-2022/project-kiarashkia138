#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <stdbool.h>


# define MAX_line 2048 


char string_inpu[MAX_line] ;
char filename[MAX_line] ; // filename 
char temp_dir[MAX_line] ; // directory 
char dir[MAX_line] ;
char format[10] ; // format of last file for undo 
int end = 1,char_pos = 0; // char_pos use for where the next start


void bringefilename(int start) // will create directory // start positin is ( " ) or ( / ) 
{
    // char filename[MAX_line] ;
    // char* filename ;
    memset(filename,0,sizeof(filename)) ;
    memset(temp_dir,0,sizeof(temp_dir)) ;

    int temp_cnt = 0;
    int cnt_dir = 0;
    if(string_inpu[start] == '"')
    {
        start += 2; // after slash 
        char_pos = start ;
        // char temp[MAX_line] ;
        // char temp_dir[MAX_line] ; // directory
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
            char_pos ++ ;
        }
    }

    else
    {
        start++ ; // after slash
        char_pos = start ;
        // char temp[MAX_line] ;
        char temp_dir[MAX_line] ;
        while(string_inpu[start] != '\0' && string_inpu[start] != '\n' && string_inpu[start] != ' ' && string_inpu[start] != '-')
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
            char_pos ++ ;
        }
    }
    filename[temp_cnt] = '\0' ;
    temp_dir[temp_cnt] = '\0' ;
}


void find_dir()
{
    memset(dir,0,sizeof(dir)) ;
    int i = 0 ;
    bool conti = true ;
    while(filename[i] != '\0')
    {
        char temp[MAX_line] ;
        int j = 0 ;
        while(filename[i] != '/')
        {
            if(filename[i] == '.')
            {
                conti = false ;
                break ;
            }
            temp[j] = filename[i] ;
            i++ ;
            j++ ;
        }
        temp[j] = filename[i] ;
        if(conti) strcat(dir,temp) ;
        i++ ;
    }
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

// create file 
void create_func() // start from 16     // can't create file or dir with ( - )
{
    bringefilename(16);
    FILE* file = fopen(filename,"a");
    if(file == NULL)
        error(1) ;
    fclose(file);
}

// insert file
void insert_func() // start from 15 //insertstr--file<address>--str<>--pos<>
{
    char_pos = 0 ; // will return pos of ( " ) or ( - )
    bringefilename(15) ;
    save_for_undo() ;
    strcat(dir,"tempfileforcopy") ;
    strcat(dir,format) ;
    FILE* new = fopen(dir,"w") ;
    FILE* file = fopen(filename,"r") ;

    char replace[MAX_line] ;

    char_pos++ ; // i want to check for ( " )
    while(string_inpu[char_pos] != '"')
    {
        char_pos++ ;
    }
    char_pos++ ;
    

}

// undo 
void undo_func() // will copy undo temp to this file
{
    char temp2[MAX_line] = "root/undo/temp2" ;
    char temp[MAX_line] = "root/undo/temp" ;
    strcat(temp,format); 
    strcat(temp2,format); 
    FILE* undo2 = fopen(temp2,"w") ;
    FILE* file = fopen(filename,"r") ;

    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        fgets(buffer,MAX_line,file) ;
        if(feof(file)) keep_reading = false ;
        else
        {
            fputs(buffer,undo2) ;
        }
    }
    fclose(file) ;
    fclose(undo2) ;

    remove(filename) ;

    rename(temp2,temp) ;
    rename(temp,filename) ;
}

void save_for_undo() // must be used before undo
{
    char temp[MAX_line] = "root/undo/temp";
    int i = 0 , j = 0;
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
    
    fclose(undo) ;
    fclose(file) ;
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
    else if(insert)
    {
        insert_func();
    }
    else if(undoo)
    {
        undo_func();
    }
    else
        printf("Invalid input\n");
}


void input_in()
{
    fgets(string_inpu,MAX_line,stdin);
    check();
}


int main()
{
    while(end)
    {
        input_in();
    }
}