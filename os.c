

 Slip1

1)


#include<stdio.h>


struct node

{

  int pno,freq;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_lfu_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].freq<frames[selfno].freq)

	selfno=fno;

  return selfno;

}

int main()

{

   int p_request[]={3,4,5,4,3,4,7,2,4,5,6,7,2,4,6};

   int size=12;

   int page_falts=0,i,j,fno;

   

   printf("\nHow many frames:");  scanf("%d",&n);


   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].freq=0;

   }


   printf("\nPageNo     Page Frames          	Page Fault");

   printf("\n---------------------------------------------------");

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_lfu_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].freq=1;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : YES");

	}

	else 

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].freq++;

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : NO");

	}

   }

  printf("\n-------------------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);

 

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int typeline( char *option, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"typeline") == 0 )

		typeline(args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   

            sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int typeline( char *option, char *fname) 

{

	FILE *fp;

	int tot_lines,ch,n,cnt;

	

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	tot_lines = 0;

	ch = fgetc(fp);

	while ( ch != EOF )

	{

		if( ch == 10 ) 

		tot_lines++;

		ch = fgetc(fp);

	}

	fclose(fp);

	

	if( strcmp(option,"a")== 0 ) 

	{

		fp= fopen(fname,"r");

		ch = fgetc(fp);

		while ( ch != EOF )

		{

			printf("%c",ch);

			ch = fgetc(fp);

		}

		fclose(fp);

	}

	else

	if( option[0] =='+') 

	{

		n = atoi(option+1);

		if( n > tot_lines)

		{	

			printf("\nInvalid  option");

			exit(0);

		}

		fp= fopen(fname,"r");

		cnt = 0;

		while( cnt < n )

		{

			ch = fgetc(fp);

			printf("%c",ch);

			if( ch == 10)

				cnt++;

		}

		fclose(fp);

	}

	else

	if( option[0] =='-') 

	{

		n = atoi(option+1);

		if( n > tot_lines)

		{	

			printf("\nInvalid  option");

			exit(0);

		}

		fp= fopen(fname,"r");

		cnt = 0;

		while( cnt < tot_lines -n )

		{

			ch = fgetc(fp);

			if( ch == 10)

				cnt++;

		}

		while( (ch=fgetc(fp)) != EOF )

			printf("%c",ch);

		fclose(fp);

	}

	else

	{

		printf("\nInvalid option");

		exit(0);

	}

	return(0);

} 




















































Slip2

1)


#include<stdio.h>


int frame[3]={-1,-1,-1};

int pg_found(int pno)

{

	int i;

	for(i=0;i<3;i++)

		if(frame[i]==pno)

		return i;

	return -1;

}

int main()

{

	int p_req[]={3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};

	int size=15,page_fault=0,i;

	

	printf("\n FIFO page replacement");

	printf("\n page no  -----------------page frames");

	printf("\n---------------------------------------");

	for(i=0;i<size;i++)

	{

		if(pg_found(p_req[i])==-1)

		{

			frame[page_fault%3]=p_req[i];

			page_fault++;

			printf("\n %4d--------------------%4d%4d%4d",p_req[i],frame[0],frame[1],frame[2]);

		}

		else

			printf("\n %4d.......No Page fault",p_req[i]);

	}

	printf("\n-------------------------------------------");

	printf("\n Total page fault=%d",page_fault);

	

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int list( char option, char dirname[]);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"list") == 0 )

		list(*args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int list( char option, char dirname[])

{

	DIR *dp;

	struct dirent *dent;

	struct stat buff;

	char orgdir[100];

	int cnt,reply;

	getcwd(orgdir,90);

	chdir(dirname);

	switch(option)

	{

	case 'f' : 

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				printf("\n%s",dent->d_name);

				dent= readdir(dp);

			}

			printf("\n");

			break;

	case 'n' : 

			cnt =0;

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				cnt++;

				dent= readdir(dp);

			}

			printf("\ntot dir entries = %d\n",cnt);

			closedir(dp);

			break;

	default :	printf("\nInvalid option");

			exit(0);

	} 

	chdir(orgdir);

	return(0);

}


















































Slip3

1)


#include<stdio.h>

struct node

{

  int pno,reftime;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_lru_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].reftime<frames[selfno].reftime)

	selfno=fno;

  return selfno;

}

main()

