from matplotlib import pyplot as plt

serial_file_SDS = 0
serial_algo_SDS = 0
serial_file_MDS = 0
serial_algo_MDS = 0
serial_file_BDS = 0
serial_algo_BDS = 0

parallel_1_file_SDS = []
parallel_1_algo_SDS = []
parallel_1_file_MDS = []
parallel_1_algo_MDS = []
parallel_1_file_BDS = []
parallel_1_algo_BDS = []

parallel_2_file_SDS = []
parallel_2_algo_SDS = []
parallel_2_file_MDS = []
parallel_2_algo_MDS = []
parallel_2_file_BDS = []
parallel_2_algo_BDS = []

parallel_1_file_HD = [0.08, 0.03, 0.03]
parallel_1_algo_HD = [304, 166, 83]

parallel_2_file_HD = [0.02, 0.01, 0.007]
parallel_2_algo_HD = [17, 15, 12]

version = 0
dataset = 0

with open('../results_formatted.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break

        if(line.strip() == 'v'):
            version += 1
            dataset = 0
            continue
        
        if(line.strip() == 'd'):
            dataset += 1
            continue

        words = line.strip().split("-")

        if(version == 0):
            if(dataset == 0):
                serial_file_SDS = float(words[0])
                serial_algo_SDS = int(words[1])
            if(dataset == 1):
                serial_file_MDS = float(words[0])
                serial_algo_MDS = int(words[1])
            if(dataset == 2):
                serial_file_BDS = float(words[0])
                serial_algo_BDS = int(words[1])
        
        if(version == 1):
            if(dataset == 0):
                parallel_1_file_SDS.append(float(words[0]))
                parallel_1_algo_SDS.append(int(words[1]))
            if(dataset == 1):
                parallel_1_file_MDS.append(float(words[0]))
                parallel_1_algo_MDS.append(int(words[1]))
            if(dataset == 2):
                parallel_1_file_BDS.append(float(words[0]))
                parallel_1_algo_BDS.append(int(words[1]))

        if(version == 2):
            if(dataset == 0):
                parallel_2_file_SDS.append(float(words[0]))
                parallel_2_algo_SDS.append(int(words[1]))
            if(dataset == 1):
                parallel_2_file_MDS.append(float(words[0]))
                parallel_2_algo_MDS.append(int(words[1]))
            if(dataset == 2):
                parallel_2_file_BDS.append(float(words[0]))
                parallel_2_algo_BDS.append(int(words[1]))

x_ticks = [1, 2, 4, 8, 16, 32, 64]
x_values = [2, 4, 8, 16, 32, 64]
x_ticks_HD = [2, 4, 8]

# SMALL DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot([0], [serial_file_SDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_1_file_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_2_file_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks)), x_ticks)
file.set_xlim(-0.5, len(x_ticks) - 0.5)

file.set_title('Small dataset file reading time') 
file.legend()

algo.plot([0], [serial_algo_SDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_1_algo_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_2_algo_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks)), x_ticks)
algo.set_xlim(-0.5, len(x_ticks) - 0.5)

algo.set_title('Small dataset algorithm time') 
algo.legend()
  
plt.show() 

# MEDIUM DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot([0], [serial_file_MDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_1_file_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_2_file_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks)), x_ticks)
file.set_xlim(-0.5, len(x_ticks) - 0.5)

file.set_title('Medium dataset file reading time') 
file.legend()

algo.plot([0], [serial_algo_MDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_1_algo_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_2_algo_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks)), x_ticks)
algo.set_xlim(-0.5, len(x_ticks) - 0.5)

algo.set_title('Medium dataset algorithm time') 
algo.legend()
  
plt.show() 

# BIG DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot([0], [serial_file_BDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_1_file_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(1, len(x_values) + 1), parallel_2_file_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks)), x_ticks)
file.set_xlim(-0.5, len(x_ticks) - 0.5)

file.set_title('Big dataset file reading time') 
file.legend()

algo.plot([0], [serial_algo_BDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_1_algo_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(1, len(x_values) + 1), parallel_2_algo_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks)), x_ticks)
algo.set_xlim(-0.5, len(x_ticks) - 0.5)

algo.set_title('Big dataset algorithm time') 
algo.legend()
  
plt.show() 

# HIGH DIMENSIONAL DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(len(x_ticks_HD)), parallel_1_file_HD, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(len(x_ticks_HD)), parallel_2_file_HD, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
file.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

file.set_title('High dimensional dataset file reading time') 
file.legend()

algo.plot(range(len(x_ticks_HD)), parallel_1_algo_HD, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(len(x_ticks_HD)), parallel_2_algo_HD, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
algo.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

algo.set_title('High dimensional dataset algorithm time') 
algo.legend()
  
plt.show() 