import subprocess 

size=1000
max_size=500000
epochs = (int)((max_size - size) /1500)
structures = [1,2]
with open("results.csv","w+") as f:
  for j in structures:
    
    for i in range(epochs):
      proc = subprocess.Popen(['mpiexec', \
        '--mca', 'btl_tcp_if_include', 'eth1', \
          '--np', str(j),\
        '-hostfile', 'machines', \
          'parallel', str(size + i*100) ]\
            , stdout = subprocess.PIPE)

      out = proc.communicate()[0]
      array = out.decode('ascii').strip().split(',')
      if i == 0 and j == structures[0]: 
          f.write(','.join([array[i].split(':')[0].strip() for i in range(len(array))]) + '\n')
      f.write(','.join([array[i].split(':')[1].strip() for i in range(len(array))]) + '\n')

