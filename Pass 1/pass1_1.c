#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void main(){
    char opcode[10], operand[10], label[10], mnemonic[10], code[10];
    int locctr, start, length;

    FILE *input, *optab, *symbol, *output;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symbol = fopen("symbol.txt", "w");
    output = fopen("output.txt", "w");

    fscanf(input,"%s\t%s\t%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        start = atoi(operand);
        locctr = start;
        fprintf(output, "\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    } else {
        locctr = 0;
    }

    while(strcmp(opcode,"END")!=0){
        fprintf(output, "%d\t",locctr);
        if(strcmp(label,"-")!=0){
            fprintf(symbol, "%s\t%d\n",label,locctr);
        }
        fscanf(optab,"%s\t%s",code,mnemonic);
        while(strcmp(code,"END")!=0){
            if(strcmp(opcode,code)==0){
                locctr += 3;
                break;
            }
            fscanf(optab,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"WORD")==0){
            locctr += 3;
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr += (3*(atoi(operand)));
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr += atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0){
            locctr+=strlen(operand)-2;
    
        }
        fprintf(output, "%s\t%s\t%s\t\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(output, "\t%s\t%s\t%s\n",label,opcode,operand);
    length = locctr-start;
    printf("The length of code: %d\n",length);
    fclose(input);
    fclose(optab);
}
