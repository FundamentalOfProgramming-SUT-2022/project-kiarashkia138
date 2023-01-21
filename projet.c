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
char name_of_file[MAX_line] ; 
char dir[MAX_line] ;
char user_str[MAX_line] ; // user string input
char clipboard[MAX_line] ; // clipboard
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
        while(string_inpu[char_pos] != ' ')
        {
            user_str[i] = string_inpu[char_pos] ;
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
        user_str[i] = string_inpu[char_pos] ;
        i++;
        char_pos++ ;
    }
}


void copy_str(char buffer[] ,char save_buffer[][100] ,int col)
{
    int len = strlen(buffer);

    for(int i = 0; i < len; i++)
    {
        save_buffer[i][col] = buffer[i];
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
            printf("not found.\n") ;
            break;
    }
}


void print_std(char* buffer)
{
    printf("%s", buffer);
}


void print_std_i(int i)
{
    printf("%d\n",i) ;
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
    print_std("\n") ;
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

// find
void find_func() // start from 10 // find--file/root/something( )--str( )["]something["]( )[-count/-at/-byword]( )[-all]
{
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
    int first_find_op = find_options() ;
    int num_pos = 0; 
    int pos = 0 ;
    int i = 0;
    int temp_pos = 0 ;
    bool find = false ;
    int option = 0 ;
    int count = 0 ;
    int cnt = 0 ; // for count 
    char c ;
    int len = strlen(user_str) - 1 ;

    if(first_find_op == 0) // no other options 
    {
        if(user_str[0] == '*')
        {
            count = 1;
            i = 1 ;
            while((c = fgetc(file)) != EOF)
            {
                if(i == len+1 && count == len+1)
                {
                    if(c == ' ' || c == '\0' || c == '\n')
                    {
                        pos++ ;
                        find = true ;
                        option =  0; 
                        break;
                    } 
                    count = 1 ;
                    i = 1 ;    
                }
                if(c == ' ' || c == '\n')
                {
                    pos = temp_pos ;
                }
                if(c == user_str[i])
                {
                    count++ ;
                    i++ ;
                }
                else
                {
                    count = 1 ;
                    i = 1 ;
                }
                temp_pos++ ;
            }
        }
        else if(user_str[len] == '*' && user_str[len-1] != '\\')
        {
            int flag = 0 ;

            while((c = fgetc(file)) != EOF)
            {
                if(user_str[i] == '\\' && user_str[i+1] == '*')
                {
                    i++ ;
                    count++ ;
                }

                if(flag == 1 && c == user_str[i])
                {
                    count++ ;
                    i++ ;
                }
                else if(flag == 1 && c != user_str[i])
                {
                    count = 0 ;
                    i = 0 ;
                    flag = 0 ;
                }
                else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                {
                    flag = 1;
                    count = 0 ;
                    i = 0 ;
                }
                pos ++ ;
                if(count == len)
                {
                    pos -= len ;
                    find = true ;
                    option =  0;
                    break ;
                }
            }
        }
        else
        {
            int flag = 0 ;
            int came = 0 ;
            len++ ;

            while((c = fgetc(file)) != EOF)
            {
                if(user_str[i] == '\\' && user_str[i+1] == '*')
                {
                    i++ ;
                    count++ ;
                }

                if(flag == 1 && c == user_str[i])
                {
                    count++ ;
                    i++ ;
                }
                else if(flag == 1 && c != user_str[i])
                {
                    count = 0 ;
                    i = 0 ;
                    flag = 0 ;
                }
                else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                {
                    flag = 1;
                    count = 0 ;
                    i = 0 ;
                }
                temp_pos ++ ;

                if(count == len && came == 0)
                {
                    pos = temp_pos - len ;
                    came = 1 ;
                    flag = 0 ;
                }
                else if(came == 1 && flag == 1)
                {
                    find = true ;
                    option =  0;
                    break ;
                }
                else if (came == 1 && flag == 0)
                {
                    came = 0 ;
                    count = 0 ;
                    i = 0 ;
                }
            }
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
            if(user_str[0] == '*')
            {
                count = 1;
                i = 1 ;
                while((c = fgetc(file)) != EOF)
                {
                    if(i == len+1 && count == len+1)
                    {
                        if(c == ' ' || c == '\0' || c == '\n')
                        {
                            pos++ ;
                            find = true ;
                            option = 1 ;
                            cnt++ ;
                        } 
                        count = 1 ;
                        i = 1 ;    
                    }
                    if(c == ' ' || c == '\n')
                    {
                        pos = temp_pos ;
                    }
                    if(c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else
                    {
                        count = 1 ;
                        i = 1 ;
                    }
                    temp_pos++ ;
                }
            }
            else if(user_str[len] == '*' && user_str[len-1] != '\\')
            {
                int flag = 0 ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }
                    pos ++ ;
                    if(count == len)
                    {
                        pos -= len ;
                        find = true ;
                        option =  1;
                        cnt++ ;
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                }
            }
            else
            {
                int flag = 0 ;
                int came = 0 ;
                len++ ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }
                    temp_pos ++ ;

                    if(count == len && came == 0)
                    {
                        pos = temp_pos - len ;
                        came = 1 ;
                        flag = 0 ;
                    }
                    else if(came == 1 && flag == 1)
                    {
                        find = true ;
                        option =  1;
                        i = 0 ;
                        count = 0 ;
                        flag = 1 ;
                        cnt++ ;
                        came = 0 ;
                    }
                    else if (came == 1 && flag == 0)
                    {
                        came = 0 ;
                        count = 0 ;
                        i = 0 ;
                    }
                }
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
            if(user_str[0] == '*')
            {
                count = 1;
                i = 1 ;
                while((c = fgetc(file)) != EOF)
                {
                    if(i == len+1 && count == len+1)
                    {
                        if(c == ' ' || c == '\0' || c == '\n')
                        {
                            pos++ ;
                            cnt++ ;
                            if(cnt == n_at)
                            {
                                find = true ;
                                option = 2 ;
                                break;
                            }
                        } 
                        count = 1 ;
                        i = 1 ;    
                    }
                    if(c == ' ' || c == '\n')
                    {
                        pos = temp_pos ;
                    }
                    if(c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else
                    {
                        count = 1 ;
                        i = 1 ;
                    }
                    temp_pos++ ;
                }
            }
            else if(user_str[len] == '*' && user_str[len-1] != '\\')
            {
                int flag = 0 ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }
                    pos ++ ;
                    if(count == len)
                    {
                        cnt++ ;
                        if(cnt == n_at)
                        {
                            pos -= len ;
                            find = true ;
                            option =  2;
                            break ;
                        }
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                }
            }
            else
            {
                int flag = 0 ;
                int came = 0 ;
                len++ ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }
                    temp_pos ++ ;

                    if(count == len && came == 0)
                    {
                        pos = temp_pos - len ;
                        came = 1 ;
                        flag = 0 ;
                    }
                    else if(came == 1 && flag == 1)
                    {
                        cnt++ ;
                        if(cnt == n_at)
                        {
                            find = true ;
                            option =  2;
                            break ;
                        }
                        i = 0 ;
                        count = 0 ;
                        flag = 1 ;
                        came = 0 ;
                    }
                    else if (came == 1 && flag == 0)
                    {
                        came = 0 ;
                        count = 0 ;
                        i = 0 ;
                    }
                }
            }
        }
    }

    else if(first_find_op == 3) //byword
    {
        int cnt_camma = 0 ;
        cnt = 1 ;
        if(find_options() == 10) // with all 
        {
            if(user_str[0] == '*')
            {
                count = 1;
                i = 1 ;
                while((c = fgetc(file)) != EOF)
                {
                    if(i == len+1 && count == len+1)
                    {
                        if(c == ' ' || c == '\0' || c == '\n')
                        {
                            find = true ;
                            option = 3 ;
                            if(cnt_camma) printf(",");
                            printf("%d ",cnt);
                            cnt_camma = 1;
                        } 
                        count = 1 ;
                        i = 1 ;    
                    }
                    if(c == ' ' || c == '\n')
                    {
                        cnt++ ;
                    }
                    if(c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else
                    {
                        count = 1 ;
                        i = 1 ;
                    }
                }
            }
            else if(user_str[len] == '*' && user_str[len-1] != '\\')
            {
                int flag = 0 ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        cnt++ ;
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }

                    if(count == len)
                    {
                        find = true ;
                        option =  3;
                        if(cnt_camma) printf(",");
                        printf("%d ",cnt) ;
                        cnt_camma = 1; 
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                }
            }
            else 
            {
                int flag = 0 ;
                int came = 0 ;
                len++ ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                        cnt++ ;
                    }
                    temp_pos ++ ;

                    if(count == len && came == 0)
                    {
                        came = 1 ;
                        flag = 0 ;
                    }
                    else if(came == 1 && flag == 1)
                    {
                        find = true ;
                        option =  3;
                        if(cnt_camma) printf(",");
                        printf("%d ",cnt) ;
                        cnt_camma = 1;
                        i = 0 ;
                        count = 0 ;
                        flag = 1 ;
                        came = 0 ;
                    }
                    else if (came == 1 && flag == 0)
                    {
                        came = 0 ;
                        count = 0 ;
                        i = 0 ;
                    }
                }
            }
        }
        else
        {
            if(user_str[0] == '*')
            {
                count = 1;
                i = 1 ;
                while((c = fgetc(file)) != EOF)
                {
                    if(i == len+1 && count == len+1)
                    {
                        if(c == ' ' || c == '\0' || c == '\n')
                        {
                            find = true ;
                            option = 3 ; 
                            printf("%d",cnt);
                            break ;
                            cnt_camma = 1;
                        } 
                        count = 1 ;
                        i = 1 ;    
                    }
                    if(c == ' ' || c == '\n')
                    {
                        cnt++ ;
                    }
                    if(c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else
                    {
                        count = 1 ;
                        i = 1 ;
                    }
                }
            }
            else if(user_str[len] == '*' && user_str[len-1] != '\\')
            {
                int flag = 0 ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        cnt++ ;
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }

                    if(count == len)
                    {
                        find = true ;
                        option =  3;
                        printf("%d",cnt) ;
                        break;
                        cnt_camma = 1; 
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                }
            }
            else 
            {
                int flag = 0 ;
                int came = 0 ;
                len++ ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                        cnt++ ;
                    }
                    temp_pos ++ ;

                    if(count == len && came == 0)
                    {
                        came = 1 ;
                        flag = 0 ;
                    }
                    else if(came == 1 && flag == 1)
                    {
                        find = true ;
                        option =  3;
                        printf("%d",cnt) ;
                        break;
                        cnt_camma = 1;
                        i = 0 ;
                        count = 0 ;
                        flag = 1 ;
                        came = 0 ;
                    }
                    else if (came == 1 && flag == 0)
                    {
                        came = 0 ;
                        count = 0 ;
                        i = 0 ;
                    }
                }
            }
        }
    }

    else if(first_find_op == 10) // all
    {
        int cnt_camma = 0 ;

        if(user_str[0] == '*')
        {
            count = 1;
            i = 1 ;
            while((c = fgetc(file)) != EOF)
            {
                if(i == len+1 && count == len+1)
                {
                    if(c == ' ' || c == '\0' || c == '\n')
                    {
                        pos++ ;
                        find = true ;
                        option =  4;
                        if(cnt_camma) printf(",") ; 
                        printf("%d ",pos);
                        cnt_camma = 1 ;
                    } 
                    count = 1 ;
                    i = 1 ;    
                }
                if(c == ' ' || c == '\n')
                {
                    pos = temp_pos ;
                }
                if(c == user_str[i])
                {
                    count++ ;
                    i++ ;
                }
                else
                {
                    count = 1 ;
                    i = 1 ;
                }
                temp_pos++ ;
            }
        }
        else if(user_str[len] == '*' && user_str[len-1] != '\\')
        {
            int flag = 0 ;

            while((c = fgetc(file)) != EOF)
            {
                if(user_str[i] == '\\' && user_str[i+1] == '*')
                {
                    i++ ;
                    count++ ;
                }

                if(flag == 1 && c == user_str[i])
                {
                    count++ ;
                    i++ ;
                }
                else if(flag == 1 && c != user_str[i])
                {
                    count = 0 ;
                    i = 0 ;
                    flag = 0 ;
                }
                else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                {
                    flag = 1;
                    count = 0 ;
                    i = 0 ;
                }
                pos ++ ;
                if(count == len)
                {
                    if(cnt_camma == 0)pos -= len ;
                    find = true ;
                    option =  4;
                    if(cnt_camma) printf(",");
                    cnt_camma = 1 ;
                    printf("%d ", pos) ;
                    count = 0 ;
                    i = 0 ;
                    flag = 0 ;
                }
            }
        }
        else
            {
                int flag = 0 ;
                int came = 0 ;
                len++ ;

                while((c = fgetc(file)) != EOF)
                {
                    if(user_str[i] == '\\' && user_str[i+1] == '*')
                    {
                        i++ ;
                        count++ ;
                    }

                    if(flag == 1 && c == user_str[i])
                    {
                        count++ ;
                        i++ ;
                    }
                    else if(flag == 1 && c != user_str[i])
                    {
                        count = 0 ;
                        i = 0 ;
                        flag = 0 ;
                    }
                    else if(flag == 0 && (c == ' ' || c == '\n' || c == '\0'))
                    {
                        flag = 1;
                        count = 0 ;
                        i = 0 ;
                    }
                    temp_pos ++ ;

                    if(count == len && came == 0)
                    {
                        pos = temp_pos - len ;
                        came = 1 ;
                        flag = 0 ;
                    }
                    else if(came == 1 && flag == 1)
                    {
                        find = true ;
                        option =  4;
                        if(cnt_camma) printf(",");
                        printf("%d ",pos) ;
                        cnt_camma = 1 ;
                        i = 0 ;
                        count = 0 ;
                        flag = 1 ;
                        came = 0 ;
                    }
                    else if (came == 1 && flag == 0)
                    {
                        came = 0 ;
                        count = 0 ;
                        i = 0 ;
                    }
                }
            }
    }

    else
    {
        error(5) ;
        return;
    }

    if(find)
    {
        if(option == 0) print_std_i(pos) ;
        else if(option == 1) print_std_i(cnt) ;
        else if(option == 2) print_std_i(pos) ;
        else if(option == 3) print_std("\n") ;
        else if(option == 4) print_std("\n") ;
        else error(3) ;
    }
    else print_std_i(-1) ;
    fclose(file) ;
}

