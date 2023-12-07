#!/bin/sh
# Update for CPOC
# Updated for 15 Mar 2022 release

set -x

# Fetch latest known TLM, then get latest ECTL signed by that TLM
wget --no-verbose https://cpoc.jrc.ec.europa.eu/L0/gettlmcertificate/1D261F9E338ECB5B -O tlm
wget --no-verbose https://cpoc.jrc.ec.europa.eu/L0/getectl/1D261F9E338ECB5B -O ectl

