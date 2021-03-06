
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t ss;
int main()
{
pthread_mutex_init(&ss, NULL);
int b_t[15],temp,j,a_t[15],w_t[15],t_t[15],t_a=0,sum=0;
float w_avg=0,t_avg=0,t_sum=0,w_sum=0;
int i,n,x[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,b_time=0;
printf(" *****Non-Preemptive Scheduling Approach*****\n");
printf("\nEnter the No. of processes in Queue :");
scanf("%d",&n);

for(i=0;i<n;i++)
{
        
    printf("\nFor P%d\n",i+1);
	pthread_mutex_lock(&ss);
	label:
        printf("Enter Arrival time:");
        scanf("%d",&a_t[i]);
	if (a_t[i]==0 || a_t[i]<0)
	{
		printf("\n Invalid arrival time as it shouldn't be zero or negative. plz re-enter the arrival time \n");
		goto label;
	}	
        b_t[i]=a_t[i]*2;
        printf("Burst Time:%d\n",b_t[i]);
        printf("******************************");
	pthread_mutex_unlock(&ss);
}

for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		if(a_t[i]<a_t[j])
		{
			temp=x[j];
			x[j]=x[i];
			x[i]=temp;
			temp=a_t[j];
			a_t[j]=a_t[i];
			a_t[i]=temp;
			temp=b_t[j];
			b_t[j]=b_t[i];
			b_t[i]=temp;
		}
	}
}



for(j=0;j<n;j++)
{
	b_time=b_time+b_t[j];
	min=b_t[k];
		for(i=k;i<n;i++)
			{
			if (b_time>=a_t[i] && b_t[i]>min)
				{
					temp=x[k];
					x[k]=x[i];
					x[i]=temp;
					temp=a_t[k];
					a_t[k]=a_t[i];
					a_t[i]=temp;
					temp=b_t[k];
					b_t[k]=b_t[i];
					b_t[i]=temp;
				}
			}
	k++;
}

w_t[0]=0;
for(i=1;i<n;i++)
{
		w_t[i]=0;
		for(int j=0;j<i;j++)
			w_t[i]+=b_t[j];
		w_sum+=w_t[i];
}

w_avg=(w_sum/n);
	for(i=0;i<n;i++)
	{
	t_a=t_a+b_t[i];
	t_t[i]=t_a-a_t[i];
	t_sum=t_sum+t_t[i];
	}

t_avg=(t_sum/n);

printf("\n TABLE:-");
printf("\nProcess Id\t  Burst time\t  Arrival time\t   Waiting\tTurn-around time" );
for(i=0;i<n;i++)
{
	printf("\n p%d\t\t   %d\t\t   %d\t\t    %d\t\t %d",x[i],b_t[i],a_t[i],w_t[i],t_t[i]);
}

printf("\n\nAVERAGE WAITING TIME : %f",w_avg);
printf("\nAVERAGE TURN AROUND TIME : %f\n",t_avg);
return 0;
}
