#include "YoungEngine.h"


Engine engineRef;

int main() {
    engineRef.Run();
    engineRef.Shutdown();
    return 0;
}