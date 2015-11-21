/*
 ============================================================================
 Name        : simulator_disk.c
 Author      : Sujith Mohan Velliyattikuzhi
 Version     :
 Copyright   : Your copyright notice
 Description : Disk Simulator using C
 ============================================================================
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void usage();

int main(int argc,char *argv[])
{
int argl,num_cylinders,flag,fcfs=1,c_scan=0,sstf=0,look=0,sw_page=0,cylinders,i,c,l=0,l1=0,l2=0;
char *t_cylinders,*t_disk,*t_file;
FILE * fp;
char ref_string[5000];
int cnt2=0,n2,i2,i3=0;
char *ch2=NULL;
char ch3;
int num_requests[400],order[400],valid_request[400],invalid_request[400];
char invalid[300],request_string[8000];
int move=0,head;// declaration for fcfs
int head1,flag1[400],dist=0,k,j,min[400],index;//declaration for sstf
int lpos=0,rpos=0,cl[200],cr[200],temp;//declaration for look


if(argc>1)// start of reading of arguments
{
for(argl = 1; argl < argc; argl++)
{

if(!strcmp(((const char *)argv[argl]), "-h"))
{
usage();
exit(0);
}

else if(!strcmp(((const char *)argv[argl]), "-n"))
{
argl++;
if(argv[argl] != NULL)
{
t_cylinders = argv[argl];
if(!(num_cylinders = atoi(t_cylinders)))
{
printf("\nInvalid number of cylinders\n");
usage();
exit(0);
}
else
flag=1;
}
else
{
printf("\nInvalid number of cylinders\n");
usage();
exit(0);
}
}

else if(!strcmp((const char *)argv[argl], "-d"))
{
argl++;
if(argv[argl] != NULL)
{
t_disk = argv[argl];
if(!(strcmp((const char *)"FCFS",(const char *)t_disk)))
{
fcfs=1;
}
else if(!(strcmp((const char *)"SSTF",(const char *)t_disk)))
{
sstf=1;
fcfs=0;
}

else if(!(strcmp((const char *)"C-SCAN",(const char *)t_disk)))
{
c_scan=1;
fcfs=0;
}

else if(!(strcmp((const char *)"LOOK",(const char *)t_disk)))
{
look=1;
fcfs=0;
}

else
{
printf("\nInvalid disk scheduling algorithm\n");
usage();
exit(0);
}
}
else
{
printf("\nInvalid disk scheduling algorithm\n");
usage();
exit(0);
}
}

else if(!strcmp(((const char *)argv[argl]), "-i"))
{
argl++;
if(argv[argl] != NULL)
{
t_file = argv[argl];
 fp=fopen(t_file,"r");
                   

if(fp==0)
  {
    printf("\nThe file %s is not found\n-------Aborting---------\n",t_file);
exit(0);
  }
  ch3=fgetc(fp);
  while(ch3!=EOF)
  {
ref_string[i3++]=ch3;
    ch3=fgetc(fp);
  }
  ref_string[i3]='\0';
  
  ch2=strtok(ref_string," ");
  while(ch2!=NULL)
  {
   if(*ch2>='a'&&*ch2<='z'||*ch2>='A'&&*ch2<='Z')
	{
	invalid[l2]=*ch2;
	l2++;
		//continue;
	}
else
{
  n2=atoi(ch2);
  //if(n2<num_cylinders&&n2>=0)  //new code
  num_requests[cnt2]=n2;
	//printf("%d\t",pages[cnt2]);	
	cnt2++;
}
    ch2=strtok(NULL," ");
  }

	sw_page=1;

  cylinders=cnt2;
 printf("\nPage Reference Sequence: ");
 for(i2=0;i2<cylinders;i2++)
  {
    printf(" %d ",num_requests[i2]);
  }
//printf("Num pages..");
 printf("\n Number of pages= %d",cylinders);
  
  }
else
{
printf("\nInvalid file path\n");
usage();
exit(0);
}
}


}
}//End of reading of arguments

if(sw_page!=1)
{
printf("\n Enter the requests in the sequence: ");


/*scanf("%d",&cylinders);

printf("\n Enter the request sequence: ");
for(i=0;i<cylinders;i++)
scanf("%d",&num_requests[i]);
*/
gets(request_string);
  
  ch2=strtok(request_string," ");
  while(ch2!=NULL)
  {
   if(*ch2>='a'&&*ch2<='z'||*ch2>='A'&&*ch2<='Z')
	{
	invalid[l2]=*ch2;
	l2++;
		//continue;
	}
else
{
  n2=atoi(ch2);
  //if(n2<num_cylinders&&n2>=0)  //new code
  num_requests[cnt2]=n2;
	//printf("%d\t",pages[cnt2]);	
	cnt2++;
}
    ch2=strtok(NULL," ");
  }
