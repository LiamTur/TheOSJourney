.globl start_thread
start_thread:
    pop %eax           
    call *%eax         
    call thread_exit   

