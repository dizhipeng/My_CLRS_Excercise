#include <stdio.h>

int counting_sort(int a[],int array_size);
int counting_sort_on_one_digit(int a[],int array_size,int digit);
int fetch_digit(int a,int digit);


int main(void)
{
	/*Radix sort:*/
	/*Helpful for sorting multifield data, like date: year-month-day*/
	int i=0;
#if 0
	int a[]={2,5,3,0,2,3,0,3}; 

	int array_size = sizeof(a)/sizeof(a[0]) ;
	if(array_size>=50)
	{
		return -1;
	}

	counting_sort(a,array_size);
#else

	int a[]={329,457,657,839,436,720,355}; 
	int max_digit=0;
	
	int array_size = sizeof(a)/sizeof(a[0]) ;
	if(array_size>=50)
	{
		return -1;
	}

	/*Get the needed digit*/
	max_digit=0;
	while(fetch_digit(a[0],++max_digit));
	
	/*Radix sort, from low digit to high digit*/	
	for(i=1;i<max_digit;++i)
	{
		counting_sort_on_one_digit(a,array_size,i);
	}
	
#endif
	
	/*Print the result*/
	printf("The reslut of radix sort of an array:\r\n");
	for(i=0;i<array_size;++i)
	{
		printf("%d,",a[i]);
	}
	printf("\b \r\n");

}

int fetch_digit(int a,int digit)
{
	int i=0;
	
	for(i=1;i<digit;++i)
	{
		a/=10;
	}

	return a%10;
}

int counting_sort(int a[],int array_size)
{
	int b[50]={0};		/*Store the sorted result*/
	int c[10]={0};	/*Store the position of elements in a[] after sorting, digits 0~9*/
	int i=0;

	int digits = sizeof(c)/sizeof(c[0]) ;

	
	/*Counter the occurance of every element in a[]*/
	for(i=0;i<array_size;++i)
	{
		if(a[i]>9)	/*Number of digits are exceeded*/
			return -1;

		++c[a[i]];		/*c[a[i]] stores the occurance of a[i]*/
	}

	/*Accumulate the position from small digits to big digits*/
	/*so that c[a[i]] is the right position for a[i]*/
	for(i=1;i<digits;++i)
	{
		c[i]=c[i]+c[i-1];
	}

	/*Counting sort*/
	/*To guarantee stable, the sort starts from the last element of a[]*/
	for(i=array_size-1;i>=0;--i)
	{
		b[c[a[i]]-1]=a[i];
		--c[a[i]];			/*one position before*/
	}

	/*Coyp b[] back to a[]*/
	for(i=0;i<array_size;++i)
	{
		a[i]=b[i];
	}

	return 0;
}

int counting_sort_on_one_digit(int a[],int array_size,int digit)
{
	int b[50]={0};		/*Store the sorted result*/
	int c[10]={0};	/*Store the position of elements in a[] after sorting, digits 0~9*/
	int i=0;
	int a_digit=0;

	/*Counter the occurance of one digit of every element in a[]*/
	for(i=0;i<array_size;++i)
	{
		a_digit=fetch_digit(a[i],digit);	/*Fetch a digit from a[i]*/
		if(a_digit>9||a_digit<0)
			return -1;
		
		++c[a_digit];		/*Stores the occurance of this digit*/
	}

	/*Accumulate the position from small digits to big digits*/
	/*so that c[a[i]] is the right position for a[i]*/
	for(i=1;i<10;++i)
	{
		c[i]=c[i]+c[i-1];
	}

	/*Counting sort base on one digit of a[i]*/
	/*To guarantee stable, the sort starts from the last element of a[]*/
	for(i=array_size-1;i>=0;--i)
	{
		
		a_digit=fetch_digit(a[i],digit);	/*Fetch a digit from a[i]*/

		/*c[a_digit] is the right position for a[i] based on the digit*/
		b[c[a_digit]-1]=a[i];
		--c[a_digit];			/*one position before*/
	}

	/*Coyp b[] back to a[]*/
	for(i=0;i<array_size;++i)
	{
		a[i]=b[i];
	}

	return 0;
}

