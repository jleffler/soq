#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const int BUFFER_SIZE = 256;
char **numberChar;
int *numbers;
int start, end, count, i;
int numbs = 0;
int sizeNumbers = 10;
int numSizes[10];
char *fileNames[8];

#define READ 0
#define WRITE 1
#define MAX 1024 
#define NUMOFFILES 8

//Prototypes
void readFile(char*);
void printNumbers(void);
void freeMem(void);
void convertToInt(void);
int intcmp(const void *n1, const void *n2);
void doLeafStuff(char*);
void createLeafs(int, int);
void breed(int);

int main(void)
{
  fileNames[0] = "1";
  fileNames[1] = "2";
  fileNames[2] = "3";
  fileNames[3] = "4";
  fileNames[4] = "5";
  fileNames[5] = "6";
  fileNames[6] = "7";
  fileNames[7] = "8";
//   int upPipe[2];
//   int leftPipe[2];
//   int rightPipe[2];
//   pid_t leftPID;
//   pid_t rightPID;
//   
//   if (pipe (upPipe) < 0 || pipe(leftPipe) < 0 || pipe(rightPipe) < 0) {
//     perror ("plumbing problem");
//     exit(1);
//   }//else 
//   
//   if ((leftPID = fork()) < 0) {
//     perror ("left fork failed");
//     exit(1);
//   }
//   
//   if(leftPID == 0){
//     dup2(leftPipe[WRITE], upPipe[WRITE]);
//     pipe(leftPipe);
//     pipe(rightPipe);
//       //pipes not needed
//       close(rightPipe[READ]);
//       close(rightPipe[WRITE]);
//       close(leftPipe[READ]);
//       close(leftPipe[WRITE]);
//       
//       numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
//       readFile(fileNames[1]);
//       convertToInt();
//       for(i = 0; i < numbs; i++)
// 	write(upPipe[WRITE], &numbers[i], sizeof(int));
//       freeMem();
//       close(upPipe[READ]);
//       close(upPipe[WRITE]);
//       exit(0);
//   }
//     
//   if((rightPID = fork()) < 0){
//     perror("right fork failed");
//   }
//     
//   if(rightPID == 0){
//     dup2(rightPipe[WRITE], upPipe[WRITE]);
//     pipe(leftPipe);
//     pipe(rightPipe);
//     //Check if leaf
//       //pipes not needed
//       close(rightPipe[READ]);
//       close(rightPipe[WRITE]);
//       close(leftPipe[READ]);
//       close(leftPipe[WRITE]);
//       
//       numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
//       readFile(fileNames[2]);
//       convertToInt();
//       for(i = 0; i < numbs; i++)
// 	write(upPipe[WRITE], &numbers[i], sizeof(int));
//       freeMem();
//       
//       close(upPipe[READ]);
//       close(upPipe[WRITE]);
//       exit(0);
//     
//   }
//   wait(&leftPID);
//   wait(&rightPID);
//   
//   close(upPipe[READ]);
//   close(upPipe[WRITE]);
//   
//   //close(leftPipe[WRITE]);
//   
//   
//   
//   
//   
//   
//   int passUp = 1;
//   int leftContents = 999999999;
//   int rightContents = 999999999;
//   int leftEmpty = 0;
//   int rightEmpty = 0;
//   int intbuffer;
//   int nbytes;
//   close(rightPipe[WRITE]);
//   close(leftPipe[WRITE]);
//   while(passUp){
//     if(leftContents == 999999999){
//       nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
//       if(nbytes > 0){
// 	leftContents = intbuffer;
// 	//printf("Set left: %d\n", leftContents);
//       }else{
// 	leftEmpty = 1;
// 	//perror("left empty");
//       }
//     }
//     
//     if(rightContents == 999999999){
//       nbytes = read(rightPipe[READ], &intbuffer, sizeof(intbuffer));
//       if(nbytes > 0){
// 	rightContents = intbuffer;
// 	//printf("Set right: %d\n", rightContents);
//       }
//       else{ 
// 	rightEmpty = 1;
// 	//perror("right empty");
//       }
//     }
//     
//     if(leftContents < rightContents){
//       //perror("***left < right***");
//       printf("Master Printout: %d\n", leftContents);
//       leftContents = 999999999;
//     }
//     else if(rightContents < leftContents){
//        //perror("***left < right***");
// 	  printf("Master Printout: %d\n", rightContents);
//       rightContents = 999999999;
//     }
//     else if((leftContents == rightContents) && (leftEmpty != 1 && rightEmpty != 1)){
// 	  printf("Master Printout: %d\n", rightContents);
// 	  printf("Master Printout: %d\n", leftContents);
//       leftContents = 999999999;
//       rightContents = 999999999;
//     }
//     else if(leftEmpty == 1 && rightEmpty == 1){
//       passUp = 0;
//       perror("exit loop");
//     }
//     
//   }
//   
//   close(rightPipe[READ]);
//   close(leftPipe[READ]);
  
  
  
  
  
  
  
  
  
  
  
  
  
  //int nbytes = 1;
  //int intbuffer;
  //while(nbytes > 0){
  //  nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
  //  printf("**********left Pipe: %d\n", intbuffer);
  //}
 // close(leftPipe[READ]);
  
 // close(rightPipe[WRITE]);
 // int nbytes2 = 1;
 // int intbuffer2;
 // while(nbytes2 > 0){
 //   nbytes2 = read(rightPipe[READ], &intbuffer2, sizeof(intbuffer));
 //   printf("**********Right Pipe: %d\n", intbuffer2);
 // }
 // close(rightPipe[READ]);
  
  
  
  //createLeafs(1, NUMOFFILES);
  breed(4);
  return 0;
  
}

