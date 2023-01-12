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


void bringefilename(int start) // will create directory // start positin is ( " ) or ( / ) // char_pos bring back ( - ) or ( \0 )
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
        char_pos ++ ;
    }

    else
    {
        start++ ; // after slash
        char_pos = start ;
        // char temp[MAX_line] ;
        // char temp_dir[MAX_line] ;
        while(string_inpu[start] != '\0' && string_inpu[start] != ' ' && string_inpu[start] != '\n' ) //  && string_inpu[start] != '-'
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


long long int into_num(int i ) // i is position of start
{
    
    long long ret = 0 ;
    while (string_inpu[i] != ':' && string_inpu[i] != '-' && string_inpu[i] != ' ' && string_inpu[i] != '\n' && string_inpu[i] != '\0')
    {   
        switch (string_inpu[i])
        {
            case '0' :
                ret *= 10 ;
                break;

            case '1': 
                ret *= 10 ;
                ret += 1;
                break;
            
            case '2':
                ret *= 10 ;
                ret += 2;
                break;

            case '3':
                ret *= 10 ;
                ret += 3;
                break;

            case '4':
                ret *= 10 ;
                ret += 4;
                break;

            case '5':
                ret *= 10 ;
                ret += 5;
                break;

            case '6':
                ret *= 10 ;
                ret += 6;
                break;

            case '7':
                ret *= 10 ;
                ret += 7;
                break;

            case '8':
                ret *= 10 ;
                ret += 8;
                break;

            case '9':
                ret *= 10 ;
                ret += 9;
                break;
        }
        i++ ;
        char_pos++ ; 
    }
    return ret;
}


void error(int number) 
{
    switch(number)
    {
        case 1:
            printf("Error create file. \n");
            break;
        case 2:
            printf("Error open file. \n");
            break;
        case 3:
            printf("Error...! something went wrong!! \n");
            break;
        case 4:
            printf("Error...! unknown move please use -f(forward) or -b(backward). \n");
            break;
    }
}


void print_std(char* buffer)
{
    printf("%s\n", buffer);
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
void insert_func() // start from 15 //(new)insertstr--file<address> --str<> --pos<>
{
    char_pos = 0 ; // will return pos of ( " ) or ( - )
    bringefilename(15) ;
    save_for_undo() ;
    find_dir() ;
    strcat(dir,"tempfileforcopy") ;
    strcat(dir,format) ;
    FILE* new = fopen(dir,"w") ;
    FILE* file = fopen(filename,"r") ;

    if(file == NULL)
    {
        error(2) ;
        return ;
    }
    if(new == NULL)
    {
        error(3);
        return ;
    }

    char replace[MAX_line] ;
    // char_pos++ ;  // will start from after " 
    while(string_inpu[char_pos] != '"')
    {
        char_pos++ ;
    }
    char_pos++ ; // start from after "
    bool keep_reading = true ;
    int i = 0 ;
    while(keep_reading)
    {
        if(string_inpu[char_pos] == '"')
        {
            if(string_inpu[char_pos+1] == '-')
            {
                if(string_inpu[char_pos+2] == '-')
                {
                    if(string_inpu[char_pos+3] == 'p')
                    {
                        if(string_inpu[char_pos+4] == 'o')
                        {
                            if(string_inpu[char_pos+5] == 's')
                            {
                                keep_reading = false ;
                                break ;
                            }
                        }
                    }
                }
            }
        }
        replace[i] = string_inpu[char_pos] ;
        i++ ;
        char_pos++ ;
    }
    // char_pos -> --pos
    char_pos += 5 ; // show the first number 
    int num_line = into_num(char_pos) ;
    int pos_in_file = into_num(char_pos+1) ;

    int corrent_line = 1 ;
    keep_reading = true ;
    char buffer[MAX_line] ;
    while(keep_reading)
    {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file))
        {
            keep_reading = false ;
            if(corrent_line == num_line)
            {
                for(int k = 0; k < pos_in_file ; k++)
                {
                    fprintf(new,"%c",buffer[k]);
                }
                fprintf(new,"%s",replace) ;
                int k = pos_in_file;
                while(buffer[k] != '\0' )
                {
                    fprintf(new,"%c",buffer[k]) ;
                    k++ ;
                }
            }
            else 
                fputs(buffer,new) ;
        }
        else if(corrent_line == num_line)
        {
            for(int k = 0; k < pos_in_file ; k++)
            {
                fprintf(new,"%c",buffer[k]);
            }
            fprintf(new,"%s",replace) ;
            int k = pos_in_file;
            while(buffer[k] != '\0' )
            {
                fprintf(new,"%c",buffer[k]) ;
                k++ ;
            }
        }
        else
        {
            fputs(buffer,new) ;
        }
        corrent_line++ ;
    }

    fclose(file); 
    fclose(new);
    remove(filename) ;
    rename(dir,filename) ;
}

