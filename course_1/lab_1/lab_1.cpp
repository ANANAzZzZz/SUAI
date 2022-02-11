#include<iostream>

int main()
{   
    unsigned char answer;
        
    answer =  97 | -29;
    printf("97 or -29 = (227) = %i\n", answer);
    
    answer = 97 ^ 29;
    printf("97 xor 29 = (124) = %i\n ", answer);

    answer = 97 >> 3;
    printf("97 >> 3 = (12) = %i\n", answer);
    
    answer = (~97 ^ -29) & 39 ^ -119;
    printf("(not 97 xor -29) and 39 xor -119 = (172) = %i\n", answer);
    
    return 0 ;
}
