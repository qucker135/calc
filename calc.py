#Calculator
#by Qucker
def calc(expr):
	"""[Pl]Oblicza wartosc liczbowa wyrazenia algebraicznego."""
	#print(expr)
	
	try:
		return float(expr)
	except ValueError:
		#print("Holy crap!")
		pass
	
	pom = True # flaga pomocnicza, sprawdza czy nawias na poczatku expr odpowiada temu na koncu
	for x in expr[1:-1]:
		if x==')':
			pom = False
			break
		elif x=='(':
			break
	
	if expr[0]=='(' and expr[-1]==')' and pom:
		return calc(expr[1:-1])
		
	b=0 # a brackets-measuring variable////////////////////////PO//CO?
		
	for i in range(len(expr)-1,-1,-1):
		
		#counting brackets
		if expr[i] == ')':
			b+=1
		elif expr[i] =='(':
			b-=1
		
		if b==0: # do sth only when b==0
			#print(i)
			if expr[i]=='+':
				return calc(expr[0:i]) + calc(expr[i+1:len(expr)])
			elif expr[i]=='-':
				return calc(expr[0:i]) - calc(expr[i+1:len(expr)])
					
	b=0
		
	for i in range(len(expr)-1,-1,-1):
		
		#counting brackets
		if expr[i] == ')':
			b+=1
		elif expr[i] =='(':
			b-=1
		
		if b==0: # do sth only when b==0
			#print(i)
			if expr[i]=='*':
				return calc(expr[0:i]) * calc(expr[i+1:len(expr)])
			elif expr[i]=='/':
				try:
					return calc(expr[0:i]) / calc(expr[i+1:len(expr)])
				except ZeroDivisionError:
					#print("Dzielenie przez zero!")
					return None
					pass
	
	b=0
		
	for i in range(len(expr)-1,-1,-1):
		
		#counting brackets
		if expr[i] == ')':
			b+=1
		elif expr[i] =='(':
			b-=1
		
		if b==0: # do sth only when b==0
			#print(i)
			if expr[i]=='^':
				return calc(expr[0:i]) ** calc(expr[i+1:len(expr)])		
			
while True:
	print(calc(input()))
#help(calc)