// cat file
void cat_func() // start from 9
{
    bringefilename(9);
    FILE* file = fopen(filename,"r");
    if(file == NULL)
    {
        error(2) ;
    }

    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file))
        {
            keep_reading = false ;
            print_std(buffer) ;
        }
        else print_std(buffer) ;
    }
    fclose(file) ;
}

// remove
void remove_func() // start from 15 // needs a lot of work !!
{
    char_pos = 0 ; // will bring ( " ) or ( - )
    bringefilename(15) ;
    save_for_undo() ; // for undo 

    char_pos += 5 ; // pos of first num 
    int num_line = into_num(char_pos) ; // line
    int num_pos = into_num(char_pos+1) ; // pos of first char
    char_pos += 5 ;
    int num_size = into_num(char_pos) ; // size for delete
    char kindofmove = string_inpu[char_pos+1] ; // kind of move (r) or (f)

    find_dir() ;
    strcat(dir,"tempforremove") ;
    strcat(dir,format) ;
    FILE* file = fopen(filename ,"r") ;
    FILE* temp = fopen(dir,"w") ;

    if(file == NULL) 
    {
        error(2) ;
        return ;
    }
    else if(temp == NULL) 
    {
        error(3) ;
        return ;
    }

    bool keep_reading = true ;
    char buffer[MAX_line] ;
    int corrent_line = 1 ;
    int corrent_pos = 0 ;
    int size_del = 0 ;
    // find the new pos (old position - size)
    // for finding the first one shoud be deleted
    if(kindofmove == 'b')
    {
        for (int i = 1; i <= num_size; i++)
        {
            if(num_pos == 0 )
            {
                num_line -= 1 ;
            }
            num_pos -= i ; // if line change will bring back negetive valiue
        }
    }

    // delete chars
    if(kindofmove == 'f')
    {
        while(keep_reading)
        {
            memset(buffer, 0, sizeof(buffer));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
            if(corrent_line == num_line)
            {
                while(buffer[corrent_pos] != '\0' )
                {
                    if(corrent_pos >= num_pos && corrent_pos < (num_pos + num_size))
                    {
                        size_del++ ;
                    }
                    else
                    {
                        fprintf(temp,"%c",buffer[corrent_pos]) ;
                    }
                    corrent_pos++ ;
                }
                if(size_del < num_size)
                {
                    num_size -= size_del ;
                    num_line += 1 ;
                } 
            }
            else
            {
                fputs(buffer,temp) ;
            }
        }
    }
    else if(kindofmove == 'b')
    {
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            fgets(buffer,MAX_line,file);
            if(feof(file))
            {
                keep_reading = false ;
                if(corrent_line == num_line)
                {

                }
                else fputs(buffer,temp) ;
            }

            else if(corrent_line == num_line)
            {
                
            }

            else
            {
                fputs(buffer,temp) ;
            }
        }
    }
    else error(4) ;

    fclose(file) ;
    fclose(temp) ;

    remove(filename) ;
    rename(dir,filename) ;
}

// copy
// void copy_func()
// {

// }

// cut
// void cut_func()
// {

// }

// paste
// void paste_func()
// {

// }

