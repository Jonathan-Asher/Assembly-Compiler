#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro2.h"
#include "constants.h"

char *ops[] = {"mov","cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"};
char *directives[]={".data", ".string", ".struct", ".entry"};

bool saved_word(char *);
bool isEffectLessLine(char *);
bool getLine(FILE *, char *);
bool validReg(char *);
void replace_multi_space_with_single_space(char *)

bool saved_word(char *str) {/*return true if str is a saved word*/
    int i;

    for(i=0; i<MAX_OPERATIONS; i++) {
        if(!strcmp(ops[i], str)) {
            return TRUE;
        }

    }
    for(i=0; i<MAX_DIRECTIVES; i++) {
        if(!strcmp(directives[i], str)) {
            return TRUE;
        }

    }
    return FALSE;
}

bool isEffectLessLine(char *line) {
    int length;
    char tmpStr[MAX_LINE_LENGTH];
    if ((length = strlen(line))== 0 || sscanf(line, "%s", tmpStr) == 0 || tmpStr[0] == ';' ) { 
        return TRUE;
    }
    return FALSE;
}

bool getLine(FILE *file, char *line) {

    if (!fgets(line, MAX_LINE_LENGTH, file)) { /* EOF encountered */
 		return FALSE;
 	}
 	return TRUE;
}

bool validReg(char *regStr) {
 	return ((regStr[0] == 'r' && '0' <= regStr[1] && regStr[1] <= '7'
 			&& regStr[2] == '\0') ? TRUE : FALSE);
}

void replace_multi_space_with_single_space(char *str) {
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

/*  ----------------------LABELS--------------------------------*/

bool does_label_exist(char *, struct symbol_table );
bool validLabel(char *, struct symbol_table);
bool add_label(char *, int , struct symbol_table *);
void print_list(struct symbol_table );

bool validLabel(char *label, struct symbol_table p1) {
    int i;
    int len=strlen(label);
    if(label[len-1]!=':') {
        return FALSE;
    }

    label[len-1]='\0'; 
    if(does_label_exist(label, p1)) {
        return FALSE;
    }
    if(saved_word(label)) {
        return FALSE;
    }
    if(!isalpha(label[0])) {
        return FALSE;
    }

    for(i=0;i<len-1; i++) {
        if(!isalpha(label[i])&&!isdigit(label[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

bool add_label(char *symbolName, int address, label_type type, struct symbol_table *p1) {
    if(!validLabel(symbolName, *p1)) {return FALSE;}
    symbol_node *newNode = malloc(sizeof(struct symbol_node));

    newNode->symbolName=(char *)(malloc(sizeof(symbolName)));
    strcpy(newNode->symbolName,symbolName);
    newNode->address=address;
    newNode->type=type;
    
    newNode->next=p1->head;
    p1->head=newNode;
    return TRUE;

}

void print_list(struct symbol_table p1) {
    symbol_node *tmp = p1.head;
    while(tmp!=NULL) {
        printf("\n nrunning : %s \n", tmp->symbolName);
        tmp=tmp->next;
    }

}

bool does_label_exist(char *label, struct symbol_table p1) {
    symbol_node *tmp = p1.head;
    while(tmp!=NULL) {
        if(!strcmp(tmp->symbolName, label)) {
            return TRUE;
        }
        tmp=tmp->next;
    }
    return FALSE;

}

/*   ----------------------------END LABELS---------------------------------------*/
