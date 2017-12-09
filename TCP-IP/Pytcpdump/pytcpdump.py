import commands
import re

deviceitem = range(10) 
devicelist = commands.getstatusoutput('ifconfig -s')
lines = re.split('\n',devicelist[1])

print "Pytcpdump ,a python wrapper for the shell tcpdump."
print "Select a interface to listen: "

for i in range(1,len(lines)):
    pattern = re.compile(r'^\w*')
    match = pattern.match(lines[i])
    deviceitem[i] = match.group()
    print ("%d. %s"%(i,match.group()))
index = input()
maxnum = input("Input a number for capturing")
def listen(device):
    #content = commands.getstatusoutput('sudo tcpdump -A -vvv -s0 -n -c 4 -i '+ device+' host 192.168.31.128'+' and port 80' )
    content = commands.getstatusoutput('sudo tcpdump -t -s0 -n -c '+str(maxnum)+' -i '+ device )


    hostcount = dict() 
    lines = re.split('\n',content[1])
    slines = range(len(lines)) 
    for i in range(len(lines)):
        slines[i] = re.split('\s',lines[i])
        if(slines[i][0] =="IP"):
            #print lines[i]
            pattern = re.compile(r'^\d*.\d*.\d*.\d*')
            match = pattern.match(slines[i][1])
            if(match.group() in hostcount):
                hostcount[match.group()].append(lines[i])
            else:
                tmp = list()
                tmp.append(lines[i])
                hostcount[match.group()] = tmp
    for k in hostcount:
        print ("\n### Source Host: %s        Count: %d  ###"%(k,len(hostcount[k])))
        print "Detail:"        
        for it in hostcount[k]:
            print it 

listen(deviceitem[index])
# just for test :remote change
