/*NAME: PRANALI SHINDE*/
/*ROLL NUMBER: 1901CS41*/
/*PH-203*/
#include <bits/stdc++.h>
#define ld long double
#define ll long long int
#define mp make_pair
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define vll vector<ll>
#define pb push_back
#define sp << " "
#define mod(n) n % 1000000007
#define startTime time_t start, end;time(&start);
#define precision(n) cout << fixed << setprecision(n);
#define endTime time(&end);double tt = double(end-start);cout<<"Time taken : "<<fixed<<tt<<setprecision(5);cout <<" sec"<< endl;

using namespace std;

string Input() /* Input(): A function to take input */
{
	cout << "Enter the input of circuit arrangement: ";
	string str;
	getline(cin, str);
	return str;
}


void printConductance(double net_conductance) /* printConductance(): A function to print out the
	result */
{
	cout << "The Net Conductance of the System is = " << net_conductance << endl;
}

string discardSpaces(string str)  /* discardSpaces(): A utility function to remove spaces
	from the string if any. */
{
	int len = str.length();
	for (int index = 0; index < len; index++) {
		if (str[index] == ' ') {
			str.erase(index, 1);
			index -= 1;
			len -= 1;
		}
	}
	return str;
}


double parallel(vector<double> conductance) /* parallel(): it is a utility function which calculates the parallel conductance from the list of given conductance. */
{
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int index = 0; index < len; index++) {
		net_conductance += conductance[index];
	}
	return net_conductance;
}

double series(vector<double> conductance) /* series(): A utility function which calculates the
	series conductance of a list of conductances given. */
{
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int index = 0; index < len; index++) {
		net_conductance += 1 / conductance[index];
	}
	return 1 / net_conductance;
}

/*	calculateans(): It is a driver function which
	controls the string stackand drives all the
	calculations appropriately. */

void calculateans(string str) {
	int len = str.length(); // Length of the string

	// A stack of circuit connections
	stack <pair <char, vector <double>> > circuit;

	// A temporary variable to store individual conductances as string
	string num_var;
	for (int index = 0; index < len; index++) {

		// Pushing the arrangement into the stack
		if (str[index] == '(') {
			vector <double> conductances;
			circuit.push(mp(str[index - 1], conductances));
		}


		else if (str[index] == ',') {// Separating the numerical entries
			if (str[index - 1] == ')') continue;
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			arrangement.second.pb(stod(num_var));
			circuit.push(arrangement);
			num_var = "";
		}

		// Closing the calculation on the top of the stack
		else if (str[index] == ')') {
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			if (num_var != "") arrangement.second.pb(stod(num_var));
			double net_conductance = 0.0;
			if (arrangement.first == 'S') {
				net_conductance = series(arrangement.second);
			} else {
				net_conductance = parallel(arrangement.second);
			}
			if (index == len - 1) {
				printConductance(net_conductance);
				return;
			}
			arrangement = circuit.top();
			circuit.pop();
			arrangement.second.pb(net_conductance);
			circuit.push(arrangement);
			num_var = "";
		}

		// Formation of numerical string
		if (str[index] != '(' && str[index] != ')' && str[index] != ',' && str[index] != 'P' && str[index] != 'S') num_var += str[index];
	}
}
/*driver function*/

int main() {
	string str = Input();
	str = discardSpaces(str);
	calculateans(str);
	string hold;
	cout << "Enter any letter and press ENTER to exit." << endl;
	cin >> hold;
}