cylinders=cnt2;
//ssssssssssssssssss
/*printf("\n The entered sequence of pages are : ");
for(i=0;i<cylinders;i++)
printf("\t%d",num_requests[i]);
printf("\n");
*/
}

if(flag!=1)
{
num_cylinders=200;
}
 
//Start of fcfs algorithm
for(i=0;i<cylinders;i++)
{
if((num_requests[i]>0)&&(num_requests[i]<num_cylinders))
{
valid_request[l]=num_requests[i];
l++;
}
else
{
invalid_request[l1]=num_requests[i];
l1++;
}
}

printf("\n Illegal I/O requests: ");
for(i=0;i<l1;i++)
printf("%d\t",invalid_request[i]);
for(i=0;i<l2;i++)
printf("%c\t",invalid[i]);

printf("\n");

if(fcfs==1)
{

head=valid_request[0];

for(i=0,c=0;i<l;i++,c++)
		{
			//printf("%d ",valid_request[i]);
			move+=abs(head-valid_request[i]);
			head=valid_request[i];
			order[c]=valid_request[i];
		}

printf("\n FCFS processing order: ");
for(i=0;i<l;i++)
printf("\t %d",order[i]);

printf("\n # of cylinders traveled: - %d\n",move);
}

//End of fcfs algorithm

//** Start of sstf algorithm
if(sstf==1)
{
head=valid_request[0];

for(i=0;i<l;i++)
flag1[i]=0;

order[0]=valid_request[0];

for(i=0,c=1;i<l;i++,c++)
		{
			//printf("%d ",valid_request[i]);
			//move+=abs(head-req[i]);
				for(k=1;k<l;k++)
				{
					if(flag1[k]!=1)
					{
					move=abs(head-valid_request[k]);
					index=k;
					break;
					}
				}
			for(j=1;j<l;j++)
			{	if(flag1[j]!=1)
				{
				min[j]=abs(head-valid_request[j]);
				}
			}
			for(j=1;j<l;j++)
			{       if(flag1[j]!=1)
				{
					if(move>min[j])
					{
					move=min[j];
					index=j;
					//flag[j]=1;
					}
				}
			}
			flag1[index]=1;
			dist+=abs(head-valid_request[index]);
			head=valid_request[index];
			order[c]=valid_request[index];
		}
printf("\n SSTF processing order: ");
for(i=0;i<l;i++)
printf("\t %d",order[i]);

printf("\n");

printf("\n # of cylinders travelled = %d \n",dist);

}

if(look==1)
{

head=valid_request[0];

                  for(i=0;i<l;i++)
		  {
		   	if(valid_request[i]<head)
		   	{
		    	cl[lpos]=valid_request[i];
		    	lpos++;
		   	}

		   	else if(valid_request[i]>=head)
		   	{
		    	cr[rpos]=valid_request[i];
		    	rpos++;
		   	}
		 }
//printf("\n The number of elements in rpos:- ");
/*for(i=0;i<rpos;i++)
printf("\t %d",cr[i]);
printf("\n cr[0]=%d\n",cr[0]);*/
//sorting

		 for(j=0;j<lpos;j++)
		 {
		  for(i=0;i<lpos-1;i++)
		  {
		   if(cl[i]<cl[i+1])
		   {
		    temp=cl[i];
		    cl[i]=cl[i+1];
		    cl[i+1]=temp;
		   }
		  }
		 }

		 for(j=0;j<rpos;j++)
		 {
		  for(i=0;i<rpos-1;i++)
		  {
		   if(cr[i]>cr[i+1])
		   {
		    temp=cr[i];
		    cr[i]=cr[i+1];
		    cr[i+1]=temp;
		   }
		  }
		 }
//printf("\n New cr[0]= %d\n",cr[0]);
/*printf("\n The elements in right position: ");
for(i=0;i<rpos;i++)
printf("\t %d",cr[i]);

printf("\n The elements in left position: ");
for(i=0;i<lpos;i++)
printf("\t %d",cl[i]);*/

//sorting end
head=cr[0];
//printf("/n head= %d",head);
//g[0]=cr[0];
for(i=0,c=0;i<rpos;i++,c++)
		{
			//printf("%d ",cr[i]);
			move+=abs(head-cr[i]);
			//printf("\t %d",move);
			head=cr[i];
			order[c]=cr[i];
		}

for(i=0,c=rpos;i<lpos;i++,c++)
		{
			//printf("%d ",cr[i]);
			move+=abs(head-cl[i]);
			//printf("\t %d",move);
			head=cl[i];
			order[c]=cl[i];
		}

printf("\n LOOK processing order: ");
for(i=0;i<l;i++)
printf("\t %d",order[i]);

printf("\n # of cylinders travelled: - %d\n",move);

}
//End of look scheduling

