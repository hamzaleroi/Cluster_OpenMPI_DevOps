Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.provider  "virtualbox" do |vb| 
    vb.memory = "256"
    vb.gui = false
  end
  config.vm.define "node1" do |node|
    node.vm.network "public_network", ip:"10.0.0.5"
  end
  config.vm.define "node2" do |node|
    node.vm.network "public_network", ip:"10.0.0.6"
  end
end