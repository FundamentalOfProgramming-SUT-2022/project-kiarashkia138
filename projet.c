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
        else return 0 ;
    }
    else return -1 ;
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
        case 5:
            printf("Error...! Invalid input.\n") ;
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

// find
// wild
void string_che(char buffer [] , int* pos, bool* find)
{
    int len_buf = strlen(buffer) ;
    int len_user = strlen(user_str); 
    int count = 0, nege = 1;
    if(user_str[0] == '*')
    {
        for(int i = 0 ; i < len_buf ; i++)
        {
            for (int j = 1; j < len_user; j++)
            {
                if(user_str[j] == '\\' && user_str[j+1] == '*')
                {
                    j++;
                    nege++ ;
                    if(user_str[j] == buffer[i+j-nege])
                        count++ ;
                    else
                        break;
                }
                else if(user_str[j] == buffer[i+j-nege])
                {
                    count++;
                }
                else 
                    break;
            }
            // printf("count : %d , nege : %d\n",count,nege);
            if(count >= (len_user-nege) && (buffer[i+len_user-nege] == ' ' || buffer[i+len_user-nege] == '\n' || buffer[i+len_user-nege] == '\0'))
            {
                while(buffer[*(pos)] != ' ')
                {
                    if(*(pos) == 0)
                    {
                        *(pos) -= 1 ;
                        break;
                    }
                    *(pos) -= 1 ;
                }
                *(pos) += 1 ;
                *(find) = true ;
                return ;
            }
            *(pos) += 1 ;
            count = 0 ;
            nege = 1;
        }
    }
    else
    {
        nege = 0;
        for(int i = 0 ; i < len_buf ; i++)
        {
            if(buffer[i-1] == ' ' || i == 0)
            {
                for (int j = 0; j < len_user; j++)
                {
                    if(user_str[j] == '\\' && user_str[j+1] == '*')
                    {
                        j++;
                        nege++;
                        if(user_str[j] == buffer[i+j-nege])
                            count++ ;
                        else
                            break;
                    }
                    else if(buffer[i+j-nege] == user_str[j])
                    {
                        count++ ;
                    }
                    else 
                        break;
                }
                if(user_str[len_user-1] == '*' && user_str[len_user-2] != '\\')
                {
                    nege++ ;
                }
                else
                {
                    count-- ;
                    if(buffer[i+len_user-nege] == ' ' || buffer[i+len_user-nege] == '\n' || buffer[i+len_user-nege] == '\0') 
                        count++ ;

                }
                if(count >= len_user-nege)
                {
                    *(find) = true ;
                    return ;
                }
            }
            count = 0;
            *(pos) += 1 ;
            nege = 0 ;
        }
    }
}


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
    bool* find = (bool*)malloc(sizeof(bool)); 
    int* pos = (int*)malloc(sizeof(int));
    *(find) = false;
    *(pos) = 0 ;

    if(first_find_op == 0) // no other options
    {
        while ((fgets(buffer,MAX_line, file)) != NULL)
        {
            *(pos) = 0 ;
            string_che(buffer, pos,find) ;
            if(*(find))
            {
                num_pos += *(pos) ;
                break;
            }
            else
                num_pos += *(pos) ;
        }
    }
    
    else if(first_find_op == 1) // count
    {
        if(find_options() == 10) // with all 
        {
            
        }
        else
        {
            
        }
    }
    else if(first_find_op == 2) // at
    {
        if(find_options() == 10) // with all 
        {
            
        }
        else
        {
            
        }
    }
    else if(first_find_op == 3)//byword
    {
        if(find_options() == 10) // with all 
        {
            
        }
        else
        {
            
        }
    }
    else if(first_find_op == 10) // all
    {
        
    }
    else
    {
        error(5) ;
    }

    if(*(find)) print_std_i(num_pos) ;
    else print_std("Not Found\n") ;
    fclose(file) ;
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