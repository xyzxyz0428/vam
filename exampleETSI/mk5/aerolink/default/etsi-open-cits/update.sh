#!/bin/sh
# Update for Open C-ITS Test PKI Root CA (546B0D01F5EF855C)

# CA is in the ECTL
./fetch-cpoc.sh

set -x

# Get CRL/CTL for this CA
wget --no-verbose https://via.teskalabs.com/cits-otenv/v1.3/dc/getctl/546B0D01F5EF855C -O ctl
wget --no-verbose https://via.teskalabs.com/cits-otenv/v1.3/dc/getcrl/546B0D01F5EF855C -O crl

