//-*****
//(c) Filimonov Ivan Sergeevich aka TheGrayCode, 2020
//
//Calculator for rational approximation of square root
//of the given integer
//
//Language: C++17
//Checked compiler: Microsoft Visual Studio C++ 2019
//	(part of Visual Studio 2019 Community Edition package)
//Version: v1.0
//-*****

#define pb(x) push_back(x)
#define fora0(ITER, LIMIT) for(int ITER = 0; ITER < LIMIT; ITER++)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cmath>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace::std;

typedef long long ll;
typedef long double ld;


void problem();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	problem();

	return 0;
}

void problem() {
	ll base = -1;
	//Target number input with error handling
	while (base < 0) {
		cout << "Please, enter a integer to count its square root's rational approximation:\n";
		string s;
		cin >> s;
		try {
			base = stoi(s);
			if (base < 0 || cin.fail() || cin.eof()) {
				cout << "Incorrect number or an input error. Try again\n";
			}
		}
		catch (std::invalid_argument e) {
			cout << "Not a valid integer format. Try again\n";
		}
	}
	//"Exact" value of base^(1/2) (actually, it's rather good approximation)
	ld real_value = sqrt(base);
	//Vector of partial quotients
	vector<ll> a;
	//Precision value. If |p/q-base^(1/2)|<EPS, calculation completes
	ld EPS = 1e-10;
	a.push_back(real_value);
	//Vector of "alpha" values
	vector<ld> alpha;
	alpha.pb(real_value);
	//Vectors of all p and q values
	vector<ll> p;
	vector<ll> q;
	p.pb(1);
	p.pb(alpha.front());
	q.pb(0);
	q.pb(1);
	while (abs(p.back() * 1.0 / q.back() - real_value) > EPS) {
		//current alpha
		ld alpha_now = 1 / (alpha.back() - a.back());
		//current partial quotient
		ll a_now = alpha_now;
		//p1 is previous p, p0 is p before p1
		//same with q1 and q0
		ll p1 = p.back(), p0 = p[p.size() - 2], q1 = q.back(), q0 = q[q.size() - 2];
		//current value of p
		ll p_now = a_now * p1 + p0;
		//current value of q
		ll q_now = a_now * q1 + q0;
		//Adding all found new values into vectors
		alpha.pb(alpha_now);
		a.pb(a_now);
		p.pb(p_now);
		q.pb(q_now);
	}
	//Printing recieved result
	cout << '\n';
	cout << "Real value of sqrt(" << base << "):\n" << fixed << setprecision(20) << real_value << '\n';
	cout << "Counted rational approximation with precision eps=1e-10: " << p.back() << '/' << q.back() << '\n';
	cout << "It's near:\n" << fixed << setprecision(20) << (p.back() * 1.0 / q.back()) << '\n';
	cout << "Partial quotients: \n";
	fora0(i, a.size()) {
		cout << a[i] << ' ';
	}
	cout << '\n';
	return;
}
