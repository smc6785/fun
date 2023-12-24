'''
import os

def test_fork():
    pid = os.fork()
    if pid == 0:
        print('child')
    else:
        print('parent')

test_fork()
'''
import os

def system(cmd):
    pid = os.fork()
    if pid == 0:
        os.execv('/bin/sh', ['sh', '-c', cmd])
    else:
        return os.waitpid(pid, 0)

system('python3 --version')
