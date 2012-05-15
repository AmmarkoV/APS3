#!/bin/bash
APS3/src/APSConverter/bin/Debug/APSConverter -e APS3/src/APSConverter/testraw0.ppm APS3/src/APSConverter/testraw0.aps3
APS3/src/APSConverter/bin/Debug/APSConverter -d APS3/src/APSConverter/testraw0.aps3 APS3/src/APSConverter/testraw1.ppm
diff APS3/src/APSConverter/testraw0.ppm APS3/src/APSConverter/testraw1.ppm
exit 0
