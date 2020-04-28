Simple client/server UDP packets sender/receiver core module. Research test before performance measurement module.

Help:
Use: -s for Server mode
Use: -c for Client mode
Use: -a for target IP address
Use: -p for listening/send port number
Use: -n for number of bytes to be sent

Example Server: ./TinyNetPerf -a 127.0.0.1 -p 2020 -s
Example Client: ./TinyNetPerf -a 127.0.0.1 -p 2020 -n 1000 -c
