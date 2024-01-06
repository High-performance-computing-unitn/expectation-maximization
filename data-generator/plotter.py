from matplotlib import pyplot as plt
import math

x_values = [1, 2, 4, 8, 16, 32, 64]
x_values_HD = [2, 4, 8, 16, 32, 64]

#Parallel 1 small dataset data
parallel_1_S_pack = [248.1, 123.8, 62.2, 34, 17.5, 8.3, 8.5]
parallel_1_S_pack_excl = [199.2, 108.2, 50.34, 34.6, 16.1, 9.5, 4.5]
parallel_1_S_scatter = []
parallel_1_S_scatter_excl = []

#Parallel 1 medium dataset data
parallel_1_M_pack = [541.3, 250.6, 125.9, 63.7, 31.3, 19.3, 10.2]
parallel_1_M_pack_excl = [540, 248.9, 125.8, 75.4, 37.3, 24, 11.2]
parallel_1_M_scatter = []
parallel_1_M_scatter_excl = []

#Parallel 1 big dataset data
parallel_1_B_pack = []
parallel_1_B_pack_excl = []
parallel_1_B_scatter = []
parallel_1_B_scatter_excl = []

#Parallel 1 small dataset speedup
parallel_1_S_pack_speedup = [parallel_1_S_pack[0] / element for element in parallel_1_S_pack]
parallel_1_S_pack_excl_speedup = [parallel_1_S_pack_excl[0] / element for element in parallel_1_S_pack_excl]
parallel_1_S_scatter_speedup = [parallel_1_S_scatter[0] / element for element in parallel_1_S_scatter]
parallel_1_S_scatter_excl_speedup = [parallel_1_S_scatter_excl[0] / element for element in parallel_1_S_scatter_excl]

#Parallel 1 medium dataset speedup
parallel_1_M_pack_speedup = [parallel_1_M_pack[0] / element for element in parallel_1_M_pack]
parallel_1_M_pack_excl_speedup = [parallel_1_M_pack_excl[0] / element for element in parallel_1_M_pack_excl]
parallel_1_M_scatter_speedup = [parallel_1_M_scatter[0] / element for element in parallel_1_M_scatter]
parallel_1_M_scatter_excl_speedup = [parallel_1_M_scatter_excl[0] / element for element in parallel_1_M_scatter_excl]

#Parallel 1 big dataset speedup
parallel_1_B_pack_speedup = [parallel_1_B_pack[0] / element for element in parallel_1_B_pack]
parallel_1_B_pack_excl_speedup = [parallel_1_B_pack_excl[0] / element for element in parallel_1_B_pack_excl]
parallel_1_B_scatter_speedup = [parallel_1_B_scatter[0] / element for element in parallel_1_B_scatter]
parallel_1_B_scatter_excl_speedup = [parallel_1_B_scatter_excl[0] / element for element in parallel_1_B_scatter_excl]

#Parallel 1 small dataset efficiency
parallel_1_S_pack_efficiency = [parallel_1_S_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_S_pack_speedup))]
parallel_1_S_pack_excl_efficiency = [parallel_1_S_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_S_pack_excl_speedup))]
parallel_1_S_scatter_efficiency = [parallel_1_S_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_S_scatter_speedup))]
parallel_1_S_scatter_excl_efficiency = [parallel_1_S_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_S_scatter_excl_speedup))]

#Parallel 1 medium dataset efficiency
parallel_1_M_pack_efficiency = [parallel_1_M_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_M_pack_speedup))]
parallel_1_M_pack_excl_efficiency = [parallel_1_M_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_M_pack_excl_speedup))]
parallel_1_M_scatter_efficiency = [parallel_1_M_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_M_scatter_speedup))]
parallel_1_M_scatter_excl_efficiency = [parallel_1_M_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_M_scatter_excl_speedup))]

#Parallel 1 big dataset efficiency
parallel_1_B_pack_efficiency = [parallel_1_B_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_B_pack_speedup))]
parallel_1_B_pack_excl_efficiency = [parallel_1_B_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_B_pack_excl_speedup))]
parallel_1_B_scatter_efficiency = [parallel_1_B_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_B_scatter_speedup))]
parallel_1_B_scatter_excl_efficiency = [parallel_1_B_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_B_scatter_excl_speedup))]


