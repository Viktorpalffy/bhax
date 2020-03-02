#include <iostream>
using namespace std;

int main(){
        int a = 1;
        int b = 0;

        while(a!=0){
                a <<= 1;
                b++;
	}

	cout<<"A szó hossza ezen a gépen: "<<b<<"\n";
	return 0;
}

