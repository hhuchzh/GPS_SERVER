#!/bin/bash
g++ -o test -I /usr/include/oracle/11.2/client64/ -L /usr/lib/oracle/11.2/client64/lib/ -locci -lsqlplus OCCIConnect.cpp
