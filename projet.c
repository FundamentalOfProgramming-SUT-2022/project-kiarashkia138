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
char dir[MAX_line] ;
char user_str[MAX_line] ; // user string input
char format[10] ; // format of last file for undo 
int end = 1,char_pos = 0; // char_pos use for where the next start

// char_pos will be space or \0 
void bringefilename(int start) // will create directory // start positin is ( " ) or ( / ) // char_pos bring back ( space ) or ( \0 )
{
    memset(filename,0,sizeof(filename)) ;

    int temp_cnt = 0;
    int cnt_dir = 0;
    if(string_inpu[start] == '"')
    {
        start += 2; // after slash 
        char_pos = start ;
        while(string_inpu[start] != '"')
        {
            if(string_inpu[start] != '/')
                filename[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                filename[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                CreateDirectory (filename, NULL);
                filename[temp_cnt] = string_inpu[start] ;
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
        while(string_inpu[start] != '\0' && string_inpu[start] != ' ' && string_inpu[start] != '\n' ) //  && string_inpu[start] != '-'
        {
            if(string_inpu[start] != '/')
                filename[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                filename[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                CreateDirectory (filename, NULL);
                filename[temp_cnt] = string_inpu[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
            char_pos ++ ;
        }
    }
    filename[temp_cnt] = '\0' ;
}


void find_next_str(int type) // char_pos = pos of space // type for having(1) or not having(0) or both(2) "
{
    // not usefull for replace 
    memset(user_str,0,sizeof(user_str));
    if(type == 1) // bring what is between ""
    {
        while(string_inpu[char_pos] != '"')
        {
            char_pos ++ ;
        }
        char_pos++;
        int first_pos = char_pos ;
        int last_pos =strlen(string_inpu);
        last_pos-- ;
        while(string_inpu[last_pos] != '"')
        {
            last_pos-- ;
        }
        last_pos-- ;
        for (char_pos; char_pos <= last_pos; char_pos++ )
        {
            user_str[char_pos - first_pos] = string_inpu[char_pos] ;
        }
        char_pos += 2 ;
        // char_pos will be on space 
    }
    else if(type == 2)  // use after --str -->> += 7
    {
        char_pos += 7 ;
        if(string_inpu[char_pos] == '"') find_next_str(1) ;
        else find_next_str(0) ;
    }
    else
    {
        char_pos++ ;
        while(string_inpu[char_pos] != ' ')
        {
            char_pos++ ;
        }
        char_pos++ ;
        int i = 0;
        while(string_inpu[char_pos] != ' ')
        {
            user_str[i] = string_inpu[char_pos] ;
            i++ ;
            char_pos++;
        }
        // char pos will be in space
    }
}


int find_options()
{
    if(string_inpu[char_pos] == ' ')
    {
        char temp[MAX_line] ;
        int i = 0 ;
        char_pos++;
        while(string_inpu[char_pos] != '\0' && string_inpu[char_pos] != ' ')
        {
            temp[i] = string_inpu[char_pos] ;
            char_pos++;
            i++ ;
        }
        int count = strstr(temp,"-count") ;
        int at = strstr(temp,"-at");
        int byword = strstr(temp,"-byword") ;
        int all = strstr(temp,"-all") ;
        if(count) return 1;
        else if(at) return 2 ;
        else if(byword) return 3 ;
        else if(all) return 10 ;
    }
    else return 0 ;
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


// check 
void check() // after adrress  comes space for seperating word 
{
    int eenndd = strstr(string_inpu,"exit");
    int create = strstr(string_inpu,"createfile--file");// createfile--file/root/test.txt
    int insert = strstr(string_inpu,"insertstr--file"); // insertstr--file/root/test.txt( )--str( )"something"( )--pos( )i:j
    int undoo = strstr(string_inpu,"undo--file");
    int catt = strstr(string_inpu,"cat--file");
    int findd = strstr(string_inpu,"find--file"); // find--file/root/something( )--str( )["]something["]( )[-count/-at/-byword]( )[-all]
    int removee = strstr(string_inpu,"removestr--file");
    int copyy = strstr(string_inpu,"copystr--file");
    int cutt = strstr(string_inpu,"cutstr--file");
    int pastee = strstr(string_inpu,"pastestr--file");
    
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