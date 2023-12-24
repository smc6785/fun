import cmath
from matplotlib.pylab import *

tau = 2*cmath.pi
def average(readings):
	base = cmath.e ** (1j*tau/360)
#total =0 
#for r in readings:
#	total += r
#return total/len(readings)
	total =0 
	for r in readings:
		v =r[1]*base** r[0]
		total += v
		arrow(0,0,v.real, v.imag, head_width=0.05, head_length=0.05, fc='r',ec='r')
	result = total/len(readings)
	arrow(0,0,result.real, result.imag, head_width=0.05, head_length=0.05, fc='b',ec='b')
	xlim((-1.5,1.5))
	ylim((-1.5,1.5))
	xlabel('Real')
	ylabel('Imaginary')	
	plt.show()
	return cmath.log(result,base).real,abs(result)
	

#print(average((12,15,13,9,16)))
#print(average((358,1,359,355,2)))
#print(average((210,290,10,90,170)))

(average(((12,1),(15,1),(13,1),(9,1),(16,1))))
