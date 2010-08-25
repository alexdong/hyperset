#!/bin/sh

cd gen-cpp
cp hyperset.cpp ../hyperset.cc
cp hyperset.h ../hyperset.h
cp hyperset_types.cpp ../hyperset_types.cc
cp hyperset_types.h ../

cd ..
cd gen-py
cp hyperset/hyperset.py ../client/hyperset.py
cp hyperset/ttypes.py ../client/
