#include <iostream>
#include <cmath>

using namespace std;

bool is_numeric(string expr){
	unsigned i=0;
	if(expr=="") return false;
	if(expr[i]=='-') i++;
	if(!(expr[i]>='0' && expr[i]<='9')) return false;
	while(expr[i]>='0' && expr[i]<='9') i++;
	if(i==expr.length()) return true;
	if(expr[i++]!='.') return false;
	if(!(expr[i]>='0' && expr[i]<='9')) return false;
	while(i<expr.length()){
		if(!(expr[i]>='0' && expr[i++]<='9')) return false;
	}
	return true;
}

double eval(string expr){
	if(is_numeric(expr)){
		return stod(expr);
	}
	//check for expression in brackets
	if(expr[0]=='(' && expr[expr.length()-1]==')'){
		unsigned brackets = 1;//number of open brackets minus closed brackets already checked
		bool expr_bracket_type = true; //let's assume it is an expression of bracket type, indeed
		for(unsigned i=1;i<expr.length()-1;i++){
			if(expr[i]=='(') brackets++;
			else if(expr[i]==')') brackets--;
			if(brackets==0){
				expr_bracket_type = false;
			}
		}
		if(expr_bracket_type) return eval(expr.substr(1,expr.length()-2));
	}
	unsigned brackets = 0;
	for(unsigned i=expr.length()-1;i!=-1;i--){	//loop for adding and substracting
		if(expr[i]==')') brackets++;
		else if(expr[i]=='(') brackets--;
		if(expr[i]=='+' && brackets==0 && i!=0 && i!=expr.length()-1) return eval(expr.substr(0,i)) + eval(expr.substr(i+1,expr.length()-i-1));
		if(expr[i]=='-' && brackets==0 && i!=0 && i!=expr.length()-1) return eval(expr.substr(0,i)) - eval(expr.substr(i+1,expr.length()-i-1));
	}
	brackets = 0;
	for(unsigned i=expr.length()-1;i!=-1;i--){	//loop for multiplying and dividing 
		if(expr[i]==')') brackets++;
		else if(expr[i]=='(') brackets--;
		if(expr[i]=='*' && brackets==0 && i!=0 && i!=expr.length()-1) {	
			return eval(expr.substr(0,i)) * eval(expr.substr(i+1,expr.length()-i-1));
		}
		if(expr[i]=='/'	&& brackets==0 && i!=0 && i!=expr.length()-1) {
			double divisor = eval(expr.substr(i+1,expr.length()-i-1));
			if(abs(divisor)==0.0) throw runtime_error("Division by zero occurred!");
			return eval(expr.substr(0,i)) / divisor;
		}
	}

	for(unsigned i=0;i<expr.length();i++){	//loop for powering
		if(expr[i]=='(') brackets++;
		else if(expr[i]==')') brackets--;
		if(expr[i]=='^' && brackets==0 && i!=0 && i!=expr.length()-1){
			double result = pow(eval(expr.substr(0,i)), eval(expr.substr(i+1,expr.length()-i-1)));	 
			if(isnan(result)) throw runtime_error("Powering error!");
			return result;
		}	
	}	
	throw runtime_error("Parsing error!");

}

int main(){
	//TEST
	/*
	try{
		cout<<eval("3*4")<<endl;
		cout<<eval("2*5-3.5")<<endl;	
		cout<<eval("0.0")<<endl;
		cout<<eval("2+3*5")<<endl;
		cout<<eval("(2+3)*(-5)")<<endl;
		cout<<eval("2^6")<<endl;
		cout<<eval("2.0^0.5")<<endl;
	}
	catch(runtime_error& e){
		cerr<<e.what()<<endl;
	}
	catch(...){
		cerr<<"Another error"<<endl;
	}
	*/
	string bfr = "";
	do{
		cout<<"calc>";
		cin>>bfr;
		if(bfr=="!end") break;
		try{
			double result = eval(bfr);
			cout<<bfr<<"="<<result<<endl;
		}
		catch(runtime_error& e){
			cout<<e.what()<<endl;
		}
		catch(...){
			cout<<"Another error"<<endl;
		}
		
	}while(true);
	return 0;
}