print("PARALLEL 1 DATA")

print("SMALL DATASET")

print("packed")
print(parallel_1_S_pack)
print(parallel_1_S_pack_speedup)
print(parallel_1_S_pack_efficiency)

print("packed exclusive")
print(parallel_1_S_pack_excl)
print(parallel_1_S_pack_excl_speedup)
print(parallel_1_S_pack_excl_efficiency)

print("scattered")
print(parallel_1_S_scatter)
print(parallel_1_S_scatter_speedup)
print(parallel_1_S_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_S_scatter_excl)
print(parallel_1_S_scatter_excl_speedup)
print(parallel_1_S_scatter_excl_efficiency)

print("MEDIUM DATASET")

print("packed")
print(parallel_1_M_pack)
print(parallel_1_M_pack_speedup)
print(parallel_1_M_pack_efficiency)

print("packed exclusive")
print(parallel_1_M_pack_excl)
print(parallel_1_M_pack_excl_speedup)
print(parallel_1_M_pack_excl_efficiency)

print("scattered")
print(parallel_1_M_scatter)
print(parallel_1_M_scatter_speedup)
print(parallel_1_M_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_M_scatter_excl)
print(parallel_1_M_scatter_excl_speedup)
print(parallel_1_M_scatter_excl_efficiency)

print("BIG DATASET")

print("packed")
print(parallel_1_B_pack)
print(parallel_1_B_pack_speedup)
print(parallel_1_B_pack_efficiency)

print("packed exclusive")
print(parallel_1_B_pack_excl)
print(parallel_1_B_pack_excl_speedup)
print(parallel_1_B_pack_excl_efficiency)

print("scattered")
print(parallel_1_B_scatter)
print(parallel_1_B_scatter_speedup)
print(parallel_1_B_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_B_scatter_excl)
print(parallel_1_B_scatter_excl_speedup)
print(parallel_1_B_scatter_excl_efficiency)

#Parallel 2 small dataset data
parallel_2_S_pack = []
parallel_2_S_pack_excl = []
parallel_2_S_scatter = []
parallel_2_S_scatter_excl = []

#Parallel 2 medium dataset data
parallel_2_M_pack = []
parallel_2_M_pack_excl = []
parallel_2_M_scatter = []
parallel_2_M_scatter_excl = []

#Parallel 2 big dataset data
parallel_2_B_pack = []
parallel_2_B_pack_excl = []
parallel_2_B_scatter = []
parallel_2_B_scatter_excl = []

#Parallel 2 small dataset speedup
parallel_2_S_pack_speedup = [parallel_2_S_pack[0] / element for element in parallel_2_S_pack]
parallel_2_S_pack_excl_speedup = [parallel_2_S_pack_excl[0] / element for element in parallel_2_S_pack_excl]
parallel_2_S_scatter_speedup = [parallel_2_S_scatter[0] / element for element in parallel_2_S_scatter]
parallel_2_S_scatter_excl_speedup = [parallel_2_S_scatter_excl[0] / element for element in parallel_2_S_scatter_excl]

#Parallel 2 medium dataset speedup
parallel_2_M_pack_speedup = [parallel_2_M_pack[0] / element for element in parallel_2_M_pack]
parallel_2_M_pack_excl_speedup = [parallel_2_M_pack_excl[0] / element for element in parallel_2_M_pack_excl]
parallel_2_M_scatter_speedup = [parallel_2_M_scatter[0] / element for element in parallel_2_M_scatter]
parallel_2_M_scatter_excl_speedup = [parallel_2_M_scatter_excl[0] / element for element in parallel_2_M_scatter_excl]

#Parallel 2 big dataset speedup
parallel_2_B_pack_speedup = [parallel_2_B_pack[0] / element for element in parallel_2_B_pack]
parallel_2_B_pack_excl_speedup = [parallel_2_B_pack_excl[0] / element for element in parallel_2_B_pack_excl]
parallel_2_B_scatter_speedup = [parallel_2_B_scatter[0] / element for element in parallel_2_B_scatter]
parallel_2_B_scatter_excl_speedup = [parallel_2_B_scatter_excl[0] / element for element in parallel_2_B_scatter_excl]

