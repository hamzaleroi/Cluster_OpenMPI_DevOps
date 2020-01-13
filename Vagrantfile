Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.provider  "virtualbox" do |vb| 
    vb.memory = "256"
    vb.gui = false
  end
  config.ssh.password = "vagrant"
  config.vm.synced_folder "./mpi_program", "/mpi_program", type: "nfs", mode: "0666"
  config.vm.define "node1" do |node|
    node.vm.network "private_network", ip:"10.0.0.6"
  end
  config.vm.define "master" do |node|
    node.vm.network "private_network", ip:"10.0.0.5"
    node.vm.provision "ansible" do |ansible|
      ansible.playbook = "site.yml"
      ansible.limit = "all"
      ansible.vault_password_file = "password"
    end
  end
end