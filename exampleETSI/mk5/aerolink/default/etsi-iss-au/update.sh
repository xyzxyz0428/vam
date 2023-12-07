#!/bin/sh
# Update for AU ISS (AA9B82A729332692)

set -x

# CA is in the ACTL, which is stored locally
cp ../aerolink/default/etsi-iss-au/TLM.oer tlm
cp ../aerolink/default/etsi-iss-au/ACTL.oer ectl

# Get CRL/CTL for this CA
wget --no-verbose https://dc.prod.au.c2x.isscms.com/getctl/AA9B82A729332692 -O ctl
wget --no-verbose https://dc.prod.au.c2x.isscms.com/getcrl/AA9B82A729332692 -O crl

