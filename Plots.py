import numpy as np 
import matplotlib.pyplot as plt
from scipy.io.wavfile import write 
from mpl_toolkits.mplot3d import axes3d
from matplotlib.animation import FuncAnimation




######################
######################
# Tambor
######################
######################
######################

Tambor = np.loadtxt("tambor.dat")
Ti = np.loadtxt("cond_ini_tambor.dat")
zlims = [-np.max(Ti), np.max(Ti)]

l = np.size(Tambor,0)
n = l/101
z1 = 0
z2 = int(n/2)
z3 = int(n/4)
z4 = int(n/8)
n = int(n)
print(z1, z2, z3, z4, n, l)
x = np.linspace(0,0.5,101)
y = np.linspace(0,0.5,101)
X,Y = np.meshgrid(x,y)



def actualiza(i, a):
	Z = Tambor[i*10:(i+1)*101,:]
	a.plot_surface(X,Y,Z, alpha = 0.8)

	a.set_xlabel('X')
	a.set_xlim(0, 0.5)
	a.set_ylabel('Y')
	a.set_ylim(0, 0.5)
	a.set_zlabel('Z')

#plt.figure()
#fig = plt.figure(figsize=(12,12))
#ax = fig.add_subplot(2, 2, 1, projection='3d')
#actualiza(z1, ax)
#ax = fig.add_subplot(2, 2, 2, projection='3d')
#actualiza(z2, ax)
#ax = fig.add_subplot(2, 2, 3, projection='3d')
#actualiza(z3, ax)
#ax = fig.add_subplot(2, 2, 4, projection='3d')
#actualiza(z4, ax)
#plt.savefig("Tiempos_Tambor.png")



def actualizar(i):
	i = i + i*50
	Z = Tambor[i*10:(i+1)*101,:]
	a.clear()
	a.plot_surface(X,Y,Z, alpha = 0.8)
	print(i)
	a.set_xlabel('X')
	a.set_xlim(0, 0.5)
	a.set_ylabel('Y')
	a.set_ylim(0, 0.5)
	a.set_zlabel('Z')
	a.set_zlim(zlims)
	a.set_title("Animacion tambor")

print("Graficando")
fig = plt.figure()
a = fig.gca(projection='3d')
#anim = FuncAnimation(fig, actualizar, frames=np.arange(0, 10))
#anim.save('Animacion_Tambor.gif', writer='imagemagick')


######################
######################
# Cuerda
######################
######################
######################



Ondas1 = np.loadtxt("Ondaextfijos.txt")
Ondas2 = np.loadtxt("Ondaperturbada.txt")

l=np.size(Ondas1,0)
m= np.size(Ondas2,0)


a0 = 0
a1 = int(l/2)
a2 = int(l/4)
a3 = int(l/8)
b0 = 0
b1 = int(m/2)
b2 = int(m/4)
b3 = int(m/8)

plt.figure()
plt.plot(Ondas1[a0,:])
plt.plot(Ondas1[a1,:])
plt.plot(Ondas1[a2,:])
plt.plot(Ondas1[a3,:])
plt.savefig("Extremos_fijos.png") 


plt.figure()
plt.plot(Ondas2[b0,:])
plt.plot(Ondas2[b1,:])
plt.plot(Ondas2[b2,:])
plt.plot(Ondas2[b3,:])
plt.savefig("Perturbada.png")


#Punto medio extreos fijos 

Pm = Ondas1[:,int(np.size(Ondas1,1)/2)]
write("sonido.wav",int(1/0.000018),Pm)






