#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>


# define MAX_line 2048 


char string_inpu[MAX_line] ;
char filename[MAX_line] ; // filename 
char name_of_file[MAX_line] ; 
char name[MAX_line] ;
char dir[MAX_line] ;
char user_str[MAX_line] ; // user string input
char clipboard[MAX_line] ; // clipboard
char format[10] ; // format of last file for undo 
int end = 1,char_pos = 0 , char_pos2 = 0; // char_pos use for where the next start


void input_in()
{
    gets(string_inpu);
    check();
}


int main()
{
    FILE* out = fopen("output.txt", "w");
    fclose(out);

    while(end)
    {
        input_in();
    }

    remove("output.txt");
}