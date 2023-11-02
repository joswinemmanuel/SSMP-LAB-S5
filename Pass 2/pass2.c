#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int searchOptab(char opcode[10]){  //for searching in optab and returning opcode
    FILE *optab;
    char op[10];
    int value;
    optab=fopen("optab.txt","r");
    while(!feof(optab)){
        fscanf(optab,"%s%d",op,&value);
        if(strcmp(op,opcode)==0){
            return value;
        }
    }
    fclose(optab);
    return -1;
}
int searchSymtab(char label[10]){  //for searching in symbab and returning its location
    FILE *symtab;
    char sym[10];
    int value;
    symtab=fopen("symtab.txt","r");
    while(!feof(symtab)){
        fscanf(symtab,"%s%d",sym,&value);
        if(strcmp(sym,label)==0){
            return value;
        }
    }
    fclose(symtab);
    return -1;
}
int main(){
    FILE *intermediate,*output,*header,*text,*end,*symtab,*optab;
    char label[10],opcode[10],operand[10],obcode[10],obcodeTe[100]="",obcodeCopy[10];
    int LOCCTR,symaddr,opaddr,i,sa,leng,lenObCode=0,flag=0,flag2=0,opc; 

    intermediate=fopen("intermediate.txt","r");       //opening all needed files
    output=fopen("output.txt","w");
    header=fopen("header.txt","w");
    text=fopen("text.txt","w");
    end=fopen("end.txt","w");

    fscanf(intermediate,"%s%s%s",label,opcode,operand);      //for label start
    if(strcmp(opcode,"START")==0){
        fprintf(header,"H^00%s^00%s",label,operand);
        fprintf(text,"T^00%s",operand);
        fprintf(end,"E^00%s",operand);
        fprintf(output,"\t%s\t%s\t%s\n",label,opcode,operand);
        sa=atoi(operand);
    }
    while (strcmp(opcode,"END")!=0){
        fscanf(intermediate,"%d%s%s%s",&LOCCTR,label,opcode,operand);
        if(strcmp(label,"**")==0){
            opaddr=searchOptab(opcode);
            if(opaddr!=-1){
                symaddr=searchSymtab(operand);
                if(symaddr!=-1){
                    sprintf(obcode,"%02d%d",opaddr,symaddr);
                    lenObCode+=3;
                } 
                strcat(obcodeTe,"^");
                strcat(obcodeTe,obcode);
            }
        }
        else if(strcmp(opcode,"BYTE")==0){
            if(flag==0){             //for entering in new line in text file if it is first byte or word opcode
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                strcpy(obcodeTe,"");
                lenObCode=0;
                flag=1;
                flag2=1;
            }
            for(i=strlen(operand);i<(6+3);i++){
                strcat(obcodeCopy,"0");
            }
            for(i=2;i<strlen(operand)-1;i++){
                strncat(obcodeCopy,&operand[i],1);
            }
            lenObCode+=3;
            sprintf(obcode,"%s",obcodeCopy);
            strcat(obcodeTe,"^");
            strcat(obcodeTe,obcode);
        }
        else if(strcmp(opcode,"WORD")==0){
            //strcpy(obcode,"");
            if(flag==0){           //for entering in new line in text file if it is first word or byte opcode
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                strcpy(obcodeTe,"");
                lenObCode=0;
                flag=1;
                flag2=1;
            }
            for(i=strlen(operand);i<6;i++){
                strcat(obcode,"0");
            }
            strcat(obcode,operand);
            lenObCode+=3;
            strcat(obcodeTe,"^");
            strcat(obcodeTe,obcode);
        }
        else{
            strcpy(obcode,"");
        }
        fprintf(output,"%d\t%s\t\t%s\t\t%s\t\t%s\n",LOCCTR,label,opcode,operand,obcode);
        if(strcmp(obcode,"")!=0){             //checking is it a valid obcode
            if(flag2==1 && (strcmp(obcodeTe,"")!=0)){      //for printing new line in text file
                fprintf(text,"\nT^%06d",LOCCTR);
                flag2=0;
            }
            if(lenObCode>17){                             //for printing new line in text file
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                strcpy(obcodeTe,"");
                lenObCode=0;
                flag2=1;
            }
        }
    }
    if(lenObCode>0){              //for printing last line of text file
        fprintf(text,"^%02d%s",lenObCode,obcodeTe);
    }
    leng=LOCCTR-sa;
    fprintf(header,"^%06d",leng);
    fclose(intermediate);
    fclose(output);
    fclose(header);
    fclose(text);
    fclose(end);
    printf("Output generated successfully");
    return 0;
}
