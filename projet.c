#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <dir.h>
#include <process.h>
#include <stdbool.h>
#include <dirent.h>


# define MAX_line 2048 


char string_inpu[MAX_line] ;
char filename[MAX_line] ; // filename 
char name_of_file[MAX_line] ; 
char dir[MAX_line] ;
char user_str[MAX_line] ; // user string input
char clipboard[MAX_line] ; // clipboard
char format[10] ; // format of last file for undo 
int end = 1,char_pos = 0 , char_pos2 = 0; // char_pos use for where the next start

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


void bringefilename2 (char filename2[] ,int start)
{
    memset(filename2,0,sizeof(filename2)) ;

    int temp_cnt = 0;
    int cnt_dir = 0;
    if(string_inpu[start] == '"')
    {
        start += 2; // after slash 
        char_pos = start ;
        while(string_inpu[start] != '"')
        {
            if(string_inpu[start] != '/')
                filename2[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                filename2[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                filename2[temp_cnt] = string_inpu[start] ;
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
                filename2[temp_cnt] = string_inpu[start] ;
            else if(string_inpu[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                filename2[temp_cnt] = string_inpu[start] ;
            }
            else if (string_inpu[start] == '/' && cnt_dir > 0)
            {
                // CreateDirectory (filename, NULL);
                filename2[temp_cnt] = string_inpu[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
            char_pos ++ ;
        }
    }
    filename2[temp_cnt] = '\0' ;
}


void bringeafter(char first[] , char second[],int start)
{
    int i = 0 ;
    int temp_cnt = 0;
    while(i < start)
    {
        second[temp_cnt] = first[i] ;
        i++;
        temp_cnt++;
    }
    int cnt_dir = 0;
    if(first[start] == '"')
    {
        second[temp_cnt] = first[start] ;
        temp_cnt ++ ;
        start ++ ;
        second[temp_cnt] = first[start] ;
        temp_cnt ++ ;
        start ++ ; 
        char_pos2 = start ;
        while(first[start] != '"')
        {
            if(first[start] != '/')
                second[temp_cnt] = first[start] ;
            else if(first[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                second[temp_cnt] = first[start] ;
            }
            else if (first[start] == '/' && cnt_dir > 0)
            {
                second[temp_cnt] = first[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
            char_pos2 ++ ;
        }
        second[temp_cnt] = first[start] ;
        temp_cnt ++ ;
        char_pos2 ++ ;
    }

    else
    {
        second[temp_cnt] = first[start] ;
        start++ ; // after slash
        temp_cnt ++ ;
        char_pos2 = start ;
        while(first[start] != '\0' && first[start] != ' ' && first[start] != '\n' ) //  && string_inpu[start] != '-'
        {
            if(first[start] != '/')
                second[temp_cnt] = first[start] ;
            else if(first[start] == '/' && cnt_dir == 0)
            {
                cnt_dir++ ;
                second[temp_cnt] = first[start] ;
            }
            else if (first[start] == '/' && cnt_dir > 0)
            {
                second[temp_cnt] = first[start] ;
            }
            start ++ ;
            temp_cnt ++ ;
            char_pos2 ++ ;
        }
    }
    second[temp_cnt] = '\0' ;
}


void find_next_str(int type) // char_pos = pos of space // type for having(1) or not having(0) or both(2) "
{
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
            if(string_inpu[char_pos] == '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                char_pos++;
                first_pos ++ ;
                // string_inpu[char_pos] = '\n' ;
            } 
            else if(string_inpu[char_pos] != '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                user_str[char_pos - first_pos] = string_inpu[char_pos] ;
                char_pos += 2;
                first_pos ++;
                string_inpu[char_pos] = '\n' ;
            }
            user_str[char_pos - first_pos] = string_inpu[char_pos] ;
        }
        char_pos += 1 ;
        // char_pos will be on space 
    }
    else if(type == 2)  // use after --str -->> += 7
    {
        char_pos += 7 ;
        if(string_inpu[char_pos] == '"') find_next_str(1) ;
        else 
        {
            char_pos -= 7 ;
            find_next_str(0) ;
        }
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
        while(string_inpu[char_pos] != ' ' && string_inpu[char_pos] != '\0')
        {
            if(string_inpu[char_pos] == '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                char_pos++;
            } 
            else if(string_inpu[char_pos] != '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                user_str[i] = string_inpu[char_pos] ;
                char_pos += 2;
                i++ ;
                string_inpu[char_pos] = '\n' ;
            }
            user_str[i] = string_inpu[char_pos] ;
            i++ ;
            char_pos++;
        }
        // char pos will be in space
    }
}


void find_next_str2(char str1[],int type)
{
    int i = 0;
    if(type == 1) // bring what is between ""
    {
        while(string_inpu[char_pos] != '"')
        {
            char_pos ++ ;
        }
        char_pos++;
        int first_pos = char_pos ;
        
        while(string_inpu[char_pos] != '\0')
        {
            if(string_inpu[char_pos] == '"')
            {
                if(string_inpu[char_pos+1] == ' ')
                {
                    if(string_inpu[char_pos+2] == '-')
                    {
                        if(string_inpu[char_pos+3] == '-')
                        {
                            if(string_inpu[char_pos+4] == 's')
                            {
                                if(string_inpu[char_pos+5] == 't')
                                {
                                    if(string_inpu[char_pos+6] == 'r')
                                    {
                                        if(string_inpu[char_pos+7] == '2')
                                        {
                                            if(string_inpu[char_pos+8] == ' ')
                                            {
                                                char_pos++;
                                                str1[i] = '\0' ;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else if(string_inpu[char_pos+3] == 'a')
                        {
                            if(string_inpu[char_pos+4] == 'l')
                            {
                                if(string_inpu[char_pos+5] == 'l')
                                {
                                    if(string_inpu[char_pos+6] == '\0')
                                    {
                                        char_pos++;
                                        str1[i] = '\0' ;
                                        break;
                                    }
                                }
                            }
                            else if(string_inpu[char_pos+4] == 't')
                            {
                                char_pos++;
                                str1[i] = '\0' ;
                                break;
                            }
                        }
                    }
                }
                else if(string_inpu[char_pos+1] == '\0')
                {
                    str1[i] = '\0' ;
                    return;
                }
            }
            if(string_inpu[char_pos] == '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                char_pos++;
            }
            else if(string_inpu[char_pos] != '\\' && string_inpu[char_pos+1] == '\\' && string_inpu[char_pos+2] == 'n')
            {
                str1[i] = string_inpu[char_pos] ;
                char_pos += 2 ;
                i++ ;
                string_inpu[char_pos] = '\n' ;
            }
            str1[i] = string_inpu[char_pos] ;
            i++ ;
            char_pos += 1 ;
        }
        // char_pos will be on space 
    }
    // else if(type == 2)  // use after --str -->> += 7
    // {
    //     char_pos += 7 ;
    //     if(string_inpu[char_pos] == '"') find_next_str(1) ;
    //     else 
    //     {
    //         char_pos -= 7 ;
    //         find_next_str(0) ;
    //     }
    // }
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
            str1[i] = string_inpu[char_pos] ;
            i++ ;
            char_pos++;
        }
        // char pos will be in space
    }
}


void find_next_str3() // for grep
{
    int i = 0 ;
    memset(user_str, 0, sizeof(user_str));

    while(string_inpu[char_pos] != '\0')
    {
        if(string_inpu[char_pos] == '"')
        {
            if(string_inpu[char_pos+1] == ' ')
            {
                if(string_inpu[char_pos+2] == '-')
                {
                    if(string_inpu[char_pos+3] == '-')
                    {
                        if(string_inpu[char_pos+4] == 'f')
                        {
                            if(string_inpu[char_pos+5] == 'i')
                            {
                                if(string_inpu[char_pos+6] == 'l')
                                {
                                    if(string_inpu[char_pos+7] == 'e')
                                    {
                                        user_str[i] = '\0' ;
                                        char_pos++ ;
                                        return ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(string_inpu[char_pos] == '\\')
        {
            if(string_inpu[char_pos+1] == '\\')
            {
                if(string_inpu[char_pos+2] == 'n')
                {
                    char_pos ++ ;
                }
            }
        }
        else if(string_inpu[char_pos] != '\\')
        {
            if(string_inpu[char_pos+1] == '\\')
            {
                if(string_inpu[char_pos+2] == 'n')
                {
                    user_str[i] = string_inpu[char_pos] ;
                    i++;
                    char_pos += 2 ;
                    string_inpu[char_pos] = '\n' ;
                }
            }
        }
        user_str[i] = string_inpu[char_pos] ;
        i++;
        char_pos++ ;
    }
}

/////// use for arman 
// printf output file
void print_out()
{
    FILE* out = fopen("output.txt", "r");

    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,out) ;
        if(feof(out))
        {
            keep_reading = false ;
            print_std(buffer) ;
        }
        else print_std(buffer) ;
    }
    print_std("\n") ;

    fclose(out);
}

// copy output
void copy_output(char* write)
{
    FILE* out = fopen("output.txt", "a");
    int i = 0 ;
    while(write[i] != '\0')
    {
        fprintf(out,"%c",write[i]) ;
        i++ ;
    }
    fclose(out) ;
}

// copy output number
void copy_output_i(int num)
{
    FILE* out = fopen("output.txt", "a");
    
    fprintf(out,"%d",num) ;

    fclose(out) ;
}


void copy_str(char buffer[] ,char save_buffer[][100] ,int col)
{
    int len = strlen(buffer);

    for(int i = 0; i < len; i++)
    {
        save_buffer[i][col] = buffer[i];
    }
}


void copy_str2(char buffer[][100],int col , char secound[],char c)
{
    int i = 0 ;
    while(secound[i] != '\0')
    {
        buffer[i][col] = secound[i] ;
        i++ ;
    }
    buffer[i][col] = c ;
    buffer[i+1][col] = '\0' ;
}


int find_options()
{
    // printf("c : %c\n",string_inpu[char_pos]) ;
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
        else return -1 ;
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


void find_name_file()
{
    memset(name_of_file,0,sizeof(name_of_file)) ;
    int last = strlen(filename) - 1 ;
    int first = strlen(filename) - 1 ;
    
    while(filename[first] != '/')
    {
        first-- ;
    }
    first++ ;
    int i = 0 ;
    for(first ; first <= last ; first++)
    {
        name_of_file[i] = filename[first] ;
        i++ ;
    }
}


long long int into_num(int i ) // i is position of start
{
    int flag = 0 ;
    if(string_inpu[i] == '-')
    {
        flag = 1 ;
        i++ ;
        char_pos ++ ;
    }
    
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
    if(flag == 0)return ret;
    else return (-1*ret) ;
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
        case 5:
            printf("Error...! Invalid input.\n") ;
            break;
        case 6:
            printf("Error...! count and all can not come together.\n") ;
            break;
        case 7:
            printf("Error...! at and all can not come together.\n") ;
            break;
        case 8:
            copy_output("not found.\n") ;
            break;
        case 9:
            printf("invalid depth.\n") ;
            break;
        case 10:
            printf("Could not open current directory.\n") ;
            break;
    }
}


void print_std(char* buffer)
{
    printf("%s",buffer) ;
}


void print_std_i(int num)
{
    printf("%d",num) ;
}


// functions

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

    find_next_str(1) ;
    char_pos += 7 ; // show the first number

    int num_line = into_num(char_pos) ;
    int pos_in_file = into_num(char_pos+1) ;
    int corrent_line = 1 ;
    bool keep_reading = true ;
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
                // fprintf(new,"%s",user_str) ;
                 for (int l = 0 ; l < strlen(user_str) ; l++)
                {
                    if(user_str[l] == '\\')
                    {
                        if(user_str[l+1] == '\\')
                        {
                            if(user_str[l+2] == 'n')
                            {
                                fprintf(new,"\\n") ;
                                l += 2 ;
                            }
                            else if(user_str[l+2] == 't')
                            {
                                fprintf(new,"\\t") ;
                                l += 2 ;
                            }
                        }
                        else if(user_str[l+1] == 'n')
                        {
                            fprintf(new,"\n") ;
                            l++ ;
                        }
                        else if(user_str[l+1] == 't')
                        {
                            fprintf(new,"\t") ;
                            l++ ;
                        }
                        else
                        {
                            fprintf(new,"\\") ;
                        }
                    }
                    else
                    {
                        fprintf(new,"%c",user_str[l]) ;
                    }
                }
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
            // fprintf(new,"%s",user_str) ;
            for (int l = 0 ; l < strlen(user_str) ; l++)
                {
                    if(user_str[l] == '\\')
                    {
                        if(user_str[l+1] == '\\')
                        {
                            if(user_str[l+2] == 'n')
                            {
                                fprintf(new,"\\n") ;
                                l += 2 ;
                            }
                            else if(user_str[l+2] == 't')
                            {
                                fprintf(new,"\\t") ;
                                l += 2 ;
                            }
                        }
                        else if(user_str[l+1] == 'n')
                        {
                            fprintf(new,"\n") ;
                            l++ ;
                        }
                        else if(user_str[l+1] == 't')
                        {
                            fprintf(new,"\t") ;
                            l++ ;
                        }
                        else
                        {
                            fprintf(new,"\\") ;
                        }
                    }
                    else
                    {
                        fprintf(new,"%c",user_str[l]) ;
                    }
                }
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
    FILE* out = fopen("output.txt" ,"w") ;
    fclose(out) ;

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
            // print_std(buffer) ;
            copy_output(buffer) ;
        }
        else 
            copy_output(buffer) ;
            // print_std(buffer) ;
    }
    // copy_output("\n") ;
    // print_std("\n") ;
    fclose(file) ;
}

// remove 
void remove_func()
{
    bringefilename(15) ;
    save_for_undo() ;
    find_dir() ;

    strcat(dir,"tempforremove") ;
    strcat(dir,format) ;

    FILE* file = fopen(filename,"r") ;
    FILE* new = fopen(dir,"w") ;

    if(file == NULL)
    {
        error(2) ; 
        return ;
    }
    char_pos++ ; // after space
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }
    char_pos ++ ; // after space
    int line = into_num(char_pos) ;
    char_pos ++ ;

    int pos = into_num(char_pos) ;
    char_pos ++ ;

    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }
    char_pos ++ ; // after space
    int size = into_num(char_pos) ;

    char_pos += 2 ;

    char c ;
    int now_line = 1;
    int now_pos = 0;
    int i = 0;
    char temp[MAX_line] ;
    int temp_i[MAX_line] = {0} ;

    if(string_inpu[char_pos] == 'b')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i-1] = 1;
                temp_i[i-size] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
            }
        
            else if(dob == 0)
            {
                fputc(temp[i] ,new) ;
            }
        }
    }
    else if(string_inpu[char_pos] == 'f')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i] = 1;
                temp_i[i+size-1] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
            }
        
            else if(dob == 0)
            {
                fputc(temp[i] ,new) ;
            }
        }
    }
    else 
    {
        fclose(file) ;
        fclose(new) ;
        error(5) ;
        return ;
    }

    // printf("line : %d , pos : %d , size : %d , type : %d\n",*(line),*(pos),size,type) ;

    fclose(file) ;
    fclose(new) ;
    remove(filename) ;
    rename(dir ,filename) ;
}

// copy
void copy_func()
{
    bringefilename(13) ;
    
    
    FILE* file = fopen(filename,"r") ;

    char_pos++ ; // after space
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }

    char_pos ++ ; // after space
    int line = into_num(char_pos) ;

    char_pos ++ ;
    int pos = into_num(char_pos) ;

    char_pos ++ ;
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }

    char_pos ++ ; // after space
    int size = into_num(char_pos) ;

    char_pos += 2 ;
    char c ;
    int now_line = 1;
    int now_pos = 0;
    int i = 0;
    char temp[MAX_line] ;
    int temp_i[MAX_line] = {0} ;
    memset(clipboard,0,MAX_line) ;

    if(string_inpu[char_pos] == 'b')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i-1] = 1;
                temp_i[i-size] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        int j = 0;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
                clipboard[j] = temp[i] ;
                j++ ;
            }
            else if(dob == 1)
            {
                clipboard[j] = temp[i] ;
                j++ ;
            }
        }
    } 

    else if(string_inpu[char_pos] == 'f')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i] = 1;
                temp_i[i+size-1] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        int j = 0 ;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
                clipboard[j] = temp[i] ;
                j++ ;
            }
        
            else if(dob == 1)
            {
                clipboard[j] = temp[i] ;
                j++ ;
            }
        }
    }

    else
    {
        fclose(file) ;
        return ;
    }
    
    fclose(file) ;
}

