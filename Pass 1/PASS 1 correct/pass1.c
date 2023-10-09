#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main(){
	FILE *inter, *symtab, *optab, *src;
	optab=fopen("optab.txt","r");
	symtab=fopen("symtab.txt","w+");
	inter=fopen("intermediate.txt","w");
	src=fopen("source.txt","r");

	char label[20],opcode[20],operand[20],sym_label[20],optab_code[20];
	int locctr,starting_address,prgrm_length;
	bool sym_found,op_found;

	fscanf(src,"%s%s%s",label,opcode,operand);

	if(strcmp(opcode,"START")==0)
	{	
		starting_address=atoi(operand);
		locctr=starting_address;
		fprintf(inter,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	}
	
	else{
		locctr=0;
	}
	
	fscanf(src,"%s%s%s",label,opcode,operand);
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(label,"XX")!=0)
		{
			sym_found=false;
			rewind(symtab);
			while(!feof(symtab)){
			
				fscanf(symtab,"%s",sym_label);
				if(strcmp(sym_label,label)==0)
				{
					printf("Error: Label found in SYMTAB");
					sym_found=true;
				}
	
			}
			
			
			if(sym_found==false){
			
				fprintf(symtab,"%d\t%s\n",locctr,label);
			}
			
			
		}
		
		op_found=false;
		rewind(optab);
		while(!feof(optab)){
			
			fscanf(optab,"%s",optab_code);
			if(strcmp(optab_code,opcode)==0){

				op_found=true;
				
			}
		}
		
		if(op_found==true){
			locctr+=3;
		}
		else if(strcmp(opcode,"WORD")==0){
			locctr+=3;
		}
		else if(strcmp(opcode,"RESW")==0){
			locctr+=3*atoi(operand);
		}
		else if(strcmp(opcode,"RESB")==0){
			locctr+=atoi(operand);
		}
		else if(strcmp(opcode,"BYTE")==0){
			locctr=locctr+strlen(operand)-3;
		}
		else{
			printf("Error: Invalid operation code");
		}
		fprintf(inter,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		
		fscanf(src,"%s%s%s",label,opcode,operand);
		
		
	}
	fprintf(inter,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	prgrm_length=locctr-starting_address;
	printf("\nProgram length: %d\n\n",prgrm_length);

	fclose(inter);
	fclose(symtab);
	fclose(optab);
	fclose(src);

}


