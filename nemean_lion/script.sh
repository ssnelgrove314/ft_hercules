#!/bin/bash
apt-get update && apt-get upgrade -y
apt-get install openssh-server -y
PORT_NUMBER="9123"
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak
sed -i "s/#Port 22/Port $PORT_NUMBER/g" /etc/ssh/sshd_config
echo "New sshport $PORT_NUMBER"
/etc/init.d/ssh restart
service sshd status
