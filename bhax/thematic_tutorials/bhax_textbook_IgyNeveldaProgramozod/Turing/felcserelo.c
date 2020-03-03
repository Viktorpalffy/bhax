#include <stdio.h>
int main()

{
    int a;
    int b;
    int c;
    printf("Kerem a felcserelni kivant szamokat! \n");
    scanf("%d",a);
    scanf("%d",b);
    printf("A ket szam: \n");
    printf("A =" "%d",a);
    printf("B = " "%d",b);

    //Elso valtozat:
    /*
        c = a;
        a = b;
        b = c;
    */
    //Masodik valtozat:
    /*
        a = a-b;
        b = a+b;
        a = b-a;
    */
    //Harmadik valtozat:
    /*
        a = a*b;
        b = a/b;
        a = a/b;
    */
    //Negyedik valtozat:
    /*
        a=a^b;
        b=a^b;
        a=a^b;
    */
    printf("A ket szam felcserelve: \n");
    printf("A =" "%d",a);
    printf("B = " "%d",b);

    return 0;
}
