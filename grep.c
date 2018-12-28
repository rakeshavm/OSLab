       #include <dirent.h>
#include <stdio.h>
#include <string.h>

 

int main(int argc,char *argv[])

{

char *files[];

if(argc==1){
printf("Enter sufficient args");
return;
}
if(argc==2){
printf("Enter a search pattern");
return ;
}
FILE *fp;
char *temp;
    DIR *d;

    struct dirent *dir;
    d = opendir(".");

    if (d)

    {

        while ((dir = readdir(d)) != NULL)

        {
            fp=fopen(dir->d_name,"r");
              while(!feof(fp)){
                 fgets()

            printf("%s\n", dir->d_name);

        }

        closedir(d);

    }

    return(0);

}
