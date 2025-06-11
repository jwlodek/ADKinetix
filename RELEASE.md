# ADKinetix Releases

The latest untagged master branch can be obtained at https://github.com/NSLS-II/ADKinetix

Tagged source code releases can be obtained at https://github.com/NSLS-II/ADKinetix/releases

# Release Notes

### R1-2 (11-Jun-2025)

* Adding autoconverted bob file by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/13
* Fix typo in docs by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/14
* Remove library for 32 bit windows by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/15
* Remove incorrect comment in Makefile by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/16
* Fix typo when setting max size y by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/18
* Fix unique name for monitor thread by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/19
* Added some guards to prevent acquisition from starting while temperat… by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/20
* Fix formatting for integer values in writeInt32 by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/21
* Use value of ADAcquire parameter to determine whether or not to start… by @jwlodek in https://github.com/NSLS2/ADKinetix/pull/23

**Full Changelog**: https://github.com/NSLS2/ADKinetix/compare/R1-1...R1-2

### R1-1 (20-Aug-2024)

* Code cleanup & formatting
* Improve logging messages
* Allow for specifying minimum exposure resolution for sub 1 ms exposures.
* Add record for tracking connection mode.

### R1-0 (26-July-2024)

* Initial release of ADKinetix.
* Extensively tested on RH8, using both USB and PCIE connection modes.
* Ran camera at full speed over PCIE, with up to 300 Hz in `Speed` mode.
* Include expert OPI screen.
* Include documentation for confiugration.