// cut
void cut_func()
{
    bringefilename(12) ;
    save_for_undo() ;
    find_dir() ;

    strcat(dir,"tempforcut") ;
    strcat(dir,format) ;

    FILE* file = fopen(filename,"r") ;
    FILE* new = fopen(dir,"w") ;

    if(file == NULL)
    {
        error(2) ; 
        return ;
    }
    char_pos++ ; // after space
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }
    char_pos ++ ; // after space
    int line = into_num(char_pos) ;
    char_pos ++ ;

    int pos = into_num(char_pos) ;
    char_pos ++ ;

    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }
    char_pos ++ ; // after space
    int size = into_num(char_pos) ;

    char_pos += 2 ;

    char c ;
    int now_line = 1;
    int now_pos = 0;
    int i = 0;
    char temp[MAX_line] ;
    int temp_i[MAX_line] = {0} ;
    memset(clipboard,0,MAX_line) ;

    if(string_inpu[char_pos] == 'b')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i-1] = 1;
                temp_i[i-size] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        int j = 0;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
                clipboard[j] = temp[i] ;
                j++ ;
            }
            else if(dob == 1)
            {
                clipboard[j] = temp[i] ;
                j++ ;
            }
            else if(dob == 0)
            {
                fputc(temp[i] ,new) ;
            }
        }
    }
    else if(string_inpu[char_pos] == 'f')
    {
        while((c = fgetc(file)) != EOF)
        {
            temp[i] = c ;
            if(now_line == line && now_pos == pos)
            {
                temp_i[i] = 1;
                temp_i[i+size-1] = 1;
            }
            if(c == '\n')
            {
                now_line++ ;
                now_pos = 0 ;
            }
            else
                now_pos++ ;
            i++ ;
        }
        temp[i] = '\0' ;
        int max = i ;
        int dob = 0 ;
        int j = 0 ;
        for(i = 0; i < max ;i++)
        {
            if(temp_i[i] == 1 )
            {   
                dob++ ;
                dob %= 2 ;
                clipboard[j] = temp[i] ;
                j++ ;
            }
            else if(dob == 1)
            {
                clipboard[j] = temp[i] ;
                j++ ;
            }
            else if(dob == 0)
            {
                fputc(temp[i] ,new) ;
            }
        }
    }
    else 
    {
        fclose(file) ;
        fclose(new) ;
        error(5) ;
        return ;
    }

    // printf("line : %d , pos : %d , size : %d , type : %d\n",*(line),*(pos),size,type) ;

    fclose(file) ;
    fclose(new) ;
    remove(filename) ;
    rename(dir ,filename) ;
}

