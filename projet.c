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
#include <winuser.h>


#define MAX_line 2048 
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


char string_inpu[MAX_line] ;
char filename[MAX_line] ; // filename 
char name_of_file[MAX_line] ; 
char name[MAX_line] ;
char dir[MAX_line] ;
char user_str[MAX_line] ; // user string input
char clipboard[MAX_line] ; // clipboard
char format[10] ; // format of last file for undo 
int end = 1,char_pos = 0 , char_pos2 = 0; // char_pos use for where the next start


void name_file(char out[])
{
    int len = strlen(filename) ;
    len-- ;

    while(filename[len] != '.' )
    {
        len-- ;
    }
    len-- ;
    int last = len ;

    while (filename[len] != '/' && len >= 0)
    {
        len-- ;
    }
    len++ ;
    int first = len ;
    int j = 0 ;
    for (int i = first; i <= last; i++)
    {
        out[j] = filename[i] ;
        j++ ;
    }
    out[j] = '\0' ;
}


void do_command(int x ,int y ,int mode , int siz)
{
    // add pos with size in string_inpu
    memset(string_inpu, 0, sizeof(string_inpu)) ;
    printf(WHT ":" RESET) ;
    int i = 0 ;
    char input = getchar() ;
    while (input != '\n' && input != '\0')
    {
        string_inpu[i] = input ;
        i++ ;
        input = getchar() ;
    }
}


int do_move(int size_line[] ,int* first_line ,int* x_i , int* y_i , char kind)
{
    char inpu ;
    if(kind != '\0')
        inpu = kind ;
    else
        inpu = getch() ;

    switch (inpu)
    {
        case 'k' :
            if((*(y_i) - *(first_line)) > 4)
            {
                *(y_i) -= 1;
                if(size_line[*(y_i) - 1] < *(x_i))
                {
                    *(x_i) = size_line[*(y_i) - 1] -1 ;
                }
            }
            else if(*(y_i) != 1)
            {
                if(*(first_line) > 1)
                {
                    *(first_line) -= 1;
                    *(y_i) -= 1;
                }
                else
                {
                    *(y_i) -= 1;
                }
                if(size_line[*(y_i) - 1] < *(x_i))
                {
                    *(x_i) = size_line[*(y_i) - 1] -1 ;
                }
            }

            break ;

        case 'j' :
            if(((*(first_line)+23) - *(y_i)) > 4)
            {
                *(y_i) += 1;
                if(size_line[*(y_i) - 1] < *(x_i))
                {
                    *(x_i) = size_line[*(y_i) - 1] -1 ;
                }
            }
            else
            {
                *(first_line) += 1 ;
                *(y_i) += 1;

                if((size_line[*(y_i) - 1] != 0 ) && (size_line[*(y_i) - 1] < *(x_i)))
                {
                    *(x_i) = size_line[*(y_i) - 1] -1 ;
                }
            }
        
            break ;
            
        case 'h' :
            if(*(x_i) > 0)
            {
                *(x_i) -= 1 ;
            }
        
            break ;
            
        case 'l' :
            if(*(x_i) < (size_line[*(y_i) - 1] -1))
            {
                *(x_i) += 1 ;
            }
        
            break ;
            
        default :
            return 1 ;
    }
    return 0 ;
}