/*THIS IS STUFF FOR THE CHILD*/

void readFile(char* fileName)
{
  char buffer[BUFFER_SIZE];
  FILE *fp;
  fp = fopen(fileName, "r");
  
  if(fp == NULL){
    perror("Error reading file");
    exit(1);
  }
  
  // While there are more lines in file
  while(fgets(buffer, sizeof(buffer), fp) != NULL){
    start = 0;
    end = 0;
    // While there are more words in line
    while(end < BUFFER_SIZE && buffer[end] != '\0'){
      if(buffer[end] == '/' &&  buffer[end+1] == '*')
	buffer[end] = '\0';
	// While there are more chars in word
      else{
	while(end < BUFFER_SIZE)
	  end++;
	  // If a word was detected
	  if(end > start){
	    // If there is no more room in 'words'
	    if(numbs == sizeNumbers){
	      sizeNumbers += 10;
	      numberChar = (char **) realloc(numberChar, sizeNumbers*sizeof(char *));
	    }

	  numberChar[numbs] = (char *) calloc(end-start+1, sizeof(char));

	  for(i = 0; i < end-start; i++)
	    numberChar[numbs][i] = buffer[start + i];
	    numberChar[numbs][i] = '\0';
	    numbs++;
	  }
	  start = ++end;
	}
    }
  }
  // Remove extra space
  if(numbs < sizeNumbers)
    numberChar = (char **) realloc(numberChar, numbs*sizeof(char *));
}

void printNumbers(void)
{
  //printf("numbs: %d\n", numbs);
  for(i = 0; i < numbs; i++){
    printf("numberChar[%d]: %s\n", i, numberChar[i]);
  }
}

void convertToInt(void){
  numbers = (int *) malloc(numbs * sizeof (int));
  for(i = 0; i < numbs; i++){
    numbers[i] = atoi(numberChar[i]);
    //printf("numbers[%d] = %d\n", i, numbers[i]);	
  }
  
  qsort(numbers, numbs, sizeof(int), intcmp);
  
  //for(i = 0; i < numbs; i++){
  //  printf("numbers[%d] = %d\n", i, numbers[i]);	
  //}
  
  
}

int intcmp(const void *n1, const void *n2)
{
  const int *num1 = (const int *) n1;
  const int *num2 = (const int *) n2;
  return (*num1 < *num2) ? -1 : (*num1 > *num2);
}

//free memory
void freeMem(void)
{
  for(i = 0; i < numbs; i++)
    free(numberChar[i]);
  free(numberChar);
  free(numbers);
}

