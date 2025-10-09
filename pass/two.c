#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char label[20],opcode[20],operand[20];
    char code[20],mnemonic[20],symlabel[20];
    int symadd,length,add,start;
    
   FILE * intermediate=fopen("intermediate.txt","r"); 
   FILE * optab=fopen("optab.txt","r");
   FILE * symtab=fopen("symtab.txt","r");
   FILE * lenfile=fopen("length.txt","r");
    
   fscanf(intermediate,"%s%s%s",label,opcode,operand);
   fscanf(lenfile,"%d",&length);
   
   if(strcmp(opcode,"START")==0)
   {
       start=atoi(operand);
   }
   else
   {
       start=0;
   }
   
   printf("H^%s^%06d^%06X\n",label,start,length);
   
   while(fscanf(intermediate,"%d%s%s%s",&add,label,opcode,operand)==4)
   {
       if(strcmp(opcode,"START")==0)
       {
           break;
       }
       int found=0;
       rewind(optab);
      
      while(fscanf(optab,"%s%s",code,mnemonic)==2)
      {
          if(strcmp(opcode,code)==0)
          {
              found=0;
              rewind(symtab);
              
               while(fscanf(symtab,"%s%d",symlabel,&symadd)==2)
               {
                   int opadd=0;
                   if(strcmp(opcode,symlabel)==0)
                   {
                       opadd=symadd;
                       printf("T^%06d^%s%06d\n",add,mnemonic,symadd);
                       break;
                   }
               }
          }
      }
      if(!found && (strcmp(opcode,"WORD")==0 || strcmp(opcode,"BYTE")==0))
      {
          printf("T^%06d^%06X\n", add, atoi(operand));
      }
   }
    printf("E^%06d\n", start);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(lenfile);

    return 0;
}