// show_window(1,0,0,1,0,1,false) ;
void show_window(int* first_line , int* mode ,int* x , int* y,int* l_x ,int* l_y , bool* saved)
{
    system("cls") ;

    FILE* file2 = fopen(filename , "r") ;
    FILE* file = fopen(filename , "r") ;
    if(file2 == NULL)
    {
        printf("Error\n") ;
        return ;
    }

    int size_line[100] = {0} ;
    char buffer[MAX_line] ;
    char be4clip[MAX_line] ;
    bool keep_reading = true ;
    int line = 1 , k = 0;
    int distance = 23 ;
    int cnt_line = 0 ;
    
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        size_line[line-1] = strlen(buffer) ;
        
        if(feof(file))
            keep_reading = false ;

        if((line >= *(first_line)) && (line <= (*(first_line)+distance)))
        {
            cnt_line++ ;

            int len = strlen(buffer) ; 
            while(len > 144)
            {
                distance -- ;
                len -= 114 ;
            }

            printf(WHT "%3d " , line ,RESET) ;
            if(*(y) <= *(l_y))
            {
                if(line >= *(y) && line <= *(l_y))
                {
                    if(line == *(y) && line == *(l_y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if(i >= *(x) && i <= *(l_x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(l_x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else if(i <= *(x) && i >= *(l_x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else if(line == *(l_y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if(i <= *(l_x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(l_x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else if(line == *(y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if(i >= *(x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            be4clip[k] = buffer[i] ;
                            k++;
                        }
                        printf(CYN "%s",buffer , RESET) ;
                    }
                }
                else
                {
                    printf(WHT "%s" , buffer ,RESET) ;
                }
            }
            else
            {
                if(line <= *(y) && line >= *(l_y))
                {
                    if(line == *(y) && line == *(l_y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if((i >= *(x) && i <= *(l_x)))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(l_x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else if(i <= *(x) && i >= *(l_x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else if(line == *(y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if(i <= *(x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(i == *(x))
                                    be4clip[k] = '\0' ;

                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else if(line == *(l_y))
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            if(i >= *(l_x))
                            {
                                be4clip[k] = buffer[i] ;
                                k++;
                                if(buffer[i] == ' ')
                                    printf(CYN "_" RESET) ;
                                else
                                    printf(CYN "%c",buffer[i],RESET) ;
                            }
                            else
                                printf(WHT "%c",buffer[i],RESET ) ;
                        }
                    }
                    else
                    {
                        for(int i = 0 ; i < strlen(buffer) ; i++)
                        {
                            be4clip[k] = buffer[i] ;
                            k++;
                        }
                        printf(CYN "%s",buffer , RESET) ;
                    }
                }
                else
                {
                    printf(WHT "%s" , buffer ,RESET) ;
                }
            }

            if(!keep_reading) printf("\n") ;
        }

        line++ ;
    }

    if(cnt_line != distance+1)
    {
        while(line >= *(first_line) && line <= (*(first_line)+distance))
        {
            cnt_line++ ;
            printf(WHT "%3d " , line ,RESET) ;

            if(line == *(l_y))
            {
                printf(CYN "_" RESET) ;
            }
            else
            {
                printf(WHT "~" RESET) ;
            }

            printf("\n") ;
            line++;
        }
    }


    char name_fi[100] ;
    name_file(name_fi) ;
    
    if(*(mode) == 0) // NORMAL
    {
        if(*(saved))
        {
            printf(RED "NORMAL   /   " RESET) ;
            printf(GRN "%s \n",name_fi,RESET) ;
        }
        else
        {
            printf(RED "NORMAL   /   " RESET) ;
            printf(GRN "%s  ",name_fi,RESET) ;
            printf(RED "+ \n" RESET) ;
        }
    }
    else if(*(mode) == 1) // VISUAL
    {
        if(*(saved))
        {
            printf(YEL "VISUAL   /   " RESET) ;
            printf(GRN "%s \n",name_fi,RESET) ;
        }
        else
        {
            printf(YEL "VISUAL   /   " RESET) ;
            printf(GRN "%s  ",name_fi,RESET) ;
            printf(RED "+ \n" RESET) ;
        }
    }
    else if(*(mode) == 2) // INSERT
    {
        if(*(saved))
        {
            printf(BLU "INSERT   /   " RESET) ;
            printf(GRN "%s \n",name_fi,RESET) ;
        }
        else
        {
            printf(BLU "INSERT   /   " RESET) ;
            printf(GRN "%s  ",name_fi,RESET) ;
            printf(RED "+ \n" RESET) ;
        }
    }

    fclose(file) ;

    if(*(mode) == 0 )
    {

    }
    else if (*(mode) == 1)
    {
        char input = getch() ;
        if(do_move(size_line,first_line,l_x,l_y,input) == 1)
        {
            if(input == '/')
            {
                *(mode) = 0 ;
                return ;
            }
            memset(string_inpu,0,sizeof(string_inpu));
            int k = 0 ;
            char command[MAX_line] ;
            while(input != '\n')
            {
                command[k] = input ;
                k++;
                input = getch() ;
            }

            int siz = strlen(be4clip) ;

            if(strcmp(command,"d") == 0 || strcmp(command,"Delete") == 0)
            {
                if(*(y) < *(l_y))
                {
                    snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                }
                else if(*(y) == *(l_y))
                {
                    if(*(l_x) >= *(x))
                    {
                        snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                    }
                    else
                    {
                        snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                    }
                }
                else
                {
                    snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                }

                remove_func() ;
            }
            else if(strcmp(command,"Cut") == 0)
            {
                if(*(y) < *(l_y))
                {
                    snprintf(string_inpu,256,"cutstr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                }
                else if(*(y) == *(l_y))
                {
                    if(*(l_x) >= *(x))
                    {
                        snprintf(string_inpu,256,"cutstr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                    }
                    else
                    {
                        snprintf(string_inpu,256,"cutstr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                    }
                }
                else
                {
                    snprintf(string_inpu,256,"cutstr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                }
                cut_func() ;
            }
            else if(strcmp(command,"Copy") == 0 || strcmp(command,"y") == 0)
            {
                // if(*(y) < *(l_y))
                // {
                //     snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                // }
                // else if(*(y) == *(l_y))
                // {
                //     if(*(l_x) >= *(x))
                //     {
                //         snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(y),*(x),siz) ;
                //     }
                //     else
                //     {
                //         snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                //     }
                // }
                // else
                // {
                //     snprintf(string_inpu,256,"removestr--file\"/%s\" --pos %d:%d -size %d -f",filename,*(l_y),*(l_x),siz) ;
                // }
                memset(clipboard ,0 ,sizeof(clipboard)) ;
                for(int i = 0 ; i <= siz ; i++)
                {
                    clipboard[i] = be4clip[i] ;
                }
            }
        }
    }
    else
    {
        memset(string_inpu,0,sizeof(string_inpu));
        char input = getch() ;
        if(input == '/')
            *(mode) = 0 ;

        else if( ( int )input == 8)
        {
            snprintf(string_inpu,256 ,"removestr--file\"/%s\" --pos %d:%d -size 1 -b",filename,y,x) ;
            remove_func() ;
        }
        else
        {
            snprintf(string_inpu,256 ,"insertstr--file\"/%s\" --str \"%c\" --pos %d:%d",filename,input,y,x) ;
            insert_func() ;
        }
    }
}


// void input_in(int* first_line , int* mode , int* x , int* y , int* l_x , int* l_y , bool* saved) 
// {
//     show_window(first_line , mode , x , y , l_x , l_y , saved) ;
// }


int main()
{
    FILE* out = fopen("output.txt", "w");
    fclose(out);

    int* first_line = 1 ;
    int* mode = 0 ;
    int* x = 0 , *l_x = 0 ;
    int* y = 1 , *l_y = 0 ;
    bool* saved = false ;

    while(end)
    {
        show_window(first_line , mode , x , y , l_x , l_y , saved);
    }

    remove("output.txt");
}