// find 
void find_func() // start from 10 // find--file/root/something--str["]something["][-count/-at/-byword][-all]
{
    char_pos = 0 ;
    bringefilename(10);
    FILE* file = fopen(filename,"r");
    char_pos += 5 ;
    int j = 0 ;
    char find_str[MAX_line] ;
    int shouid_count = 0 , shouid_at = 0 , shouid_word = 0,shouid_all = 0 ,num_word = 0;
    if(string_inpu[char_pos] == '"' )
    {
        char_pos ++ ;
        while (string_inpu[char_pos] != '\0' )
        {
            if(string_inpu[char_pos] == '-') // check for ( -count ) ( -at ) ( -byword )
            {
                if(string_inpu[char_pos + 1] == 'c')
                {
                    if(string_inpu[char_pos + 2] == 'o')
                    {
                        if(string_inpu[char_pos + 3] == 'u')
                        {
                            if(string_inpu[char_pos + 4] == 'n')
                            {
                                if(string_inpu[char_pos + 5] == 't')
                                {
                                    char_pos += 6;
                                    shouid_count = 1 ;
                                    break;
                                }
                            }
                        }
                    }
                }
                else if(string_inpu[char_pos + 1] == 'a')
                {
                    if(string_inpu[char_pos + 2] == 't')
                    {
                        char_pos += 3 ;
                        shouid_at = 1 ;
                        int which_n = into_num(char_pos) ; // come n with zero space 
                        break;
                    }
                }
                else if(string_inpu[char_pos + 1] == 'b')
                {
                    if(string_inpu[char_pos + 2] == 'y')
                    {
                        if(string_inpu[char_pos + 3] == 'w')
                        {
                            if(string_inpu[char_pos + 4] == 'o')
                            {
                                if(string_inpu[char_pos + 5] == 'r')
                                {
                                    if(string_inpu[char_pos + 6] == 'd')
                                    {
                                        char_pos += 7;
                                        shouid_word = 1 ;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            find_str[j] = string_inpu[char_pos] ;
            j++ ;
            char_pos ++ ;
        }
        if(string_inpu[char_pos] == '-')
        {
            if(string_inpu[char_pos + 1] == 'a')
            {
                if(string_inpu[char_pos + 2] == 'l')
                {
                    if(string_inpu[char_pos + 3] == 'l')
                    {
                        shouid_all = 1 ;
                    }
                }
            }
        }


        if(shouid_count )
        {

        }
        else if(shouid_at)
        {

        }
        else if(shouid_word)
        {

        }
        else if (shouid_all )
        {

        }
        else
        {

        }
    }
    else
    {

    }
}


// undo 
void undo_func() // will copy undo temp to this file // just undo the  last file or will do nonscnene
{
    char temp2[MAX_line] = "root/undo/temp2" ;
    char temp[MAX_line] = "root/undo/temp" ;
    strcat(temp,format); 
    strcat(temp2,format); 
    FILE* undo2 = fopen(temp2,"w") ;
    FILE* file = fopen(filename,"r") ;

    if(file == NULL )
    {
        error(3);
        return ;
    }
    if(undo2 == NULL)
    {
        error(3);
        return;
    }
    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file))
        {
            keep_reading = false ;
            fputs(buffer,undo2) ;
        }
        else
        {
            fputs(buffer,undo2) ;
        }
    }
    fclose(file) ;
    fclose(undo2) ;

    remove(filename) ;

    rename(temp,filename) ;
    rename(temp2,temp) ;
}


void save_for_undo() // must be used before undo
{
    char temp[MAX_line] = "root/undo/temp";
    int i = 0 , j = 0 ,check = 0;
    while(filename[i] != '\0' && filename[i] != '\n') // for file format
    {
        if(filename[i] == '.')
        {
            while(filename[i] != '\0' && filename[i] != '\n')
            {
                format[j] = filename[i];
                j++ ;
                i++ ;   
                check = 1 ; 
            }
        }
        if(check == 0) i++ ;
    }
    strcat(temp,format) ;
    FILE* undo = fopen(temp,"w") ;
    FILE* file = fopen(filename,"r") ;
    if(file == NULL )
    {
        error(3);
        return ;
    }
    if(undo == NULL)
    {
        error(3);
        return;
    }
    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file)) 
        {
            keep_reading = false ;
            fputs(buffer,undo) ;
        }
        else fputs(buffer,undo) ;
    }
    
    fclose(undo) ;
    fclose(file) ;
}

// check 
void check() // after adrress  comes space for seperating word 
{
    int eenndd = strstr(string_inpu,"exit");
    int create = strstr(string_inpu,"createfile--file");
    int insert = strstr(string_inpu,"insertstr--file");
    int undoo = strstr(string_inpu,"undo--file");
    int catt = strstr(string_inpu,"cat--file");
    int removee = strstr(string_inpu,"removestr--file");
    int copyy = strstr(string_inpu,"copystr--file");
    int cutt = strstr(string_inpu,"cutstr--file");
    int pastee = strstr(string_inpu,"pastestr--file");
    int findd = strstr(string_inpu,"find--file"); // find--file/root/something --str["]something["] [-count/-at/-byword] [-all]
    
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
    else if(catt)
    {
        cat_func() ;
    }
    else if(removee)
    {
        remove_func() ;
    }
    // else if(copyy)
    // {
    //     copy_func() ;
    // }
    // else if(cutt)
    // {
    //     cut_func() ;
    // }
    // else if(pastee)
    // {
    //     paste_func() ;
    // }
    else if(findd)
    {
        find_func() ;
    }
    else
        printf("Invalid input\n");
}


void input_in()
{
    gets(string_inpu);
    check();
}


int main()
{
    while(end)
    {
        input_in();
    }
}