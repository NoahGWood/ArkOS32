# ArkOS32
## Welcome to ArkOS-32bit!
 Right now our operating system is very small, just enough to display a line or two of text and loop until interrupted.
 ![Alt text](/images/grub_screen.png?raw=true "short and sweet")
 ![Alt text](/images/OS.png?raw=true "short and sweet")
## Pre-requisites:
 The included iso should run on any x86 computer.
 If you want to make changes to the source code you'll need to do some work.

### Dev requirements:
 (incomplete)

## I want to steal your code!
 Go for it! All files uploaded here are open sourced and unlicensed with the exception of GRUB which contains its' own license.

## How do I make it mine/reskin your OS?
 In order to reskin the OS you will need to ensure you have all the Dev Requirements satisfied.
 
 After you have satisfied the dependencies, the first thing you will want to do is rename the OS. This can be done with the following terminal commands:

```
$ cd /path/to/ArkOS
$ grep -lr --exclude-dir=".git" -e "arkos" . | xargs sed -i "s/arkos/YOUR_NAME_HERE/g"
```

Next, the easiest way to build and run your new OS is to use the following command:

```
$ ./qemu.sh
```

Congratulations! You now have a bootable "Operating System", feel free to edit, modify, and hack to your heart's content

## I need help!
I recommend consulting the [OS Dev Wiki](http://wiki.osdev.org); they have a wealth of information available and very in-depth tutorials. Don't forget, it is a wiki which means revisions are saved for review; if you're stuck on a problem it doesn't hurt to scan the previous revisions to see if anyone had a similar issue and work around before.