#Parallel 2 small dataset efficiency
parallel_2_S_pack_efficiency = [parallel_2_S_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_S_pack_speedup))]
parallel_2_S_pack_excl_efficiency = [parallel_2_S_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_S_pack_excl_speedup))]
parallel_2_S_scatter_efficiency = [parallel_2_S_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_S_scatter_speedup))]
parallel_2_S_scatter_excl_efficiency = [parallel_2_S_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_S_scatter_excl_speedup))]

#Parallel 2 medium dataset efficiency
parallel_2_M_pack_efficiency = [parallel_2_M_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_M_pack_speedup))]
parallel_2_M_pack_excl_efficiency = [parallel_2_M_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_M_pack_excl_speedup))]
parallel_2_M_scatter_efficiency = [parallel_2_M_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_M_scatter_speedup))]
parallel_2_M_scatter_excl_efficiency = [parallel_2_M_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_M_scatter_excl_speedup))]

#Parallel 2 big dataset efficiency
parallel_2_B_pack_efficiency = [parallel_2_B_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_B_pack_speedup))]
parallel_2_B_pack_excl_efficiency = [parallel_2_B_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_B_pack_excl_speedup))]
parallel_2_B_scatter_efficiency = [parallel_2_B_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_B_scatter_speedup))]
parallel_2_B_scatter_excl_efficiency = [parallel_2_B_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_B_scatter_excl_speedup))]

print("PARALLEL 2 DATA")

print("SMALL DATASET")

print("packed")
print(parallel_2_S_pack)
print(parallel_2_S_pack_speedup)
print(parallel_2_S_pack_efficiency)

print("packed exclusive")
print(parallel_2_S_pack_excl)
print(parallel_2_S_pack_excl_speedup)
print(parallel_2_S_pack_excl_efficiency)

print("scattered")
print(parallel_2_S_scatter)
print(parallel_2_S_scatter_speedup)
print(parallel_2_S_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_S_scatter_excl)
print(parallel_2_S_scatter_excl_speedup)
print(parallel_2_S_scatter_excl_efficiency)

print("MEDIUM DATASET")

print("packed")
print(parallel_2_M_pack)
print(parallel_2_M_pack_speedup)
print(parallel_2_M_pack_efficiency)

print("packed exclusive")
print(parallel_2_M_pack_excl)
print(parallel_2_M_pack_excl_speedup)
print(parallel_2_M_pack_excl_efficiency)

print("scattered")
print(parallel_2_M_scatter)
print(parallel_2_M_scatter_speedup)
print(parallel_2_M_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_M_scatter_excl)
print(parallel_2_M_scatter_excl_speedup)
print(parallel_2_M_scatter_excl_efficiency)

print("BIG DATASET")

print("packed")
print(parallel_2_B_pack)
print(parallel_2_B_pack_speedup)
print(parallel_2_B_pack_efficiency)

print("packed exclusive")
print(parallel_2_B_pack_excl)
print(parallel_2_B_pack_excl_speedup)
print(parallel_2_B_pack_excl_efficiency)

print("scattered")
print(parallel_2_B_scatter)
print(parallel_2_B_scatter_speedup)
print(parallel_2_B_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_B_scatter_excl)
print(parallel_2_B_scatter_excl_speedup)
print(parallel_2_B_scatter_excl_efficiency)

#Parallel 1 high dim dataset data
parallel_1_6D = [304, 166, 83, 42, 20, 19]
parallel_1_8D = [4347, 2032, 1476, 705, 415, 114]

#Parallel 2 high dim dataset data
parallel_2_6D = [17, 15, 12, 7, 4, 8]
parallel_2_8D = [4.6, 4.4, 2.3, 2.4, 0.7, 1]

