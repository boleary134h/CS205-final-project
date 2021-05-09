import numpy as np
import matplotlib.pyplot as plt


# Main
if __name__ == '__main__':

    # serial results
    serial_time = 158.0393

    ######################################################
    ## MPI results
    ######################################################
    np_1 = [1,2,4]
    mpi_1_time = [serial_time,160.105,163.084]
    mpi_1_speedup = [serial_time/t for t in mpi_1_time]
    print('MPI speedup:',mpi_1_speedup)



    # Plot the results
    plt.plot(np_1, mpi_1_speedup,linestyle='--', marker='o', color='b')
    #plt.yscale('log')
    plt.xlabel('# Processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('MPI Speedup: Weak Scaling')
    plt.ylim(0.0,1.2)
    plt.savefig('mpi_speedup_plot_ws.png')
    plt.show()

    

    ######################################################
    ## Hybrid results
    ######################################################
    np_1 = [1,2,4,8]
    hybrid_1_time = [serial_time,318.669,323.245,323.847]
    hybrid_1_speedup = [serial_time/t for t in hybrid_1_time]
    print('Hybrid  speedup:',hybrid_1_speedup)

    # Plot the results
    plt.plot(np_1, hybrid_1_speedup,linestyle='--', marker='o', color='b')
    #plt.yscale('log')
    plt.xlabel('# Processes')
    plt.ylabel('Serial Time (sec) / Parallel Time (sec)')   
    plt.title('Hybrid Speedup: Weak Scaling')
    plt.ylim(0.0,1.2)
    plt.savefig('hybrid_speedup_plot_ws.png')
    plt.show()



