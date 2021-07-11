#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846
#define E  2.71828182845904523536

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
	unsigned brackets = 0;
	for(unsigned i=expr.length()-1;i!=-1;i--){	//loop for adding and substracting
		if(expr[i]==')') brackets++;
		else if(expr[i]=='(') brackets--;
		if(expr[i]=='+' && brackets==0 ) return eval(expr.substr(0,i)) + eval(expr.substr(i+1,expr.length()-i-1));
		if(expr[i]=='-' && brackets==0 ) return eval(expr.substr(0,i)) - eval(expr.substr(i+1,expr.length()-i-1));
	}
	brackets = 0;
	for(unsigned i=expr.length()-1;i!=-1;i--){	//loop for multiplying and dividing 
		if(expr[i]==')') brackets++;
		else if(expr[i]=='(') brackets--;
		if(expr[i]=='*' && brackets==0 ) {	
			return eval(expr.substr(0,i)) * eval(expr.substr(i+1,expr.length()-i-1));
		}
		if(expr[i]=='/'	&& brackets==0 ) {
			double divisor = eval(expr.substr(i+1,expr.length()-i-1));
			if(abs(divisor)==0.0) throw runtime_error("Division by zero occurred!");
			return eval(expr.substr(0,i)) / divisor;
		}
	}

	for(unsigned i=0;i<expr.length();i++){	//loop for powering
		if(expr[i]=='(') brackets++;
		else if(expr[i]==')') brackets--;
		if(expr[i]=='^' && brackets==0 ){
			double result = pow(eval(expr.substr(0,i)), eval(expr.substr(i+1,expr.length()-i-1)));	 
			if(isnan(result)) throw runtime_error("Powering error!");
			return result;
		}	
	}
	//check for expression in brackets
	if(expr[0]=='(' && expr[expr.length()-1]==')'){
		return eval(expr.substr(1,expr.length()-2));	
	}
	//Functions
	//Trygonometry
	if(expr.length()>3 && expr.substr(0,4)=="sin(" && expr[expr.length()-1]==')'){
		return sin(eval(expr.substr(4,expr.length()-5)));
	}
	if(expr.length()>3 && expr.substr(0,4)=="cos(" && expr[expr.length()-1]==')'){
		return cos(eval(expr.substr(4,expr.length()-5)));
	}
	if(expr.length()>3 && expr.substr(0,4)=="tan(" && expr[expr.length()-1]==')'){	
		double cosinus = cos(eval(expr.substr(4,expr.length()-5)));
		if(abs(cosinus)==0.0) throw runtime_error("Tangent domain error!"); 
		return tan(eval(expr.substr(4,expr.length()-5)));
	}
	if(expr.length()>3 && expr.substr(0,4)=="cot(" && expr[expr.length()-1]==')'){	
		double sinus = sin(eval(expr.substr(4,expr.length()-5)));
		if(abs(sinus)==0.0) throw runtime_error("Cotangent domain error!"); 
		return cos(eval(expr.substr(4,expr.length()-5)))/sinus;
	}
	if(expr.length()>3 && expr.substr(0,4)=="sec(" && expr[expr.length()-1]==')'){
		double cosinus = cos(eval(expr.substr(4,expr.length()-5)));
		if(abs(cosinus)==0.0) throw runtime_error("Secant domain error!"); 
		return 1.0/cosinus;
	}
	if(expr.length()>3 && expr.substr(0,4)=="csc(" && expr[expr.length()-1]==')'){
		double sinus = sin(eval(expr.substr(4,expr.length()-5)));
		if(abs(sinus)==0.0) throw runtime_error("Cosecant domain error!"); 
		return 1.0/sinus;
	}
	//Hiperbolic functions
	if(expr.length()>4 && expr.substr(0,5)=="sinh(" && expr[expr.length()-1]==')'){
		return sinh(eval(expr.substr(5,expr.length()-6)));	
	}
	if(expr.length()>4 && expr.substr(0,5)=="cosh(" && expr[expr.length()-1]==')'){
		return cosh(eval(expr.substr(5,expr.length()-6)));	
	}
	if(expr.length()>4 && expr.substr(0,5)=="tanh(" && expr[expr.length()-1]==')'){
		return tanh(eval(expr.substr(5,expr.length()-6)));	
	}
	if(expr.length()>4 && expr.substr(0,5)=="coth(" && expr[expr.length()-1]==')'){
		double tan_h = tanh(eval(expr.substr(5,expr.length()-6)));	
		if(abs(tan_h)==0.0) throw runtime_error("Hiperbolic tangent domain error!");
		return 1.0/tan_h;  
	}
	if(expr.length()>4 && expr.substr(0,5)=="sech(" && expr[expr.length()-1]==')'){
		double cos_h = cosh(eval(expr.substr(5,expr.length()-6)));	
		if(abs(cos_h)==0.0) throw runtime_error("Hiperbolic secant domain error!");
		return 1.0/cos_h;  
	}
	if(expr.length()>4 && expr.substr(0,5)=="csch(" && expr[expr.length()-1]==')'){
		double sin_h = sinh(eval(expr.substr(5,expr.length()-6)));	
		if(abs(sin_h)==0.0) throw runtime_error("Hiperbolic cosecant domain error!");
		return 1.0/sin_h;  
	}
	//Natural logarithm
	if(expr.length()>2 && expr.substr(0,3)=="ln(" && expr[expr.length()-1]==')'){
		double arg = eval(expr.substr(3,expr.length()-4)); 
		if(arg<=0.0) throw runtime_error("Logarithm domain error!");
		return log(arg);
	}
	//Predefined constants
	if(expr=="%PI") return PI;
	if(expr=="%E" ) return E; 

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
		//cin>>bfr;
		getline(cin,bfr);
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
