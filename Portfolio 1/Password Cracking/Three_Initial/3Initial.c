#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    cc -o 3Initial 3Initial.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./3Initial > 3Initial.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$FmTfpwFMTz.o88JW5ZCHeLgUNR7yHGWCWlMSJBmoUpg/3WlM5yttrKXQ05itpPN1vw4tgb5O0X6z86tBIJGtx/",
  "$6$KB$3B3xJgo5ev2qsG9hxZluBqPtfehOuPeZ/l7uSKXT1NsZaOrm6xqGSBLrsW.RM4pYfCexZxdL7TVW86AUEaTD..",
  "$6$KB$7Iw.3Zea0XI0MpTAa3gRGm9WZylw5xuvnDE1.mKmcGqvzTzmZPg5ER1gCR.bs1DlxE.ii6yeMOofcBdSrBbNG1",
  "$6$KB$BuweWaLXbo9M4NgY2pLGa/5mBmVVENRdpUYyXSuGKvP855q74tnlusF0UT.9Fcte/E7/WvR85msWM7dvlhu3F1"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void Pcrack(char *salt_and_encrypted){
  int a, b, c, d;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
	for(c='A'; c<='Z'; c++){
      	for(d=0; d<=99; d++){
		sprintf(plain, "%c%c%c%02d", a, b, c,d); 
		enc = (char *) crypt(plain, salt);
		count++;
		if(strcmp(salt_and_encrypted, enc) == 0){
		  printf("#%-8d%s %s\n", count, plain, enc);
		} /*else {
		  printf(" %-8d%s %s\n", count, plain, enc);
		}*/
      }
	}
    }
  }
  printf("%d solutions explored\n", count);
}

//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	int i;
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	for(i=0;i<n_passwords;i<i++) 
	{
    		Pcrack(encrypted_passwords[i]);
  	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