{

   int p_request[]={3,5,7,2,5,1,2,3,1,3,5,3,1,6,2};

   int size=15,currtime;

   int page_falts=0,i,j,fno;

  

   printf("\nHow many frames:");  scanf("%d",&n);

   

   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].reftime=-1;

   }


   printf("\nPageNo     Page Frames          Page Fault");

   printf("\n-------------------------------------------");

   currtime=0;

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_lru_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].reftime=currtime;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : YES");

	}

	else

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].reftime=currtime;

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : NO");

	}

	   currtime++;

   }

  printf("\n------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);


}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int count( char option, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"count") == 0 )

		count(*args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int count( char option, char *fname)

{

	int ccnt,wcnt,lcnt,wflag;

	int ch;

	FILE *fp;

	int i;

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	ccnt =wcnt = lcnt = 0;

	wflag=1;

	ch = fgetc(fp);

	while ( ch != EOF)

	{

		ccnt++;

		if( ch ==' ' || ch== '\t')

		{

			if( wflag == 0 )

			{

				wcnt++;

				wflag = 1;

			}	

		}

		else

		if( ch == '\n')

		{

			lcnt++;

			if( wflag == 0 )

			{

				wcnt++;	

				wflag = 1;

			}

		}

		else

		{

			wflag = 0;

		}

		ch = fgetc(fp);

	}

	if( wflag == 0 )

	{	

		wcnt++;

		lcnt++;

	}

	fclose(fp);

	switch(option)

	{

	case 'c' : 

			printf("\nTot chars = %d\n",ccnt);

			break;

	case 'w' : 

			printf("\nTot words = %d\n",wcnt);

			break;

	case 'l' : 

			printf("\nTot lines = %d\n",lcnt);

			break;

	} 

	return;

}















































Slip4

1)


#include<stdio.h>


struct node

{

  int pno,freq;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_mfu_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].freq>frames[selfno].freq)

	selfno=fno;

  return selfno;

}

int main()

{

   int p_request[]={8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};

   int size=12;

   int page_falts=0,i,j,fno;

   

   printf("\nHow many frames:");  scanf("%d",&n);

   

   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].freq=0;

   }


   printf("\nPageNo     Page Frames          	Page Fault");

   printf("\n---------------------------------------------------");

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_mfu_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].freq=1;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : YES");

	}

	else 

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].freq++;

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : NO");

	}

   }

  printf("\n-------------------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);

 

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int search(char option, char *pattern, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"search") == 0 )

		search(*args[1],args[2],args[3]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int search(char option, char *pattern, char *fname)

{

	char buff[100],*ptr;

	int cnt;

	FILE *fp;

	int i;

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	switch(option)

	{

	    case 'a' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

					printf("%s",buff);

			}

			fclose(fp);

			break;

	    case 'c' : 

			cnt=0;

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				while(ptr != NULL )

				{

					cnt++;

					ptr = ptr + strlen(pattern);

					ptr = strstr(ptr,pattern);

				} 

			}

			fclose(fp);

			printf("\nThe serach string %s occurs %d times",pattern,cnt);

			break;

	} 

	return;

}








































Slip6

1)



#include<stdio.h>

#include<conio.h>

struct frmnode

{

 int pno,counter;

}

frames[20];


int n;


int page_found(int pno)

{

 int fno;

 for(fno=0;fno<n;fno++)

 {if(frames[fno].pno==pno)

    return fno;

  }

 return -1;

}


int get_free_frame()

{int fno;

 for (fno=0; fno<n; fno++)

 {

  if (frames[fno].pno==-1)

   return(fno);

  }

 return(-1);

}


int get_mru_Frame()

{

 int lrufno=0,fno;

 for (fno=1; fno<n; fno++)

 {

  if(frames[fno].counter>frames[lrufno].counter)

   lrufno=fno;

 }

 return lrufno;

}

void main()

