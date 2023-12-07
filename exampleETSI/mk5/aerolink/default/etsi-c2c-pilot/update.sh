#!/bin/sh
# Update for C2C-CC V2X Pilot PKI Root (4E31BB174A492DF6)

# CA is in the ECTL
./fetch-cpoc.sh

set -x

# Get CRL/CTL for this CA
wget --no-verbose http://c2ccc.v2x-pilot.escrypt.com/dc/getctl/4E31BB174A492DF6 -O ctl
wget --no-verbose http://c2ccc.v2x-pilot.escrypt.com/dc/getcrl/4E31BB174A492DF6 -O crl