// grep
void grep_func() // grep [-c/-l] --str "something" --file/root/test.txt --file/root/test.txt --file/root/test.txt ...
{
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
                        printf("%s: %s\n",name_of_file,buffer); 
                    }
                }
                else 
                {
                    if(strstr(buffer,user_str))
                    {
                        printf("%s: %s",name_of_file,buffer); 
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
                        printf("%s\n",name_of_file); 
                        break;
                    }
                }
                else 
                {
                    if(strstr(buffer,user_str))
                    {
                        printf("%s\n",name_of_file); 
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
                printf("============ #%d ============\n" ,line1) ;
                print_std(buffer1);
                // print_std("\n");
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
                printf("============ #%d ============\n" ,line1) ;
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
                printf("============ #%d ============\n" ,line1) ;
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

        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",save_line ,(line1-1)) ;
        for(int i = 0 ; i < col ; i++)
        {
            int j = 0 ;
            while(save_buffer[j][i] != '\0')
            {
                printf("%c", save_buffer[j][i]);
                j++ ;
            }
        }
        printf("\n");
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
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",save_line ,(line2-1)) ;
        for(int i = 0 ; i < col ; i++)
        {
            int j = 0 ;
            while(save_buffer[j][i] != '\0')
            {
                printf("%c", save_buffer[j][i]);
                j++ ;
            }
        }
        printf("\n");
    }


    fclose(file) ;
    fclose(file2) ;
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
    int create = strstr(string_inpu,"createfile--file");// createfile--file/root/test.txt
    int insert = strstr(string_inpu,"insertstr--file"); // insertstr--file/root/test.txt( )--str( )"something"( )--pos( )i:j
    int undoo = strstr(string_inpu,"undo--file");
    int catt = strstr(string_inpu,"cat--file");
    int findd = strstr(string_inpu,"find--file"); // find--file/root/something( )--str( )["]something["]( )[-count/-at/-byword]( )[-all]
    int removee = strstr(string_inpu,"removestr--file"); // removestr--file/root/something( )--pos( )a:b( )[-b/-f]
    int copyy = strstr(string_inpu,"copystr--file");
    int cutt = strstr(string_inpu,"cutstr--file");
    int pastee = strstr(string_inpu,"pastestr--file");
    int grepp = strstr(string_inpu,"grep");
    int autoo = strstr(string_inpu,"auto-indent--file");
    int comparee = strstr(string_inpu,"compare--file");
    
    if(create)
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
    else if(copyy)
    {
        copy_func() ;
    }
    else if(cutt)
    {
        cut_func() ;
    }
    else if(pastee)
    {
        paste_func() ;
    }
    else if(findd)
    {
        find_func() ;
    }
    else if(grepp)
    {
        grep_func() ;
    }
    else if(autoo)
    {
        auto_func() ;
    }
    else if(comparee)
    {
        compare_func() ;
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
    while(end)
    {
        input_in();
    }
}