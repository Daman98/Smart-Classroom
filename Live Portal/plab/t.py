from pexpect import pxssh
s = pxssh.pxssh()
if not s.login ('10.42.0.145', 'pi', 'raspberry'):
    print "SSH session failed on login."
    print str(s)
else:
    print "SSH session login successful"
    s.sendline ('mv 1.py Downloads/')
    s.prompt()         # match the prompt
    print s.before     # print everything before the prompt.
    s.logout()
    
#We can also execute multiple command like this:
# s.sendline ('uptime;df -h')