#parallel_1_file_6D = [0.08, 0.03, 0.03, 0.15, 0.03, 0.14]
#parallel_2_file_6D = [0.02, 0.01, 0.007, 0.01, 0.02, 0.01]
#parallel_1_file_8D = [0.03, 0.04, 0.01, 0.3, 0.008, 0.008]
#parallel_2_file_8D = [0.006, 0.003, 0.005, 0.005, 0.02, 0.006] 


#Parallel 1 small dataset data log
parallel_1_S_pack_l = [math.log(x) for x in parallel_1_S_pack]
parallel_1_S_pack_excl_l = [math.log(x) for x in parallel_1_S_pack_excl]
parallel_1_S_scatter_l = [math.log(x) for x in parallel_1_S_scatter]
parallel_1_S_scatter_excl_l = [math.log(x) for x in parallel_1_S_scatter_excl]

#Parallel 1 medium dataset data log
parallel_1_M_pack_l = [math.log(x) for x in parallel_1_M_pack]
parallel_1_M_pack_excl_l = [math.log(x) for x in parallel_1_M_pack_excl]
parallel_1_M_scatter_l = [math.log(x) for x in parallel_1_M_scatter]
parallel_1_M_scatter_excl_l = [math.log(x) for x in parallel_1_M_scatter_excl]

#Parallel 1 big dataset data log
parallel_1_B_pack_l = [math.log(x) for x in parallel_1_B_pack]
parallel_1_B_pack_excl_l = [math.log(x) for x in parallel_1_B_pack_excl]
parallel_1_B_scatter_l = [math.log(x) for x in parallel_1_B_scatter]
parallel_1_B_scatter_excl_l = [math.log(x) for x in parallel_1_B_scatter_excl]


#Parallel 2 small dataset data log
parallel_2_S_pack_l = [math.log(x) for x in parallel_2_S_pack]
parallel_2_S_pack_excl_l = [math.log(x) for x in parallel_2_S_pack_excl]
parallel_2_S_scatter_l = [math.log(x) for x in parallel_2_S_scatter]
parallel_2_S_scatter_excl_l = [math.log(x) for x in parallel_2_S_scatter_excl]

#Parallel 2 medium dataset data log
parallel_2_M_pack_l = [math.log(x) for x in parallel_2_M_pack]
parallel_2_M_pack_excl_l = [math.log(x) for x in parallel_2_M_pack_excl]
parallel_2_M_scatter_l = [math.log(x) for x in parallel_2_M_scatter]
parallel_2_M_scatter_excl_l = [math.log(x) for x in parallel_2_M_scatter_excl]

#Parallel 2 big dataset data log
parallel_2_B_pack_l = [math.log(x) for x in parallel_2_B_pack]
parallel_2_B_pack_excl_l = [math.log(x) for x in parallel_2_B_pack_excl]
parallel_2_B_scatter_l = [math.log(x) for x in parallel_2_B_scatter]
parallel_2_B_scatter_excl_l = [math.log(x) for x in parallel_2_B_scatter_excl]


########################
# TIME PLOT PARALLEL 1 #
########################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_1_S_pack_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_M_pack_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_B_pack_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('seconds') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_1_S_pack_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_M_pack_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_B_pack_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('seconds') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_1_S_scatter_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_M_scatter_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_B_scatter_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('seconds') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_1_S_scatter_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_M_scatter_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_B_scatter_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('seconds') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 1st implementation execution time over different configurations')
plt.show() 

########################
# TIME PLOT PARALLEL 2 #
########################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_2_S_pack_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_M_pack_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_B_pack_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('seconds') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_2_S_pack_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_M_pack_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_B_pack_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('seconds') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_2_S_scatter_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_M_scatter_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_B_scatter_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('seconds') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_2_S_scatter_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_M_scatter_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_B_scatter_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('seconds') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 2nd implementation execution time over different configurations')
plt.show() 

###########################
# SPEEDUP PLOT PARALLEL 1 #
###########################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_1_S_pack_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_M_pack_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_B_pack_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('speedup') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_1_S_pack_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_M_pack_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_B_pack_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('speedup') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_1_S_scatter_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_M_scatter_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_B_scatter_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('speedup') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_1_S_scatter_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_M_scatter_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_B_scatter_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('speedup') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 1st implementation speedup over different configurations')
plt.show() 