{

 int p_request[]={8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};

 int size=sizeof(p_request)/2,currtime;

 int page_falts=0,i,j,fno;

 clrscr();

 printf("\nHow many frames:");  scanf("%d",&n);

 

 for (i=0; i<n; i++)

 { frames[i].pno=-1;

 }


 printf("\nPageNo     Page Frames     Page Fault");

 printf("\n---------------------------------------------------");

 currtime=0;

 for(i=0;i<size;i++)

 {

  j=page_found(p_request[i]);

  if(j==-1)  

  {

   j=get_free_frame();

   if (j==-1) 

    j=get_mru_Frame();

   page_falts++;

   frames[j].pno=p_request[i];

   frames[j].counter=currtime;

   printf("\n%4d\t ",p_request[i]);

   for (fno=0; fno<n; fno++)

    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);

   printf(" : YES");

  }

  else

  {frames[j].counter=currtime;

   printf("\n%4d\t ",p_request[i]);

   for (fno=0; fno<n; fno++)

    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);

   printf(" : NO");


  }

  currtime++;

 }

 printf("\n------------------------------------------");

 printf("\n Number of Page_Falts=%d",page_falts);


}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int search(char option, char *pattern, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"search") == 0 )

		search(*args[1],args[2],args[3]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}



int search(char option, char *pattern, char *fname)

{

	char buff[100],*ptr;

	int cnt;

	FILE *fp;

	int i;

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	switch(option)

	{

	    case 'f' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

				{

					printf("%s",buff);

					break;

				}

			}

			fclose(fp);

			break;

        case 'a' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

					printf("%s",buff);

			}

			fclose(fp);

			break;


	} 

	return;

}















































Slip8

1)


#include<stdio.h>

struct node

{

  int pno,reftime;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_lru_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].reftime<frames[selfno].reftime)

	selfno=fno;

  return selfno;

}

main()

{

   int p_request[]={8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};

   int size=15,currtime;

   int page_falts=0,i,j,fno;

  

   printf("\nHow many frames:");  scanf("%d",&n);

   

   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].reftime=-1;

   }


   printf("\nPageNo     Page Frames          Page Fault");

   printf("\n-------------------------------------------");

   currtime=0;

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_lru_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].reftime=currtime;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : YES");

	}

	else

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].reftime=currtime;

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : NO");

	}

	   currtime++;

   }

  printf("\n------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);


}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int search(char option, char *pattern, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"search") == 0 )

		search(*args[1],args[2],args[3]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int search(char option, char *pattern, char *fname)

{

	char buff[100],*ptr;

	int cnt;

	FILE *fp;

	int i;

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	switch(option)

	{

	    case 'f' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

				{

					printf("%s",buff);

					break;

				}

			}

			fclose(fp);

			break;


        case 'c' : 

			cnt=0;

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				while(ptr != NULL )

				{

					cnt++;

					ptr = ptr + strlen(pattern);

					ptr = strstr(ptr,pattern);

				} 

			}

			fclose(fp);

			printf("\nThe serach string %s occurs %d times",pattern,cnt);

			break;

	} 

	return;

}

















































































Slip9

1)


#include<stdio.h>


int frame[3]={-1,-1,-1};

int pg_found(int pno)

{

	int i;

	for(i=0;i<3;i++)

		if(frame[i]==pno)

		return i;

	return -1;

}

int main()

{

	int p_req[]={8,5,7,8,5,7,2,3,7,3,5,9,4,6,2};

	int size=15,page_fault=0,i;

	

	printf("\n FIFO page replacement");

	printf("\n page no  -----------------page frames");

	printf("\n---------------------------------------");

	for(i=0;i<size;i++)

	{

		if(pg_found(p_req[i])==-1)

		{

			frame[page_fault%3]=p_req[i];

			page_fault++;

			printf("\n %4d--------------------%4d%4d%4d",p_req[i],frame[0],frame[1],frame[2]);

		}

		else

			printf("\n %4d.......No Page fault",p_req[i]);

	}

	printf("\n-------------------------------------------");

	printf("\n Total page fault=%d",page_fault);

	

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int search(char option, char *pattern, char *fname);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"search") == 0 )

		search(*args[1],args[2],args[3]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int search(char option, char *pattern, char *fname)

{

	char buff[100],*ptr;

	int cnt;

	FILE *fp;

	int i;

	fp= fopen(fname,"r");

	if( fp == NULL )

	{

		printf("\nUnable to open file");

		exit(0);

	}

	switch(option)

	{

	    case 'f' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

				{

					printf("%s",buff);

					break;

				}

			}

			fclose(fp);

			break;


        case 'a' : 

			while ( !feof (fp))

			{

				buff[0] = '\0';

				fgets(buff,80,fp);

				ptr = strstr(buff,pattern);

				if( ptr != NULL )

					printf("%s",buff);

			}

			fclose(fp);

			break;

	} 

	return;

}








































































