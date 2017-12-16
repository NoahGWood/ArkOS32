# ArkOS32

## Welcome to ArkOS-32bit!
 Right now our operating system is very small, just enough to display a line or two of text and loop until interrupted.

## Pre-requisites:
 The included iso should run on any x86 computer.
 If you want to make changes to the source code you'll need to do some work.

### Dev requirements:


## I want to steal your code!
 Go for it! All files uploaded here are completely open sourced and unlicensed.

## How do I make it mine/reskin your OS?
 In order to reskin the OS you will need to 
     cd /path/to/ArkOS
     grep -lr --exclude-dir=".git" -e "arkos" . | xargs sed -i "s/arkos/YOUR_NAME_HERE/g"


