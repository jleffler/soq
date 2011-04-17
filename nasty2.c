    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(int argc, char **argv)   
    {  
        void (*fn)(char*) = (void(*)(char*))system;  
        char buf[256];  
    
        fn = (void(*)(char*))puts;  
        strcpy(buf, argv[1]);  
        fn(argv[2]);  
        exit(1);  
    }
