#!/bin/sh
# Update for 1_CTAG-2-ROOT-CA_L0 (BA23FBBEB9388FAA)

# CTAG PKI is in the ECTL
./fetch-cpoc.sh

set -x

# Get CRL/CTL for this CA
wget --no-verbose http://1.ctag-dc.l0.siscoga4cad.com/DC/getcrl/BA23FBBEB9388FAA -O crl
wget --no-verbose http://1.ctag-dc.l0.siscoga4cad.com/DC/getctl/BA23FBBEB9388FAA -O ctl

