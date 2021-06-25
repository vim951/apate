# apate

## Use case

Apate is a linux software that performs various anti-debugging, anti-VM, and anti- "fake" (i.e. a computer only used for analysis), to help you improve your setup, and stay under the radar.

## Options

There are two options that you can specify, to tune the output of apate:
* Verbose (-v): print details when a test fails
* Compact (-c): only display test that have failed

Those two parameters can be combined.

## List of tests performed

### Anti-debugging

* Checks existence of LINES and COLUMNS environment variables.
* Checks for breakpoint in _dl_debug_state.
* Compares beginning of the heap to address of own BSS.
* Checks base address of ELF and shared libraries for hard-coded values used by GDB.
* Checks if parent's name is gdb, lldb, strace or ltrace.
* Tries to debug itself by calling ptrace.
* Measures distance of vdso and stack.

Credits: those tests are from [debugmenot](https://github.com/kirschju/debugmenot).

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