void createLeafs(int min, int max){
  int upPipe[2];
  int leftPipe[2];
  int rightPipe[2];
  pid_t leftPID;
  pid_t rightPID;
  int fMin = min;
  int fMax = max;
  int fileNumber = 0;
  
  //Create pipe
  if (pipe (upPipe) < 0 || pipe(leftPipe) < 0 || pipe(rightPipe) < 0) {
    perror ("plumbing problem");
    exit(1);
  }//else 
  
  if ((leftPID = fork()) < 0) {
    perror ("left fork failed");
    exit(1);
  }
  
  if(leftPID == 0){
    fMax = ((fMax)/2);
    dup2(leftPipe[WRITE], upPipe[WRITE]);
    pipe(leftPipe);
    pipe(rightPipe);
    //Check if leaf
    if(fMax == 1){
      perror("Created left leaf");
      //pipes not needed
      close(rightPipe[READ]);
      close(rightPipe[WRITE]);
      close(leftPipe[READ]);
      close(leftPipe[WRITE]);
      
      numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
      readFile(fileNames[fileNumber]);
      convertToInt();
      for(i = 0; i < numbs; i++)
	write(upPipe[WRITE], &numbers[i], sizeof(int));
      freeMem();
      close(upPipe[READ]);
      close(upPipe[WRITE]);
      exit(0);
    }
    else{
      createLeafs(fMin, fMax);
    }
  }
    
  if((rightPID = fork()) < 0){
    perror("right fork failed");
  }
    
  if(rightPID == 0){
    fMax = ((fMax)/2);
    dup2(rightPipe[WRITE], upPipe[WRITE]);
    pipe(leftPipe);
    pipe(rightPipe);
    //Check if leaf
    if(fMax == 1){
      perror("Created right leaf");
      //pipes not needed
      close(rightPipe[READ]);
      close(rightPipe[WRITE]);
      close(leftPipe[READ]);
      close(leftPipe[WRITE]);
      
      numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
      readFile(fileNames[fileNumber]);
      fileNumber++;
      convertToInt();
      for(i = 0; i < numbs; i++)
	write(upPipe[WRITE], &numbers[i], sizeof(int));
      freeMem();
      
      close(upPipe[READ]);
      close(upPipe[WRITE]);
      exit(0);
    }
    else{
      createLeafs(fMin, fMax);
    }
  }
  wait(&leftPID);
  wait(&rightPID);
  
  int master = 0;
  if(fMax == 8){
    perror("Master was set********************");
    master = 1;
    close(upPipe[READ]);
    //dup2(upPipe[WRITE], STDOUT_FILENO);
    close(upPipe[WRITE]);
  }
  
  int passUp = 1;
  int leftContents = 999999999;
  int rightContents = 999999999;
  int leftEmpty = 0;
  int rightEmpty = 0;
  int intbuffer;
  int nbytes;
  close(rightPipe[WRITE]);
  close(leftPipe[WRITE]);
  while(passUp){
    if(leftContents == 999999999){
      nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
      if(nbytes > 0){
	leftContents = intbuffer;
	//perror("left set");
      }else{
	leftEmpty = 1;
	//perror("left empty");
      }
    }
    
    if(rightContents == 999999999){
      nbytes = read(rightPipe[READ], &intbuffer, sizeof(intbuffer));
      if(nbytes > 0){
	rightContents = intbuffer;
	//perror("right set");
      }
      else{ 
	rightEmpty = 1;
	//perror("right empty");
      }
    }
    
    if(leftContents < rightContents){
      //perror("***left < right***");
      if(master)
	  printf("Master Printout: %d\n", leftContents);
      else
	write(upPipe[WRITE], &leftContents, sizeof(int));
      leftContents = 999999999;
      perror("left contents sent up");
    }
    else if(rightContents < leftContents){
       //perror("***left < right***");
      if(master)
	  printf("Master Printout: %d\n", rightContents);
      else
	write(upPipe[WRITE], &rightContents, sizeof(int));
      rightContents = 999999999;
      perror("right contents sent up");
    }
    else if((leftContents == rightContents) && (leftEmpty != 1 && rightEmpty != 1)){
      if(master){
	  printf("Master Printout: %d\n", rightContents);
	  printf("Master Printout: %d\n", leftContents);
	  perror("MASTER PROCESS WENT THROUGH*********************");
      }
      else{
	write(upPipe[WRITE], &rightContents, sizeof(int));
	//perror("*************left = right***************");
	write(upPipe[WRITE], &leftContents, sizeof(int));
      }
      leftContents = 999999999;
      rightContents = 999999999;
      perror("both contents sent up");
    }
    else if(leftEmpty == 1 && rightEmpty == 1){
      passUp = 0;
      perror("exit loop");
    }
    
  }
 // perror("while done");
  //close(upPipe[WRITE]);
      
  
    
  
  //if(master){
    //while(read(rightPipe[READ], &intbuffer, sizeof(intbuffer)) < 0){
      //perror("Numbers in order:");// %d\n")//, intbuffer);
    //}
  //}
  close(rightPipe[READ]);
  close(leftPipe[READ]);
  if(!master){
    close(upPipe[WRITE]);
    //perror("processes exited");
    exit(0);
  }//else{
   // nbytes = read(upPipe[READ], &intbuffer, sizeof(intbuffer));
    //printf("THIS IS A PRINOUT OF THE FIRST IN PIPE %d\n", intbuffer);
   // close(upPipe[READ]);
   //if((nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer))) == -1)
     // perror("failed to read");
    //printf("%d\n", intbuffer);
   //if((nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer))) == -1)
     // perror("failed to read");
    //printf("%d\n", intbuffer);
  //}
}

void doLeafStuff(char *fileName){
  //numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
  //readFile(fileName);
  //convertToInt();
  //for(i = 0; i < numbs; i++)
  //  write(upPipe[WRITE], &numbers[i], sizeof(int));
  //freeMem();
}


