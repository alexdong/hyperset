#!/usr/bin/env python

import sys
import pprint
from urlparse import urlparse
from thrift.transport import TTransport
from thrift.transport import TSocket
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

import hyperset
from ttypes import *


host = 'localhost'
port = 9091
socket = TSocket.TSocket(host, port)
transport = TTransport.TFramedTransport(socket)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = hyperset.Client(protocol)
transport.open()

client.add("scr:0", [1, 2, 3, 4, 5])
client.add("scr:20", [6, 7, 8])
client.add("scr:30", [9, 10])
client.add("geo:1", [1, 2, 3, 4, 5, 6])
client.add("geo:2", [7, 8, 9, 10])
client.add("date:20100826", [1, 3, 4, 5, 7, 8])
client.add("date:20100827", [1, 4, 6, 7, 9])
client.add("date:20100828", [2, 4, 6, 7, 8, 10])
client.save()

print client.calc("union scr:0 scr:20; union geo:1 geo:2;" + \
        "union date:20100826 date:20100827 date:20100828;" + \
        "intersect $ $ $")

transport.close()
