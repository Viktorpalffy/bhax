{
    int a=0;
    int b=0;
    int c=0;
    cout<<"Kerem a felcserelni kivant szamokat!"<<"\n";
    cin>>a>>b;
    cout<<"A ket szam: "<<"\n"<<"A = "<<a<<"\n"<<"B = "<<b<<"\n";

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
    cout<<"A ket szam felcserelve: "<<"\n"<<"A = "<<a<<"\n"<<"B = "<<b<<"\n";

    return 0;
}