void breed(int spawns){
  int upPipe[2];
  int leftPipe[2];
  int rightPipe[2];
  int status;
  pid_t leftPID;
  pid_t rightPID;
  
  if (pipe (upPipe) < 0 || pipe(leftPipe) < 0 || pipe(rightPipe) < 0) {
    perror ("plumbing problem");
    exit(1);
  }//else 
  
  if ((leftPID = fork()) < 0) {
    perror ("left fork failed");
    exit(1);
  }
  
  if(leftPID == 0){
    dup2(leftPipe[WRITE], upPipe[WRITE]);
    pipe(leftPipe);
    pipe(rightPipe);
    close(upPipe[READ]);
    spawns = (spawns/2);
    if(spawns == 1){//we are a leaf node
      //pipes not needed
      close(rightPipe[READ]);
      close(rightPipe[WRITE]);
      close(leftPipe[READ]);
      close(leftPipe[WRITE]);
      
      numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
      readFile(fileNames[1]);
      convertToInt();
      for(i = 0; i < numbs; i++)
	write(upPipe[WRITE], &numbers[i], sizeof(int));
      freeMem();
      
      close(upPipe[WRITE]);
      exit(0);
    }
    breed(spawns);
    
  }
    
  if((rightPID = fork()) < 0){
    perror("right fork failed");
  }
    
  if(rightPID == 0){
    dup2(rightPipe[WRITE], upPipe[WRITE]);
    pipe(leftPipe);
    pipe(rightPipe);
    spawns = (spawns/2);
    if(spawns == 1){
    //Check if leaf
      //pipes not needed
      close(rightPipe[READ]);
      close(rightPipe[WRITE]);
      close(leftPipe[READ]);
      close(leftPipe[WRITE]);
      close(upPipe[READ]);
      
      numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
      readFile(fileNames[2]);
      convertToInt();
      for(i = 0; i < numbs; i++)
	write(upPipe[WRITE], &numbers[i], sizeof(int));
      freeMem();
      
      
      close(upPipe[WRITE]);
      exit(0);
    }
      breed(spawns);
    
  }
  waitpid(leftPID, &status , 0);
  waitpid(rightPID, &status, 0);
  
  
  
  //close(leftPipe[WRITE]);
  
  
  int master = 0;
  if(spawns == 4){
    master = 1;
    close(upPipe[READ]);
    close(upPipe[WRITE]);
    perror("we are master");
  }
  
  
  int passUp = 1;
  int leftContents = 999999999;
  int rightContents = 999999999;
  int leftEmpty = 0;
  int rightEmpty = 0;
  int intbuffer;
  int nbytes;
  close(rightPipe[WRITE]);
  close(leftPipe[WRITE]);
  if(master)
    perror("Master is going into while loop");
  while(passUp){
    if(leftContents == 999999999){
      nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
      if(nbytes > 0){
	leftContents = intbuffer;
	//perror("left set");
	//printf("Set left: %d\n", leftContents);
      }else{
	leftEmpty = 1;
	perror("left empty");
      }
    }
    
    if(rightContents == 999999999){
      nbytes = read(rightPipe[READ], &intbuffer, sizeof(intbuffer));
      if(nbytes > 0){
	//perror("right set");
	rightContents = intbuffer;
	//printf("Set right: %d\n", rightContents);
      }
      else{ 
	rightEmpty = 1;
	//perror("right empty");
      }
    }
    
    if(leftContents < rightContents){
      //perror("***left < right***");
      if(master == 1)
	printf("Master Printout: %d\n", leftContents);
      else
	write(upPipe[WRITE], &leftContents, sizeof(int));
      leftContents = 999999999;
      perror("**left sent");
    }
    else if(rightContents < leftContents){
       //perror("***left < right***");
      if(master == 1)
	 printf("Master Printout: %d\n", rightContents);
      else
	write(upPipe[WRITE], &rightContents, sizeof(int));
      rightContents = 999999999;
      perror("**right sent");
    }
    else if((leftContents == rightContents) && (leftEmpty != 1 && rightEmpty != 1)){
      if(master == 1){
	  printf("Master Printout: %d\n", rightContents);
	  printf("Master Printout: %d\n", leftContents);
      }else{
	write(upPipe[WRITE], &leftContents, sizeof(int));
	write(upPipe[WRITE], &rightContents, sizeof(int));
      }
      leftContents = 999999999;
      rightContents = 999999999;
      perror("*****both sent");
    }
    else if(leftEmpty == 1 && rightEmpty == 1){
      if(!master){
	close(upPipe[WRITE]);
	close(upPipe[READ]);
      }
      passUp = 0;
      perror("exit loop");
    }
    
  }
  
  close(rightPipe[READ]);
  close(leftPipe[READ]);
  if(!master)
    exit(0);
}
