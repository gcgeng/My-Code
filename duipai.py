from random import *
from os import *
mknod("input")
fp = open("input", w)
while 1:
	n = randint(1, 20)
	k = randint(1, 40)
	while k > (n/2)*(n-n/2):
		k = randint(1,40)	
	fp.write(n, k)
	os.system("./a.out < input > output.a")
 	os.system("./check < output.a > output.b")
	os.system("diff output.a input")
fp.close()	 
		    
