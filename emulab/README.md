# Emulab

To set up ATS on Emulab, follow the steps below:

1. Go to Emulab.Net. Under Experimentation, select Begin an Experiment.
2. Fill out relevant fields and provide the file path to client-server.ns.
3. Once the experiment has been successfully started, SSH into server.[_NAME_OF_EXPERIMENT_].comp150.emulab.net.
4. Run ubuntuEC2_setup.sh to install ATS. Configure it as a forward proxy.
5. SSH into client.[_NAME_OF_EXPERIMENT_].comp150.emulab.net and route all HTTP traffic through the proxy.


### client-server.ns

Network simulation script for Emulab
