import matplotlib.pyplot as plt
import math
import numpy as np


#Generate line points
def line_gen(A,B):
  len =10
  dim = A.shape[0]
  x_AB = np.zeros((dim,len))
  lam_1 = np.linspace(0,1,len)
  for i in range(len):
    temp1 = A + lam_1[i]*(B-A)
    x_AB[:,i]= temp1.T
  return x_AB

#GIVEN POINTS

a=np.array([1,1])
b=np.array([3,5])
c=np.array([-2,4])
d=np.array([-1,-5])






#LINE GENERATIONS FOR PLOT

#SIDES OF A QUADRILATERAL

x_ab = line_gen(a,b)
print(x_ab)
x_bc = line_gen(b,c)
x_cd = line_gen(c,d)
x_da = line_gen(d,a)

# DIAGONALS OF QUADRILATERAL

x_ac = line_gen(a,c)
x_bd = line_gen(b,d)

# PLOTTING THE LINES

plt.plot(x_ab[0,:],x_ab[1,:], label="$AB$")
plt.plot(x_bc[0,:],x_bc[1,:], label="$BC$")
plt.plot(x_cd[0,:],x_cd[1,:], label="$CD$")
plt.plot(x_da[0,:],x_da[1,:], label="$DA$")
plt.plot(x_ac[0,:],x_ac[1,:], label="$AC$")
plt.plot(x_bd[0,:],x_bd[1,:], label="$BD$")

#ANNOTATIONS IN GRAPH
quad_coords = np.vstack((a,b,c,d)).T
plt.scatter(quad_coords[0,:], quad_coords[1,:])
vert_labels = ['A','B','C','D']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt, # this is the text
                 (quad_coords[0,i], quad_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

#plt.plot(x_values,y_values)
plt.grid()
plt.xlim(-10,10)
plt.ylim(-10,10)
plt.savefig('/home/user/txhome/storage/shared/github/training/math/figs/QUAD.png')
plt.show()