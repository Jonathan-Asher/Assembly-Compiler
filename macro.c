#include "macro.h"



int main(){
    bool success;
    FILE *src=fopen("text.tx", "r");
    FILE *dest=fopen("textout.txt", "w");
    success=macro_func(src, dest);
    fclose(src);
    fclose(dest);
    return success;
}




bool macro_func(FILE *src, FILE *dest){
    char line[MAX_LINE_LENGTH]; /* get next line */
    char *line_pointer;
    char tmpStr[MAX_LINE_LENGTH];  
    bool Ismacro=FALSE; /* inside a macro? */
    bool success=TRUE; /* no errors in the proccess */
    macro * macro_arr=NULL; /* aray of all macros */
    int macro_arr_index=0;
    int i;
    bool normal_line=TRUE;
    int lineIndex;
    int word_index;    

    for (lineIndex = 1; TRUE; lineIndex++) { /* Runs through all the lines. */
        word_index=0;
        normal_line=TRUE;
        Ismacro=FALSE;
        if (!getLine(src, line)) {	
                end(src, dest, macro_arr, macro_arr_index);
          /*end of code lines, save file*/
                return TRUE; /* End when EOF is encountered - step 9*/
        }


        replace_multi_space_with_single_space(line);

        if (isEffectLessLine(line)) {/*comments etc*/
 			continue;

        }
        line_pointer=line;
        sscanf(line_pointer, "%s", tmpStr);
        line_pointer+=strlen(tmpStr)+1;


        for(i=0; i<macro_arr_index; i++){
            if(!strcmp(macro_arr[i].macro_name, tmpStr)){
                fprintf(dest,"%s", macro_arr[i].macro_lines);
                normal_line=FALSE;
                
                break;
            }

        }


        if(!strcmp(tmpStr,"macro")){/*new macro*/

            macro_arr = realloc(macro_arr, sizeof(macro)*(macro_arr_index+1));
            Ismacro=TRUE;
            normal_line=FALSE;

        }
        if(Ismacro){
            sscanf(line_pointer, "%s", tmpStr);
            line_pointer+=strlen(tmpStr)+1;
            if(validReg(tmpStr)){/*here I check for valid macro*/
                success=FALSE;
                continue;
            }    
            else{

                strcpy(macro_arr[macro_arr_index].macro_name, tmpStr);
                /*save macro name in table. then read all macro*/
                while(TRUE){
                    if (!getLine(src, line)) {	/*step 1*/
                    success=FALSE;
                    end(src, dest, macro_arr, macro_arr_index);
 			         /* End when EOF is encountered - step 9*/ 
                    break;
                    }    
                    sscanf(line, "%s", tmpStr);
                    if(!strcmp(tmpStr,"endmacro")){
                        macro_arr_index++;
                        break;

                    }  
                    else{
                        /*add the line of the macro into the macro memory HERE!@*/

                        macro_arr[macro_arr_index].macro_lines=(char *)realloc(macro_arr[macro_arr_index].macro_lines, sizeof(macro_arr[macro_arr_index].macro_lines)+sizeof(line));
                        strcat(macro_arr[macro_arr_index].macro_lines, line);



                    }

                }

            }    
 		}
        if(normal_line){
            fprintf(dest,"%s", line);

        }
         /*if non of above then just write the line into the file*/
    }


    return success;
}


int end(FILE *src, FILE *dest, macro *macro_arr,int arr_length){
    int index=0;

    for (; index<arr_length; index++){
        free(macro_arr[index].macro_lines);
    }

    free(macro_arr);

    return TRUE;

}





bool isEffectLessLine(char *line){
    int length;
    char tmpStr[MAX_LINE_LENGTH];
    if ((length = strlen(line))== 0 || sscanf(line, "%s", tmpStr) == 0 || tmpStr[0] == ';' ) { 
        return TRUE;
    }
    return FALSE;
}


bool getLine(FILE *file, char *line){

    if (!fgets(line, MAX_LINE_LENGTH, file)) { /* EOF encountered */
 		return FALSE;
 	}
 	return TRUE;
}




bool validReg(char *regStr) {
 	return ((regStr[0] == 'r' && '0' <= regStr[1] && regStr[1] <= '7'
 			&& regStr[2] == '\0') ? TRUE : FALSE);
}





void replace_multi_space_with_single_space(char *str)
{
    char *tmp = str;  

    while (*str != '\0')
    {

        while (((*tmp == ' ')||(*tmp == '\t')) && ((*(tmp + 1) == ' ')||(*(tmp + 1) == '\t')))
            tmp++;  /* Just skip to next character */


        *str++ = *tmp++;
    }

     /* Make sure the string is properly terminated */    
    *str = '\0';

}