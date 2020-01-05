#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

/****************************************************************************
 *
 *
 * Compile with:
 *   nvcc -o pw pw.cu
 * 
 * 
 *****************************************************************************/
__device__ int is_a_match(char *attempt){
char password1[] ="AV1234";
char password2[] ="IP4567";
char password3[] ="SH7891";
char password4[] ="AA0142";

char *a = attempt;
char *b = attempt;
char *c = attempt;
char *d = attempt;
char *p1 = password1;
char *p2 = password2;
char *p3 = password3;
char *p4 = password4;

 while(*a ==*p1){
 	if(*a == '\0')
	{
		printf("password:%s\n", password1);
		break;
	}
	a++;
	p1++;
}
while(*b ==*p2){
 	if(*b == '\0')
	{
		printf("password:%s\n", password2);
		break;
	}
	b++;
	p2++;
}
while(*c ==*p3){
 	if(*c == '\0')
	{
		printf("password:%s\n", password3);
		break;
	}
	c++;
	p3++;
}
while(*d ==*p4){
 	if(*d == '\0')
	{
		printf("password: %s\n", password4);
		return 1;
	}
	d++;
	p4++;
}
return 0;
}

__global__ void kernel(){
char i1, i2, i3, i4;

char password[7];
password[6] ='\0';

int i = blockIdx.x +65;
int j = threadIdx.x+65;
char firstMatch =i;
char secondMatch =j;

password[0] =firstMatch;
password[1] =secondMatch;
	for(i1='0'; i1<='9'; i1++){
		for(i2='0'; i2<='9'; i2++){
			for(i3='0'; i3<='9'; i3++){
				for(i4='0'; i4<='9'; i4++){
					password[2] =i1;
					password[3] =i2;
					password[4] =i3;
					password[5] =i4;
	if(is_a_match(password)){
	}
	else{
	//printf("tried: %s\n",password);
	}
     }
    }
  }
}
}

int time_difference(struct timespec *start, struct timespec *finish,long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

	
int main() {

 struct timespec start, finish;   
 long long int time_elapsed;

 clock_gettime(CLOCK_MONOTONIC, &start);

  kernel<<<26,26>>>();
  cudaThreadSynchronize();
  

 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 
return 0;
}
