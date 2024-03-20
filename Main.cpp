#include<iostream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<cctype>
using namespace std;
const string operators = "+,-,*,/,^,=";
const string functions = "abs,exp,ln,log,cos,sin,tan,sec,csc,cot";
int numConditions = 2;
int numOperators(string);
char* toOperatorsArr(string, char*, int);
const int numberOfOperators = numOperators(operators);
char* operatorsArr = toOperatorsArr(operators, operatorsArr, numberOfOperators);
int numFunctions(string);
string* toFunctionsArr(string, string*, int);
const int numberOfFunctions = numFunctions(functions);
string* functionsArr = toFunctionsArr(functions, functionsArr, numberOfFunctions);
bool isExpressionStringWellFormed(string, char*, int, string*, int, string, int);
void readInEachExp(string exp, int**& var, double**& deg, int**& degNumerator, int**& degDenominator, double*& coeff, int*& coeffNumerator, int*& coeffDenominator, int*& numVar, int& num);
string simplifyInputExpressionString(string);
//int MAXCOMPUTER /
int SIZE1 = 100;
int SIZE2 = 200;
template <typename T>
void shouldResize(T*, int, int, int);
void printErrorMessage(int);
int power10(int num);
int convert(string num);
double convertFract(string num);
double convertDeci(string num);
double tenthFract(int num);
int main() {
	string exp = "ln(x+y)+(9)exp(y+z)";
	string simplifiedExp = simplifyInputExpressionString(exp);
	cout << simplifiedExp << endl;

	string variables = "x,y,z";
	cout << numberOfOperators << endl;
	for (int i = 0; i < numberOfOperators; i++) {
		cout << operatorsArr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < numberOfFunctions; i++) {
		cout << functionsArr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < numConditions; i++) {
		if(!isExpressionStringWellFormed(exp, operatorsArr, numberOfOperators, functionsArr, numberOfFunctions, variables, i)) {
			printErrorMessage(i);
			system("pause");
			exit(1);
		}
	}
	/*if (isExpressionStringWellFormed(exp, operatorsArr, numberOfOperators, functionsArr, numberOfFunctions, 0)) {
		for (int i = 0; i < numberOfFunctions; i++) {
			cout << functionsArr[i] << " ";
		}
		cout << endl;
	}
	if (isExpressionStringWellFormed(exp, operatorsArr, numberOfOperators, functionsArr, numberOfFunctions, 1)) {
		cout << "no issue found" << endl;
	}*/
	delete[] operatorsArr;
	delete[] functionsArr;
	return 0;
}
int numOperators(string operators) {
	int num = 0;
	for (int i = 0; i < operators.length(); i++) {
		if (operators[i] == ',') {
			num++;
		}
	}
	num++;
	return num;
}
char* toOperatorsArr(string operators, char* operatorsArr, int numberOfOperators) {
	operatorsArr = new char[numberOfOperators];
	int count = 0;
	for (int i = 0; i < numberOfOperators; i++) {
		while (count < operators.size() && operators[count] != ',') {
			operatorsArr[i] = operators[count];
			count++;
		}
		count++;
	}
	return operatorsArr;
}
int numFunctions(string functions) {
	int num = 0;
	for (int i = 0; i < functions.length(); i++) {
		if (functions[i] == ',') {
			num++;
		}
	}
	num++;
	return num;
}
string* toFunctionsArr(string functions, string* functionsArr, int numberOfFunctions) {
	functionsArr = new string[numberOfFunctions];
	int count = 0;
	string temp = "";
	for (int i = 0; i < numberOfFunctions; i++) {
		temp = "";
		while (count < functions.size() && functions[count] != ',') {
			//functionsArr[i] = functions[count];
			temp += functions[count];
			count++;
		}
		functionsArr[i] = temp;
		count++;
	}
	return functionsArr;
}
void printErrorMessage(int num) {
	if (num == 1) {
		cout << "Incorrect string syntax" << endl;
		system("pause");
		exit(1);
	}
}
bool isExpressionStringWellFormed(string exp, char* op, int numOp, string* func, int numFunctions, string variables, int mode) {
	if (mode == 0) {
		bool beginning = true;
		for (int i = 0; i < exp.size(); i++) {
			if (beginning) {
				for (int j = 0; j < numOp; j++) {
					if (op[j] != '-' && exp[i] == op[j]) {
						cout << "Missplaced operators" << endl;
						system("pause");
						exit(1);
					}
				}
				beginning = false;
			}
			if (exp[i] == '(') {
				beginning = true;
			}
			else {
				beginning = false;
			}
		}
		bool end = true;
		for (int i = exp.size() - 1; i > 0; i--) {
			if (end) {
				for (int j = 0; j < numOp; j++) {
					if (exp[i] == op[j]) {
						cout << "Missplaced operators" << endl;
						system("pause");
						exit(1);
					}
				}
			}
			if (exp[i] == ')') {
				end = true;
			}
			else {
				end = false;
			}

		}
	}
	else if (mode == 1) {
		bool correct = true;
		int count = 0;
		for (int i = 0; i < exp.size(); i++) {
			for (int j = 0; j < numberOfFunctions; j++) {
				//cout << func[j] << endl;
				if (i + func[j].size() - 1 < exp.size() - func[j].size() && exp.substr(i, func[j].size()) == func[j]) {
					//cout << exp.substr(i, func[j].size()) << endl;
					//cout << func[j] << endl;
					if (exp[i + func[j].size()] != '(') {
						//cout << i << endl;
						//cout << func[j] << endl;
						correct = false;
					}
					i += func[j].size() - 1;
					//cout << "i " << i << endl;
					count++;
				}
				//else {
				//	count++;
				//}
			}
			if (!correct) {
				cout << "Incorrect functions called syntax" << endl;
				system("pause");
				return 0;
			}
		}
		//cout << count << endl;
		int* funcStartPos = new int[count];
		int* funcEndPos = new int[count];
		int numFunctionsInExp = 0;
		for (int i = 0; i < exp.size(); i++) {
			for (int j = 0; j < numberOfFunctions; j++) {
				//cout << func[j] << endl;
				if (i + func[j].size() - 1 < exp.size() - func[j].size() && exp.substr(i, func[j].size()) == func[j]) {
					funcStartPos[numFunctionsInExp] = i;
					funcEndPos[numFunctionsInExp] = i + func[j].size() - 1;
					numFunctionsInExp++;
				}
			}
		}
		cout << "Number of Functions: " << numFunctionsInExp << endl;
		for (int i = 0; i < numFunctionsInExp; i++) {
			cout <<"Function Start: " << funcStartPos[i] << endl;
			cout <<"Function End: " << funcEndPos[i] << endl;
			cout << endl;
		}
		/////////TO DO 3-17-2024 2:02pm latest////////////////////////////////////////////////////////////////////////////////
		/*bool onlyOne = true;
		for (int i = 0; i < exp.size(); i++) {
			onlyOne = false;
			for (int j = 0; j < count; j++) {
				if (exp[i] == op[j]) {
					if (i + 1 < exp.size()) {//any pair of consecutive operators are not correct
						for (int k = 0; k < count; k++) {
							if (exp[i + 1] == op[k]) {
								cout << "Missplaced operators" << endl;
								system("pause");
								return 0;
							}
						}
					}
					break;
				}
			}
		}*/
		int zero = 0;
		for (int i = 0; i < exp.size(); i++) {
			if (exp[i] == '(') {
				zero++;
			}
			else if (exp[i] == ')') {
				zero--;
			}
		}
		if (zero != 0) {
			cout << "Missplaced paranthesis" << endl;
			system("pause");
			return 0;
		}
		count = 0;
		for (int i = 0; i < variables.length(); i++) {
			if (variables[i] == ',') {
				count++;
			}
		}
		count++;
		string* var = new string[count];
		int* varLength = new int[count];
		int start = 0;
		bool first = true;
		string temp = "";
		count = 0;
		for (int i = 0; i < variables.length(); i++) {
			//cont = false;
			//if (i == 3){
			//	cont = true;
			//	cout << "test " << variables[i] << endl;
			//	cout << "first " << first << endl;
			//	cout << i << endl;
			//}
			if (first) {
				start = i;////////////////////
				cout << "start " << start << endl;
				first = false;
				temp = "";
			}
			//cont = false;
			if (variables[i] == ',') {
				for (int j = start; j < i; j++) {
					temp += variables[j];
				}
				var[count] = temp;
				varLength[count] = i - start;
				first = true;
				cout << "i " << i << endl;
				//i += varLength[count];
				count++;
			}
			else if (i + 1 == variables.length()) {
				for (int j = start; j < i + 1; j++) {
					temp += variables[j];
				}
				var[count] = temp;
				varLength[count] = i - start + 1;
				//i += varLength[count];
				count++;
			}
			//if(i==2){
			//	cout<<"test "<<variables[i]<<endl;
			//}
		}
		for (int i = 0; i < count; i++) {
			cout << var[i] << " ";
		}
		cout << endl;
		bool notAFunc = true;
		int count2 = 0;
		bool finished;
		int varCount = count;
		count = 0;
		notAFunc = true;
		int numMatched = 0;
		bool alreadyIn = false;
		for (int i = 0; i < exp.size(); i++) {
			notAFunc = true;
			if (isalpha(exp[i])) {
				//if(isalpha(exp[i])){
				start = i;
				//}
				for (int j = 0; j < varCount; j++) {
					count = 0;
					//cout<<var[j].size()<<endl;
					while (count < var[j].size() && exp[i] == var[j][count]) {
						//cout<<"exp "<<exp[i]<<endl;
						i++;
						count++;
					}
					if (count == var[j].size()) {
						//cout<<"var exp: "<<exp[i]<<" var var; "<<var[j]<<endl;
						numMatched++;
						break;
					}
				}

				//i = start;
				bool notFunc = false;
				for (int j = 0; j < numFunctionsInExp; j++) {
					if (funcStartPos[j] <= i && i <= funcEndPos[j])
					{
						cout << "Function Not counted " << funcStartPos[j] << endl;
						while (isalpha(exp[i])) {
							i++;
						}
						cout << "test99 Pos " << i << endl;
						notFunc = true;
						break;
					}
				}
				if (notFunc == false) {
					//alreadyIn = false;
					//for (int j = 0; j < count3; j++){
						//if (funcStartPos[j] <= i && i <= funcEndPos[j])
						//{
						//	cout << "Function Not counted " << funcStartPos[j] << endl;
						//	while (isalpha(exp[i])){
						//		i++;
						//	}
						//	cout << "test99 Pos " << i << endl;
						//	break;
						//}
						//if (!(funcStartPos[j] <= i && i <= funcEndPos[j])){
					while (isalpha(exp[i])) {
						//if (i == funcEndPos[j]){
						alreadyIn = true;
						//}
						i++;
						//if (alreadyIn){
						//i--;
						//break;
						//}
					}
					//if (alreadyIn){
					//	break;
					//}
				//}
			//}
			//if (alreadyIn){

				//i--;
					count2++;
					//}
				}
				i--;

				cout << "End pos " << i << endl;
			}
		}
		cout << numMatched << endl;
		cout << count2 << endl;
		if (numMatched != count2) {
			cout << "no matching variables from the list in the expression" << endl;
			system("pause");
			exit(1);
		}
		else {
			cout << "passed" << endl;
		}
		//delete[] op;
		delete[] funcStartPos;
		delete[] funcEndPos;
	}
	return true;
}

