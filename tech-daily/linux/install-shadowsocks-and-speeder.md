# 1. Install and config Shadowsocks.
```sh
apt-get install python-pip
pip install shadowsocks
vi /etc/shadowsocks.json
# here is the configuration schema of shadowsocks.json.
{
    "port_password": {
        "port number": "your password",
        // if need others port
        "port number2": "your password", 
        ...
    },
    "method": "rc4-md5", // rc4 may faster than aes
    "timeout": 300
}
```

# 2. Install the cracked version of RuiSu speeder.
For more information about the speeder you can see: https://www.91yun.org/archives/683.
```sh
# Search for the a suitable linux kernel version listed in https://www.91yun.org/serverspeeder91yun, then copy a command.
your copied command
# or run the common command below.
wget -N --no-check-certificate https://github.com/91yun/serverspeeder/raw/master/serverspeeder.sh && bash serverspeeder.sh
```
> **Notice:**  
  If you can't find a suitable linux kernel version for RuiSu speeder, you'd better manually change your linux kernel version.
```sh
# Search images
apt-cache search linux-image-you-want

# Install the image you chose. e.g. `linux-image-4.2.0-35-generic`
apt-get install linux-image-4.2.0-35-generic

# List all the images in your host
dpkg -l|grep linux-image

# Remove all except your need
sudo apt-get purge linux-image-3.16.0-36-generic linux-image-extra-3.16.0-36-generic

# Update grup file then reboot
update-grub
reboot
```

# 3. now you can run your ssserver
```sh
ssserver -c /etc/shadowsocks.json -d start
```