Slip10

1)


#include<stdio.h>


int frame[3]={-1,-1,-1};

int pg_found(int pno)

{

	int i;

	for(i=0;i<3;i++)

		if(frame[i]==pno)

		return i;

	return -1;

}

int main()

{

	int p_req[]={2,4,5,6,9,4,7,3,4,5,6,7,2,4,7,1};

	int size=15,page_fault=0,i;

	

	printf("\n FIFO page replacement");

	printf("\n page no  -----------------page frames");

	printf("\n---------------------------------------");

	for(i=0;i<size;i++)

	{

		if(pg_found(p_req[i])==-1)

		{

			frame[page_fault%3]=p_req[i];

			page_fault++;

			printf("\n %4d--------------------%4d%4d%4d",p_req[i],frame[0],frame[1],frame[2]);

		}

		else

			printf("\n %4d.......No Page fault",p_req[i]);

	}

	printf("\n-------------------------------------------");

	printf("\n Total page fault=%d",page_fault);

	

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int list( char option, char dirname[]);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"list") == 0 )

		list(*args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int list( char option, char dirname[])

{

	DIR *dp;

	struct dirent *dent;

	struct stat buff;

	char orgdir[100];

	int cnt,reply;

	getcwd(orgdir,90);

	chdir(dirname);

	switch(option)

	{

	    case 'f' : 

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				printf("\n%s",dent->d_name);

				dent= readdir(dp);

			}

			printf("\n");

			break;


	    case 'i' : 

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				reply = stat(dent->d_name,&buff);

				if( reply < 0 )

				printf("\nError");

				else

				printf("\n%s %ld",dent->d_name,buff.st_ino);

				dent= readdir(dp);

			}

			closedir(dp);

			break;

	    default :	printf("\nInvalid option");

			exit(0);

	} 

	chdir(orgdir);

	return(0);

}

















































Slip11

1)


#include<stdio.h>


struct node

{

  int pno,freq;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_lfu_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].freq<frames[selfno].freq)

	selfno=fno;

  return selfno;

}

int main()

{

   int p_request[]={3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};

   int size=12;

   int page_falts=0,i,j,fno;

   

   printf("\nHow many frames:");  scanf("%d",&n);

   

   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].freq=0;

   }


   printf("\nPageNo     Page Frames          	Page Fault");

   printf("\n---------------------------------------------------");

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_lfu_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].freq=1;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : YES");

	}

	else 

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].freq++;

	   for (fno=0; fno<n; fno++)

		printf("%4d:%2d",frames[fno].pno,frames[fno].freq);

	   printf(" : NO");

	}

   }

  printf("\n-------------------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);

 

}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int list( char option, char dirname[]);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"list") == 0 )

		list(*args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int list( char option, char dirname[])

{

	DIR *dp;

	struct dirent *dent;

	struct stat buff;

	char orgdir[100];

	int cnt,reply;

	getcwd(orgdir,90);

	chdir(dirname);

	switch(option)

	{

	    case 'f' : 

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				printf("\n%s",dent->d_name);

				dent= readdir(dp);

			}

			printf("\n");

			break;

	    case 'n' : 

			cnt =0;

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				cnt++;

				dent= readdir(dp);

			}

			printf("\ntot dir entries = %d\n",cnt);

			closedir(dp);

			break;

	    default :	printf("\nInvalid option");

			exit(0);

	} 

	chdir(orgdir);

	return(0);

}





































































Slip12

1)


#include<stdio.h>

struct node

{

  int pno,reftime;

}frames[20];

int n;


int page_found(int pno)

{

  int fno;

  for(fno=0;fno<n;fno++)

	if(frames[fno].pno==pno)

	   return fno;

	return -1;

}


int get_free_frame()

{  int fno;

  for (fno=0; fno<=n; fno++)

	if (frames[fno].pno==-1)

		return(fno);

   return(-1);

}


int get_lru_frame()

{

  int fno;

  int selfno=0;

  for (fno=1; fno<n; fno++)

	if(frames[fno].reftime<frames[selfno].reftime)

	selfno=fno;

  return selfno;

}

main()

