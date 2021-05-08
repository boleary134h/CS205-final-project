import numpy as np
import matplotlib.pyplot as plt


# Main
if __name__ == '__main__':

    # serial results
    serial_time = 2305.43

    ######################################################
    ## MPI results
    ######################################################
    np_1 = [1,2,4]
    mpi_1_time = [serial_time,1164.98,576.182]
    mpi_1_speedup = [serial_time/t for t in mpi_1_time]
    print('MPI 1 instance speedup:',mpi_1_speedup)

    np_2 = [1,2,4,8]
    mpi_2_time = [serial_time,1609.11,802.049,403.478]
    mpi_2_speedup = [serial_time/t for t in mpi_2_time]
    print('MPI 2 instance speedup:',mpi_2_speedup)


    # Plot the results
    plt.plot(np_1, mpi_1_speedup, label='1 instance')
    plt.plot(np_2, mpi_2_speedup, label='2 instances')
    #plt.yscale('log')
    plt.xlabel('# Processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('MPI Speedup')
    plt.legend()
    plt.savefig('mpi_speedup_plot.png')
    plt.show()

    

    ######################################################
    ## Hybrid results
    ######################################################
    np_1 = [1,2,4,8]
    n_threads = 2
    hybrid_1_time = [serial_time,2323.35,1164.16,582.572]
    hybrid_1_speedup = [serial_time/t for t in hybrid_1_time]
    print('Hybrid 1 instance speedup:',hybrid_1_speedup)


    np_2 = [1,4,8,16]
    hybrid_2_time = [serial_time,1636.17,819.445,401.661]
    hybrid_2_speedup = [serial_time/t for t in hybrid_2_time]
    print('Hybrid 2 instance speedup:',hybrid_2_speedup)

    # Plot the results
    plt.plot(np_1, hybrid_1_speedup, label='1 instance')
    plt.plot(np_2, hybrid_2_speedup, label='2 instances')
    #plt.yscale('log')
    plt.xlabel('# Processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('Hybrid Speedup')
    plt.legend()
    plt.savefig('hybrid_speedup_plot.png')
    plt.show()



