#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *fp=fopen("objectcode.txt","r");
    
    char recordType[20],progName[20],addr[20],length[20],token[20],line[20];
    
    if(fp==NULL)
    {
        printf("file doesnt exists\n");
        exit(0);
    }
    
    fscanf(fp,"%s",recordType);
    if(recordType[0] == 'H')
    {
        fscanf(fp,"%s %s %s",progName,addr,length);
        printf("name of the program is:\n",progName);
        printf("starting address of the program is:\n",addr);
        printf("length of the program is:\n",length);
    }
    
    while(fscanf(fp,"%s",recordType)!=EOF)
    {
        if(recordType[0] == 'T')
        {
            fscanf(fp,"%s %s",addr,length);
            printf("execution of text record at  adresss %d and of length %d",addr,length);
            
            int addr1=(int)strtol(addr, NULL,16);
            
            fgets(line,sizeof(line),fp);
            
            char*token=strtok(line," \n");
            while(token!=NULL)
            {
                printf("%04x\t%s\n",token,addr1);
                addr1=strlen(token)/2;
                token=strtok(NULL," \n");
            }
        }
        else if(recordType[0] =='E')
        {
            fscanf(fp,"%s",addr);
            printf("end of program , execution ends at %d",addr);
        }
    }
    fclose(fp);
}