{

   int p_request[]={3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};

   int size=15,currtime;

   int page_falts=0,i,j,fno;

  

   printf("\nHow many frames:");  scanf("%d",&n);

   

   for (i=0; i<n; i++)

   { frames[i].pno=-1;

	frames[i].reftime=-1;

   }


   printf("\nPageNo     Page Frames          Page Fault");

   printf("\n-------------------------------------------");

   currtime=0;

   for(i=0;i<size;i++)

   {

	j=page_found(p_request[i]);

	if(j==-1)  

	{

	   j=get_free_frame();

	   if (j==-1) 

		j=get_lru_frame();

	   page_falts++;

	   frames[j].pno=p_request[i];

	   frames[j].reftime=currtime;

	   printf("\n%4d\t ",p_request[i]);

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : YES");

	}

	else

	{

	   printf("\n%4d\t ",p_request[i]);

	   frames[j].reftime=currtime;

	   for (fno=0; fno<n; fno++)

		printf("%4d",frames[fno].pno);

	   printf(" : NO");

	}

	   currtime++;

   }

  printf("\n------------------------------------------");

  printf("\n Number of Page_Falts=%d",page_falts);


}


2)

#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <dirent.h>


char comm[100],*ptr;

char *args[10];

int tot_arg;


int list( char option, char dirname[]);


main()

{

	do

	{

		printf("myshell $ ");

		getcomm();

		sep_arg();

		take_action();

	}while(1);

} 


sep_arg()

{

	int i,j;

	i = j = tot_arg = 0;


	args[tot_arg] = (char*)malloc(sizeof(char) * 20);

	for(i=0; comm[i] !='\0' ; i++)

	{

		if( comm[i] == ' ')

		{

			args[tot_arg][j] = '\0';

			tot_arg++;

			args[tot_arg] = (char*)malloc(sizeof(char) * 20);	

			j=0;

		}

		else

		{

			args[tot_arg][j] =comm[i];

			j++;

		}

	} 

	args[tot_arg][j] = '\0'; 

 	return;

}


getcomm()

{

	int len;

	ptr = fgets(comm,80,stdin);

	len = strlen(comm);

	comm[len-1] = '\0';

	return;

} 


take_action()

{

	char str[100];

	pid_t   pid;

	int status;


	if(strcmp(args[0],"list") == 0 )

		list(*args[1],args[2]);

	else

	{	

		if( ptr == NULL )

			exit(0);

		if ( strlen(comm) <= 1 )

			return;

		if( ( pid = fork() ) < 0 )

		{

			printf("\nUnable to create process");

		}

		else

		if(  pid == 0 ) 

		{   sscanf(comm,"%s",comm);

			execvp(comm,args);

			strcpy(str,"./");

			strcat(str,args[0]);

			execvp(str,args);

			printf("\n%s : command not found",comm);

			exit(0);

		}

		else 

		waitpid(pid,&status,0);

	} 

}


int list( char option, char dirname[])

{

	DIR *dp;

	struct dirent *dent;

	struct stat buff;

	char orgdir[100];

	int cnt,reply;

	getcwd(orgdir,90);

	chdir(dirname);

	switch(option)

	{

	    case 'f' : 

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				printf("\n%s",dent->d_name);

				dent= readdir(dp);

			}

			printf("\n");

			break;

	    case 'n' : 

			cnt =0;

			dp= opendir(".");

			if( dp == NULL )

			{

				printf("\nUnable to open dir");

				exit(0);

			}

			dent = readdir(dp);

			while( dent != NULL )

			{

				cnt++;

				dent= readdir(dp);

			}

			printf("\ntot dir entries = %d\n",cnt);

			closedir(dp);

			break;

	    default :	printf("\nInvalid option");

			exit(0);

	} 

	chdir(orgdir);

	return(0);

}







































Slip22

1)

#include<stdio.h>

#include<unistd.h>

#include<stdlib.h>


void main()

{

    int pid,retnice;

    printf("press DEL to stop process\n");

    pid=fork();

    while(1)

    {

        if(pid==0)

        {

            retnice=nice(-5);

            printf("child gets higher CPU priority %d\n",retnice);

            sleep(1);

        }

        else

        {

            retnice=nice(4);

            printf("Parent gets lower CPU priority %d\n",retnice);

            sleep(1);      

        }

    }

}


2)



#include <stdio.h>


#include <stdlib.h>


struct proc_info

{

  int atime;

  int cpub;

  int prio;

} proc[20];


struct rqnode

 { int pid,prio;

   struct rqnode *link;

 } *first=NULL, *curr, *prev, *last;


struct ganttchart

{