// paste
void paste_func()
{
    bringefilename(14) ;
    save_for_undo() ;
    find_dir() ;

    strcat(dir,"tempforpaste") ;
    strcat(dir,format) ;

    FILE* file = fopen(filename,"r") ;
    FILE* new = fopen(dir,"w") ;

    if(file == NULL)
    {
        error(2) ; 
        return ;
    }
    char_pos++ ; // after space
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }
    char_pos ++ ; // after space
    int line = into_num(char_pos) ;
    char_pos ++ ;

    int pos = into_num(char_pos) ;
    
    int corrent_line = 1 ;
    int corrent_pos = 0 ;
    bool keep_reading = true ;
    char buffer[MAX_line] ;
    while(keep_reading)
    {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file))
        {
            keep_reading = false ;
            if(corrent_line == line)
            {
                for(int k = 0; k < pos ; k++)
                {
                    fprintf(new,"%c",buffer[k]);
                }
                // fprintf(new,"%s",user_str) ;
                 for (int l = 0 ; l < strlen(clipboard) ; l++)
                {
                    if(clipboard[l] == '\\')
                    {
                        if(clipboard[l+1] == '\\')
                        {
                            if(clipboard[l+2] == 'n')
                            {
                                fprintf(new,"\\n") ;
                                l += 2 ;
                            }
                            else if(clipboard[l+2] == 't')
                            {
                                fprintf(new,"\\t") ;
                                l += 2 ;
                            }
                        }
                        else if(clipboard[l+1] == 'n')
                        {
                            fprintf(new,"\n") ;
                            l++ ;
                        }
                        else if(clipboard[l+1] == 't')
                        {
                            fprintf(new,"\t") ;
                            l++ ;
                        }
                        else
                        {
                            fprintf(new,"\\") ;
                        }
                    }
                    else
                    {
                        fprintf(new,"%c",clipboard[l]) ;
                    }
                }
                int k = pos;
                while(buffer[k] != '\0' )
                {
                    fprintf(new,"%c",buffer[k]) ;
                    k++ ;
                }
            }
            else 
                fputs(buffer,new) ;
        }
        else if(corrent_line == line)
        {
            for(int k = 0; k < pos ; k++)
            {
                fprintf(new,"%c",buffer[k]);
            }
            // fprintf(new,"%s",user_str) ;
            for (int l = 0 ; l < strlen(clipboard) ; l++)
                {
                    if(clipboard[l] == '\\')
                    {
                        if(clipboard[l+1] == '\\')
                        {
                            if(clipboard[l+2] == 'n')
                            {
                                fprintf(new,"\\n") ;
                                l += 2 ;
                            }
                            else if(clipboard[l+2] == 't')
                            {
                                fprintf(new,"\\t") ;
                                l += 2 ;
                            }
                        }
                        else if(clipboard[l+1] == 'n')
                        {
                            fprintf(new,"\n") ;
                            l++ ;
                        }
                        else if(clipboard[l+1] == 't')
                        {
                            fprintf(new,"\t") ;
                            l++ ;
                        }
                        else
                        {
                            fprintf(new,"\\") ;
                        }
                    }
                    else
                    {
                        fprintf(new,"%c",clipboard[l]) ;
                    }
                }
            int k = pos;
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

// comp
int comp(char word1[][100], char word2[],int col) // word2 is the bigger one
{
    int len1 = 0 ;
    int i = 0;
    char word11[MAX_line] ;
    while(word1[i][col] != '\0')
    {
        word11[i] = word1[i][col] ;
        len1++;
        i++;
    }
    word11[i] = '\0' ;
    int len2 = strlen(word2) ;

    int count = 0 , nege = 1 ,save_count = 0;
    int j = 0,flag_star = 0; // 1 for *something and 2 for something*

    if(word1[0][col] == '*')
        flag_star = 1 ;
    else if(word1[len1-1][col] == '*' && word1[len1-2][col] != '\\')
        flag_star = 2 ;

    if(flag_star == 1)
    {
        count = 1 ;
        i = 1 ;
        while(word2[j] != '\0')
        {
            if(word11[i] == '\\' && word11[i+1] == '*')
            {
                i++;
                count++ ;
            }

            if(word2[j] == word11[i])
            {
                count++;
                i++ ;
            }
            else
            {
                count = 1;
                i = 1 ;
            }
            j++;
            if(count == len1 && j == len2)
            {
                return 1 ;
            }
        }
    }
    else if(flag_star == 2)
    {
        // printf("here\n");
        for(i = 0; i < len1-1 ; i++)
        {
            if(word11[i] == '\\' && word11[i+1] == '*')
            {
                i++; 
                count++;
            }
            
            if(word11[i] == word2[j])
            {
                j++;
                count++ ;
            }
            else
                return 0 ;

            
            if(count == len1-1)
            {
                return 1 ;
            }
        }
    }
    else
    {
        count = 0 ;
        for(i = 0; i < len1 ; i++)
        {
            if(word11[i] == '\\' && word11[i+1] == '*')
            {
                i++; 
                count++;
            }
            
            if(word11[i] == word2[j])
            {
                j++;
                count++ ;
            }
            else
                return 0 ;

            if(count == len1)
            {
                if(word2[j] == '\0')
                {
                    return 1 ;
                }
                count = 1;
            }
        }
    }
    return 0 ;
}

// find
void find_func() // start from 10 // find--file/root/something( )--str( )["]something["]( )[-count/-at/-byword]( )[-all]
{
    FILE* out = fopen("output.txt" ,"w") ;
    fclose(out) ;

    char_pos = 0;
    bringefilename(10) ; // char_pos will be ( )
    FILE* file = fopen(filename,"r") ;
    if(file == NULL) 
    {
        error(2) ;
        return ;
    }
    find_next_str(2) ;

    char buffer[MAX_line] ;
    char temp[MAX_line] ;
    char temp_user[MAX_line][100] ;
    char en_sp[100] ;
    int first_find_op = find_options() ;

    bool find = false ;
    bool keep_reading = true ;
    int pos = 0 ,cnt = 0 , i = 0 , j = 0 , k = 0 ,col = 0;
    int temp_pos = 0 ,word_cnt = 1, count = 0 ,save_pos = 0;
    int save_count = 1 ;
    int option = 0 ;
    char check ;

    while(user_str[i] != '\0')
    {
        // printf("%c", user_str[i]) ;
        if(user_str[i] == ' ' || user_str[i] == '\n')
        {
            word_cnt++;
            en_sp[k] = user_str[i] ;
            temp_user[j][col] = '\0' ;
            i++;
            k++ ;
            j = 0 ;
            col++ ;
        }
        else
        {
            temp_user[j][col] = user_str[i] ;
            j++;
            i++;
        }
    }
    en_sp[k] = '\0' ;

    i = 0 ;
    j = 0 ;
    col = 0 ;
    k = 0 ;

    if(first_find_op == 0) // no other options 
    {
        temp_pos = 0 ;
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            memset(temp,0,sizeof(temp));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
            
            while(buffer[i] != '\0')
            {
                if(buffer[i] == ' ' || buffer[i] == '\n')
                {
                    if(count == 0)
                    {
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            option = 1 ;
                            break;
                        }
                    }
                    else
                    {
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                    memset(temp,0,sizeof(temp));
                    j = 0 ;
                }
                else
                {
                    temp[j] = buffer[i];
                    j++ ;
                }
                temp_pos ++ ;
                i++;
            }
            if(find)
                break;

            if(!keep_reading)
            {
                if(count == 0)
                {
                    save_pos = pos ;
                    pos = temp_pos+1 ;
                }

                temp[j] = '\0' ; 
                int l = 0 ;

                if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                {
                    col++ ;
                    k++ ;
                    count++ ;
                    if(count == word_cnt)
                    {
                        find = true ;
                        option = 1 ;
                        break;
                    }   
                }
            }

            i = 0 ;
            j = 0 ;
        }
    }
    
    else if(first_find_op == 1) // count
    {
        if(find_options() == 10) // with all 
        {
            error(6) ; // all and count can come together
            return;
        }
        else
        {
            temp_pos = 0 ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                memset(temp,0,sizeof(temp));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                }
                
                while(buffer[i] != '\0')
                {
                    if(buffer[i] == ' ' || buffer[i] == '\n')
                    {
                        if(count == 0)
                        {
                            save_pos = pos ;
                            pos = temp_pos+1 ;
                        }

                        temp[j] = '\0' ; 
                        int l = 0 ;

                        if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                        {
                            col++ ;
                            k++ ;
                            count++ ;
                            if(count == word_cnt)
                            {
                                find = true ;
                                cnt++ ;
                                option = 2 ;
                                col = 0;
                                k = 0;
                                count = 0 ;
                            }
                        }
                        else
                        {
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                        memset(temp,0,sizeof(temp));
                        j = 0 ;
                    }
                    else
                    {
                        temp[j] = buffer[i];
                        j++ ;
                    }
                    temp_pos ++ ;
                    i++;
                }
                if(!keep_reading)
                {
                    if(count == 0)
                    {
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)                            
                        {
                            find = true ;
                            cnt++ ;
                            option = 2 ;
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                }
                i = 0 ;
                j = 0 ;
            }
        }
    }

    else if(first_find_op == 2) // at
    {
        // find n
        char_pos ++ ;
        int n_at = into_num(char_pos) ;

        if(find_options() == 10) // with all 
        {
            error(7) ;
            return;
        }
        else
        {
            temp_pos = 0 ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                memset(temp,0,sizeof(temp));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                }
                
                while(buffer[i] != '\0')
                {
                    if(buffer[i] == ' ' || buffer[i] == '\n')
                    {
                        if(count == 0)
                        {
                            save_pos = pos ;
                            pos = temp_pos+1 ;
                        }

                        temp[j] = '\0' ; 
                        int l = 0 ;

                        if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                        {
                            col++ ;
                            k++ ;
                            count++ ;
                            if(count == word_cnt)
                            {
                                cnt++ ;
                                if(cnt == n_at)
                                {
                                    find = true ;
                                    option = 3 ;
                                    break;
                                }
                                col = 0;
                                k = 0;
                                count = 0 ;
                            }
                        }
                        else
                        {
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                        memset(temp,0,sizeof(temp));
                        j = 0 ;
                    }
                    else
                    {
                        temp[j] = buffer[i];
                        j++ ;
                    }
                    temp_pos ++ ;
                    i++;
                }
                if(find)
                    break;

                if(!keep_reading)
                {
                    if(count == 0)
                    {
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            cnt++ ;
                            if(cnt == n_at)
                            {
                                find = true ;
                                option = 3 ;
                                break;
                            }
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                }
                i = 0 ;
                j = 0 ;
            }
        }
    }

    else if(first_find_op == 3) //byword
    {
        int cnt_camma = 0 ;
        int count_word = 0 ;

        if(find_options() == 10) // with all 
        {
            temp_pos = 0 ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                memset(temp,0,sizeof(temp));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                }
                
                while(buffer[i] != '\0')
                {
                    if(buffer[i] == ' ' || buffer[i] == '\n')
                    {
                        count_word++ ;
                        if(count == 0)
                        {
                            save_count = count_word ;
                            save_pos = pos ;
                            pos = temp_pos+1 ;
                        }

                        temp[j] = '\0' ; 
                        int l = 0 ;

                        if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                        {
                            col++ ;
                            k++ ;
                            count++ ;
                            if(count == word_cnt)
                            {
                                find = true ;
                                cnt++ ;
                                option = 4 ;
                                if(cnt_camma) copy_output(",");
                                copy_output_i(save_count);
                                cnt_camma = 1 ;
                                col = 0;
                                k = 0;
                                count = 0 ;
                            }
                        }
                        else
                        {
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                        memset(temp,0,sizeof(temp));
                        j = 0 ;
                    }
                    else
                    {
                        temp[j] = buffer[i];
                        j++ ;
                    }
                    temp_pos ++ ;
                    i++;
                }
                if(!keep_reading)
                {
                    count_word++ ;
                    if(count == 0)
                    {
                        save_count = count_word ;
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            cnt++ ;
                            option = 4 ;
                            if(cnt_camma) copy_output(",");
                            copy_output_i(save_count);
                            cnt_camma = 1 ;
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                }
                i = 0 ;
                j = 0 ;
            }
        }
        else
        {
            temp_pos = 0 ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                memset(temp,0,sizeof(temp));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                }
                
                while(buffer[i] != '\0')
                {
                    if(buffer[i] == ' ' || buffer[i] == '\n')
                    {
                        count_word++ ;
                        if(count == 0)
                        {
                            save_count = count_word ;
                            save_pos = pos ;
                            pos = temp_pos+1 ;
                        }

                        temp[j] = '\0' ; 
                        int l = 0 ;

                        if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                        {
                            col++ ;
                            k++ ;
                            count++ ;
                            if(count == word_cnt)
                            {
                                find = true ;
                                cnt++ ;
                                option = 5 ;
                                break;
                            }
                        }
                        else
                        {
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                        memset(temp,0,sizeof(temp));
                        j = 0 ;
                    }
                    else
                    {
                        temp[j] = buffer[i];
                        j++ ;
                    }
                    temp_pos ++ ;
                    i++;
                }
                if(find)
                    break; 

                if(!keep_reading)
                {
                    count_word++ ;
                    if(count == 0)
                    {
                        save_count = count_word ;
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            cnt++ ;
                            option = 5 ;
                            break;
                        }
                    }
                } 
                i = 0 ;
                j = 0 ;
            }
        }
    }

    else if(first_find_op == 10) // all
    {
        int cnt_camma = 0 ;
        temp_pos = 0 ;
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            memset(temp,0,sizeof(temp));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
            
            while(buffer[i] != '\0')
            {
                if(buffer[i] == ' ' || buffer[i] == '\n')
                {
                    if(count == 0)
                    {
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            option = 4 ;
                            if(cnt_camma) copy_output(",");
                            copy_output_i(save_pos);
                            cnt_camma = 1 ;
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                    else
                    {
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                    memset(temp,0,sizeof(temp));
                    j = 0 ;
                }
                else
                {
                    temp[j] = buffer[i];
                    j++ ;
                }
                temp_pos ++ ;
                i++;
            }
            if(!keep_reading)
            {
                if(count == 0)
                {
                    save_pos = pos ;
                    pos = temp_pos+1 ;
                }

                temp[j] = '\0' ; 
                int l = 0 ;

                if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                {
                    col++ ;
                    k++ ;
                    count++ ;
                    if(count == word_cnt)
                    {
                        find = true ;
                        option = 4 ;
                        if(cnt_camma) copy_output(",");
                        copy_output_i(save_pos);
                        cnt_camma = 1 ;
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                }
            }
            i = 0 ;
            j = 0 ;
        }
    }

    else
    {
        error(5) ;
        fclose(file) ;
        return;
    }

    if(find)
    {
        if(option == 1) copy_output_i(save_pos) ;
        else if(option == 2) copy_output_i(cnt) ;
        else if(option == 3) copy_output_i(save_pos) ;
        else if(option == 4) copy_output("\n") ;
        else if(option == 5) copy_output_i(save_count) ;
        else error(3) ;
    }
    else copy_output_i(-1) ;
    fclose(file) ;
}

// replace
void replace_func()
{
    FILE* out = fopen("output.txt" ,"w") ;
    fclose(out) ;

    bringefilename(13) ;
    save_for_undo();
    find_dir(); 

    strcat(dir,"tempforreplace") ;
    strcat(dir,format) ;

    FILE* file = fopen(filename,"r") ;
    if(file == NULL)
    {
        error(2) ; 
        return ;
    }

    FILE* new = fopen(dir,"w") ;

    char_pos++ ; // after space
    while(string_inpu[char_pos] != ' ')
    {
        char_pos++;
    }

    char str1[MAX_line] ;
    char str2[MAX_line] ;


    find_next_str2(str1,1);
    find_next_str2(str2,1);
    int op = find_options() ;


    char buffer[MAX_line] ;
    char temp[MAX_line] ;
    char temp_user[MAX_line][100] ;
    char temp_user2[MAX_line][100] ;
    char for_paste[MAX_line] ;
    char en_sp[100] ;

    bool find = false ;
    bool keep_reading = true ;
    int pos = 0 ,cnt = 0 , i = 0 , j = 0 , k = 0 ,col = 0;
    int temp_pos = 0 ,word_cnt = 1, count = 0 ,save_pos = 0;
    int save_count = 1 ;
    int option = 0 ;
    char check ;

    while(str1[i] != '\0')
    {
        // printf("%c", user_str[i]) ;
        if(str1[i] == ' ' || str1[i] == '\n')
        {
            word_cnt++;
            en_sp[k] = str1[i] ;
            temp_user[j][col] = '\0' ;
            i++;
            k++ ;
            j = 0 ;
            col++ ;
        }
        else
        {
            temp_user[j][col] = str1[i] ;
            j++;
            i++;
        }
    }
    en_sp[k] = '\0' ;

    i = 0 ;
    j = 0 ;
    col = 0 ;
    k = 0 ;


    
    if(op == 0)
    {
        temp_pos = 0 ;
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            memset(temp,0,sizeof(temp));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
            
            while(buffer[i] != '\0')
            {
                if(buffer[i] == ' ' || buffer[i] == '\n')
                {
                    if(count == 0)
                    {
                        memset(temp_user2,0,sizeof(temp_user2));
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(find == false && comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        count++ ;
                        copy_str2(temp_user2,col,temp,buffer[i]) ;
                        col++ ;
                        k++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            fputs(str2,new);
                            fputc(buffer[i],new) ;
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                    else if(count != 0)
                    {
                        for(int y = 0; y < col ; y++)
                        {
                            memset(for_paste,0,sizeof(for_paste));
                            int x = 0 ;
                            while(temp_user2[x][y] != '\0')
                            {
                                for_paste[x] = temp_user2[x][y] ;
                                x++ ;
                            }
                            fputs(for_paste,new);
                        }
                    }
                    else
                    {
                        col = 0;
                        k = 0;
                        count = 0 ;
                        fputs(temp,new) ;
                        fputc(buffer[i],new) ;
                    }
                    memset(temp,0,sizeof(temp));
                    j = 0 ;
                }
                else
                {
                    temp[j] = buffer[i];
                    j++ ;
                }
                temp_pos ++ ;
                i++;
            }
            if(!keep_reading)
            {
                if(count == 0)
                {
                    memset(temp_user2,0,sizeof(temp_user2));
                    save_pos = pos ;
                    pos = temp_pos+1 ;
                }

                temp[j] = '\0' ; 
                int l = 0 ;

                if(find == false && comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                {
                    count++ ;
                    copy_str2(temp_user2,col,temp,buffer[i]) ;
                    col++ ;
                    k++ ;
                    if(count == word_cnt)
                    {
                        find = true ;
                        fputs(str2,new);
                        fputc(buffer[i],new) ;
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                }
                else if(count != 0)
                {
                    for(int y = 0; y < col ; y++)
                    {
                        memset(for_paste,0,sizeof(for_paste));
                        int x = 0 ;
                        while(temp_user2[x][y] != '\0')
                        {
                            for_paste[x] = temp_user2[x][y] ;
                            x++ ;
                        }
                        fputs(for_paste,new);
                    }
                }
                else
                {
                    col = 0;
                    k = 0;
                    count = 0 ;
                    fputs(temp,new) ;
                    fputc(buffer[i],new) ;
                }
            }
            i = 0 ;
            j = 0 ;
        }
    }
    else if(op == 10)
    {
        temp_pos = 0 ;
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            memset(temp,0,sizeof(temp));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
            
            while(buffer[i] != '\0')
            {
                if(buffer[i] == ' ' || buffer[i] == '\n')
                {
                    if(count == 0)
                    {
                        memset(temp_user2,0,sizeof(temp_user2));
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        copy_str2(temp_user2,col,temp,buffer[i]) ;
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            find = true ;
                            fputs(str2,new) ;
                            fputc(buffer[i],new) ;
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                    else if(count != 0)
                    {
                        for(int y = 0; y < col ; y++)
                        {
                            memset(for_paste,0,sizeof(for_paste));
                            int x = 0 ;
                            while(temp_user2[x][y] != '\0')
                            {
                                for_paste[x] = temp_user2[x][y] ;
                                x++ ;
                            }
                            fputs(for_paste,new);
                        }
                    }
                    else
                    {
                        col = 0;
                        k = 0;
                        count = 0 ;
                        fputs(temp,new) ;
                        fputc(buffer[i],new) ;
                    }
                    memset(temp,0,sizeof(temp));
                    j = 0 ;
                }
                else
                {
                    temp[j] = buffer[i];
                    j++ ;
                }
                temp_pos ++ ;
                i++;
            }
            if(!keep_reading)
            {
                if(count == 0)
                {
                memset(temp_user2,0,sizeof(temp_user2));
                save_pos = pos ;
                pos = temp_pos+1 ;
                }

                temp[j] = '\0' ; 
                int l = 0 ;

                if(comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                {
                    copy_str2(temp_user2,col,temp,buffer[i]) ;
                    col++ ;
                    k++ ;
                    count++ ;
                    if(count == word_cnt)
                    {
                        find = true ;
                        fputs(str2,new) ;
                        fputc(buffer[i],new) ;
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                }
                else if(count != 0)
                {
                    for(int y = 0; y < col ; y++)
                    {
                        memset(for_paste,0,sizeof(for_paste));
                        int x = 0 ;
                        while(temp_user2[x][y] != '\0')
                        {
                            for_paste[x] = temp_user2[x][y] ;
                            x++ ;
                        }
                        fputs(for_paste,new);
                    }
                }
                else
                {
                    col = 0;
                    k = 0;
                    count = 0 ;
                    fputs(temp,new) ;
                    fputc(buffer[i],new) ;
                }
            }
            i = 0 ;
            j = 0 ;
        }
    }
    else if(op == 2)
    {
        char_pos ++ ;
        int n_at = into_num(char_pos) ;
        temp_pos = 0 ;
        while(keep_reading)
        {
            memset(buffer,0,sizeof(buffer));
            memset(temp,0,sizeof(temp));
            fgets(buffer,MAX_line,file) ;
            if(feof(file))
            {
                keep_reading = false ;
            }
                
            while(buffer[i] != '\0')
            {
                if(buffer[i] == ' ' || buffer[i] == '\n')
                {
                    if(count == 0)
                    {
                        memset(temp_user2,0,sizeof(temp_user2));
                        save_pos = pos ;
                        pos = temp_pos+1 ;
                    }

                    temp[j] = '\0' ; 
                    int l = 0 ;

                    if(find == false && comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                    {
                        copy_str2(temp_user2,col,temp,buffer[i]) ;
                        col++ ;
                        k++ ;
                        count++ ;
                        if(count == word_cnt)
                        {
                            cnt++ ;
                            if(cnt == n_at)
                            {
                                find = true ;
                                fputs(str2,new) ;
                                fputc(buffer[i],new) ;
                            }
                            else
                            {
                                for(int y = 0; y < col ; y++)
                                {
                                    memset(for_paste,0,sizeof(for_paste));
                                    int x = 0 ;
                                    while(temp_user2[x][y] != '\0')
                                    {
                                        for_paste[x] = temp_user2[x][y] ;
                                        x++ ;
                                    }
                                    fputs(for_paste,new);
                                }
                            }
                            col = 0;
                            k = 0;
                            count = 0 ;
                        }
                    }
                    else if(count != 0)
                    {
                        for(int y = 0; y < col ; y++)
                        {
                            memset(for_paste,0,sizeof(for_paste));
                            int x = 0 ;
                            while(temp_user2[x][y] != '\0')
                            {
                                for_paste[x] = temp_user2[x][y] ;
                                x++ ;
                            }
                            fputs(for_paste,new);
                        }
                    }
                    else
                    {
                        col = 0;
                        k = 0;
                        count = 0 ;
                        fputs(temp,new) ;
                        fputc(buffer[i],new) ;
                    }
                    memset(temp,0,sizeof(temp));
                    j = 0 ;
                }
                else
                {
                    temp[j] = buffer[i];
                    j++ ;
                }
                temp_pos ++ ;
                i++;
            }
            if(!keep_reading)
            {
                if(count == 0)
                {
                    memset(temp_user2,0,sizeof(temp_user2));
                    save_pos = pos ;
                    pos = temp_pos+1 ;
                }
                temp[j] = '\0' ; 
                int l = 0 ;

                if(find == false && comp(temp_user,temp,col) && (en_sp[k] == '\0' || en_sp[k] == buffer[i]))
                {
                    copy_str2(temp_user2,col,temp,buffer[i]) ;
                    col++ ;
                    k++ ;
                    count++ ;
                    if(count == word_cnt)
                    {
                        cnt++ ;
                        if(cnt == n_at)
                        {
                            find = true ;
                            fputs(str2,new) ;
                            fputc(buffer[i],new) ;
                        }
                        else
                        {
                            for(int y = 0; y < col ; y++)
                            {
                                memset(for_paste,0,sizeof(for_paste));
                                int x = 0 ;
                                while(temp_user[x][y] != '\0')
                                {
                                    for_paste[x] = temp_user[x][y] ;
                                    x++ ;
                                }
                                fputs(for_paste,new);
                            }
                        }
                        col = 0;
                        k = 0;
                        count = 0 ;
                    }
                }
                else if(count != 0)
                {
                    for(int y = 0; y < col ; y++)
                    {
                        memset(for_paste,0,sizeof(for_paste));
                        int x = 0 ;
                        while(temp_user[x][y] != '\0')
                        {
                            for_paste[x] = temp_user[x][y] ;
                            x++ ;
                        }
                        fputs(for_paste,new);
                    }
                }
                else
                {
                    col = 0;
                    k = 0;
                    count = 0 ;
                    fputs(temp,new) ;
                    fputc(buffer[i],new) ;
                }
            }
            i = 0 ;
            j = 0 ;
        }
        
    }
    else
    {
        error(5) ;
        return ;
    }

    if(find) copy_output("success\n") ;
    else copy_output("could not find\n") ;


    fclose(file) ;
    fclose(new) ;
    remove(filename) ;
    rename(dir ,filename) ;
}

// grep
void grep_func() // grep [-c/-l] --str "something" --file/root/test.txt --file/root/test.txt --file/root/test.txt ...
{
    FILE* out = fopen("output.txt" ,"w") ;

    char_pos = 6 ;
    int len = strlen(string_inpu);
    char buffer[MAX_line] ;
    bool keep_reading = true ;

    if(string_inpu[char_pos] == '-') // none
    {
        char_pos = 12 ; // first of string
        find_next_str3() ;
        char_pos += 7 ; // after file

        while(char_pos < len)
        {
            bringefilename(char_pos);
            FILE* file = fopen(filename ,"r") ;
            if(file == NULL)
            {
                error(2) ;
                fclose(out) ;
                return ;
            }

            find_name_file() ;

            keep_reading = true ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                    if(strstr(buffer,user_str))
                    {
                        fprintf(out,"%s: %s\n",name_of_file,buffer); 
                    }
                }
                else 
                {
                    if(strstr(buffer,user_str))
                    {
                        fprintf(out,"%s: %s",name_of_file,buffer); 
                    }
                }
            }

            fclose(file) ;
            char_pos += 7 ;
        }
    }
    else if(string_inpu[char_pos] == 'c') // count
    {
        int cnt = 0 ;
        char_pos = 15 ; // first of string
        find_next_str3() ;
        char_pos += 7 ; // after file

        while(char_pos < len)
        {
            bringefilename(char_pos);
            FILE* file = fopen(filename ,"r") ;
            if(file == NULL)
            {
                error(2) ;
                fclose(out) ;
                return ;
            }

            keep_reading = true ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                    if(strstr(buffer,user_str))
                    {
                        cnt++;
                    }
                }
                else 
                {
                    if(strstr(buffer,user_str))
                    {
                        cnt++; 
                    }
                }
            }

            fclose(file) ;
            char_pos += 7 ;
        }

        if(cnt == 0) error(8) ;
        else print_std_i(cnt) ;
    }
    else if(string_inpu[char_pos] == 'l') // file name
    {
        char_pos = 15 ; // first of string
        find_next_str3() ;
        char_pos += 7 ; // after file

        while(char_pos < len)
        {
            bringefilename(char_pos);
            FILE* file = fopen(filename ,"r") ;
            if(file == NULL)
            {
                error(2) ;
                fclose(out) ;
                return ;
            }

            find_name_file() ;

            keep_reading = true ;
            while(keep_reading)
            {
                memset(buffer,0,sizeof(buffer));
                fgets(buffer,MAX_line,file) ;
                if(feof(file))
                {
                    keep_reading = false ;
                    if(strstr(buffer,user_str))
                    {
                        fprintf(out,"%s\n",name_of_file); 
                        break;
                    }
                }
                else 
                {
                    if(strstr(buffer,user_str))
                    {
                        fprintf(out,"%s\n",name_of_file); 
                        break;
                    }
                }
            }

            fclose(file) ;
            char_pos += 7 ;
        }
    }
    else
        error(5);

    fclose(out) ;
}

//auto indent
void auto_func() // start from 17
{
    bringefilename(17) ;
    save_for_undo() ;
    find_dir() ;

    strcat(dir,"tempforindent") ;
    strcat(dir,format) ;

    FILE* file = fopen(filename,"r") ;

    if(file == NULL)
    {
        error(2) ; 
        return ;
    }
    FILE* new = fopen(dir,"w") ;

    char buffer[MAX_line] ;
    int tabb = 0 ;
    int came = 0 , first = 0 ;
    int i = 0 ;
    bool keep_reading = true ;

    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,file) ;
        if(feof(file))
        {
            keep_reading = false ;
            while(buffer[i] != '\0')
            {
                if(first == 1)
                {
                    for(int j = 0 ; j < tabb ; j++)
                    {
                        fputc('\t',new) ;
                    }
                    first = 0 ;
                }

                if(buffer[i] == '{')
                {
                    if(buffer[i-1] != ' ' && buffer[i-1] != '{' && buffer[i-1] != '}' && i-1 >= 0)
                    {
                        fputc(' ',new) ;
                    }
                    fputc(buffer[i],new) ;
                    fputc('\n',new) ;
                    tabb++ ;
                    came = 1 ;
                    first = 1 ;
                }
                else if(buffer[i] == '}')
                {
                    tabb-- ;
                    int check = 1 ;
                    int k = i ;
                    while(buffer[k] != '}')
                    {
                        if(buffer[k] != ' ')
                        {
                            check = 0 ;
                            break;
                        }
                        k++ ;
                    }
                    fputc('\n',new) ;
                    for(int j = 0 ; j < tabb ; j++)
                    {
                        fputc('\t',new) ;
                    }
                    fputc(buffer[i],new) ;
                    if(!check) fputc('\n',new) ;
                    first = 1 ;
                    came = 0 ;
                }
                else if(buffer[i] == ' ' && came == 1)
                {
                    came = 1 ;
                }
                else
                {
                    came = 0 ;
                    fputc(buffer[i],new) ;
                }

                i++ ;
            }
        }
        else 
        {
            while(buffer[i] != '\0')
            {
                if(first == 1)
                {
                    for(int j = 0 ; j < tabb ; j++)
                    {
                        fputc('\t',new) ;
                    }
                    first = 0 ;
                }

                if(buffer[i] == '{')
                {
                    if(buffer[i-1] != ' ' && buffer[i-1] != '{' && buffer[i-1] != '}' && i-1 >= 0)
                    {
                        fputc(' ',new) ;
                    }
                    fputc(buffer[i],new) ;
                    fputc('\n',new) ;
                    tabb++ ;
                    came = 1 ;
                    first = 1 ;
                }
                else if(buffer[i] == '}')
                {
                    tabb-- ;
                    int check = 1 ;
                    int k = i ;
                    while(buffer[k] != '}')
                    {
                        if(buffer[k] != ' ')
                        {
                            check = 0 ;
                            break;
                        }
                        k++ ;
                    }
                    fputc('\n',new) ;
                    for(int j = 0 ; j < tabb ; j++)
                    {
                        fputc('\t',new) ;
                    }
                    fputc(buffer[i],new) ;
                    if(!check) fputc('\n',new) ;
                    first = 1 ;
                    came = 0 ;
                }
                else if(buffer[i] == ' ' && came == 1)
                {
                    came = 1 ;
                }
                else
                {
                    came = 0 ;
                    fputc(buffer[i],new) ;
                }

                i++ ;
            }
        }
    }

    fclose(file);
    fclose(new);
    remove(filename) ;
    rename(dir,filename);
}

// compare
void compare_func() // start from 13
{
    FILE* out = fopen("output.txt" ,"w") ;

    char_pos = 13 ;
    bringefilename(char_pos) ;
    
    char_pos += 7 ;
    char filename2[MAX_line] ;
    bringefilename2(filename2,char_pos) ;

    FILE* file = fopen(filename,"r");
    FILE* file2 = fopen(filename2,"r");
    if(file == NULL || file2 == NULL)
    {
        error(2) ;
        fclose(out) ;
        return ;
    }

    int line1 = 1 ;
    int line2 = 1 ;
    char buffer1[MAX_line] ;
    char buffer2[MAX_line] ;

    int which_first = 0 ;
    bool keep_reading = true ;

    while(!which_first)
    {
        memset(buffer1,0,sizeof(buffer1));
        memset(buffer2,0,sizeof(buffer2));

        fgets(buffer1,MAX_line,file) ;
        fgets(buffer2,MAX_line,file2) ;

        if(feof(file))
        {
            which_first = 2 ; // i shouid print from file2
            if(strcmp(buffer1,buffer2) != 0)
            {
                fprintf(out,"============ #%d ============\n" ,line1) ;
                print_std(buffer1);
                print_std("\n");
                print_std(buffer2);
                print_std("\n");
            }

            if(feof(file2))
                which_first = 3 ;
        }
        else if(feof(file2))
        {
            which_first = 1 ;
            if(strcmp(buffer1,buffer2) != 0)
            {
                fprintf(out,"============ #%d ============\n" ,line1) ;
                print_std(buffer1);
                // print_std("\n");
                print_std(buffer2);
                print_std("\n");
            }

            if(feof(file))
                which_first = 3 ;
        }
        else
        {
            if(strcmp(buffer1,buffer2) != 0)
            {
                fprintf(out,"============ #%d ============\n" ,line1) ;
                print_std(buffer1);
                // print_std("\n");
                print_std(buffer2);
                print_std("\n");
            }
        }
        line1 ++;
        line2 ++;
    }

    int save_line ;
    int col = 0;
    char save_buffer[MAX_line][100] ;

    if(which_first == 1)
    {
        save_line = line1 ;
        while(keep_reading)
        {
            memset(buffer1,0,sizeof(buffer1));
            fgets(buffer1,MAX_line,file) ;

            if(feof(file))
            {
                keep_reading = false ;
                copy_str(buffer1,save_buffer,col) ;
                col++ ;
            }
            else
            {
                copy_str(buffer1,save_buffer,col) ;
                col++ ;
            }
            line1 ++;
        }

        fprintf(out,"<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",save_line ,(line1-1)) ;
        for(int i = 0 ; i < col ; i++)
        {
            int j = 0 ;
            while(save_buffer[j][i] != '\0')
            {
                fprintf(out,"%c", save_buffer[j][i]);
                j++ ;
            }
        }
        fprintf(out,"\n");
    }
    else if(which_first == 2)
    {
        save_line = line2 ;
        while(keep_reading)
        {
            memset(buffer2,0,sizeof(buffer2));
            fgets(buffer2,MAX_line,file2) ;

            if(feof(file2))
            {
                keep_reading = false ;
                copy_str(buffer2,save_buffer,col) ;
                col++ ;
            }
            else
            {
                copy_str(buffer2,save_buffer,col) ;
                col++ ;
            }
            line2 ++;
        }
        fprintf(out,">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",save_line ,(line2-1)) ;
        for(int i = 0 ; i < col ; i++)
        {
            int j = 0 ;
            while(save_buffer[j][i] != '\0')
            {
                fprintf(out,"%c", save_buffer[j][i]);
                j++ ;
            }
        }
        fprintf(out,"\n");
    }

    fclose(out) ;
    fclose(file) ;
    fclose(file2) ;
}

// tree
void tree(FILE* out ,char *firstpath ,int depth ,int h)
{
    if(h == depth || depth+1 == h)
        return ;

    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(firstpath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i = 0; i < h ; i++) 
            {
                if (i%2 == 0 || i == 0)
                    fprintf(out,"|");
                else
                    fprintf(out,"\t");
            }
            // if(strcmp(dp->d_name ,"."))
            fprintf(out,"L--%s\n", dp->d_name);

            strcpy(path, firstpath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(out,path, depth , h+2);
        }
    }

    closedir(dir);
}


