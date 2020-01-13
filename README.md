## Description of the project:  
It's a dynamic way of creating an OpenMPI cluster in which you can execute MPI code.
It has been created using DevOps tools to speed up, automate and allow reusability
of the Development Environement. To scale the project to a different extent simply
add your modification on one of the files and the rest will adapt automatically. The VMs are 
Ubuntu Trusty VMs which is fairly an old version of ubuntu, but it's enough to support all 
the functionalities.  
Some performance mesurement and analysis scripts are also provided.

## DevOps Tools Used:  
Ansible: Used for provisionning and configuration management  
Vagrant: Used to create the developement environement on which all the work will be applied  

## Tasks ensured by the project:  
* Create a user with an identifier "**mpi-user**" and password "**12345678**"
* Ensure the connection is passwordless
* Create Ansible inventory locally to allow any further configuration
* Ensure the hosts are considered known by the host
* Ensure the connection is passwordless between the VMs
* Install all the needed packages to work with openmpi; which are not shipped by default with ubuntu
* Naming working hosts in the master node; to allow referncing nodes with their names rather than their IP addresses.
* share a folder with the host machine, using NFS, which will contain the MPI programs. 
* A script for generating a dataset to use in jupyter notebook.


## Provisioning the VMs:  
To start working on the project, execute the following command:
```bash
vagrant up
```
This command will first create the VMs and then start the provisionning using Ansible which will do the rest of the job

## Setting Machines as known on the host:  

To do that simply execute the playbook `known_hosts.yml` using the command:
```bash
ansible-playbook known_hosts.yml --vault-password-file password
```  
## Configuring the VMs:  
After the provisionning comes the configuration. To do that here's the command to execute on a shell:  
```bash
ansible-playbook mpi.yml --vault-password-file password
```  
The password and the username has been encrypted inside the playbooks as part of the best practices; but it's not the case (I know) for 
the file password which have been left unencrypted to allow other users to use the playbooks (since this is a public repo). Ideally, you would store your passwords somewhere else safe. 

### Note:  
The access provided by `vagrant ssh` has been overloaded in the configuration phase and that's because 
the rsa key that has been configured is the one that has been generated for the new user __mpi-user__. You can still have access 
to these machines with that command; because the user still exists and the password for it is __vagrant__.  

## Working with OpenMPI:  
A folder has been created `/mpi-program`, which is a shared NFS folder. You can either code on the host or on the guets, but the execution will always be on the master node.

## Mesuring performance:  
In the shared folder, there exists 2 versions of a program that calculates the dot function of two vectors. One is sequential and the other is parallel. The parallel can be executed on the cluster. The parallel program can also be forced to be sequential if we execute it on one single node. There is also
a script for mesuring the performance of the cluster and that generates a data set. Th data set is next analysed in the Jupyter Notebook.
