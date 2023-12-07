#!/bin/sh
# Update for Autostrade PKI Root (5E8245FF22FEB0D9)

set -x

wget --no-verbose http://autostrade.staging.cycurv2x.com/tlm/getectl/2E9F12E1B687E345 -O ectl

# TLM is in the ECTL
extractSignerTlmFromEctl --ectlFile ectl --outputFile tlm

# Get CRL/CTL for this CA
wget --no-verbose http://autostrade.staging.cycurv2x.com/dc/getctl/5E8245FF22FEB0D9 -O ctl
wget --no-verbose http://autostrade.staging.cycurv2x.com/dc/getcrl/5E8245FF22FEB0D9 -O crl

