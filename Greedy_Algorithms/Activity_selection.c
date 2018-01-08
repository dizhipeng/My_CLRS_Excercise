#include <stdio.h>

int main(void)
{
	int s[]={1,3,0,5,3,5,6,8,8,2,12};				/*Start time for activities*/
	int f[]={4,5,6,7,9,9,10,11,12,14,16};		/*Finish time for activities,!! increasingly sorted!!*/
	
	int number_of_activities = sizeof(s)/sizeof(int) ;
	if(number_of_activities!=sizeof(f)/sizeof(int) )
	{
		return -1;
	}
	
	int i;
	int mca[50]={0};		/*Maximum Compatible Activities*/
	int mca_len=0;
	int a_m=0;				/*Current activity*/
	
	/*Pick the activity a_k which has the earliest finist time f_k*/
	/*Search every activiy after a_k, to find the first element in S_k, (the first is the one who has the earliest finish time)*/
	/*S_k is the set that contains all activities whose start time is no earlier than a_k*/
	 
	a_m=0;								/*The first activity must be in the MAC*/
	mca_len=0;
	mca[mca_len++]=a_m;				
	printf("The maximum compatible activities are:\r\na_%d(%d,%d)",a_m+1,s[a_m],f[a_m]);
	
	for(i=1;i<number_of_activities;++i)	
	{
		if(s[i]>=f[a_m])				/*Find the first one a_k in S_k*/
		{
			mca[mca_len++]=i;		/*Save a_k in MCA*/
			a_m=i;							/*The activity a_k becomes current*/
			printf(",a_%d(%d,%d)",a_m+1,s[a_m],f[a_m]);
		}
	}
	printf("\r\n");	
}
