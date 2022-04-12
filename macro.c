#include "macro.h"
#include "utils.c"



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
    

    
    char line[MAX_LINE_LENGTH]; /*get next line*/
    char tmpStr[MAX_LINE_LENGTH];  
    bool Ismacro=FALSE; /*inside a macro? */
    bool success=TRUE; /*no errors in the proccess */
    macro *macro_arr=NULL; /*aray of all macros*/
    int macro_arr_index=0;
    int i;
    bool normal_line=TRUE;
    int lineIndex;
    int word_index;    /*holds the position in the line*/
    macro *current_macro=NULL;
    struct macro_list list;
    list.head=NULL;




    for (lineIndex = 1; TRUE; lineIndex++) { /* Runs through all the lines. */
        word_index=0;
        normal_line=TRUE;
        Ismacro=FALSE;
		if (!getLine(src, line)) {	
                end(&list);
            
            /*end of code lines, save file*/
		    return success; /* End when EOF is encountered - step 9*/
		}

        
        replace_multi_space_with_single_space(line);

        if (isEffectLessLine(line)) {/*comments etc*/
			continue;

        }
        sscanf(line, "%s", tmpStr);/*get 2st word of the line*/
        word_index+=strlen(tmpStr)+1;


        /*check if it is  amacro name if it is -insert macro lines into file*/
        normal_line = !does_macro_exist(tmpStr, list, dest);
    

        if(!strcmp(tmpStr,"macro")){/*new macro*/
            Ismacro=TRUE;
            normal_line=FALSE;

        }
        if(Ismacro){
            sscanf(line + word_index, "%s", tmpStr);/*6 is the length of word "macro"*/
            word_index+=strlen(tmpStr)+1;
            if(validReg(tmpStr)){/*here I check for valid macro*/
                success=FALSE;
                continue;
            }    
            else{
                /*add macro to list*/
                current_macro=add_macro(tmpStr, &list);

                /*save macro name in table. then read all macro*/
                while(TRUE){
                    if (!getLine(src, line)) {	/*step 1*/
                    success=FALSE;
                    end(&list);
			         /* End when EOF is encountered - step 9*/ 
                    break;
                    }    
                    sscanf(line, "%s", tmpStr);
                    if(!strcmp(tmpStr,"endmacro")){
                        break;

                    }  
                    else{
                        add_macro_line(line, current_macro);
                       

                    }

                }
                
            }    
		}
        /*if non of above then just write the line into the file*/
        if(normal_line){
           fprintf(dest,"%s", line);

        }
        
    }
        

    return success;
}


int end(macro_list *macros){
    macro *macro_loop = macros.head;
    macro *tmp = NULL;

    macro_line *line_loop;
    macro_line *tmp2=NULL;

    while(tmp!=NULL){
        macro_line *line_loop=macro_loop->head;
        while(line_loop!=NULL){
            tmp2=line_loop->next;
            free(line_loop);
            line_loop=tmp2
        }    

        tmp=macro_loop->next;
        free(macro_loop);
        macro_loop=tmp2;



    }


}






bool does_macro_exist(char *name, struct macro_list p1, FILE *dest){
    macro *tmp = p1.head;
    while(tmp!=NULL){/*going through macros*/
        if(!strcmp(tmp->macro_name, name)){
            macro_line *tmp2=tmp->head;
            while(tmp2!=NULL){/*going through lines*/
                printf("\n line i %s\n", tmp2->line);

                fprintf(dest, "%s", tmp2->line);
                tmp2=tmp2->next;

            }
            return TRUE;
        }
        tmp=tmp->next;
    }
    return FALSE;

}


macro *add_macro(char *name, struct macro_list *p1){
    printf("\n add macro %s", name);
    macro *newNode = malloc(sizeof(struct macro));
    strcpy(newNode->macro_name,name);
    newNode->head=newNode->tail;




    newNode->next=p1->head;
    p1->head=newNode;
    return newNode;

}



   
void print_list(struct macro_list p1){
    printf("\n print list");
    macro *tmp = p1.head;
    while(tmp!=NULL){
        printf("\n nrunning : %s \n", tmp->macro_name);
        tmp=tmp->next;
    }

}




void add_macro_line(char *line, macro *node){
    static macro_line *myLine;
    static macro *last_node;
    if(last_node!=node){
        myLine=NULL;
    }
    last_node=node;
    printf("\n my Line is %s \n", myLine->line);
    macro_line *newLine = malloc(sizeof(macro_line));
    newLine->line[0]='\0';
    newLine->next=NULL;
    strcpy(newLine->line, line);
    if(node->head==NULL){
        node->head=myLine;
    }
    if(myLine==NULL){
        myLine=newLine;
    }
    else{  
        myLine->next=newLine;
        myLine=myLine->next;
    }
    printf("%s", newLine->line);
    
    


}

