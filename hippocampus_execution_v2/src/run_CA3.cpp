// Run CA3 from the project root; see README for the required input files.
// ModelSupport.h retains the original copyright and license notice.
#include "ca3/ModelSupport.h"

int main() {
#include "ca3/LoadConnectivity.h"
#include "ca3/FixedWeights.h"
#include "ca3/SetupNetwork.h"

    watch.lap("runNetwork");

    // Four 10-second runs give 40 seconds of activity.
    // For 1200 seconds (place-field analysis), change 4 to 120 in all three mains.
    // The MEC input recordings must also cover the full simulation duration.
    for (int i = 0; i < 4; ++i) {
        sim.runNetwork(10, 0);
    }

    watch.stop();
    return 0;
}