//Start of c_scan scheduling
if(c_scan==1)

{

head=valid_request[0];

                  for(i=0;i<l;i++)
		  {
		   	if(valid_request[i]<head)
		   	{
		    	cl[lpos]=valid_request[i];
		    	lpos++;
		   	}

		   	else if(valid_request[i]>=head)
		   	{
		    	cr[rpos]=valid_request[i];
		    	rpos++;
		   	}
		 }
//printf("\n The number of elements in rpos:- ");
/*for(i=0;i<rpos;i++)
printf("\t %d",cr[i]);
printf("\n cr[0]=%d\n",cr[0]);*/
//sorting

		 for(j=0;j<lpos;j++)
		 {
		  for(i=0;i<lpos-1;i++)
		  {
		   if(cl[i]>cl[i+1])
		   {
		    temp=cl[i];
		    cl[i]=cl[i+1];
		    cl[i+1]=temp;
		   }
		  }
		 }

		 for(j=0;j<rpos;j++)
		 {
		  for(i=0;i<rpos-1;i++)
		  {
		   if(cr[i]>cr[i+1])
		   {
		    temp=cr[i];
		    cr[i]=cr[i+1];
		    cr[i+1]=temp;
		   }
		  }
		 }
//printf("\n New cr[0]= %d\n",cr[0]);
/*printf("\n The elements in right position: ");
for(i=0;i<rpos;i++)
printf("\t %d",cr[i]);

printf("\n The elements in left position: ");
for(i=0;i<lpos;i++)
printf("\t %d",cl[i]);*/

//sorting end
head=cr[0];
//printf("/n head= %d",head);
//g[0]=cr[0];
for(i=0,c=0;i<rpos;i++,c++)
		{
			//printf("%d ",cr[i]);
			move+=abs(head-cr[i]);
			//printf("\t %d",move);
			head=cr[i];
			order[c]=cr[i];
		}
order[rpos]=num_cylinders-1;
order[rpos+1]=0;
head=order[rpos+1];

for(i=0,c=rpos+2;i<lpos;i++,c++)
		{
			//printf("%d ",cr[i]);
			move+=abs(head-cl[i]);
			//printf("\t %d",move);
			head=cl[i];
			order[c]=cl[i];
		}

printf("\n C-SCAN processing order: ");
for(i=0;i<l+2;i++)
printf("\t %d",order[i]);

printf("\n # of cylinders travelled: - %d\n",move+(num_cylinders-order[rpos-1])+num_cylinders-2);
return 0;
}

}
void usage()
{

printf("\n Usage Summary - simdisk [-h] [-n number-of-cylinders] [-d disk-shed-policy] [-i input file]\n");
printf("OPTIONS:\n");
printf("-h\t: Print a usage summary with all options and exit.\n");
printf("-n number-of-cylinders\t: Set the total number cylinders on the disk. By default it should be 200.\n");
printf("-d disk-shed-policy\t: Set the disk scheduling policy. It can be either FCFS (First-come-first-served), SSTF (Shortest-seek-time-first), C-SCAN, or LOOK. The default will be FCFS. Assume at the t=t0, the disk was moving from 0 towards other end of the disk.\n");
printf("-i input file\t: Read the request sequence from a specified file. If not given, the sequence should be read from STDIN (ended with ENTER).\n");
}
