import numpy as np
import matplotlib.pyplot as plt


# Main
if __name__ == '__main__':

    # serial results
    serial_time = 0.0

    ######################################################
    ## MPI results
    ######################################################
    np_1 = [1,2,4]
    mpi_1_time = [serial_time,50.8844,25.11,16.8283]
    mpi_1_speedup = [serial_time/t for t in mpi_1_time]

    np_2 = [1,2,4,6,8]
    mpi_2_time = [serial_time,50.8844,25.11,16.8283,0.0]
    mpi_2_speedup = [serial_time/t for t in mpi_2_time]

    # Plot the results
    plt.plot(np, mpi_1_speedup, label='1 instance')
    plt.plot(np, mpi_2_speedup, label='2 instances')
    #plt.yscale('log')
    plt.xlabel('# processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('MPI Speedup')
    plt.legend()
    plt.show()

    

    ######################################################
    ## Hybrid results
    ######################################################
    np_1 = [1,2,4]
    n_threads = 2
    hybrid_1_time = [serial_time,50.8844,25.11,16.8283]
    hybrid_1_speedup = [serial_time/t for t in mpi_1_time]

    np_2 = [1,2,4,6,8]
    hybrid_2_time = [serial_time,50.8844,25.11,16.8283,0.0]
    hybrid_2_speedup = [serial_time/t for t in mpi_2_time]

    # Plot the results
    plt.plot(np, hybrid_1_speedup, label='1 instance')
    plt.plot(np, hybrid_2_speedup, label='2 instances')
    #plt.yscale('log')
    plt.xlabel('# processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('MPI Speedup')
    plt.legend()
    plt.show()



