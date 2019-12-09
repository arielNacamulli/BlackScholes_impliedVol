# shift + alt + E
import numpy as np
import matplotlib.pyplot as plt

file = open("curve.txt", "r")
data = file.read()

strVec = data.split()
vecLen = int(len(strVec)/2)

K = np.zeros(vecLen)
sigma = np.zeros(vecLen)


for i in range(vecLen):
    K[i] = float(strVec[i*2])
    sigma[i] = float(strVec[i*2+1])

plt.plot(K, sigma)
