// Definite Itegral Calculater
// use of Reiman Sums

#include <iostream>
#include <cmath>

// number of intervals
int n = 1000000;
// bounds for definite integral
double a ;
double b ;


using namespace std;

// defined function; 
double funct(double x)
{
	return x*x;
}


// implement Reiman Sums
double calc(double a, double b)
{
	double x = (b-a)/double(n);
	double total = 0.0;
	for (int i = 0; i < n; i++)
	{
		total+= x * funct(a + i*x);
	}	
	return total;
}

int main(){

	cout << "A? " << endl;
	cin >> a ;

	cout << "B?" << endl;
	cin >> b ;	

	double total = calc(a, b);
	cout << total << endl;

	return 0;
}