void tree_func()
{
    FILE* out = fopen("output.txt","w") ;
    char_pos = 5 ;
    int depth = into_num(char_pos) ;
    
    char *path = "./root" ;
    if(depth == -1)
    {
        tree(out,path, 5,0) ;
    }
    else if(depth < -1)
    {
        error(9) ;
    }
    else
    {
        int a = 2*depth + 1 ;
        tree(out,path, a,0) ;
    }
    fclose(out) ;
}

// undo 
void undo_func() // will copy undo temp to this file // just undo the  last file or will do nonscnene
{
    char temp2[MAX_line] = "undo/temp2" ;
    char temp[MAX_line] = "undo/temp" ;
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
    char temp[MAX_line] = "undo/temp";
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


// compare my self func
int compare_my_func(char* mainstr , char* findstr)
{
    int i = 0 , j = 0 ;
    int count = 0 ;
    int len = strlen(findstr) ;

    while(mainstr[i] != '\0' && mainstr[i] != ' ')
    {
        if(mainstr[i] == findstr[j])
        {
            j++;
            count++ ;
            if(count == len)
            {
                return 1 ;
            }
        }
        else
        {
            j = 0 ;
            count = 0 ;
        }
        i++ ;
    }
    return 0 ;
}


int find_2_func(char* mainstr , char* findstr)
{
    char_pos2 = 0 ;
    int i = 0 , j = 0 ;
    int count = 0 ;
    int len = strlen(findstr) ;

    while(mainstr[i] != '\0')
    {
        if(mainstr[i] == '=' && mainstr[i+1] == 'D')
        {
            i += 3 ;
            char_pos2 += 3 ;
            break ;
        }
        char_pos2 ++ ;
        i++ ;
    }


    while(mainstr[i] != '\0' && mainstr[i] != ' ')
    {
        if(mainstr[i] == findstr[j])
        {
            j++;
            count++ ;
            if(count == len)
            {
                return 1 ;
            }
        }
        else
        {
            j = 0 ;
            count = 0 ;
        }
        i++ ;
    }
    return 0 ;
}


void make_string_inpu_right(int after)
{
    int i = 0 , j = char_pos2;
    char temp[MAX_line] ;
    char add[MAX_line] ;

    // printf("char_pos2 = %d\n", char_pos2) ;
    while(string_inpu[j] != '\0') // start after =D( )
    {
        temp[i] = string_inpu[j] ;
        i++ ;
        j++ ;
    }
    bringeafter(temp,add,after) ;

    // printf("temp : -%s\n",temp) ;
    // printf("add : -%s\n", add) ;

    memset(string_inpu,0,sizeof(string_inpu)) ;

    strcat(string_inpu,add) ;
    strcat(string_inpu," --str \"") ;


    FILE* out = fopen("output.txt", "r");
    char buffer[MAX_line] ;
    bool keep_reading = true ;
    while(keep_reading)
    {
        memset(buffer,0,sizeof(buffer));
        fgets(buffer,MAX_line,out) ;
        if(feof(out))
        {
            keep_reading = false ;
            strcat(string_inpu,buffer) ;
        }
        else 
            strcat(string_inpu,buffer) ;
    }
    fclose(out) ;


    memset(add,0,sizeof(add)) ;
    add[0] = '"' ;
    j = char_pos2 ;
    i = 1;
    while(temp[j] != '\0') // start after =D( )
    {
        add[i] = temp[j] ;
        i++ ;
        j++ ;
    }    
    strcat(string_inpu,add) ;
}

// check 
void check() // after adrress  comes space for seperating word 
{
    int eenndd   = compare_my_func(string_inpu,"exit");
    int create   = compare_my_func(string_inpu,"createfile--file");// createfile--file/root/test.txt
    int insert   = compare_my_func(string_inpu,"insertstr--file"); // insertstr--file/root/test.txt( )--str( )"something"( )--pos( )i:j
    int undoo    = compare_my_func(string_inpu,"undo--file");
    int catt     = compare_my_func(string_inpu,"cat--file");
    int findd    = compare_my_func(string_inpu,"find--file"); // find--file/root/something( )--str( )["]something["]( )[-count/-at/-byword]( )[-all]
    int replacee = compare_my_func(string_inpu,"replace--file"); // replace--file/root/something( )str1( )
    int removee  = compare_my_func(string_inpu,"removestr--file"); // removestr--file/root/something( )--pos( )a:b( )[-b/-f]
    int copyy    = compare_my_func(string_inpu,"copystr--file");
    int cutt     = compare_my_func(string_inpu,"cutstr--file");
    int pastee   = compare_my_func(string_inpu,"pastestr--file");
    int grepp    = compare_my_func(string_inpu,"grep");
    int autoo    = compare_my_func(string_inpu,"auto-indent--file");
    int comparee = compare_my_func(string_inpu,"compare--file");
    int treee    = compare_my_func(string_inpu,"tree");
    int arman    = strstr(string_inpu,"=D");

    if(create == 1 && arman == 0)
    {
        create_func();
    }
    else if(insert == 1 && arman == 0)
    {
        insert_func();
    }
    else if(undoo == 1 && arman == 0)
    {
        undo_func();
    }
    else if(catt)
    {
        if(!arman)
        {
            cat_func();
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                cat_func();
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                cat_func();
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                cat_func();
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                cat_func();
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(removee == 1 && arman == 0)
    {
        remove_func();
    }
    else if(copyy == 1 && arman == 0)
    {
        copy_func();
    }
    else if(cutt == 1 && arman == 0)
    {
        cut_func();
    }
    else if(pastee == 1 && arman == 0)
    {
        paste_func();
    }
    else if(findd)
    {
        find_func();
        if(!arman)
        {
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(replacee)
    {
        replace_func();
        if(!arman)
        {
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(grepp)
    {
        grep_func();
        if(!arman)
        {
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(autoo == 1 && arman == 0)
    {
        auto_func();
    }
    else if(comparee)
    {
        compare_func();
        if(!arman)
        {
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(treee)
    {
        tree_func();
        if(!arman)
        {
            print_out() ;
        }
        else
        {
            if(find_2_func(string_inpu , "insertstr--file"))
            {
                make_string_inpu_right(15) ;
                insert_func() ;
            }
            else if(find_2_func(string_inpu,"removestr--file"))
            {
                make_string_inpu_right(15) ;
                remove_func() ;
            }
            else if (find_2_func(string_inpu,"find--file"))
            {
                make_string_inpu_right(10) ;
                find_func() ;
                print_out() ;
            }
            else if(find_2_func(string_inpu,"grep"))
            {
                make_string_inpu_right(4) ;
                grep_func() ;
                print_out() ;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
    }
    else if(eenndd)
        end = 0 ;
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
    FILE* out = fopen("output.txt", "w");
    fclose(out);

    while(end)
    {
        input_in();
    }

    remove("output.txt");
}