  int stime;

  int pid;

  int etime;

} gchart[20];


int i,n,ctime,gi=0,wtime[20],ttime[20];


void getprocs();

void start();

void addprocq();

void attachtoq(int );

void addgchart(int);

void dispgchart();

void disptimes();


void main()

{ 

  

  getprocs();

  ctime=0; 

  start();

  dispgchart();

  disptimes();

}


void getprocs()

{ printf("\nHow many processes: "); scanf("%d",&n);

  printf("\nPID\tATIME\tCPUB\tPriority\n");

  for (i=1; i<=n; i++)

  { printf("%d\t",i);

    scanf("%d%d%d",&proc[i].atime,&proc[i].cpub,&proc[i].prio);

   }

}


void start()

{ int pid;

  addprocq(); 

  pid=getfirstproc();

  while(!finished()) 

  {

    if(pid!=-1)

    { 

      ctime++;  

      proc[pid].cpub--;

      if(proc[pid].cpub==0)

      {

	printf("\nProc %d completed at time %d..",pid,ctime);

	ttime[pid]=ctime-proc[pid].atime;

	pid=getfirstproc();

      }

    }

   else

    ctime++;


   addprocq(); 

  }

  gchart[gi].etime=ctime;

}


void addprocq()

{

  for(i=1;i<=n;i++)

  { if(proc[i].atime==ctime)

      attachtoq(i);

   }

}


void attachtoq(int pid)

{

  struct rqnode *selp,*pselp;

  curr=(struct rqnode *)malloc(sizeof(struct rqnode));

  curr->pid=pid;curr->prio=proc[pid].prio; curr->link=NULL;

  if(first==NULL)

  { first=curr;

    return;

  }

  selp=first;

  while(selp->prio<=curr->prio && selp!=NULL)

  { pselp=selp;

    selp=selp->link;

  }

  if(selp==first)

  { curr->link=first;

    first=curr;

  }

  else

  {pselp->link=curr;

   curr->link=selp;

   }

}


int finished() 

{

  for(i=1;i<=n;i++)

  { if(proc[i].cpub!=0)

     return(0);

  }

  return(1);

}


int getfirstproc()

{

  int pid;

  if(first==NULL)

    return(-1);

  pid=first->pid;

  curr=first; 

  first=first->link;

  free(curr);

  addgchart(pid);

  wtime[pid]=ctime-proc[pid].atime;

  return(pid);


}



void addgchart(int pid)

{

   gchart[++gi].pid=pid;

   gchart[gi].stime=ctime;

   gchart[gi-1].etime=gchart[gi].stime;

}


void dispgchart()

{ printf("\n");


  for(i=1;i<=gi;i++)

    printf("|----");

  printf("|\n");


  for(i=1;i<=gi;i++)

    printf("| %d  ",gchart[i].pid);

  printf("|\n");


  for(i=1;i<=gi;i++)

    printf("|----");

  printf("|\n");


  for(i=1;i<=gi;i++)

   printf("%d    ",gchart[i].stime);


  printf("%d\n",gchart[gi].etime);

 


}


void disptimes()

{ int sumwt=0,sumtt=0,pid;


  printf("\n**Waiting Time**");

  printf("\nPID\tWtime");

  for(i=1;i<=n;i++)

  {

    printf("\n%d\t%d",i,wtime[i]);

    sumwt+=wtime[i];

  }

  printf("\nAverage:%.2f",(float)sumwt/n);


  printf("\n**Turnaround Time**");

  printf("\nPID\t ttime");

  for(i=1;i<=n;i++)

  {

    printf("\n%d\t%d",i,ttime[i]);

    sumtt+=ttime[i];

  }

  printf("\nAverage:%.2f",(float)sumtt/n);


  getch();

}


Slip23

1)

#include<stdio.h>

#include<unistd.h>

#include<stdlib.h>


void main()

{

    int pid;

    pid=fork();

    if(pid>0)

    {

        printf("I am parent process and my id is:",getppid());

    }

    else if(pid==0)

    {

        printf("I am child process and my id is:",getpid());

        printf("My parent id before termination is:",getppid());

        sleep(5);

        printf("My parent id after termination is:",getppid());

    }

    else

    {

        printf("The process is unsuccessful!");

    }

}

2)

Comments
Powered by Blogger
Theme images by Radius Images

Legend

Visit profile
Archive
Report Abuse
