def calc(expr):
	try:
		if expr==None:
			return None
		return float(expr)
	except ValueError:
		pass
	
	pom = True  # auxiliary flag, checks if initial bracket corresponds to the final one
	
	for x in expr[1:-1]:
		if x==')':
			pom = False
			break
		elif x=='(':
			break
	
	if expr[0]=='(' and expr[-1]==')' and pom:
		return calc(expr[1:-1])
		
	b=0 # a brackets-measuring variable
		
	for i in range(len(expr)-1,-1,-1):
		
		#counting brackets
		if expr[i] == ')':
			b+=1
		elif expr[i] =='(':
			b-=1
		
		if b==0: # do sth only when b==0
			if expr[i]=='+' or expr[i]=='-':
				x = calc(expr[0:i])
				y = calc(expr[i+1:len(expr)])
				if x==None or y==None:
					return None
				if expr[i]=='+':
					return x + y
				if expr[i]=='-':
					return x - y
					
	b=0
		
	for i in range(len(expr)-1,-1,-1):
		
		#counting brackets
		if expr[i] == ')':
			b+=1
		elif expr[i] =='(':
			b-=1
		
		if b==0: # do sth only when b==0
			if expr[i]=='*' or expr[i]=='/':
				x = calc(expr[0:i])
				y = calc(expr[i+1:len(expr)])
				if x==None or y==None:
					return None
				if expr[i]=='*':
					return x * y
				if expr[i]=='/':
					try:
						return calc(expr[0:i]) / calc(expr[i+1:len(expr)])
					except ZeroDivisionError:
						return None


	b=0
		
	#for i in range(len(expr)-1,-1,-1):
	for i in range(len(expr)):	
		#counting brackets
		if expr[i] == '(':
			b+=1
		elif expr[i] ==')':
			b-=1
		
		if b==0: # do sth only when b==0
			if expr[i]=='^':
				x = calc(expr[0:i])
				y = calc(expr[i+1:len(expr)])
				if x!=None and y!=None:
					return x ** y		
			
while True:
	print(calc(input()))