template <typename T> void readInEachExp(string exp, int**& var, T**& deg, int**& degNumerator, int**& degDenominator, T*& coeff, int*& coeffNumerator, int*& coeffDenominator, int*& numVar, int& num) {
	var = new int*[SIZE1];
	deg = new T*[SIZE1];
	degNumerator = new int* [SIZE1];
	degDenominator = new int* [SIZE1];
	for (int i = 0; i < SIZE1; i++) {
		var[i] = new int[SIZE2];
		deg[i] = new T*[SIZE2];
		degNumerator[i] = new int[SIZE2];
		degDenominator[i] = new int[SIZE2];
	}
	coeff = new T[SIZE1];
	coeffNumerator = new int[SIZE1];
	coeffDenominator = new int[SIZE1];
	numVar = new int[SIZE1];
	string simplifiedExp = simplifyInputExpressionString(exp);
	int startPos = 0;
	int prevStartPos = 0;
	num = 0;
	string c;
	int count = 0;
	numVar[num] = 0;
	int i;
	int neg = 1;
	int fractOrDeci = 0;
	if (simplifiedExp[startPos] == '-') {
		neg = -1;
		startPos++;
	}
	if (simplifiedExp[startPos] == '(') {
		fractOrDeci = 0;
		startPos++;
		while ((startPos < simplifiedExp.size() || simplifiedExp[startPos] != ')') && (isdigit(simplifiedExp[startPos]) || simplifiedExp[startPos] == '/')) {/////////////////////////////////////////////////////////////////{//Right here need to rethink
			c += simplifiedExp[startPos];
			startPos++;
		}
		startPos++;
	}
	else {
		fractOrDeci = 1;
		while (startPos < simplifiedExp.size() && (isdigit(simplifiedExp[startPos]) || simplifiedExp[startPos] == '.')) {
			c += simplifiedExp[startPos];
			startPos++;
		}
	}
	if (c != "" && fractOrDeci == 1) {
		coeff[num] = convertDeci(c);
	}
	else if (c != "") {
		coeff[num] = convertFract(c);
	}
	else {//no coeff
		coeff[num] = 1;
	}
	coeff[num] *= neg;
	for (i = 0; i < simplifiedExp.length(); i++) {

	}

	//shouldResize<int>(var, SIZE1,  ,SIZE1*2);
}
string simplifyInputExpressionString(string exp) {
	/*int numPairParanthesis = 0;
	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == '(') {
			numPairParanthesis++;
		}
	}*/
	//int* posOpenParanthesis = new int[numPairParanthesis];
	//int* posClosedParanthesis = new int[numPairParanthesis];
	//int pos = 0;
	//cout << "test1" << endl;
	bool simplifyPartOfExp = false;
	bool negative = false;
	int savedPos = 0;
	for (int i = 0; i < exp.length(); i++) {
		simplifyPartOfExp = true;
		if (exp[i] == '(') {
			//cout << "test2" << endl;
			savedPos = i;
			negative = false;
			if (i!=0 && exp[i-1] == '-') {
				negative = true;
			}
			i++;
			cout << "Sim or Not1 " << simplifyPartOfExp << endl;
			while (exp[i] != ')') {
				if (!isdigit(exp[i])) {
					if (negative == false) {
						simplifyPartOfExp = false;
					}
				}
				i++;
			}
			cout << "( " << savedPos << endl;
			cout << "Sim or Not2 " << simplifyPartOfExp << endl;
			if (simplifyPartOfExp == true) {
				if (negative == true) {
					//for (int j = i + 2; j < exp.length();j++) {
					char temp = exp[savedPos - 1];
					exp[savedPos - 1] = exp[savedPos];
					exp[savedPos] = temp;
					/*exp += exp[exp.length() - 1];
					for(int j = exp.length() - 2; j >= i + 2; j--)
						exp[j] = exp[j - 1];
					}
					exp[i + 1] = '-';*/
				}
				else {
					cout << "test3" << endl;
					bool notShiftByTwo = true;
					
					for (int j = savedPos + 1; j < exp.length()-1; j++) {
						//cout << "j " << j << endl;
						//cout << "i " << i << endl;
						cout << "test4" << endl;
						if (j == i) {
							notShiftByTwo = false;
							//j++;
						}
						if (notShiftByTwo == true) {
							cout << "open " << j - 1;
							exp[j - 1] = exp[j];
						}
						else if (notShiftByTwo == false) {
							exp[j - 1] = exp[j + 1];
						}
					}
					//exp[exp.length() - 1] = null;
					
				}
			}
		}
	}
	////////////////cases
	string tempString="";
	for(int i=0;i<exp.length-2;i++)
        {
             tempString += exp[i];
	}
	//delete[] posOpenParanthesis;
	//delete[] posClosedParanthesis;
	//return exp;//slow
	return tempString;
}
template <typename T> void shouldResize(T*& arrayToResize, int oldSize, int pos, int newSize) {
	T* temp = new T[pos];
	for (int i = 0; i <= pos; i++) {
		temp[i] = arrayToResize[i];
	}
	if (pos >= oldSize) {
		delete[] arrayToResize;
		arrayToResize = new T[newSize];
		for (int i = 0; i <= pos; i++) {
			arrayToResize[i] = temp[i];
		}
	}
	delete[] temp;
}
int power10(int num)
{
	int factor = 10;
	int result = 1;
	if (num == 0)
	{
		return 1;
	}
	for (int i = 0; i < num; i++)
	{
		result *= factor;
	}
	return result;
}
int convert(string num)
{
	int total = 0;
	for (int i = num.size(); i > 0; i--)
	{
		total += power10(i - 1) * (num[num.size() - i] - '0');
	}
	return total;
}
double convertDeci(string num) {
	double total = 0;
	int count = 0;
	count = num.size();
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == '.') {
			count = i;
			break;
		}
	}
	for (int i = num.size() - 1; i > count; i--)
	{
		total += tenthFract(i - count) * (num[i] - '0');
		//cout<<tenthFract(i-count)*(num[i]-'0')<<endl;
	}
	//cout<<total<<endl;
	/*cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(num.size()-count-1);*/
	//cout<<total<<endl;
	//total+=1000;
	//cout<<total<<endl;
	for (int i = count; i > 0; i--)
	{
		total += power10(i - 1) * (num[count - i] - '0');
		//cout<<power10(i - 1) * (num[count - i] - '0')<<endl;
	}
	//cout<<total<<endl;
	return total;
}
double convertFract(string num) {
	double numerator = 0;
	double denominator = 0;
	int count = 0;
	count = num.size();
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == '/') {
			count = i;
			break;
		}
	}
	//cout<<count<<endl;
	//cout<<num.size()<<endl;
	for (int i = num.size() - 1; i > count; i--)
	{
		//cout<<"no"<<endl;
		denominator += power10((num.size() - 1) - i) * (num[i] - '0');
		//cout<<power10(i - (count+1))<<endl;
		//cout<<tenthFract(i-count)*(num[i]-'0')<<endl;
	}
	//cout<<denominator<<endl;
	for (int i = count; i > 0; i--)
	{
		numerator += power10(i - 1) * (num[count - i] - '0');
		//cout<<power10(i - 1) * (num[count - i] - '0')<<endl;
	}
	//cout<<numerator<<endl;

	return numerator / denominator;
}
double tenthFract(int num) {
	double factor = 0.1;
	double result = 1;
	if (num == 0)
	{
		return 1;
	}
	for (int i = 0; i < num; i++)
	{
		result *= factor;
	}
	return result;
}
