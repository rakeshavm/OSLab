#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
void main(int argc, char *argv[])
{
  FILE *fp;
  int fd,r,j=0,lineno=0;
  char temp,line[100];
  if(argc < 3)
    printf("error");
  else{
    if((fd=open(argv[1],O_RDONLY)) != -1)
      {
        while((r=read(fd,&temp,sizeof(char)))!= 0)
	  {
            if(temp!='\n')
	      {
                line[j]=temp;
                j++;
	      }
            else
	      {
		lineno++;
		line[j]='\0';
                if(strstr(line,argv[1])!=NULL)
		  printf("%d %s\n",lineno,line);
                j=0;
	      }

	  }
      }   
    

  }
  
}
