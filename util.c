bool validLabel(char *label){
    int i;
    int len=sizeof(label)/sizeof(char);
    if(does_label_exist(label)){
        return FALSE;
    }
    if(saved_word(label)){
        return FALSE;
    }
    if(!isalpha(label[0])){
        return FALSE;
    }
    if(labe[len-1]!=':'){
        return FALSE;
    }
    for(i=0;i<len; i++){
        if(!(isalpha(label[i])||!isdigit(label[i])){
            return FALSE;
        }
    }
    return TRUE;
    
}



bool add_label(char *symbolName, int address, struct symbol_table *p1){
    symbol_node *newNode = malloc(sizeof(struct symbol_node));

    newNode->symbolName=(char *)(malloc(sizeof(symbolName)));
    newNode->symbolName=symbolName;
    newNode->address=address;
    
    newNode->next=p1->head;
    p1->head=newNode;
   

}


    
void print_list(struct symbol_table p1){
    symbol_node *tmp = p1.head;
    while(tmp!=NULL){
        printf("\n nrunning : %s \n", tmp->symbolName);
        tmp=tmp->next;
    }

}

bool does_label_exist(char *label, struct symbol_table p1){
    symbol_node *tmp = p1.head;
    while(tmp!=NULL){
        if(!strcmp(tmp->symbolName, label)){
            return TRUE;
        }
        tmp=tmp->next;
    }
    return FALSE;

}

