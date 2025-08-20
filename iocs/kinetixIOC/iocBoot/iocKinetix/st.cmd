#!/bin/bash

# The SDK version is determined by environment variables, loaded from these files.
. /etc/profile.d/pvcam.sh
. /etc/profile.d/pvcam-sdk.sh

../../bin/linux-x86_64/kinetixApp st_base.cmd
