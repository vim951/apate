# apate

Note: a pre-compiled binary (on Ubuntu 20.04.2 LTS) is available in the release section ([direct download](https://github.com/vim951/apate/releases/download/v1.0/apate)).

## Use case

Apate is a linux software that performs various anti-debugging, anti-VM, and anti-sandbox tricks, to help you improve your setup, and stay under the radar.

For example, here is the output when apate is attached to gdb:
![Screenshot using gdb](https://firebasestorage.googleapis.com/v0/b/publicsurls.appspot.com/o/Screenshot%20-%20gdb.png?alt=media&token=cfe7de43-60ef-4b39-98c9-863951274359)

And here is the output when apate is running inside a fresh VM:
![Screenshot in a VM](https://firebasestorage.googleapis.com/v0/b/publicsurls.appspot.com/o/Screenshot%20-%20VM.png?alt=media&token=1cc8f523-5087-430f-ad82-2ccae8c9fd72)

## Options

There are two options that you can specify, to tune the output of apate:
* Verbose (-v): print details when a test fails
* Compact (-c): only display test that have failed

Those two parameters can be combined.

Use -h for help if you ever forget those options.

## List of tests performed

### Anti-debugging

* Checks existence of LINES and COLUMNS environment variables.
* Checks for breakpoint in _dl_debug_state (note: not reliable).
* Compares beginning of the heap to address of own BSS.
* Checks base address of ELF and shared libraries for hard-coded values used by GDB.
* Checks if parent's name is gdb, lldb, strace or ltrace.
* Tries to debug itself by calling ptrace.
* Measures distance of vdso and stack.

Credits: those tests were adapted from [debugmenot](https://github.com/kirschju/debugmenot).

### Anti-VM

* Looks for the hypervisor flag in 'cpuinfo'.
* Inspects currently loaded modules.
* Looks for suspicious MAC addresses.
* Looks for suspicious SCSI devices.
* Looks for suspicious bios vendor.
* Looks for suspicious board vendor.
* Looks for suspicious product name.
* Looks for suspicious system vendors.
* Scans the content of '/usr/bin' for known VM names.
* Checks the screen resolution.
* Checks if the file system is bigger than 120GB.
* Checks if the system has at least 4GB of RAM.

### Anti-fake

* Inspects browsers histories
* Checks that the system has been running for at least 30 minutes
* Checks the coherence of system age

Note: all chrome/chromium windows must be closed for history inspection (otherwise the database is locked). This is not necessary for firefox windows.