##############################
# EFFICIENCY PLOT PARALLEL 1 #
##############################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_1_S_pack_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_M_pack_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_1_B_pack_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('efficiency') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_1_S_pack_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_M_pack_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_1_B_pack_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('efficiency') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_1_S_scatter_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_M_scatter_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_1_B_scatter_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('efficiency') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_1_S_scatter_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_M_scatter_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_1_B_scatter_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('efficiency') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 1st implementation efficiency over different configurations')
plt.show() 


###########################
# SPEEDUP PLOT PARALLEL 2 #
###########################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_2_S_pack_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_M_pack_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_B_pack_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('speedup') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_2_S_pack_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_M_pack_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_B_pack_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('speedup') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_2_S_scatter_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_M_scatter_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_B_scatter_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('speedup') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_2_S_scatter_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_M_scatter_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_B_scatter_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('speedup') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 2nd implementation speedup over different configurations')
plt.show() 

##############################
# EFFICIENCY PLOT PARALLEL 2 #
##############################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (packed, packedexcl, scatter, scatterexcl) = plt.subplots(2, 2)

packed.plot(range(0, len(x_values)), parallel_2_S_pack_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_M_pack_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packed.plot(range(0, len(x_values)), parallel_2_B_pack_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packed.set_xlabel('processes') 
packed.set_ylabel('efficiency') 

packed.set_xticks(range(len(x_values)), x_values)
packed.set_xlim(-0.5, len(x_values) - 0.5)

packed.set_title('Packed') 
packed.legend()

packedexcl.plot(range(0, len(x_values)), parallel_2_S_pack_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_M_pack_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
packedexcl.plot(range(0, len(x_values)), parallel_2_B_pack_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

packedexcl.set_xlabel('processes') 
packedexcl.set_ylabel('efficiency') 

packedexcl.set_xticks(range(len(x_values)), x_values)
packedexcl.set_xlim(-0.5, len(x_values) - 0.5)

packedexcl.set_title('Packed exclusive') 
packedexcl.legend()

scatter.plot(range(0, len(x_values)), parallel_2_S_scatter_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_M_scatter_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatter.plot(range(0, len(x_values)), parallel_2_B_scatter_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatter.set_xlabel('processes') 
scatter.set_ylabel('efficiency') 

scatter.set_xticks(range(len(x_values)), x_values)
scatter.set_xlim(-0.5, len(x_values) - 0.5)

scatter.set_title('Scattered') 
scatter.legend()

scatterexcl.plot(range(0, len(x_values)), parallel_2_S_scatter_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_M_scatter_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
scatterexcl.plot(range(0, len(x_values)), parallel_2_B_scatter_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

scatterexcl.set_xlabel('processes') 
scatterexcl.set_ylabel('efficiency') 

scatterexcl.set_xticks(range(len(x_values)), x_values)
scatterexcl.set_xlim(-0.5, len(x_values) - 0.5)

scatterexcl.set_title('Scattered exclusive') 
scatterexcl.legend()

plt.set_title('Parallel 2nd implementation efficiency over different configurations')
plt.show() 


#################################
# HIGH DIMENSIONAL DATASET PLOT #
#################################

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(len(x_values_HD)), parallel_1_6D, label = "parallel 1", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
file.plot(range(len(x_values_HD)), parallel_2_6D, label = "parallel 2", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_values_HD)), x_values_HD)
file.set_xlim(-0.5, len(x_values_HD) - 0.5)

file.set_title('Six dimensional dataset time') 
file.legend()

algo.plot(range(len(x_values_HD)), parallel_1_8D, label = "parallel 1", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
algo.plot(range(len(x_values_HD)), parallel_2_8D, label = "parallel 2", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_values_HD)), x_values_HD)
algo.set_xlim(-0.5, len(x_values_HD) - 0.5)

algo.set_title('Eight dimensional dataset time') 
algo.legend()
  
plt.set_title('Comparison between two implementations on high dimensional datasets')
plt.show() 